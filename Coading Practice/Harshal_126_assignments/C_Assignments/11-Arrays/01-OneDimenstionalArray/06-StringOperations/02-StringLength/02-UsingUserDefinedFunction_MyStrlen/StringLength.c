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
	len = MyStrlen(cArray);
	printf("Length of String is = %d Char's !!\n\n", len);
	return 0;
}

int MyStrlen(char str[])
{
	int j;
	int str_len = 0;

	for (j = 0;j < MAX_STRING_LEN;++j)
	{
		if (str[j] == '\0')
			break;
		else
			str_len++;
	}
	return str_len;
}


