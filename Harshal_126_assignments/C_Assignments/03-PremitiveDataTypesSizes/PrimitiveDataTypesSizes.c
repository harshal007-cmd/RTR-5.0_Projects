#include<stdio.h>

int main(void)
{
	printf("\n");

	printf("Size of 'int'				=%zd bytes\n",sizeof(int));
	printf("Size of 'unsigned int'			=%zd bytes\n",sizeof(unsigned int));
	printf("Size of 'long'				=%zd bytes\n",sizeof(long));
	printf("Size of 'long long'			=%zd bytes\n",sizeof(long long));
	
	printf("\n-------------\n");
	printf("Size of 'float'				=%zd bytes\n",sizeof(float));
	printf("Size of 'double'			=%zd bytes\n",sizeof(double));
	printf("Size of 'long double'			=%zd bytes\n",sizeof(long double));
	
	printf("\n");
	return 0;
}
