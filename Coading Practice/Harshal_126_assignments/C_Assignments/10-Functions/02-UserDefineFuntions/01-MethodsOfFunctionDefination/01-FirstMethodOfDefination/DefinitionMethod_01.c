#include<stdio.h>

int main(int argc, char* argv[], char* envp[])
{
	void MyAddition(void);
	MyAddition();
	return 0;
}

void MyAddition(void)
{
	int a, b, sum;
	printf("\n\n");
	printf("Enter 1st number A : ");
	scanf("%d", &a);

	printf("Enter 2nd number B : ");
	scanf("%d", &b);

	sum = a + b;
	printf("\n\n");
	printf("Sum of %d And %d = %d\n\n", a, b, sum);

}
