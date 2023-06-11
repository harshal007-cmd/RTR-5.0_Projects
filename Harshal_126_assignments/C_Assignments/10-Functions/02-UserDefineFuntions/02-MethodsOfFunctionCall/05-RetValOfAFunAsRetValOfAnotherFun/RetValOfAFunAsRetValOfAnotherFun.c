#include<stdio.h>

int main()
{
	int addition(int, int);

	int num1=72, num2=54;

	printf("\n\n%d + %d = %d\n", num1, num2, addition(num1, num2));

	return 0;
}

int addition(int a, int b)
{
	int add(int, int);
	return add(a,b);
}

int add(int x, int y)
{
	return x + y;
}