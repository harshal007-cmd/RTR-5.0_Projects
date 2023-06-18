#include<stdio.h>
#define MAX_NUM(a,b) ((a>b) ? a : b)

int main(int argc, char* argv[], char* envp[])
{
	int inum_01, inum_02, iResult;
	float fnum_01, fnum_02, fResult;

	printf("\n\n");
	printf("Enter an integer number : \n\n");
	scanf("%d,", &inum_01);

	printf("\n\n");
	printf("Enter an integer number : \n\n");
	scanf("%d,", &inum_02);

	iResult = MAX_NUM(inum_01, inum_02);
	printf("\n\n");
	printf("Result of Macro function MAX_NUM() = %d\n", iResult);

	printf("\n\n");
	
	//------ Floating point values

	printf("\n\n");
	printf("Enter an Float number : \n\n");
	scanf("%f,", &fnum_01);

	printf("\n\n");
	printf("Enter an Float number : \n\n");
	scanf("%f,", &fnum_02);

	fResult = MAX_NUM(fnum_01, fnum_02);
	printf("\n\n");
	printf("Result of Macro function MAX_NUM() = %f\n", fResult);

	printf("\n\n");
	return 0;
}
