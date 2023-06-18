#include<stdio.h>

int main(int argc, char* argv[], char* envp[])
{

	int MyAddition(int, int);
	int a, b, result;
	
	printf("\n\n");
	printf("Enter Interger value A : ");
	scanf("%d", &a);

	printf("\n\n");
	printf("Enter Interger value B : ");
	scanf("%d", &b);

	result = MyAddition(a, b);
	printf("Sum of %d and %d = %d\n", a, b, result);

	return 0;
}

int MyAddition(int a , int b)
{
	int sum;
	sum = a + b;
	return sum;
}
