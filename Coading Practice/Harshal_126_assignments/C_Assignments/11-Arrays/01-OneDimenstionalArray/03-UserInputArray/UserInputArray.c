#include<stdio.h>

#define INT_ARRAY_NUM_ELEMENTS 5
#define FLOAT_ARRAY_NUM_ELEMENTS 3
#define CHAR_ARRAY_NUM_ELEMENTS 15

int main()
{
	int iArray[INT_ARRAY_NUM_ELEMENTS];
	float fArray[FLOAT_ARRAY_NUM_ELEMENTS];
	char cArray[CHAR_ARRAY_NUM_ELEMENTS];
	int i, num;
	//code

	printf("\n\nEnter Elements for Integer arrya : \n");
	for (i = 0;i < INT_ARRAY_NUM_ELEMENTS;++i)
		scanf("%d", &iArray[i]);

	printf("\n\nEnter Elements for Float arrya : \n");
	for (i = 0;i < FLOAT_ARRAY_NUM_ELEMENTS;++i)
		scanf("%f", &fArray[i]);

	printf("\n\nEnter Elements for Char arrya : \n");
	for (i = 0;i < CHAR_ARRAY_NUM_ELEMENTS;++i)
		scanf("%c", &cArray[i]);

	//output

	printf("\n\nInterger array entered by you :\n");
	for (i = 0;i < INT_ARRAY_NUM_ELEMENTS;++i)
		printf("%d\n", iArray[i]);

	printf("\n\nFloat array entered by you :\n");
	for (i = 0;i < FLOAT_ARRAY_NUM_ELEMENTS;++i)
		printf("%f\n", fArray[i]);

	printf("\n\nChar array entered by you :\n");
	for (i = 0;i < CHAR_ARRAY_NUM_ELEMENTS;++i)
		printf("%c\n", cArray[i]);

	printf("\n\n");

	return 0;
}
