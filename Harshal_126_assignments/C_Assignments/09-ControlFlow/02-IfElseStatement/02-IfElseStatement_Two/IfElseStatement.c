#include<stdio.h>

int main()
{
	int age;

	printf("\n");
	printf("Enter age :");
	scanf("%d", &age);
	if (age>=18)
	{
		printf("In if block...\n\n");
		printf("You are eligible to voting..\n");
	}
	else {
		printf("In else block...\n\n");
		printf("You are not eligible to Voting..\n");
	}
	printf("Bye\n");
	return 0;

}

