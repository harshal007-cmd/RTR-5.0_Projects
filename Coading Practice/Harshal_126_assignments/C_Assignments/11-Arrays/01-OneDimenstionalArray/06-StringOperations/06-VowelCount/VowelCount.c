#include<stdio.h>
#define MAX_STRING_LEN 512

int main()
{
	int MyStrlen(char[]);

	char cArray[MAX_STRING_LEN];
	int strlen;
	int i, countA = 0, countE = 0, countI = 0, countO = 0, countU = 0;

	//Input
	printf("\n\nEnter A string : \n");
	gets_s(cArray, MAX_STRING_LEN);

	//output
	printf("\n\nString entered :\n");
	printf("%s\n", cArray);

	strlen = MyStrlen(cArray);
	for (i = 0;i < strlen;++i)
	{
		switch (cArray[i])
		{
		case 'A':
		case 'a':
			countA++;
			break;
		case 'E':
		case 'e':
			countE++;
			break;
		case 'I':
		case 'i':
			countI++;
			break;
		case 'O':
		case 'o':
			countO++;
			break;
		case 'U':
		case 'u':
			countU++;
			break;

		default:
			break;
		}
	}
	printf("\n\nIn string entered by you, the Vowels and Number of their occurences are : \n\n");
	printf("A has Occured = %d times !!!\n\n", countA);
	printf("E has Occured = %d times !!!\n\n", countE);
	printf("I has Occured = %d times !!!\n\n", countI);
	printf("O has Occured = %d times !!!\n\n", countO);
	printf("U has Occured = %d times !!!\n\n", countU);

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








