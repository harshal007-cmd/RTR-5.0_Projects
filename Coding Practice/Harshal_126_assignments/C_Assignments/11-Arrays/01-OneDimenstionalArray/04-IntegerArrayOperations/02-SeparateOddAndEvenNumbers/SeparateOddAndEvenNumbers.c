#include<stdio.h>

#define NUM_ELE 10

int main()
{
	int Array[NUM_ELE];
	int i,num;
	
	//Input
	printf("\n\nEnter integer element for Array : \n\n");
	for (i = 0; i< NUM_ELE; ++i)
	{
		scanf("%d", &num);
		Array[i] = num;
	}

	//Saperating even numbers
	printf("\n\nEven numbers in array are : \n");
	for (i = 0;i < NUM_ELE;++i)
	{
		if ((Array[i] % 2) == 0)
			printf("%d\n", Array[i]);
	}
	//Saperating odd numbers
	printf("\n\nOdd numbers in array are : \n");
	for (i = 0;i < NUM_ELE;++i)
	{
		if ((Array[i] % 2) != 0)
			printf("%d\n", Array[i]);
	}

	return 0;
}

