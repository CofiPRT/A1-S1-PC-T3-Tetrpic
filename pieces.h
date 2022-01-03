void piece_O(char **piece, int *rows, int *columns)
{
	(*rows) = 2;
	(*columns) = 2;
	piece[0][0] = 'O';
	piece[0][1] = 'O';
	piece[1][0] = 'O';
	piece[1][1] = 'O';
}

void piece_I(char **piece, int *rows, int *columns)
{
	(*rows) = 4;
	(*columns) = 1;
	piece[0][0] = 'I';
	piece[1][0] = 'I';
	piece[2][0] = 'I';
	piece[3][0] = 'I';
}

void piece_S(char **piece, int *rows, int *columns)
{
	(*rows) = 2;
	(*columns) = 3;
	piece[0][0] = '.';
	piece[0][1] = 'S';
	piece[0][2] = 'S';
	piece[1][0] = 'S';
	piece[1][1] = 'S';
	piece[1][2] = '.';
}

void piece_Z(char **piece, int *rows, int *columns)
{
	(*rows) = 2;
	(*columns) = 3;
	piece[0][0] = 'Z';
	piece[0][1] = 'Z';
	piece[0][2] = '.';
	piece[1][0] = '.';
	piece[1][1] = 'Z';
	piece[1][2] = 'Z';
}

void piece_L(char **piece, int *rows, int *columns)
{
	(*rows) = 3;
	(*columns) = 2;
	piece[0][0] = 'L';
	piece[0][1] = '.';
	piece[1][0] = 'L';
	piece[1][1] = '.';
	piece[2][0] = 'L';
	piece[2][1] = 'L';
}

void piece_J(char **piece, int *rows, int *columns)
{
	(*rows) = 3;
	(*columns) = 2;
	piece[0][0] = '.';
	piece[0][1] = 'J';
	piece[1][0] = '.';
	piece[1][1] = 'J';
	piece[2][0] = 'J';
	piece[2][1] = 'J';
}

void piece_T(char **piece, int *rows, int *columns)
{
	(*rows) = 2;
	(*columns) = 3;
	piece[0][0] = 'T';
	piece[0][1] = 'T';
	piece[0][2] = 'T';
	piece[1][0] = '.';
	piece[1][1] = 'T';
	piece[1][2] = '.';
}

color_struct find_color(char square, int blank_color)
{
	color_struct colors;
	switch (square)
	{
		case 'O':
		{
			colors.blue = 0;
			colors.green = 255;
			colors.red = 255;
			break;
		}
		case 'I':
		{
			colors.blue = 255;
			colors.green = 0;
			colors.red = 0;
			break;
		}
		case 'S':
		{
			colors.blue = 0;
			colors.green = 0;
			colors.red = 255;
			break;
		}
		case 'Z':
		{
			colors.blue = 0;
			colors.green = 255;
			colors.red = 0;
			break;
		}
		case 'L':
		{
			colors.blue = 0;
			colors.green = 140;
			colors.red = 255;
			break;
		}
		case 'J':
		{
			colors.blue = 255;
			colors.green = 0;
			colors.red = 255;
			break;
		}
		case 'T':
		{
			colors.blue = 255;
			colors.green = 0;
			colors.red = 130;
			break;
		}
		case '.':
		{
			if (blank_color == 1)
			{
				//white
				colors.blue = 255;
				colors.green = 255;
				colors.red =255;
				break;
			}

			colors.blue = 0;
			colors.green = 0;
			colors.red = 0;
			break;
		}
	}

	return colors;
}