#include<stdio.h>

int main()
{
	int hvs_a;
	int hvs_b;
	int h_result;

	printf("\n\n");
	printf("Enter 1st number : ");
	scanf("%d", &hvs_a);

	printf("\n\n");
	printf("Enter 2nd number : ");
	scanf("%d", &hvs_b);

	printf("\n\n");

	h_result = hvs_a;
	hvs_a += hvs_b;
	printf("Addition of %d and %d gives = %d\n", h_result, hvs_b, hvs_a);

	h_result = hvs_a;
	hvs_a -= hvs_b;
	printf("Subtraction of %d and %d gives = %d\n", h_result, hvs_b, hvs_a);
	
	h_result = hvs_a;
	hvs_a *= hvs_b;
	printf("Multiplication of %d and %d gives = %d\n", h_result, hvs_b, hvs_a);

	h_result = hvs_a;
	hvs_a /= hvs_b;
	printf("Division of %d and %d gives Quotient = %d\n", h_result, hvs_b, hvs_a);


	h_result = hvs_a;
	hvs_a %= hvs_b;
	printf("Subtraction of %d and %d gives Reminder = %d\n", h_result, hvs_b, hvs_a);

	printf("\n\n");
	return 0;
}
