#include<stdio.h>

int main()
{
	void MyAddition(void);
	int MySubtraction(void);
	void MyMultiplication(int, int);
	int MyDivision(int, int);

	int result_sub, a_multiply, b_multiply, a_division, b_division, result_division;

	MyAddition();

	//Subtraction

	result_sub = MySubtraction();
	printf("\n\n");
	printf("Subtraction yield result = %d\n", result_sub);

	//Multiply
	printf("\n\n");
	printf("Enter integer values A for Multiplication : ");
	scanf("%d", &a_multiply);

	printf("\n\n");
	printf("Enter integer values B for Multiplication : ");
	scanf("%d", &b_multiply);

	MyMultiplication(a_multiply, b_multiply);

	//Division
	printf("\n\n");
	printf("Enter integer values A for Division : ");
	scanf("%d", &a_division);

	printf("\n\n");
	printf("Enter integer values B for Division : ");
	scanf("%d", &b_division);

	result_division = MyDivision(a_division, b_division);
	printf("\n\n");
	printf("Division of %d and %d gives = %d (Quotient)\n", a_division, b_division, result_division);

	printf("\n\n");
	return 0;

}

void MyAddition(void)
{
	int a, b, sum;
	printf("\n\n");
	printf("Enter int value A for addition : ");
	scanf("%d", &a);

	printf("\n\n");
	printf("Enter int value B for addition : ");
	scanf("%d", &b);

	sum = a + b;
	printf("\n\nSum of %d and %d = %d\n", a, b, sum);

}

int MySubtraction(void)
{
	int a, b, sub;
	printf("\n\n");
	printf("Enter int value A for Subtraction : ");
	scanf("%d", &a);

	printf("\n\n");
	printf("Enter int value B for Subtraction : ");
	scanf("%d", &b);

	sub = a - b;
	return sub;

}

void MyMultiplication(int a, int b)
{
	int  mul;
	mul = a * b;
	printf("\n\nMultiplication of %d and %d = %d\n", a, b, mul);
}

int MyDivision(int a, int b)
{
	int division_quotient;

	if (a > b)
	{
		division_quotient = a / b;
	}
	else
		division_quotient = b / a;

	return division_quotient;
}
