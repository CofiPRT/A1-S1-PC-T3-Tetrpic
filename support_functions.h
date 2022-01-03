void add_border(char **piece, int *rows, int *columns)
{
	int i, j;
	char **matrix = new_matrix(MAXSIZE); //new matrix to work with

	//copying the piece
	for (i = 0; i < *rows; i++)
	{
		matrix[i + 1][0] = '.'; //left border
		for (j = 0; j < *columns; j++)
		{
			matrix[i + 1][j + 1] = piece[i][j]; /* indented due to top and
												left borders */
		}
		matrix[i + 1][(*columns) + 1] = '.'; //right border
	}

	//incremented due to the addition of borders
	(*rows) += 2;
	(*columns) += 2;

	//adding borders
	for (i = 0; i < *columns; i++)
	{
		matrix[0][i] = '.'; //top border (first row)
		matrix[(*rows) - 1][i] = '.'; //bottom border (last row)
	}

	//saving the new matrix
	for (i = 0; i < *rows; i++)
	{
		for (j = 0; j < *columns; j++)
		{
			piece[i][j] = matrix[i][j];
		}
	}

	free_matrix(matrix, MAXSIZE);
}

char find_symbol(color_struct colors)
{
	if (colors.blue == 0 && colors.green == 255 && colors.red == 255)
	{
		return 'O';
	}
	if (colors.blue == 255 && colors.green == 0 && colors.red == 0)
	{
		return 'I';
	}
	if (colors.blue == 0 && colors.green == 0 && colors.red == 255)
	{
		return 'S';
	}
	if (colors.blue == 0 && colors.green == 255 && colors.red == 0)
	{
		return 'Z';
	}
	if (colors.blue == 0 && colors.green == 140 && colors.red == 255)
	{
		return 'L';
	}
	if (colors.blue == 255 && colors.green == 0 && colors.red == 255)
	{
		return 'J';
	}
	if (colors.blue == 255 && colors.green == 0 && colors.red == 130)
	{
		return 'T';
	}
	
	return '.';
}

int collision(char **map, int height, piece_attr piece, int level)
{
	//returns 1 if it will be a collision, and 0 otherwise

	if (level == 0)
	{
		return 1; //bottom of the map
	}

	level--; //suppose the piece can go down further

	int irow, icolumn;
	for (irow = 0; irow < piece.rows; irow++)
	{
		for (icolumn = 0; icolumn < piece.columns; icolumn++)
		{
			//coordinates of the square of the piece RELATIVE to the map
			int map_irow = height - level - piece.rows + irow;
			int map_icolumn = piece.map_column + icolumn;

			if (piece.matrix[irow][icolumn] != '.' &&
				map[map_irow][map_icolumn] != '.')
			{
				//pieces overwrite each other
				return 1;
			}
		}
	}

	return 0;
}

void save_piece(char **map, int height, piece_attr piece, int level)
{
	int irow, icolumn;
	for (irow = 0; irow < piece.rows; irow++)
	{
		for (icolumn = 0; icolumn < piece.columns; icolumn++)
		{
			//coordinates of the square of the piece RELATIVE to the map
			int map_irow = height - level - piece.rows + irow;
			int map_icolumn = piece.map_column + icolumn;

			/*	simulate the bit-wise OR operation
			(period '.' stands for 0
			everything else stands for 1) */	

			if (piece.matrix[irow][icolumn] != '.')
			{
				map[map_irow][map_icolumn] = piece.matrix[irow][icolumn];
			}
		}
	}
}

void erase_lines(char **map, int height, int width)
{
	//if a row is full, erase it and drop everything above it
	int irow, icolumn;
	for (irow = 0; irow < height; irow++)
	{
		int full = 1;
		for (icolumn = 0; icolumn < width; icolumn++)
		{
			if (map[irow][icolumn] == '.')
			{
				full = 0;
				break;
			}
		}
		if (full)
		{
			int row;
			for (row = irow; row > 0; row--)
			{
				strcpy(map[row], map[row - 1]);
			}

			for (icolumn = 0; icolumn < width; icolumn++)
			{
				map[0][icolumn] = '.'; //an empty line
			}
		}
	}
}

int check_piece(char **map,
				int map_irow,
				int map_icolumn,
				char **piece,
				int rows,
				int columns)
{
	int i, j;
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < columns; j++)
		{
			if (piece[i][j] != '.' && //if it's blank, it doesn't matter
				map[map_irow + i][map_icolumn + j] != piece[i][j])
			{
				return 0;
			}
		}
	}
	//delete the piece from the map
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < columns; j++)
		{
			if (piece[i][j] != '.')
			{
				map[map_irow + i][map_icolumn + j] = '.';
			}
		}
	}
	return 1;
}