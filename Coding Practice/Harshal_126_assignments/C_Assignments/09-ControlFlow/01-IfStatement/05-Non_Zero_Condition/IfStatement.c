#include<stdio.h>

int main()
{
	int a;

	printf("\n");

	a = 5;
	if (a)
	{
		printf("if block 1 : A exists and has value = %d !!\n", a);
	}

	a = -5;
	if (a)
	{
		printf("if block 2 : A exists and has value = %d !!\n", a);
	}
	a = 0;
	if (a)
	{
		printf("if block 3 : A exists and has value = %d !!\n", a);
	}
	printf("All three if statements are done\n");
	return 0;

}
