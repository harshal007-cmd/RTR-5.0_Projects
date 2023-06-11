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
	int i = 0;
	//code

	printf("\n\nIn_line Initialization and Piece-meal display of elemetns of array iArray[] : \n\n");


	int_size = sizeof(int);
	iArray_size = sizeof(iArray);
	iArray_num_elements = iArray_size / int_size;

	for (i = 0;i < iArray_num_elements;++i)
	{
		printf("iArray[%d] (Element %d) = %d\n", i, (i + 1), iArray[i]);
	}
	printf("Size of Data type 'int'             = %d bytes\n", int_size);
	printf("Number of elements in iArray        = %d Elements\n", iArray_num_elements);
	printf("Size of Array iArray  (%d Elements * %d bytes) = %d Bytes\n\n", iArray_num_elements, int_size, iArray_size);

	
	//fArray

	printf("\n\nIn_line Initialization and Piece-meal display of elemetns of array fArray[] : \n\n");

	float_size = sizeof(float);
	fArray_size = sizeof(fArray);
	fArray_num_elements = fArray_size / float_size;
	for (i = 0;i < fArray_num_elements;++i)
	{
		printf("fArray[%d] (Element %d) = %f\n", i, (i + 1), fArray[i]);
	}


	printf("Size of Data type 'float'             = %d bytes\n", float_size);
	printf("Number of elements in fArray          = %d Elements\n", fArray_num_elements);
	printf("Size of Array fArray  (%d Elements * %d bytes) = %d Bytes\n\n", fArray_num_elements, float_size, fArray_size);

	//cArray

	printf("\n\nIn_line Initialization and Piece-meal display of elemetns of array cArray[] : \n\n");

	char_size = sizeof(char);
	cArray_size = sizeof(cArray);
	cArray_num_elements = cArray_size / char_size;
	for (i = 0;i < cArray_num_elements;++i)
	{
		printf("cArray[%d] (Element %d) = %d\n", i, (i + 1), cArray[i]);
	}


	printf("Size of Data type 'char'              = %d bytes\n", char_size);
	printf("Number of elements in cArray          = %d Elements\n", cArray_num_elements);
	printf("Size of Array cArray  (%d Elements * %d bytes) = %d Bytes\n\n", cArray_num_elements, char_size, cArray_size);

	return 0;
}
