#include<stdio.h>

int main(void)
{
	printf("\n\n*************************************\n");
	printf("Hello World: RTR 5.0\n\n");


	int i = 14;
	printf("Inter decimal value of 'i' = %d\n", i);
	printf("Inter Hexadecimal value of 'i' (in lowercase) = %x\n", i);
	printf("Inter Hexadecimal value of 'i' (in Uppercase) = %X\n\n", i);

	char c = 'H';
	printf("Charater c = %c\n", c);
	char str[] = "Astromedicom's Real Time Rendaring Batch";
	printf("String str = %s\n\n", str);

	long numL = 1234567L;
	printf("Long interger = %ld\n\n", numL);

	unsigned int b = 8;
	printf("Unsigned Int 'b'= %u\n\n", b);

	float fnum = 3412.231343f;
	printf("Floating point number with just %%f 'fnum'	= %f\n", fnum);
	printf("Floating point number with just %%4.2f 'fnum'	= %4.2f\n", fnum);
	printf("Floating point number with just %%6.5f 'fnum'	= %6.5f\n\n", fnum);


	double d_pi = 3.14159265358979;
	printf("Double precision floating point number withou Exponential = %g\n", d_pi);
	printf("Double precision floating point number withou Exponential (lowecase) = %e\n", d_pi);
	printf("Double precision floating point number withou Exponential (Uppercase) = %E\n", d_pi);
	printf("Double Hexadecimal value of 'd_pi' = %a\n", d_pi);
	printf("Double Hexadecimal value of 'd_pi' = %A\n\n", d_pi);

	printf("\n**************************************\n");
	return 0;
}

