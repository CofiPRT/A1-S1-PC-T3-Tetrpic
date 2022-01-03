#pragma pack(1)

struct bmp_fileheader
{
    unsigned char  fileMarker1; /* 'B' */
    unsigned char  fileMarker2; /* 'M' */
    unsigned int   bfSize; /* File's size */
    unsigned short unused1;
    unsigned short unused2;
    unsigned int   imageDataOffset; /* Offset to the start of image data */
};

struct bmp_infoheader
{
    unsigned int   biSize; /* Size of the info header - 40 bytes */
    signed int     width; /* Width of the image */
    signed int     height; /* Height of the image */
    unsigned short planes;
    unsigned short bitPix;
    unsigned int   biCompression;
    unsigned int   biSizeImage; /* Size of the image data */
    int            biXPelsPerMeter;
    int            biYPelsPerMeter;
    unsigned int   biClrUsed;
    unsigned int   biClrImportant;
};

struct color_struct
{
    unsigned char blue;
    unsigned char green;
    unsigned char red;
};

struct piece_attr
{
	char symbol;							//defines the piece
	int rotation;							//multiple of 90
	int map_column;							//column alignment in the map
	char **matrix;							//its representation
	int rows;								//rows of the piece
	int columns;							//columns of the pice
};

#pragma pack()

typedef struct bmp_fileheader bmp_fileheader;
typedef struct bmp_infoheader bmp_infoheader;

typedef struct color_struct color_struct;

typedef struct piece_attr piece_attr;

char *new_array(int elem_num)
{
	//allocate an array of 'elem_num' length
	char *point = malloc(elem_num * sizeof(char));

	if (point == NULL)
	{
		//check if allocated
		printf("Allocation error!\n");
		exit(-1);
	}

	return point;
}

char **new_matrix(int length)
{
	char **point = malloc(length * sizeof(char *));
	int i;
	for (i = 0; i < length; i++)
	{
		point[i] = new_array(length);
	}

	return point;
}

void free_matrix(char **matrix, int size)
{
	int i;
	for (i = 0; i < size; i++)
	{
		free(matrix[i]);
	}
	free(matrix);
}

void rotate_matrix(char **matrix, int *rows, int *columns)
{
	int i, j;

	char **rotated = new_matrix(MAXSIZE);
	//rotating
	for (i = 0; i < *columns; i++)
	{
		for (j = 0; j < *rows; j++)
		{
			rotated[i][j] = matrix[(*rows) - 1 - j][i];
		}
	}

	//saving new matrix
	for (i = 0; i < *columns; i++)
	{
		for (j = 0; j < *rows; j++)
		{
			matrix[i][j] = rotated[i][j];
		}
	}

	//swapping rows and columns
	(*rows) += (*columns);
	(*columns) = (*rows) - (*columns);
	(*rows) -= (*columns);

	free_matrix(rotated, MAXSIZE);
}

int to_four(int number)
{
	//increments 'number' until it becomes a multiple of 4
	while (number % 4)
	{
		number++;
	}
	return number;
}