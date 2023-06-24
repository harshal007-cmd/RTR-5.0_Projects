#include<stdio.h>

int main(void)
{
	int i = 10;
	float f = 10.20f;
	double d = 5.54321;
	char c = 'H';

	//code
	printf("\n");
	printf("i= %d\n",i);
	printf("f= %f\n", f);
	printf("d = % lf\n", d);
	printf("c= %c\n", c);

	printf("\n---------------");

	i = 20;
	f = 20.30;
	d = 7.654321;
	c = 'S';

	printf("\n");
	printf("i= %d\n", i);
	printf("f= %f\n", f);
	printf("d = % lf\n", d);
	printf("c= %c\n", c);

	return 0;
}

