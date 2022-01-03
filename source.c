#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PIECES "OISZLJT" //a string containing all the pieces
#define MAXSIZE 34 //maximum size of a matrix (MAXHEIGHT + 4)
#define MAXFILENAME 15 //max chars for a file name
#define MAXPIECES 50
#define MAXBONUSPIECES 5000

#include "accessories.h"
#include "pieces.h"
#include "write_functions.h"
#include "support_functions.h"
#include "primary_functions.h"

void task1()
{
	char piece_ids[] = PIECES, //pass through all the pieces
		file_name[MAXFILENAME]; //to open all the files
	
	FILE *out_file;

	bmp_fileheader file_header;
	bmp_infoheader info_header;

	int ipiece;
	for(ipiece = 0; ipiece < 7; ipiece++)
	{
		//prepare the piece
		char **piece = new_matrix(MAXSIZE);
		int rows, columns;

		//create the piece (while passing its attributes)
		fill_piece(piece_ids[ipiece], piece, &rows, &columns);

		add_border(piece, &rows, &columns);

		write_header(&file_header, &info_header, rows, columns);

		//creating the filename then opening it
		sprintf(file_name, "piesa_%c.bmp", piece_ids[ipiece]);
		out_file = fopen(file_name, "wb");

		//writing the header
		fwrite(&file_header, sizeof(file_header), 1, out_file);
		fwrite(&info_header, sizeof(info_header), 1, out_file);

		write_matrix(out_file, piece, rows, columns, 0);
		
		fclose(out_file);
		free_matrix(piece, MAXSIZE);
	}

}

void task2()
{
	char piece_ids[] = PIECES, //pass through all the pieces
		file_name[MAXFILENAME]; //to open all the files

	FILE *out_file;

	bmp_fileheader file_header;
	bmp_infoheader info_header;

	int ipiece, irot;
	for (ipiece = 0; ipiece < 7; ipiece++)
	{
		//prepare the piece
		char **piece = new_matrix(MAXSIZE);
		int rows, columns;

		//create the piece (while passing its attributes)
		fill_piece(piece_ids[ipiece], piece, &rows, &columns);

		add_border(piece, &rows, &columns);

		for (irot = 90; irot <= 270; irot += 90)
		{
			rotate_matrix(piece, &rows, &columns);

			write_header(&file_header, &info_header, rows, columns);

			//creating the filename then opening it
			sprintf(file_name,
					"piesa_%c_%d.bmp",
					piece_ids[ipiece], irot);
			out_file = fopen(file_name, "wb");

			//writing the header
			fwrite(&file_header, sizeof(file_header), 1, out_file);
			fwrite(&info_header, sizeof(info_header), 1, out_file);

			write_matrix(out_file, piece, rows, columns, 0);

			fclose(out_file);
		}

		free_matrix(piece, MAXSIZE);
	}

}

void task3()
{
	FILE *in_file;

	int piece_no, height, width;
	piece_attr pieces[MAXPIECES];

	in_file = fopen("cerinta3.in", "r");

	fscanf(in_file, "%d %d %d\n", &piece_no, &height, &width);
	height += 4; //the 4 white lines

	//read all the moves
	int i, j;
	for (i = 0; i < piece_no; i++)
	{
		fscanf(in_file, "%c %d %d\n", &pieces[i].symbol, 
									&pieces[i].rotation,
									&pieces[i].map_column);
	}

	fclose(in_file);
	//fill an empty map
	char **map = new_matrix(MAXSIZE);

	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			map[i][j] = '.';
		}
	}

	game_logic(map, pieces, piece_no, height, width);

	FILE *out_file;
	out_file = fopen("task3.bmp", "wb");

	bmp_fileheader file_header;
	bmp_infoheader info_header;

	write_header(&file_header, &info_header, height, width);

	//writing the header to the file
	fwrite(&file_header, sizeof(file_header), 1, out_file);
	fwrite(&info_header, sizeof(info_header), 1, out_file);

	write_matrix(out_file, map, height, width, 1);

	fclose(out_file);
	free_matrix(map, MAXSIZE);
}

void task4()
{
	//initially empty map
	char **map = new_matrix(MAXSIZE);

	FILE *in_file;
	in_file = fopen("cerinta4.bmp", "rb");

	signed int width, height;
	fill_map(in_file, map, &width, &height);

	fclose(in_file);

	//scale down
	width /= 10;
	height /= 10;

	int piece_no;
	piece_attr pieces[MAXPIECES];

	in_file = fopen("cerinta4.in", "r");

	fscanf(in_file, "%d\n", &piece_no);

	//read all the moves
	int i;
	for (i = 0; i < piece_no; i++)
	{
		fscanf(in_file, "%c %d %d\n", 	&pieces[i].symbol, 
										&pieces[i].rotation,
										&pieces[i].map_column);
	}

	fclose(in_file);

	game_logic(map, pieces, piece_no, height, width);

	FILE *out_file;
	out_file = fopen("task4.bmp", "wb");

	bmp_fileheader file_header;
	bmp_infoheader info_header;

	write_header(&file_header, &info_header, height, width);

	//writing the header to the file
	fwrite(&file_header, sizeof(file_header), 1, out_file);
	fwrite(&info_header, sizeof(info_header), 1, out_file);

	write_matrix(out_file, map, height, width, 1);

	fclose(out_file);
	free_matrix(map, MAXSIZE);
}

void bonus()
{
	//initially empty map
	char **map = new_matrix(MAXSIZE);

	FILE *in_file;
	in_file = fopen("bonus.bmp", "rb");

	signed int width, height;
	fill_map(in_file, map, &width, &height);

	fclose(in_file);

	//scale down
	width /= 10;
	height /= 10;

	FILE *out_file;
	out_file = fopen("bonus.out", "w");

	find_pieces(out_file, map, height, width);

	fclose (out_file);
	free_matrix(map, MAXSIZE);
}

int main(int argc, char **argv)
{
	(void)argc; //suppress the warning...
	
	switch(atoi(argv[1]))
	{
		case 1:
		{
			task1();
			break;
		}
		case 2:
		{
			task2();
			break;
		}
		case 3:
		{
			task3();
			break;
		}
		case 4:
		{
			task4();
			break;
		}
		case 5:
		{
			bonus();
			break;
		}
	}

	return 0;
}