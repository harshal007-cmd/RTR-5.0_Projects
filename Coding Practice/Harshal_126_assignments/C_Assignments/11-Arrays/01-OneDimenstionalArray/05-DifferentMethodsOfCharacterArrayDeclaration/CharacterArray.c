#include<stdio.h>

int main()
{

	char cArray1[] = { 'A','S','T','R','O','M','E','D','I','C','O','M','P','\0' };
	char cArray2[9] = "WELCOMES";
	char cArray3[] = { 'Y','O','U','\0' };
	char cArray4[] = "To";
	char cArray5[] = "REAL TIME RENDARING BATCH OF 2023-24";


	char cArray_WithoutNullTerminator[] = { 'H','E','L','L','O' };

	//code

	printf("\n\nSize of cArray1 : %zu\n\n", sizeof(cArray1));
	printf("\n\nSize of cArray2 : %zu\n\n", sizeof(cArray2));
	printf("\n\nSize of cArray3 : %zu\n\n", sizeof(cArray3));
	printf("\n\nSize of cArray4 : %zu\n\n", sizeof(cArray4));
	printf("\n\nSize of cArray5 : %zu\n\n", sizeof(cArray5));

	printf("\n\nThe strings Are : \n\n");
	printf("cArray1 : %s\n\n", cArray1);
	printf("cArray2 : %s\n\n", cArray2);
	printf("cArray3 : %s\n\n", cArray3);
	printf("cArray4 : %s\n\n", cArray4);
	printf("cArray5 : %s\n\n", cArray5);

	printf("\n\n");
	printf("Size of cArray_WithoutNullTerminator : %zu\n\n", sizeof(cArray_WithoutNullTerminator));
	printf("cArray_WithoutNullTerminator : %s\n\n", cArray_WithoutNullTerminator);

	return 0;

}

