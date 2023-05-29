#include<stdio.h>

void PrintBinaryFormOfNumber(unsigned int);

int main()
{
	

	unsigned int hvs_a;
	unsigned int h_numBits, h_result;


	printf("\n\n");
	printf("Enter 1st integer: ");
	scanf("%u", &hvs_a);

	printf("\n\n");
	printf("How many bits do you want to shift hvs_a = %d to RIGHT ? ",hvs_a);
	scanf("%u", &h_numBits);

	printf("\n\n");
	h_result = hvs_a << h_numBits;

	printf("Bitwise LEFT-SHIFTING of hvs_a = %d by %d bits gives result = %d (Decimal).\n\n", hvs_a, h_numBits, h_result);

	PrintBinaryFormOfNumber(hvs_a);
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
