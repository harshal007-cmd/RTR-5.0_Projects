#include<stdio.h>
#define MAX_STRING_LEN 512

int main()
{
	int MyStrlen(char[]);
	void MyStrcpy(char[], char[]);
	char cArrayOriginal[MAX_STRING_LEN],cArrayVowelsReplaced[MAX_STRING_LEN];
	int strlen, i;
	
	//Input
	printf("\n\nEnter A string : \n");
	gets_s(cArrayOriginal, MAX_STRING_LEN);

	//output
	MyStrcpy(cArrayVowelsReplaced, cArrayOriginal);
	strlen = MyStrlen(cArrayVowelsReplaced);

	for (i = 0;i < strlen;++i)
	{
		switch (cArrayVowelsReplaced[i])
		{
		case 'A':
		case 'a':
		case 'E':
		case 'e':
		case 'I':
		case 'i':
		case 'O':
		case 'o':
		case 'U':
		case 'u':
			cArrayVowelsReplaced[i] = '*';
		default:
			break;
		}
	}
	//Str output
	printf("\n\nString entered : \n\n");
	printf("%s\n", cArrayOriginal);

	printf("\n\nString with Vowels replaced : \n\n");
	printf("%s\n", cArrayVowelsReplaced);


	return 0;
}

void MyStrcpy(char str_copy[], char str_origial[])
{
	int MyStrlen(char[]);
	int str_len = 0;
	int j;

	str_len = MyStrlen(str_origial);
	for (j = 0;j < str_len;++j)
		str_copy[j] = str_origial[j];

	str_copy[j] = '\0';

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








