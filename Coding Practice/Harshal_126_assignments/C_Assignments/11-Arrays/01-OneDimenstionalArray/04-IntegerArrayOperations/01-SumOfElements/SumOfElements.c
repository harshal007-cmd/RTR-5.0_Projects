#include<stdio.h>

#define NUM_ELE 5

int main()
{
	int Array[NUM_ELE];
	int i, num, sum = 0;

	printf("\n\nEnter integer element for Array : \n\n");
	for (i = 0; i< NUM_ELE; ++i)
	{
		scanf("%d", &num);
		Array[i] = num;
	}
	for (i = 0; i < NUM_ELE;++i)
	{
		sum = sum + Array[i];
	}
	printf("\n\nSum of all elements of Array = %d\n\n", sum);
	return 0;
}
