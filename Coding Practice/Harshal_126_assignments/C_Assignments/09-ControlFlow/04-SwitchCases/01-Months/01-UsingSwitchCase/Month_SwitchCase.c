#include<stdio.h>

int main()
{
	int num_month;

	printf("\n");
	printf("Enter num :");
	scanf("%d", &num_month);
	printf("\n\n");

	switch (num_month)
	{
	case 1:
		printf("Month of %d is JANUARY !!\n\n", num_month);
		break;
	case 2:
		printf("Month of %d is FEBRUARY !!\n\n", num_month);
		break;
	case 3:
		printf("Month of %d is MARCH !!\n\n", num_month);
		break;
	case 4:
		printf("Month of %d is APRIL !!\n\n", num_month);
		break;
	case 5:
		printf("Month of %d is MAY !!\n\n", num_month);
		break;
	case 6:
		printf("Month of %d is JUNE !!\n\n", num_month);
		break;
	case 7:
		printf("Month of %d is JULY !!\n\n", num_month);
		break;
	case 8:
		printf("Month of %d is AUGUST !!\n\n", num_month);
		break;
	case 9:
		printf("Month of %d is SEPTMBER !!\n\n", num_month);
		break;
	case 10:
		printf("Month of %d is OCTOBER !!\n\n", num_month);
		break;
	case 11:
		printf("Month of %d is NOVEMBER !!\n\n", num_month);
		break;
	case 12:
		printf("Month of %d is DECEMBER !!\n\n", num_month);
		break;

	default:
		printf("Invalid month number %d entered !! please try again...\n\n", num_month);
		break;
	}

	return 0;

}


