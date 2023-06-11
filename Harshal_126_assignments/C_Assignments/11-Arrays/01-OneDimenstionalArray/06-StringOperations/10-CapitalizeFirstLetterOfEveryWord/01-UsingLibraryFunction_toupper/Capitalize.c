#include<stdio.h>
#include<ctype.h>
#define MAX_STRING_LEN 512

int main()
{
	int MyStrlen(char[]);

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
			cArrayCapitalizeFirstLetter[i] = toupper(cArray[i]);
		else if (cArray[i] == ' ')
		{
			cArrayCapitalizeFirstLetter[j] = cArray[i];
			cArrayCapitalizeFirstLetter[j + 1] = toupper(cArray[i + 1]);
			j++;
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
