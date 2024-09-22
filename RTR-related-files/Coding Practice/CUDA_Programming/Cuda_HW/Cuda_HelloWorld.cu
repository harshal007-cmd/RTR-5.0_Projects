#include<stdio.h>
#include<cuda.h>

int main()
{
	cudaDeviceProp pCuda;
	int cnt;

	cudaGetDeviceCount(&cnt);

	for(int i=0;i < cnt; ++i)
	{
		cudaGetDeviceProperties(&pCuda, i);
		printf("Name = %s\n",pCuda.name);
		printf("Compute Capability = %d.%d\n", pCuda.major, pCuda.minor);
	}
	return 0;
}
