#include<stdio.h>

int main()
{
	int hvs_a;
	int hvs_b;
	int h_result;

	printf("\n\n");

	printf("Enter 1st Integer: ");
	scanf("%d", &hvs_a);
	
	printf("\n");
	
	printf("Enter 2nd Integer: ");
	scanf("%d", &hvs_b);

	printf("\n\n");
	
	printf("IF answer is 0 it is 'False'\n ");
	printf("IF answer is 1 it is 'True'\n ");

	h_result = (hvs_a < hvs_b);
	printf("(hvs_a < hvs_b) hvs_a=%d is less than hvs_b=%d  \t Answer= %d\n", hvs_a, hvs_b, h_result);

	h_result = (hvs_a > hvs_b);
	printf("(hvs_a > hvs_b) hvs_a=%d is greater than hvs_b=%d  \t Answer= %d\n", hvs_a, hvs_b, h_result);

	h_result = (hvs_a <= hvs_b);
	printf("(hvs_a <= hvs_b) hvs_a=%d is less than OR equal to hvs_b=%d  \t Answer= %d\n", hvs_a, hvs_b, h_result);

	h_result = (hvs_a >= hvs_b);
	printf("(hvs_a >= hvs_b) hvs_a=%d is greater than OR equal hvs_b=%d  \t Answer= %d\n", hvs_a, hvs_b, h_result);

	h_result = (hvs_a == hvs_b);
	printf("(hvs_a == hvs_b) hvs_a=%d is Equal to hvs_b=%d  \t Answer= %d\n", hvs_a, hvs_b, h_result);

	h_result = (hvs_a != hvs_b);
	printf("(hvs_a != hvs_b) hvs_a=%d is not Equal to hvs_b=%d  \t Answer= %d\n", hvs_a, hvs_b, h_result);


	return 0;

}
