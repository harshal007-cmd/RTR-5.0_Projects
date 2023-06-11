#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>


int main(int argc, char* argv[], char* envp[])
{
	int i = 0, sum = 0, num;

	if (argc == 1)
	{
		printf("\n\n");
		printf("No number given for addition !! Exiting now..\n");
		printf("Usage : CommandLineArgumentApplication <first Numner> <Second Number>..\n\n");
		exit(0);

	}

	printf("\n\n");

	printf("Sum of All interger Command line argument is : \n\n");
	for (i = 1;i < argc;++i)
	{
		num = atoi(argv[i]);
		sum = sum + num;
	}
	printf("Sum = %d\n\n", sum);
	return 0;
}
