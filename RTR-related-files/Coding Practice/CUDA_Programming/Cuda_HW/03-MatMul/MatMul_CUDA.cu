#include<stdio.h>
#define CL_TARGET_OPENCL_VERSION 120
#include<cuda.h>
#include"helper_timer.h"

#define BLOCK_WIDTH 32
//global ver


int* hostA = NULL;
int* hostB = NULL;
int* hostC = NULL;
int* gold = NULL;

int* deviceA = NULL;
int* deviceB = NULL;
int* deviceC = NULL;

float timeOnGPU = 0.0f;
float timeOnCPU = 0.0f;

//CUDA Kernel
__global__ void matMulGPU(int* A, int* B, int* C, int numARows, int numAColumns, int numBColumns, int numCColumns)
{
	//code
	int row = blockIdx.y * blockDim.y + threadIdx.y;
	int column = blockIdx.x * blockDim.x + threadIdx.x;

	if ((row < numARows) && (column < numBColumns))
	{
		int value = 0.0;
		for (int k = 0;k < numAColumns;k++)
		{
			int a = A[row * numAColumns + column];
			int b = B[k * numBColumns + column];
			value += a * b;
		}
		C[row * numCColumns + column] = value;
	}

}

int main()
{
	void InitA(int* data, int, int);
	void InitB(int* data, int, int);
	void matMulCPU(int*, int*, int*, int, int, int, int);
	void cleanup(void);

	//var declare
	int numARows = BLOCK_WIDTH;
	int numAColumns = BLOCK_WIDTH;
	int numBRows = BLOCK_WIDTH;
	int numBColumns = BLOCK_WIDTH;
	int numCRows = numARows;
	int numCColumns = numBColumns;
	
	int numGoldRows = numARows;
	int numGoldColumns = numBColumns;
	
	int sizeA = numARows * numAColumns * sizeof(int);
	int sizeB = numBRows * numBColumns * sizeof(int);
	int sizeC = numCRows * numCColumns * sizeof(int);
	int sizeGold = numGoldRows * numGoldColumns * sizeof(int);

	cudaError_t result = cudaSuccess;

	//host memo allocation
	hostA = (int*)malloc(sizeA);
	if (hostA == NULL)
	{
		printf("Host memo allocation failed for host1 array\n");
		cleanup();
		exit(EXIT_FAILURE);
	}

	hostB = (int*)malloc(sizeB);
	if (hostB == NULL)
	{
		printf("Host memo allocation failed for host2 array\n");
		cleanup();
		exit(EXIT_FAILURE);
	}

	hostC = (int*)malloc(sizeC);
	if (hostC == NULL)
	{
		printf("Host memo allocation failed for hostoutput array\n");
		cleanup();
		exit(EXIT_FAILURE);
	}

	gold = (int*)malloc(sizeGold);
	if (gold == NULL)
	{
		printf("Host memo allocation failed for gold array.\n");
		cleanup();
		exit(EXIT_FAILURE);
	}

	//printing matrix dimentions and sizes
	printf("The Dimensions of Matrix 'hostA' are : %d x %d\n", numARows, numAColumns);
	printf("The Dimensions of Matrix 'hostB' are : %d x %d\n", numBRows, numBColumns);
	printf("The Dimensions of Matrix 'hostC' are : %d x %d\n", numCRows, numCColumns);
	printf("The Dimensions of Matrix 'hostGold' are : %d x %d\n", numGoldRows, numGoldColumns);

	printf("Size of Matrix hostA = %d\n", sizeA);
	printf("Size of Matrix hostB = %d\n", sizeB);
	printf("Size of Matrix hostC = %d\n", sizeC);
	printf("Size of Matrix hostGold = %d\n", sizeGold);

	//fill source matrices
	InitA(hostA, numARows, numAColumns);
	InitB(hostB, numBRows, numBColumns);

	//device memo allocation
	result = cudaMalloc((void**)&deviceA, sizeA);
	if (result != cudaSuccess)
	{
		printf("Device Memo allocation is failed for deviceA array\n");
		cleanup();
		exit(EXIT_FAILURE);
	}
	
	result = cudaMalloc((void**)&deviceB, sizeB);
	if (result != cudaSuccess)
	{
		printf("Device Memo allocation is failed for deviceB array\n");
		cleanup();
		exit(EXIT_FAILURE);
	}

	result = cudaMalloc((void**)&deviceC, sizeC);
	if (result != cudaSuccess)
	{
		printf("Device Memo allocation is failed for deviceC array\n");
		cleanup();
		exit(EXIT_FAILURE);
	}

	//copy data from host array to device arrays
	result = cudaMemcpy(deviceA, hostA, sizeA, cudaMemcpyHostToDevice);
	if (result != cudaSuccess)
	{
		printf("Host to Device data copy is failed for deviceA array\n");
		cleanup();
		exit(EXIT_FAILURE);
	}


	result = cudaMemcpy(deviceB, hostB, sizeB, cudaMemcpyHostToDevice);
	if (result  != cudaSuccess)
	{
		printf("Host to Device data copy is failed for deviceB array\n");
		cleanup();
		exit(EXIT_FAILURE);
	}


	//CUDA kernel conf
	dim3 dimGrid = dim3(ceil((int)numBColumns / (int)BLOCK_WIDTH), ceil((int)numARows / (int)BLOCK_WIDTH), 1);
	dim3 dimBlock = dim3(BLOCK_WIDTH, BLOCK_WIDTH, 1);

	
	//start timer
	StopWatchInterface* timer = NULL;
	sdkCreateTimer(&timer);
	sdkStartTimer(&timer);

	matMulGPU <<<dimGrid, dimBlock >>> (deviceA, deviceB, deviceC, numARows, numAColumns, numBColumns, numCColumns);

	//stop timer
	sdkStopTimer(&timer);
	timeOnGPU = sdkGetTimerValue(&timer);
	sdkDeleteTimer(&timer);
	timer = NULL;

	//copy data from device to host
	result = cudaMemcpy(hostC, deviceC, sizeC, cudaMemcpyDeviceToHost);
	if (result != cudaSuccess)
	{
		printf("Device to host data copy failed for hostC matrix.\n");
		cleanup();
		exit(EXIT_FAILURE);
	}

	//matMul on host
	matMulCPU(hostA, hostB, gold, numARows, numAColumns, numBColumns, numCColumns);


	//comparison
	int breakValue = -1;
	bool bAccuracy = true;
	
	for (int i = 0; i < numCRows*numCColumns; ++i)
	{
		float val1 = gold[i];
		float val2 = hostC[i];
		if (val1 != val2)
		{
			bAccuracy = false;
			breakValue = i;
			break;
		}
	}

	char str[128];
	if (bAccuracy == false)
		sprintf(str, "Comparison of CPU and GPU Matrix Multiplication is not accurate at array index %d", breakValue);
	else
		sprintf(str, "Comparison of CPU and GPU Matrix Multiplication is accurate\n");

	
	//output
	printf("Time taken for Matrix Multiplication on CPU = %.6f\n", timeOnCPU);
	printf("Time taken for Matrix Multiplication on GPU = %.6f\n", timeOnGPU);
	printf("%s\n", str);

	cleanup();

	return 0;
}

