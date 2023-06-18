#include<stdio.h>
#include<string.h>

#define MAX_STRING_LEN 512

int main()
{
	char cArray1[MAX_STRING_LEN];
	char cArray2[MAX_STRING_LEN];

	//code
	printf("\n\nEnter A string : \n");
	gets_s(cArray1, MAX_STRING_LEN);
	
	printf("\n\nEnter A string : \n");
	gets_s(cArray2, MAX_STRING_LEN);

	//String Concat
	printf("\n\n");
	printf("##### Before CONCATINATION #####");
	printf("\n\n");

	printf("The Original 1st String entered : cArray1[] is :\n\n");
	printf("%s\n", cArray1);

	printf("\n\nThe Original 2nd String entered : cArray1[] is :\n\n");
	printf("%s\n", cArray2);

	strcat(cArray1, cArray2);

	printf("\n\n");
	printf("#### After CONCATINATION ####\n\n");
	printf("cArray1[] is : \n\n");
	printf("%s\n", cArray1);

	printf("\n\ncArray2[] is : \n\n");
	printf("%s\n", cArray2);

	return 0;
}
