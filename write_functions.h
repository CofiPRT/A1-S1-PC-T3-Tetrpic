void write_header(	bmp_fileheader *file_header,	//the two headers
					bmp_infoheader *info_header,
					int rows,
					int columns)
{
	//filling second struct
	info_header->biSize = sizeof(*info_header);	//always 40
	info_header->width = 10 * columns;			//scaled accordingly
	info_header->height = 10 * rows;			//scaled accordingly
	info_header->planes = 1;
	info_header->bitPix = 24;					//3 channels (BGR) * 8 bits
	info_header->biCompression = 0;
	info_header->biSizeImage =	to_four(3 * info_header->width) * //padding
								info_header->height;
	info_header->biXPelsPerMeter = 0;
	info_header->biYPelsPerMeter = 0;
	info_header->biClrUsed = 0;
	info_header->biClrImportant = 0;
	
	//filling first struct
	file_header->fileMarker1 = 'B';
	file_header->fileMarker2 = 'M';
	file_header->imageDataOffset = 	sizeof(*file_header) + 	//always 14
									sizeof(*info_header); 	//always 40
	file_header->bfSize = 	file_header->imageDataOffset + 	//always 54
							info_header->biSizeImage;
	file_header->unused1 = 0;
	file_header->unused2 = 0;
}

void write_to_file(FILE *out_file, char square, int blank_color)
{
	/*'blank_color' will decide if an empty
	square will be black (0) or white (1)*/
	
	//find the square's color
	color_struct color = find_color(square, blank_color);

	int i; //do it 10 times (to scale it)
	for (i = 0; i < 10; i++)
	{
		fwrite(&color, sizeof(color), 1, out_file);
	}
}

void write_padding(FILE *out_file, int columns)
{
	columns *= 30; //match the width
	for (; columns % 4; columns++)
	{
		char zero = 0;
		fwrite(&zero, sizeof(char), 1, out_file);
	}
}

void write_matrix(	FILE *out_file,
					char **matrix,
					int rows,
					int columns,
					int is_map)
{
	int irow, icolumn, i;
	//move through the matrix (according to bitmap format)
	for (irow = rows - 1; irow >= 0; irow--)
	{
		//bottom-up
		for (i = 0; i < 10; i++)
		{
			//to scale accordingly, pass through each line 10 times
			for (icolumn = 0; icolumn < columns; icolumn++)
			{
				//left ro right
				if (irow < 4)
				{
					write_to_file(out_file, matrix[irow][icolumn], 1);
				}
				else
				{
					write_to_file(out_file, matrix[irow][icolumn], !is_map);
				}
			}
			write_padding(out_file, columns);
		}
	}
}

