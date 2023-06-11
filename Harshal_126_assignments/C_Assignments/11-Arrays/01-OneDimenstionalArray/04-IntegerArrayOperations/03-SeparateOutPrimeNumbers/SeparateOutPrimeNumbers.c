#include<stdio.h>

#define NUM_ELE 10

int main()
{
	int Array[NUM_ELE];
	int i, num, j, cnt = 0;
		
	//Input
	printf("\n\nEnter integer element for Array : \n\n");
	for (i = 0; i< NUM_ELE; ++i)
	{
		scanf("%d", &num);
		if (num < 0)
			num = -1 * num;
		Array[i] = num;
	}

	//Print full array
	printf("\n\nElements in array are : \n");
	for (i = 0;i < NUM_ELE;++i)
	{
		printf("%d\n", Array[i]);
	}
	
	//Saperate Prime no.

	printf("\n\nPrime number in Array elemets are : \n");
	for (i = 0;i < NUM_ELE;++i)
	{
		for (j = 1;j <= Array[i];++j)
		{
			if ((Array[i] % j) == 0)
				cnt++;
		}
		if (cnt == 2)
			printf("%d\n", Array[i]);

		cnt = 0;
	}
	return 0;
}

