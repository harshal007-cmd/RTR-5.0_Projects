#include<stdio.h>

void PrintBinaryFormOfNumber(unsigned int);

int main()
{
	

	unsigned int hvs_a;
	unsigned int hvs_b;
	unsigned int h_result;


	printf("\n\n");
	printf("Enter 1st integer: ");
	scanf("%u", &hvs_a);

	printf("\n\n");
	printf("Enter 2nd integer: ");
	scanf("%u", &hvs_b);

	printf("\n\n");
	h_result = hvs_a ^ hvs_b;

	printf("Bitwise XOR-ing of hvs_a = %d (Decimal) and hvs_b= %d (Decimal) gives result = %d (Decimal).\n\n", hvs_a, hvs_b, h_result);

	PrintBinaryFormOfNumber(hvs_a);
	PrintBinaryFormOfNumber(hvs_b);
	PrintBinaryFormOfNumber(h_result);
	
	return 0;
}

void PrintBinaryFormOfNumber(unsigned int decimal_no)
{
	unsigned int quotient, reminder, num, binray_array[8];
	int i;

	for (i = 0;i < 8;i++)
	{
		binray_array[i] = 0;
		
	}
	printf("Binary form of decimal integer %d is\t=\t", decimal_no);
	num = decimal_no;
	i = 7;
	while (num != 0)
	{
		quotient = num / 2;
		reminder = num % 2;
		binray_array[i] = reminder;
		num = quotient;
		i--;
	}

	for (i = 0;i < 8;i++)
		printf("%u", binray_array[i]);

	printf("\n\n");

}
