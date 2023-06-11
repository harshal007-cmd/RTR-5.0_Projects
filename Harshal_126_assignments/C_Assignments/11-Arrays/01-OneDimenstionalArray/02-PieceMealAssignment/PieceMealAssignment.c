#include<stdio.h>

int main()
{
	int iArray1[5], iArray2[5];

	//Arrya1
	iArray1[0] = 2;
	iArray1[1] = 22;
	iArray1[2] = 45;
	iArray1[3] = 67;
	iArray1[4] = 82;
	
	//code

	printf("\n\nPiece-meal (Hard-coded) Assignment And Display of element iArray1[] : \n\n");
	
	printf("1st Element of iArray1[] Or 0th index element of iArray1[] = %d\n", iArray1[0]);
	printf("2nd Element of iArray1[] Or 1st index element of iArray1[] = %d\n", iArray1[1]);
	printf("3rd Element of iArray1[] Or 2nd index element of iArray1[] = %d\n", iArray1[2]);
	printf("4th Element of iArray1[] Or 3rd index element of iArray1[] = %d\n", iArray1[3]);
	printf("5th Element of iArray1[] Or 4th index element of iArray1[] = %d\n", iArray1[4]);

	
	
	//iArray2
	printf("\n\n");

	printf("Enter 1st element in iArray2[] : ");
	scanf("%d", &iArray2[0]);
	printf("Enter 2nd element in iArray2[] : ");
	scanf("%d", &iArray2[1]);
	printf("Enter 3rd element in iArray2[] : ");
	scanf("%d", &iArray2[2]);
	printf("Enter 4th element in iArray2[] : ");
	scanf("%d", &iArray2[3]);
	printf("Enter 5th element in iArray2[] : ");
	scanf("%d", &iArray2[4]);

	printf("\n\n");
	printf("Piece-meal (User input) Assignment and Display of Element to Array iArray2[] :\n\n");
	printf("1st Element of iArray2[] Or 0th index element of iArray2[] = %d\n", iArray2[0]);
	printf("2nd Element of iArray2[] Or 1st index element of iArray2[] = %d\n", iArray2[1]);
	printf("3rd Element of iArray2[] Or 3rd index element of iArray2[] = %d\n", iArray2[2]);
	printf("4th Element of iArray2[] Or 4th index element of iArray2[] = %d\n", iArray2[3]);
	printf("5th Element of iArray2[] Or 5th index element of iArray2[] = %d\n", iArray2[4]);

	
	return 0;
}
