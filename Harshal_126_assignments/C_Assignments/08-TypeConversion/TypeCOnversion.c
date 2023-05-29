#include<stdio.h>

int main(void)
{
	int i, j, hvs_a, h_result_int, i_explicit;
	char hvs_01, hvs_02;
	float hvs_f, h_result_float, f_explicit;

	printf("\n\n");
	//Interconversion and implecit type casting between char and int types 
	i = 70;
	hvs_01 = i;
	printf("I = %d\n", i);
	printf("Character 1 (after hvs_01 = i) = %c\n\n", hvs_01);

	hvs_02 = 'H';
	j = hvs_02;
	printf("Character 2 = %c\n", hvs_02);
	printf("J (after J = hvs_02) = %d\n\n", j);

	//Implicite conversion of int to float
	hvs_a = 10;
	hvs_f = 10.2f;
	h_result_float = hvs_a + hvs_f;
	printf("Integer hvs_a = %d And Floating point number %f Added gives Floating point result Sum = %f\n\n", hvs_a, hvs_f, h_result_float);
	
	h_result_int = hvs_a + hvs_f;
	printf("Integer hvs_a = %d And Floating point number %f Added gives Interger result Sum = %f\n\n", hvs_a, hvs_f, h_result_float);

	//Ecplicite type casting using casting operator
	f_explicit = 15.4554f;
	i_explicit = (int)f_explicit;
	printf("Floating point number which will be typed cast Explicitly = %f\n", f_explicit);
	printf("Resulatat integer after Explicit type casting of %f = %d\n\n", f_explicit, i_explicit);



	return 0;
}


