void fill_piece(char piece_id,			//selects the piece
				char **piece, 			//saves the piece
				int *rows,				//piece's rows (to be decided)
				int *columns)			//piece's columns (to be decided)	
{
	switch (piece_id)
	{
		case 'O':
		{
			piece_O(piece, rows, columns);
			break;
		}
		case 'I':
		{
			piece_I(piece, rows, columns);
			break;
		}
		case 'S':
		{
			piece_S(piece, rows, columns);
			break;
		}
		case 'Z':
		{
			piece_Z(piece, rows, columns);
			break;
		}
		case 'L':
		{
			piece_L(piece, rows, columns);
			break;
		}
		case 'J':
		{
			piece_J(piece, rows, columns);
			break;
		}
		case 'T':
		{
			piece_T(piece, rows, columns);
			break;
		}
	}
}

void game_logic(char **map,				//the map
				piece_attr pieces[],	//the pieces
				int piece_no,			//number of pieces
				int height,				//height of the map
				int width)				//width of the map
{
	int ipiece;
	for (ipiece = 0; ipiece < piece_no; ipiece++)
	{
		pieces[ipiece].matrix = new_matrix(MAXSIZE);
		fill_piece(	pieces[ipiece].symbol,
					pieces[ipiece].matrix,
					&pieces[ipiece].rows,
					&pieces[ipiece].columns);

		for (; pieces[ipiece].rotation; pieces[ipiece].rotation -= 90)
		{
			rotate_matrix(	pieces[ipiece].matrix,
							&pieces[ipiece].rows,
							&pieces[ipiece].columns);
		}

		int level; 	/*	piece height level in [0, height - 4]
						(bottom of the piece) */

		for (level = height - 4; level >= 0; level--)
		{
			if (collision(map, height, pieces[ipiece], level))
			{
				//the piece can't go down any further
				save_piece(map, height, pieces[ipiece], level);

				if (level + pieces[ipiece].rows > height - 4)
				{
					//game-over
					return;
				}
				
				level = 0; //piece's job is done
			}

			erase_lines(map, height, width);
		}
		free_matrix(pieces[ipiece].matrix, MAXSIZE);
	}	
}

void fill_map(FILE *in_file, char **map, signed int *width, signed int *height)
{
	//jump to the bmp's width and height
	fseek(in_file, sizeof(bmp_fileheader) + sizeof(unsigned int), SEEK_SET);

	fread(width, sizeof(signed int), 1, in_file);
	fread(height, sizeof(signed int), 1, in_file);

	//jump to the bmp's bitmap
	fseek(in_file, sizeof(bmp_fileheader) + sizeof(bmp_infoheader), SEEK_SET);

	int irow, icolumn;
	for (irow = (*height) / 10 - 1; irow >= 0; irow--)
	{
		for (icolumn = 0; icolumn < (*width) / 10; icolumn++)
		{
			color_struct colors;
			fread(&colors, sizeof(colors), 1, in_file);

			map[irow][icolumn] = find_symbol(colors);

			//jump to the next pixel 
			fseek(in_file, 27, SEEK_CUR);
		}
		fseek(in_file, to_four(*width) - (*width), SEEK_CUR); //padding

		//jump to the next line in the bitmap
		fseek(in_file, 9 * to_four(3 * (*width)), SEEK_CUR);
	}
}

void find_pieces(FILE *out_file, char **map, int height, int width)
{
	char out_pieces[MAXBONUSPIECES][MAXSIZE];
	int pieces_number = 0; //these 2 are for writing to the file

	char piece_ids[] = PIECES;
	int map_irow, map_icolumn;
	//move through the map
	for (map_irow = 0; map_irow < height; map_irow++)
	{
		for (map_icolumn = 0; map_icolumn < width; map_icolumn++)
		{
			int ipiece;
			for (ipiece = 0; ipiece < 7; ipiece++)
			{
				//prepare the piece
				char **piece = new_matrix(MAXSIZE);
				int rows, columns;

				//create the piece
				fill_piece(piece_ids[ipiece], piece, &rows, &columns);

				int irot = 0; //rotation
				do
				{
					if (map_irow + rows > height ||
						map_icolumn + columns > width)
					{
						//segfault
						rotate_matrix(piece, &rows, &columns);
						irot += 90;
						continue;
					}
					int result = check_piece(map, map_irow, map_icolumn,
											piece, rows, columns);
					if (result)
					{
						sprintf(out_pieces[pieces_number],
								"%c %d %d",
								piece_ids[ipiece], irot, map_icolumn);
						pieces_number++;
						ipiece = 7; //break the 'for'
						break;
					}

					rotate_matrix(piece, &rows, &columns);
					irot += 90;
				} while (irot <= 270);

				free_matrix(piece, MAXSIZE);
			}
		}
	}

	int i; //write to file
	fprintf(out_file, "%d\n", pieces_number);
	for (i = 0; i < pieces_number; i++)
	{
		fprintf(out_file, "%s\n", out_pieces[i]);
	}
}