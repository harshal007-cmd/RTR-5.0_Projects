#include<stdio.h>
#include<string.h>
#define MAX_STRING_LEN 512

int main()
{
	char cArrayOriginal[MAX_STRING_LEN];
	char cArrayCopy[MAX_STRING_LEN];
	
	//code
	printf("\n\nEnter A string : \n");
	gets_s(cArrayOriginal, MAX_STRING_LEN);
	
	//copy
	strcpy(cArrayCopy, cArrayOriginal);
	//output
	printf("\nString entered by you is : \n");
	printf("%s\n", cArrayOriginal);
	printf("\nCopied String is : \n");
	printf("%s\n", cArrayCopy);

	return 0;
}
