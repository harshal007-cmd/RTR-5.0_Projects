#include<stdio.h>
#define MAX_STRING_LEN 512

int main()
{
	char cArray[MAX_STRING_LEN];
	//code
	printf("\n\nEnter A string : \n");
	gets_s(cArray, MAX_STRING_LEN);

	printf("\nString entered by you is : \n");
	printf("%s\n", cArray);
	return 0;
}
