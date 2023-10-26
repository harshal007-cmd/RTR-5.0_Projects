#include<stdio.h>
#include<stdlib.h>
#include<CL/opencl.h>
#include<math.h>
#include"helper_timer.h"

//global ver
const int iNumberOfArrayElements = 11444777;

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
"__kernel void vecAddGPU(__global float *in1, __global float *in2, __global float *out, int len)"\
"{"\
"int i=get_global_id(0);"\
"if(i<len)"\
"{"\
"out[i]=in1[i]+in2[i];"\
"}"\
"}";

int main()
{
	void fillFloatArrayWithRandomeNumbers(float*, int);
	size_t roundGlobalSizeToNearestMulOfLocalSize(int, unsigned int);
	void vecAddCPU(const float*, const float*, float*, int);
	void cleanup(void);

	//var declare
	int size = iNumberOfArrayElements * sizeof(float);
	cl_int result;

	//host memo allocation
	hostInput1 = (float*)malloc(size);
	if (hostInput1 == NULL)
	{
		printf("Host memo allocation failed for host1 array\n");
		cleanup();
		exit(EXIT_FAILURE);
	}
	hostInput2 = (float*)malloc(size);

	if (hostInput2 == NULL)
	{
		printf("Host memo allocation failed for host2 array\n");
		cleanup();
		exit(EXIT_FAILURE);
	}

	hostOutput = (float*)malloc(size);

	if (hostOutput == NULL)
	{
		printf("Host memo allocation failed for hostoutput array\n");
		cleanup();
		exit(EXIT_FAILURE);
	}

	gold = (float*)malloc(size);
	if (gold == NULL)
	{
		printf("Host memo allocation failed for gold array.\n");
		cleanup();
		exit(EXIT_FAILURE);
	}

	//filling values in host array
	fillFloatArrayWithRandomeNumbers(hostInput1, iNumberOfArrayElements);
	fillFloatArrayWithRandomeNumbers(hostInput2, iNumberOfArrayElements);

	//get opencl supporting platform ids
	result = clGetPlatformIDs(1, &oclPlatformID, NULL);
	if (result != CL_SUCCESS)
	{
		printf("clGetPlatformIDs() failed : %d\n", result);
		cleanup();
		exit(EXIT_FAILURE);
	}

	//get opencl supporting CPU device ids
	result clGetDeviceIDs(oclPlatform, CL_DEVICE_TYPE_GPU, 1, &oclDeviceID, NULL);
	if (result != CL_SUCCESS)
	{
		printf("clGetDeviceIDs() failed : %d\n", result);
		cleanup();
		exit(EXIT_FAILURE);

	}

	//create opencl compute context
	oclCOntext = clCreateContex(NULL, 1, &oclDeviceID, NULL, NULL, &result);
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
	oclkernel = clCreateKernel(oclProgram, "vedAddGPU", &result);
	if (result != CL_SUCCESS)
	{
		printf("clCreateKernel() failed : %d\n", result);
		cleanup();
		exit(EXIT_FAILURE);
	}

	//device memory allocation
	deviceInput1 = clCreateBuffer(oclContext, CL_MEM_READ_ONLY, size, NULL, &result);
	if (result != CL_SUCCESS)
	{
		printf("clCreateBuffer() failed for 1st input array : %d\n", result);
		cleanup();
		exit(EXIT_FAILURE);
	}

	deviceInput2 = clCreateBuffer(oclContext, CL_MEM_READ_ONLY, size, NULL, &result);
	if (result != CL_SUCCESS)
	{
		printf("clCreateBuffer() failed for 2nd input array : %d\n", result);
		cleanup();
		exit(EXIT_FAILURE);
	}

	deviceInput = clCreateBuffer(oclContext, CL_MEM_WRITE_ONLY, size, NULL, &result);
	if (result != CL_SUCCESS)
	{
		printf("clCreateBuffer() failed for output array : %d\n", result);
		cleanup();
		exit(EXIT_FAILURE);
	}

	//SET 0 based 0th argument dev1
	result = clSetKernelArg(oclKernel, 1, sizeof(cl_mem), (void*)&deviceInput1);
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
		printf("clSetKernelArg() faild for 1st Argument : %d\n", result);
		cleanup();
		exit(EXIT_FAILURE);
	}
	//dev output
	result = clSetKernelArg(oclKernel, 1, sizeof(cl_mem), (void*)&deviceOutput);
	if (result != CL_SUCCESS)
	{
		printf("clSetKernelArg() faild for 1st Argument : %d\n", result);
		cleanup();
		exit(EXIT_FAILURE);
	}

	return 0;
}

void cleanup()
{

}

//cl.exe filename.cpp /I "C:/NVDIA toolkit/include" /Link /LIBPATH: "LIB/x64.../lib" OpenCL.lib /OUT:"filename.exe"












