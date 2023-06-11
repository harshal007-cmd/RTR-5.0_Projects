#include<stdio.h>
#include<string.h>

#define MAX_STRING_LEN 512

int main()
{
	void MyStrcat(char[], char[]);

	char cArray1[MAX_STRING_LEN];
	char cArray2[MAX_STRING_LEN];

	//code
	printf("\n\nEnter A string : \n");
	gets_s(cArray1, MAX_STRING_LEN);
	
	printf("\n\nEnter A string : \n");
	gets_s(cArray2, MAX_STRING_LEN);

	//String Concat
	printf("\n\n");
	printf("##### Before CONCATINATION #####");
	printf("\n\n");

	printf("The Original 1st String entered : cArray1[] is :\n\n");
	printf("%s\n", cArray1);

	printf("\n\nThe Original 2nd String entered : cArray1[] is :\n\n");
	printf("%s\n", cArray2);

	MyStrcat(cArray1, cArray2);

	printf("\n\n");
	printf("#### After CONCATINATION ####\n\n");
	printf("cArray1[] is : \n\n");
	printf("%s\n", cArray1);

	printf("\n\ncArray2[] is : \n\n");
	printf("%s\n", cArray2);

	return 0;
}

void MyStrcat(char str_dest[], char str_source[])
{
	int MyStrlen(char[]);

	int strlen_source = 0, strlen_dest = 0;
	int i, j;

	strlen_source = MyStrlen(str_source);
	strlen_dest = MyStrlen(str_dest);

	for (i = strlen_dest, j = 0;j < strlen_source;++i, ++j)
	{
		str_dest[i] = str_source[j];
	}
	str_dest[i] = '\0';

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








