#include<stdio.h>

int main()
{
	int iArray[] = { 2,23,45,66,7,5,8 };
	int int_size;
	int iArray_size;
	int iArray_num_elements;


	float fArray[] = { 1.2f,3.3f,5.4f,6.5f };
	int float_size;
	int fArray_size;
	int fArray_num_elements;

	char cArray[] = { 'H','A','R','S','H','A','L' };
	int char_size;
	int cArray_num_elements;
	int cArray_size;

	//code

	printf("\n\nIn_line Initialization and Piece-meal display of elemetns of array iArray[] : \n\n");

	printf("iArray[0] (1st Element) = %d\n", iArray[0]);
	printf("iArray[1] (2nd Element) = %d\n", iArray[1]);
	printf("iArray[2] (3rd Element) = %d\n", iArray[2]);
	printf("iArray[3] (4th Element) = %d\n", iArray[3]);
	printf("iArray[4] (5th Element) = %d\n", iArray[4]);
	printf("iArray[5] (6th Element) = %d\n", iArray[5]);
	printf("iArray[6] (7th Element) = %d\n", iArray[6]);
	printf("iArray[7] (8th Element) = %d\n", iArray[7]);

	int_size = sizeof(int);
	iArray_size = sizeof(iArray);
	iArray_num_elements = iArray_size / int_size;

	printf("Size of Data type 'int'             = %d bytes\n", int_size);
	printf("Number of elements in iArray        = %d Elements\n", iArray_num_elements);
	printf("Size of Array iArray  (%d Elements * %d bytes) = %d Bytes\n\n", iArray_num_elements, int_size, iArray_size);

	
	//fArray

	printf("\n\nIn_line Initialization and Piece-meal display of elemetns of array fArray[] : \n\n");
	printf("fArray[0] (1st Element) = %f\n", fArray[0]);
	printf("fArray[1] (2nd Element) = %f\n", fArray[1]);
	printf("fArray[2] (3rd Element) = %f\n", fArray[2]);
	printf("fArray[3] (4th Element) = %f\n", fArray[3]);
	printf("fArray[4] (5th Element) = %f\n", fArray[4]);

	float_size = sizeof(float);
	fArray_size = sizeof(fArray);
	fArray_num_elements = fArray_size / float_size;

	printf("Size of Data type 'float'             = %d bytes\n", float_size);
	printf("Number of elements in fArray          = %d Elements\n", fArray_num_elements);
	printf("Size of Array fArray  (%d Elements * %d bytes) = %d Bytes\n\n", fArray_num_elements, float_size, fArray_size);

	//cArray

	printf("\n\nIn_line Initialization and Piece-meal display of elemetns of array cArray[] : \n\n");
	printf("cArray[0] (1st Element) = %c\n", cArray[0]);
	printf("cArray[1] (2nd Element) = %c\n", cArray[1]);
	printf("cArray[2] (3rd Element) = %c\n", cArray[2]);
	printf("cArray[3] (4th Element) = %c\n", cArray[3]);
	printf("cArray[4] (5th Element) = %c\n", cArray[4]);
	printf("cArray[5] (6th Element) = %c\n", cArray[5]);
	printf("cArray[6] (7th Element) = %c\n", cArray[6]);

	char_size = sizeof(char);
	cArray_size = sizeof(cArray);
	cArray_num_elements = cArray_size / char_size;

	printf("Size of Data type 'char'              = %d bytes\n", char_size);
	printf("Number of elements in cArray          = %d Elements\n", cArray_num_elements);
	printf("Size of Array cArray  (%d Elements * %d bytes) = %d Bytes\n\n", cArray_num_elements, char_size, cArray_size);

	return 0;
}
