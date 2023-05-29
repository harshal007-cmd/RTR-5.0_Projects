#include<stdio.h>

int main()
{
	int num;

	printf("\n");
	printf("Enter num :");
	scanf("%d", &num);
	
	if (num < 0)
	{
		printf("Num = %d Is less than 0 (NEGATIVE) !!\n", num);
	}
	else
	{
		if ((num > 0) && (num <= 100))
		{
			printf("Num = %d Is between 0 and 100 !!\n", num);
		}
		else
		{
			if ((num > 100) && (num <= 200))
			{
				printf("Num = %d Is between 100 and 200 !!\n", num);

			}
			else
			{
				if ((num > 200) && (num <= 300))
				{
					printf("Num = %d Is between 200 and 300 !!\n", num);

				}
				else
				{
					if ((num > 300) && (num <= 400))
					{
						printf("Num = %d Is between 300 and 400 !!\n", num);

					}
					else
					{
						if ((num > 400) && (num <= 500))
						{
							printf("Num = %d Is between 400 and 500 !!\n", num);

						}
						else
						{
							printf("Num = %d Is greater than 500 !! \n\n", num);
						}

					}
				}
			}
		}
	}

	return 0;

}

