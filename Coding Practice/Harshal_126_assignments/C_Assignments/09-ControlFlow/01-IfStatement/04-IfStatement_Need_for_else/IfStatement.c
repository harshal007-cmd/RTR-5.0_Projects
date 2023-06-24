#include<stdio.h>

int main()
{
	int age;

	printf("\n");
	printf("Enter age: ");
	scanf("%d", &age);
	if (age >= 18)
	{
		printf("You are Eligible for Voting !!\n\n");
	}
	printf("You are Not Eligible for Voting !!\n\n");
	return 0;
}
