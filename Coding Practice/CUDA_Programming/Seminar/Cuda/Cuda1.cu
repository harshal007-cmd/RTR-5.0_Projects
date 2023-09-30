#include<stdio.h>
#include<cuda.h>

const int iNumElement = 5;

float* hostInput1 = NULL;
float* hostInput2 = NULL;
float* hostInput3 = NULL;

float* deviceInput1 = NULL;
float* deviceInput2 = NULL;
float* deviceInput = NULL;

__global__ void vecAddGPU(float* in1, float* in2, float* out, int len)
{
	int i = blockIdx.x * blockDim.x + threadIdx.x;

	if (i < len)
	{
		out[i] = in1[i] + in2[i];
	}
}

int main(void)
