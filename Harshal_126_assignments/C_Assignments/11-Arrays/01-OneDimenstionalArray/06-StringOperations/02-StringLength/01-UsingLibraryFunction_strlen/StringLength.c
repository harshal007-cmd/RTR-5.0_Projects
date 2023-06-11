#include<stdio.h>
#define MAX_STRING_LEN 512

int main()
{
	char cArray[MAX_STRING_LEN];
	int len = 0;
	//code
	printf("\n\nEnter A string : \n");
	gets_s(cArray, MAX_STRING_LEN);
	//output
	printf("\nString entered by you is : \n");
	printf("%s\n", cArray);
	
	//length
	len = strlen(cArray);

	printf("Length of String is = %d Char's !!\n\n", len);
	return 0;
}
