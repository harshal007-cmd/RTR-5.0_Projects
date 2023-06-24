#include<stdio.h>

#define MAX_STRING_LEN 512
#define SPACE ' '
#define COMMA ','
#define FULLSTOP '.'
#define EXCLAMATION '!'
#define QUESTION_MARK '?'


int main()
{
	int MyStrlen(char[]);
	char MyToUpper(char);

	char cArray[MAX_STRING_LEN];
	char cArrayCapitalizeFirstLetter[MAX_STRING_LEN];
	int strlen, i, j;

	//Input
	printf("\n\nEnter A string : \n");
	gets_s(cArray, MAX_STRING_LEN);

	//output
	strlen = MyStrlen(cArray);
	j = 0;
	
	for (i = 0;i < strlen;++i)
	{
		if (i == 0)
			cArrayCapitalizeFirstLetter[i] = MyToUpper(cArray[i]);
		else if (cArray[i] == ' ')
		{
			cArrayCapitalizeFirstLetter[j] = cArray[i];
			cArrayCapitalizeFirstLetter[j + 1] = MyToUpper(cArray[i + 1]);
			j++;
			i++;
		}
		else if ((cArray[i] == FULLSTOP || cArray[i] == COMMA || cArray[i] == EXCLAMATION || cArray[i] == QUESTION_MARK) && (cArray[i] != SPACE))
		{
			cArrayCapitalizeFirstLetter[j] = cArray[i];
			cArrayCapitalizeFirstLetter[j + 1] = SPACE;
			cArrayCapitalizeFirstLetter[j + 2] = MyToUpper(cArray[i + 1]);

			j = j + 2;
			i++;
		}
		else
			cArrayCapitalizeFirstLetter[j] = cArray[i];
		j++;
	}
	cArrayCapitalizeFirstLetter[j] = '\0';
	
	//Str output
	printf("\n\nString entered : \n\n");
	printf("%s\n", cArray);

	printf("\n\nString after Capitalize 1st letter : \n\n");
	printf("%s\n", cArrayCapitalizeFirstLetter);

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

char MyToUpper(char ch)
{
	int num, c;
	num = 'a' - 'A';
	if ((int)ch >= 97 && (int)ch <= 122)
	{
		c = (int)ch - num;
		return (char)c;
	}
	else
		return ch;
}
