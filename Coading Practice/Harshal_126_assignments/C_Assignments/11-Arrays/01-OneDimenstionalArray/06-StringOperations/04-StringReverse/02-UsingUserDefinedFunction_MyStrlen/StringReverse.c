#include<stdio.h>
#include<string.h>
#define MAX_STRING_LEN 512

int main()
{
	void MyStringRev(char[], char[]);

	char cArrayOriginal[MAX_STRING_LEN];
	char cArrayReverse[MAX_STRING_LEN];
	
	//Input
	printf("\n\nEnter A string : \n");
	gets_s(cArrayOriginal, MAX_STRING_LEN);
	
	MyStringRev(cArrayReverse, cArrayOriginal);
	//output
	printf("\nString entered by you is : \n");
	printf("%s\n", cArrayOriginal);

	printf("\nReversed String is : \n");
	printf("%s\n", cArrayReverse);

	return 0;
}
void MyStringRev(char str_dest[], char str_original[])
{
	int MyStrlen(char[]);

	int strlen = 0;
	int i, j, len;
	strlen = MyStrlen(str_original);

	len = strlen - 1;
	for (i = 0, j = len; i < strlen, j >= 0; ++i, --j)
	{
		str_dest[i] = str_original[j];
	}
	str_dest[i]='\0';

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

