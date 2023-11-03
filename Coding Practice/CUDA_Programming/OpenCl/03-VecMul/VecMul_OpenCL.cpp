#include<stdio.h>
#include<math.h>
#define CL_TARGET_OPENCL_VERSION 120
#include<CL/opencl.h>
#include"helper_timer.h"

//global ver
const int iNumberOfArrayElements = 211444777;

cl_platform_id oclPlatformID;
cl_device_id oclDeviceID;

cl_context oclContext;
cl_command_queue oclCommandQueue;

cl_program oclProgram;
cl_kernel oclKernel;

float* hostInput1 = NULL;
float* hostInput2 = NULL;
float* hostOutput = NULL;
float* gold = NULL;

cl_mem deviceInput1 = NULL;
cl_mem deviceInput2 = NULL;
cl_mem deviceOutput = NULL;

float timeOnGPU = 0.0f;
float timeOnCPU = 0.0f;

const char* oclSourceCode =
"__kernel void vecMulGPU(__global int *in1, __global int *in2, __global int *out, int numRows, int numAColumns, int numBColumns, int numCColumns)"\
"{"\
"int row=get_global_id(0);"\
"int column=get_global_id(1)"\
"if((row < numARows) && (column < numBColumns))"\
"{"\
"int value=0;"\
"for(int k=0; k < numAColumns; k++)"\
"{"\
"int a=A[row * numAColumns + k];"\
"int b=B[k * numBColumns + column];"\
"value += a*b;"\
"}"\
"C[row * numCColumns + column]=value;"\
"}"\
"}";

