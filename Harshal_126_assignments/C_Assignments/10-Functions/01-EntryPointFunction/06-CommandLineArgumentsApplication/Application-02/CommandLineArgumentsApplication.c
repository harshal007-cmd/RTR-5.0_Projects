#include<stdio.h>
#include<stdlib.h>

int main(int argc, char* argv[], char* envp[])
{
	int i = 0;
	if (argc != 4)
	{
		printf("\n\n");
		printf("Invalid Usage !! Exiting now..\n");
		printf("Usage : CommandLineArgumentApplication <first Numner> <Second Number>..\n\n");
		exit(0);

	}
	printf("\n\n");
	printf("Your full Name is : \n\n");
	for (i = 1;i < argc;++i)
	{
		printf("%s ", argv[i]);
	}
	printf("\n\n");
	return 0;
}

