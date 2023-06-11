#include<stdio.h>

int main(int argc, char* argv[], char* envp[])
{

	int MyAddition(void);
	int result;
	result = MyAddition();

	printf("\n\n");
	printf("Sum = %d\n\n", result);
	return 0;
}

int MyAddition(void)
{
	int a, b, sum;
	printf("\n\n");
	printf("Enter 1st number A : ");
	scanf("%d", &a);

	printf("Enter 2nd number B : ");
	scanf("%d", &b);

	sum = a + b;
	return sum;
}