void InitA(int* data, int row, int col)
{
	int num = 1;
	for (int i = 0;i < row;i++)
	{
		for (int j = 0;j < col; j++)
		{
			*(data + i * col + j) = num;
			num++;
		}
	}
}

void InitB(int* data, int row, int col)
{
	int num = BLOCK_WIDTH;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0;j < col; j++)
		{
			*(data + i * col + j) = num;
			num--;
		}
	}
}


void matMulCPU(int* A, int* B, int* C, int numARows, int numAColumns, int numBColumns, int numCColumns)
{
	StopWatchInterface* timer = NULL;
	sdkCreateTimer(&timer);
	sdkStartTimer(&timer);

	for (int i = 0;i < numARows;++i)
	{
		int value = 0.0f;
		for (int j = 0; i < numBColumns; ++j)
		{
			for (int k = 0;i < numAColumns; ++k)
			{
				int a = A[i * numAColumns + k];
				int b = B[k * numBColumns + j];
				value += a * b;
			}
			C[i * numCColumns + j] = value;
		}
	}

	sdkStopTimer(&timer);
	timeOnCPU = sdkGetTimerValue(&timer);
	sdkDeleteTimer(&timer);
	timer = NULL;

}

void cleanup()
{
	if (deviceC)
	{
		cudaFree(deviceC);
		deviceC = NULL;
	}

	if (deviceB)
	{
		cudaFree(deviceB);
		deviceB = NULL;
	}

	if (deviceA)
	{
		cudaFree(deviceA);
		deviceA = NULL;
	}

	
	if (hostC)
	{
		free(hostC);
		hostC = NULL;
	}

	if (hostB)
	{
		free(hostB);
		hostB = NULL;
	}

	if (hostA)
	{
		free(hostA);
		hostA = NULL;
	}

}

//cl.exe filename.cpp /I "C:/NVDIA toolkit/include" /Link /LIBPATH: "LIB/x64.../lib" OpenCL.lib /OUT:"filename.exe"