int main()
{
	//func decl
	void InitA(int* data, int, int);
	void InitB(int* data, int, int);
	void matMulCPU(int*, int*, int*, int, int, int, int);
	void cleanup(void);

	//var declare
	int numARows = BLOCK_WIDTH;
	int numAColumns = BLOCK_WIDTH;
	int numBRows = BLOCK_WIDHT;		
	int numBColumns = BLOCK_WIDTH;

	int numCRows = numARows;
	int numCColumns = numBColumns;

	int numGoldRows = numARows;
	int numGoldColumns = numBColumns;

	int sizeA = numARows * numAColumns * sizeof(int);
	int sizeB = numBRows * numBColumns * sizeof(int);
	int sizeC = numCRows * numCColumns * sizeof(int);
	int sizeGold = numGoldRows * numGoldColumns * sizeof(int);


	cl_int result;

	//host memo allocation
	hostInput1 = (int*)malloc(sizeA);
	if (hostInput1 == NULL)
	{
		printf("Host memo allocation failed for host1 array\n");
		cleanup();
		exit(EXIT_FAILURE);
	}
	hostInput2 = (int*)malloc(sizeB);

	if (hostInput2 == NULL)
	{
		printf("Host memo allocation failed for host2 array\n");
		cleanup();
		exit(EXIT_FAILURE);
	}

	hostOutput = (int*)malloc(sizeC);

	if (hostOutput == NULL)
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

	//printing matrix dimension and size
	printf("The Dimension of matrix 'hostA' are : %d x %d\n", numARows, numAColumns);
	printf("The Dimension of matrix 'hostB' are : %d x %d\n", numBRows, numBColumns);
	printf("The Dimension of matrix 'hostC' are : %d x %d\n", numCRows, numCColumns);
	printf("The Dimension of matrix 'gold' are : %d x %d\n", numGoldRows, numGoldColumns);

	printf("Size of Matrix hostA = %d\n", sizeA);
	printf("Size of Matrix hostB = %d\n", sizeB);
	printf("Size of Matrix hostC = %d\n", sizeC);
	printf("Size of Matrix gold = %d\n", sizeGold);

	//fill source matrics
	InitA(hostInput1, numARows, numAColumns);
	InitB(hostInput2, numBRows, numBColumns);

	//get opencl supporting platform ids
	result = clGetPlatformIDs(1, &oclPlatformID, NULL);
	if (result != CL_SUCCESS)
	{
		printf("clGetPlatformIDs() failed : %d\n", result);
		cleanup();
		exit(EXIT_FAILURE);
	}

	//get opencl supporting CPU device ids
	result = clGetDeviceIDs(oclPlatformID, CL_DEVICE_TYPE_GPU, 1, &oclDeviceID, NULL);
	if (result != CL_SUCCESS)
	{
		printf("clGetDeviceIDs() failed : %d\n", result);
		cleanup();
		exit(EXIT_FAILURE);

	}

	//create opencl compute context
	oclContext = clCreateContext(NULL, 1, &oclDeviceID, NULL, NULL, &result);
	if (result != CL_SUCCESS)
	{
		printf("clCreateContex() failed : %d\n", result);
		cleanup();
		exit(EXIT_FAILURE);

	}

	//create command queue
	oclCommandQueue = clCreateCommandQueue(oclContext, oclDeviceID, 0, &result);
	if (result != CL_SUCCESS)
	{
		printf("clCreateContex() failed : %d\n", result);
		cleanup();
		exit(EXIT_FAILURE);
	}

	//create OpenCL program from .cl
	oclProgram = clCreateProgramWithSource(oclContext, 1, (const char**)&oclSourceCode, NULL, &result);
	if (result != CL_SUCCESS)
	{
		printf("clCreateProgramWithSource() Failed : %d\n", result);
		cleanup();
		exit(EXIT_FAILURE);
	}

	//build opencl program
	result = clBuildProgram(oclProgram, 0, NULL, NULL, NULL, NULL);
	if (result != CL_SUCCESS)
	{
		size_t len;
		char buffer[2048];
		clGetProgramBuildInfo(oclProgram, oclDeviceID, CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, &len);
		printf("Program build log %s\n", buffer);
		printf("clBuildProgram() Failed: %d\n", result);
		cleanup();
		exit(EXIT_FAILURE);

	}
	
	//create Opencl kernel by passing kernel fun name that we used .cl file
	oclKernel = clCreateKernel(oclProgram, "matMulGPU", &result);
	if (result != CL_SUCCESS)
	{
		printf("clCreateKernel() failed : %d\n", result);
		cleanup();
		exit(EXIT_FAILURE);
	}

	//device memory allocation
	deviceInput1 = clCreateBuffer(oclContext, CL_MEM_READ_ONLY, sizeA, NULL, &result);
	if (result != CL_SUCCESS)
	{
		printf("clCreateBuffer() failed for 1st input array : %d\n", result);
		cleanup();
		exit(EXIT_FAILURE);
	}

	deviceInput2 = clCreateBuffer(oclContext, CL_MEM_READ_ONLY, sizeB, NULL, &result);
	if (result != CL_SUCCESS)
	{
		printf("clCreateBuffer() failed for 2nd input array : %d\n", result);
		cleanup();
		exit(EXIT_FAILURE);
	}

	deviceOutput = clCreateBuffer(oclContext, CL_MEM_WRITE_ONLY, sizeC, NULL, &result);
	if (result != CL_SUCCESS)
	{
		printf("clCreateBuffer() failed for output array : %d\n", result);
		cleanup();
		exit(EXIT_FAILURE);
	}

	//SET 0 based 0th argument dev1
	result = clSetKernelArg(oclKernel, 0, sizeof(cl_mem), (void*)&deviceInput1);
	if (result != CL_SUCCESS)
	{
		printf("clSetKernelArg() faild for 1st Argument : %d\n", result);
		cleanup();
		exit(EXIT_FAILURE);
	}

	//dev2
	result = clSetKernelArg(oclKernel, 1, sizeof(cl_mem), (void*)&deviceInput2);
	if (result != CL_SUCCESS)
	{
		printf("clSetKernelArg() faild for 2nd Argument : %d\n", result);
		cleanup();
		exit(EXIT_FAILURE);
	}
	//dev output
	result = clSetKernelArg(oclKernel, 2, sizeof(cl_mem), (void*)&deviceOutput);
	if (result != CL_SUCCESS)
	{
		printf("clSetKernelArg() faild for 3rd Argument : %d\n", result);
		cleanup();
		exit(EXIT_FAILURE);
	}

	result = clSetKernelArg(oclKernel, 3, sizeof(cl_int), (void*)&numARows);
	if (result != CL_SUCCESS)
	{
		printf("clSetKernelArg() failed for 4th Argument : %d\n", result);
		cleanup();
		exit(EXIT_FAILURE);
	}

	result = clSetKernelArg(oclKernel, 4, sizeof(cl_int), (void*)&numAColumns);
	if (result != CL_SUCCESS)
	{
		printf("clSetKernelArg() failed for 5th Argument : %d\n", result);
		cleanup();
		exit(EXIT_FAILURE);
	}

	result = clSetKernelArg(oclKernel, 5, sizeof(cl_int), (void*)&numBColumns);
	if (result != CL_SUCCESS)
	{
		printf("clSetKernelArg() failed for 6th Argument : %d\n", result);
		cleanup();
		exit(EXIT_FAILURE);
	}

	result = clSetKernelArg(oclKernel, 6, sizeof(cl_int), (void*)&numCColumns);
	if (result != CL_SUCCESS)
	{
		printf("clSetKernelArg() failed for 7th Argument : %d\n", result);
		cleanup();
		exit(EXIT_FAILURE);
	}


	//write abve intput device buffer to device memo
	result = clEnqueueWriteBuffer(oclCommandQueue, deviceInput1, CL_FALSE, 0, size, hostInput1, 0, NULL, NULL);
	if (result != CL_SUCCESS)
	{
		printf("clEnqueueBuffer() failed for 1st input buffer : %d\n", result);
	}

	result = clEnqueueWriteBuffer(oclCommandQueue, deviceInput2, CL_FALSE, 0, size, hostInput2, 0, NULL, NULL);
	if (result != CL_SUCCESS)
	{
		printf("clEnqueueWriteBuffer() failed for 2nd Input Device buffer : %d\n", result);
		cleanup();
		exit(EXIT_FAILURE);
	}

	size_t localWorkSize = 256;
	size_t globalWorkSize;

	globalWorkSize = roundGlobalSizeToNearestMultipleOfLocalSize(localWorkSize, iNumberOfArrayElements);

	//start timer
	StopWatchInterface* timer = NULL;
	sdkCreateTimer(&timer);
	sdkStartTimer(&timer);

	result = clEnqueueNDRangeKernel(oclCommandQueue, oclKernel,1, NULL, &globalWorkSize, &localWorkSize, 0, NULL, NULL);
	if (result != CL_SUCCESS)
	{
		printf("clEnqueueNDRangeKernel() failed : %d\n", result);
		cleanup();
		exit(EXIT_FAILURE);
	}

	//finish OpenCL command
	clFinish(oclCommandQueue);

	//stop timer
	sdkStopTimer(&timer);
	timeOnGPU = sdkGetTimerValue(&timer);
	sdkDeleteTimer(&timer);

	//read back result from device into cpu var ie hostOutput
	result = clEnqueueReadBuffer(oclCommandQueue, deviceOutput, CL_TRUE, 0, size, hostOutput, 0, NULL, NULL);
	if (result != CL_SUCCESS)
	{
		printf("clEnqueueReadBuffer() failed : %d\n", result);
		cleanup();
		exit(EXIT_FAILURE);
	}

	//vector addition on host
	vecAddCPU(hostInput1, hostInput2, gold, iNumberOfArrayElements);

	//comparison
	const float epsilon = 0.000001f;
	int breakValue = -1;
	bool bAccuracy = true;
	
	for (int i = 0;i < iNumberOfArrayElements;++i)
	{
		float val1 = gold[i];
		float val2 = hostOutput[i];
		if (fabs(val1 - val2) > epsilon)
		{
			bAccuracy = false;
			breakValue = i;
			break;
		}
	}

	char str[128];
	if (bAccuracy == false)
		sprintf(str, "Comparison of CPU and GPU vector addition is not within accuracy of 0.000001 at array index %d", breakValue);
	else
		sprintf(str, "Comparison of CPu and GPU vector addtion is within accuracy of 0.000001");

	
	//output
	printf("Array1 begins from 0th index %.6f to %dth index %.6f\n", hostInput1[0], iNumberOfArrayElements - 1, hostInput1[iNumberOfArrayElements - 1]);
	printf("Array1 begins from 0th index %.6f to %dth index %.6f\n", hostInput2[0], iNumberOfArrayElements - 1, hostInput2[iNumberOfArrayElements - 1]);
	
	printf("OpenCL kernel global work size = %zu and local work size = %zu\n", globalWorkSize, localWorkSize);
	printf("Output array begins from 0th index %.6f to %dth index %.6f\n", hostOutput[0], iNumberOfArrayElements - 1, hostOutput[iNumberOfArrayElements - 1]);

	printf("Time taken for Vector additional on CPU = %.6f\n", timeOnCPU);
	printf("Time taken for Vector additional on GPU = %.6f\n", timeOnGPU);
	printf("%s\n", str);

	cleanup();

	return 0;
}

