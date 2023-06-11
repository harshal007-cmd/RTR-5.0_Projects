#include<stdio.h>
#include<string.h>
#define MAX_STRING_LEN 512
int main()
{
	void MyStrcpy(char[], char[]);
	char cArrayOriginal[MAX_STRING_LEN];
	char cArrayCopy[MAX_STRING_LEN];

	//code
	printf("\n\nEnter A string : \n");
	gets_s(cArrayOriginal, MAX_STRING_LEN);

	//copy
	MyStrcpy(cArrayCopy, cArrayOriginal);
	//output
	printf("\nString entered by you is : \n");
	printf("%s\n", cArrayOriginal);
	printf("\nCopied String is : \n");
	printf("%s\n", cArrayCopy);

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
