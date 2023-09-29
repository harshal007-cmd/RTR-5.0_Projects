#include<stdio.h>
#include<cuda.h>

int main()
{
	cudaDeviceProp pCuda;
	int cnt;

	cudaGetDeviceCount(&cnt);

	for(int i;i < cnt; ++i)
	{
		cudaGetDeviceProperties(&pCuda, i);
		printf("Name = %s\n",pCuda.name);
		printf("Compute Capability = %d.%d\n", pCuda.major, pCude.minor);
	}
	return 0;
}