void fillFloatArrayWithRandomNumbers(float* arr, int len)
{
	const float fscale = 1.0f / (float)RAND_MAX;
	for (int i = 0;i < len;i++)
	{
		arr[i] = fscale * rand();
	}

}

void vecAddCPU(const float* arr1, const float* arr2, float* out, int len)
{
	StopWatchInterface* timer = NULL;
	sdkCreateTimer(&timer);
	sdkStartTimer(&timer);

	for (int i = 0;i < len;++i)
	{
		out[i] = arr1[i] + arr2[i];
	}

	sdkStopTimer(&timer);
	timeOnCPU = sdkGetTimerValue(&timer);
	sdkDeleteTimer(&timer);
	timer = NULL;

}

size_t roundGlobalSizeToNearestMultipleOfLocalSize(int local_size, unsigned int global_size)
{
	unsigned int r = global_size % local_size;
	if (r == 0)
	{
		return global_size;
	}
	else
	{
		return (global_size + local_size - r);
	}

}

void cleanup()
{
	if (deviceOutput)
	{
		clReleaseMemObject(deviceOutput);
		deviceOutput = NULL;
	}

	if (deviceInput2)
	{
		clReleaseMemObject(deviceInput2);
		deviceInput2 = NULL;
	}

	if (deviceInput1)
	{
		clReleaseMemObject(deviceInput1);
		deviceInput1 = NULL;
	}

	if (oclKernel)
	{
		clReleaseKernel(oclKernel);
		oclKernel = NULL;
	}

	if (oclProgram)
	{
		clReleaseProgram(oclProgram);
		oclProgram = NULL;
	}

	if (oclCommandQueue)
	{
		clReleaseCommandQueue(oclCommandQueue);
		oclCommandQueue = NULL;
	}

	if (oclContext)
	{
		clReleaseContext(oclContext);
		oclContext = NULL;
	}

	if (hostOutput)
	{
		free(hostOutput);
		hostOutput = NULL;
	}

	if (hostInput2)
	{
		free(hostInput2);
		hostInput2 = NULL;
	}

	if (hostInput1)
	{
		free(hostInput1);
		hostInput1 = NULL;
	}

}

//cl.exe filename.cpp /I "C:/NVDIA toolkit/include" /Link /LIBPATH: "LIB/x64.../lib" OpenCL.lib /OUT:"filename.exe"












