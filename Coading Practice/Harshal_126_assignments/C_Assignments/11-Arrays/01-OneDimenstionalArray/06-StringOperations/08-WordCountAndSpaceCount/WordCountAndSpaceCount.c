#include<stdio.h>
#define MAX_STRING_LEN 512

int main()
{
	int MyStrlen(char[]);
	void MyStrcpy(char[], char[]);
	char cArray[MAX_STRING_LEN];
	int strlen, i, word_count = 0, space_count = 0;
	
	//Input
	printf("\n\nEnter A string : \n");
	gets_s(cArray, MAX_STRING_LEN);

	//output
	strlen = MyStrlen(cArray);

	for (i = 0;i < strlen;++i)
	{
		switch (cArray[i])
		{
		case 32:
			space_count++;
		default:
			break;
		}

	}
	word_count = space_count + 1;
	//Str output
	printf("\n\nString entered : \n\n");
	printf("%s\n", cArray);

	printf("\n\nNumber of Spaces In input string = %d\n", space_count);
	printf("\n\nNumber of Words In input string = %d\n", word_count);
	
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








