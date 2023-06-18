#include<stdio.h>

int main(int argc, char* argv[], char* envp[])
{
	int i = 0;
	printf("\n\n");
	printf("Hello All !!!...(in Library funtion, with return type int)\n");
	printf("Number of Command line Arguments = %d\n", argc);

	printf("Command line arguments passed to this program are : \n\n");
	for (i = 0;i < argc;++i)
	{
		printf("Command line argument number %d = %s\n", (i + 1), argv[i]);
	}
	printf("\n\n");

	printf("First 20 Envionmenatal vaiables passed to this program are : \n\n");
	for (i = 0;i < 20;++i)
	{
		printf("Environmental variable number %d = %s\n", (i + 1), envp[i]);
	}
	printf("\n\n");
	return 0;
}


