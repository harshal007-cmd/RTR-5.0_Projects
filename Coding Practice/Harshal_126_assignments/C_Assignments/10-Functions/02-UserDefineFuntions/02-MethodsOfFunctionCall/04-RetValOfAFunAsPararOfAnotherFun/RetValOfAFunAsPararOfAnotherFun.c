#include<stdio.h>

int main()
{
	int addition(int, int);

	int r, num1=12, num2=23, num3=34, num4=45;

	r = addition(addition(num1, num2), addition(num3, num4));

	printf("\n\n%d + %d + %d + %d = %d\n", num1, num2, num3, num4, r);

	return 0;
}

int addition(int a, int b)
{
	int sum;
	sum = a + b;
	return sum;
}
