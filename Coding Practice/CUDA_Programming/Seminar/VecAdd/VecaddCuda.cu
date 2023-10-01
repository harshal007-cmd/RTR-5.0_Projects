#include<stdio.h>
#include<cuda.h>
#include"helper_timer.h"

const int iNumElement = 5;

float* hostInput1 = NULL;
float* hostInput2 = NULL;
float* hostInput  = NULL;
float* gold = NULL;

float* deviceInput1 = NULL;
float* deviceInput2 = NULL;
float* deviceInput = NULL;

float timeOnCPU = 0.0;
float timeOnGPU = 0.0;

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
	void fillFloatArrayWithRandomNumber(float*, int);
	void vecAddCPU(const float*, const float*, float*, int);

	int size = iNumElement * sizeof(flaot);
	cudaError_t result_t = cudaSuccess;

	hostInput1 = (float*)malloc(size);
	if (hostInput1 = NULL)
	{
		printf("Host memory allocation is falied for hostInput1 array.\n");
		cleanup();
		exit(EXIT_FAILURE);
	}

	hostInput2 = (float*)malloc(size);
	if (hostInput2 = NULL)
	{
		printf("Host memory allocation is falied for hostInput2 array.\n");
		cleanup();
		exit(EXIT_FAILURE);
	}

	hostInput = (float*)malloc(size);
	if (hostInput = NULL)
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
	result cudaMemcpy(deviceInput1, hostInput1, size, cudaMemcpyHostToDevice);
	if (result != cudaSuccess)
	{
		printf("Host to device data is failed for dev1 array\n");
		cleanup();
		exit(EXIT_FAILURE);
	}

	result cudaMemcpy(deviceInput2, hostInput2, size, cudaMemcpyHostToDevice);
	if (result != cudaSuccess)
	{
		printf("Host to device data is failed for dev2 array\n");
		cleanup();
		exit(EXIT_FAILURE);
	}

	dim3 dimGrid = dim3((int)ceil((float)iNumElement/256.0), 1, 1);
	dim3 dimBlock = dim3(256, 1, 1);

	StopWatchInterface* timer = NULL;
	sdkCreateTimer(&timer);
	sdkStartTimer(&timer);


	//CUDA karnel for vector addition
	vecAddGPU <<< dimGrid,dimBlock >>> (deviceInput1, deviceInput2, deviceInput, iNumElement);
	
	sdkStopTimer(&timer);
	timeOnGPU = sdkGetTimerValue(&timer);
	sdkDeleteTimer(&timer);
	timer = NULL;
	
	//copy data to array
	result = cudaMemcpy(hostInput,deviceInput,size,cudaMemcpyHostToDevice);
	
	if(result != cudaSuccess)
	{
		printf("Device to host copy is failed \n");
		cleanup();
		exit(EXIT_FAILURE);
	}
	
	vecAddCPU(hostInput1, hostInput2, gold, iNumElement);

	//comparison
	const float epsilon = 0.000001f;
	int breakValue = -1;
	bool bAccuracy = true;
	for (int i = 0; i < iNumElement; ++i)
	{
		float val1 = gold[i];
		float val2 = hostInput[i];
		if (fabs(val1 - val2) > epsilon)
		{
			bAccuracy = false;
			breakValue = i;
			break;
		}
	}

	for(int i=0,i<iNumElement;++i)
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








