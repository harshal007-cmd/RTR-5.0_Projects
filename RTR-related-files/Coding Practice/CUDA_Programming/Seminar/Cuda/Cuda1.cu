#include<stdio.h>
#include<cuda.h>

const int iNumElement = 5;

float* hostInput1 = NULL;
float* hostInput2 = NULL;
float* hostInput  = NULL;

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
{
	void cleanup(void);

	int size = iNumElement * sizeof(float);
	cudaError_t result = cudaSuccess;

	hostInput1 = (float*)malloc(size);
	if (hostInput1 == NULL)
	{
		printf("Host memory allocation is falied for hostInput1 array.\n");
		cleanup();
		exit(EXIT_FAILURE);
	}

	hostInput2 = (float*)malloc(size);
	if (hostInput2 == NULL)
	{
		printf("Host memory allocation is falied for hostInput2 array.\n");
		cleanup();
		exit(EXIT_FAILURE);
	}

	hostInput = (float*)malloc(size);
	if (hostInput == NULL)
	{
		printf("Host memory allocation is falied for hostInput array.\n");
		cleanup();
		exit(EXIT_FAILURE);
	}

	//inputs
	hostInput1[0] = 101.0;
	hostInput1[1] = 102.0;
	hostInput1[2] = 103.0;
	hostInput1[3] = 104.0;
	hostInput1[4] = 105.0;

	hostInput2[0] = 201.0;
	hostInput2[1] = 202.0;
	hostInput2[2] = 203.0;
	hostInput2[3] = 204.0;
	hostInput2[4] = 205.0;

	result = cudaMalloc((void**)&deviceInput1, size);
	if (result != cudaSuccess)
	{
		printf("Device memory allocation failed for dev1\n");
		cleanup();
		exit(EXIT_FAILURE);
	}

	result = cudaMalloc((void**)&deviceInput2, size);
	if (result != cudaSuccess)
	{
		printf("Device memory allocation failed for dev2\n");
		cleanup();
		exit(EXIT_FAILURE);
	}
	
	result = cudaMalloc((void**)&deviceInput, size);
	if (result != cudaSuccess)
	{
		printf("Device memory allocation failed for dev\n");
		cleanup();
		exit(EXIT_FAILURE);
	}

	//copy data from host array to device array
	result = cudaMemcpy(deviceInput1, hostInput1, size, cudaMemcpyHostToDevice);
	if (result != cudaSuccess)
	{
		printf("Host to device data is failed for dev1 array\n");
		cleanup();
		exit(EXIT_FAILURE);
	}

	result = cudaMemcpy(deviceInput2, hostInput2, size, cudaMemcpyHostToDevice);
	if (result != cudaSuccess)
	{
		printf("Host to device data is failed for dev2 array\n");
		cleanup();
		exit(EXIT_FAILURE);
	}

	dim3 dimGrid = dim3(iNumElement, 1, 1);
	dim3 dimBlock = dim3(1, 1, 1);

	//CUDA karnel for vector addition
	vecAddGPU <<< dimGrid,dimBlock >>> (deviceInput1, deviceInput2, deviceInput, iNumElement);
	
	//copy data to array
	result = cudaMemcpy(hostInput,deviceInput,size,cudaMemcpyHostToDevice);
	
	if(result != cudaSuccess)
	{
		printf("Device to host copy is failed \n");
		cleanup();
		exit(EXIT_FAILURE);
	}
	
	for(int i=0; i < iNumElement;++i)
	{
		printf("%f + %f = %f\n",hostInput1[i],hostInput2[i],hostInput[i]);
	}

	cleanup();
	return 0;


}

void cleanup()
{
	if(deviceInput)
	{
		cudaFree(deviceInput);
		deviceInput = NULL;
	}
	
	if(deviceInput)
	{
		cudaFree(deviceInput2);
		deviceInput2 = NULL;
	}
	if(deviceInput1)
	{
		cudaFree(deviceInput1);
		deviceInput1 = NULL;
	}
	
	if(hostInput)
	{
		cudaFree(hostInput);
		hostInput=NULL;
	}
	
	if(hostInput2)
	{
		cudaFree(hostInput2);
		hostInput2=NULL;
	}
	if(hostInput1)
	{
		cudaFree(hostInput1);
		hostInput1 = NULL;
	}
}








