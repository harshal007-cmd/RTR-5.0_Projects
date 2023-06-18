#include<stdio.h>

int main(int argc, char* argv[], char* envp[])
{

	void MyAddition(int, int);
	int a, b;
	
	printf("\n\n");
	printf("Enter Interger value A : ");
	scanf("%d", &a);

	printf("\n\n");
	printf("Enter Interger value B : ");
	scanf("%d", &b);

	MyAddition(a, b);
	return 0;
}

void MyAddition(int a , int b)
{
	int sum;
	sum = a + b;

	printf("Sum of %d and %d = %d\n", a, b, sum);
	
}
