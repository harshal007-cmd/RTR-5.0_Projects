#include<stdio.h>

int main()
{
	int a, b, c;

	a = 10;
	b = 15;
	c = 20;

	printf("\n");

	if (a < b)
	{
		printf("In 1st if block...\n\n");
		printf("A is less than B..\n");
	}
	else {
		printf("In 1st else block...\n\n");
		printf("A is not less than B..\n");

	}
	printf("First if else pair is done...\n\n");


	printf("\n");
	if (b != c)
	{
		printf("In 2nd if block...\n\n");
		printf("B is not equal to C..\n");
	}
	else
	{
		printf("In 2nd else block...\n\n");
		printf("B is equal to C..\n");

	}
	printf("2nd if-else pair is done..\n\n");

	return 0;

}
