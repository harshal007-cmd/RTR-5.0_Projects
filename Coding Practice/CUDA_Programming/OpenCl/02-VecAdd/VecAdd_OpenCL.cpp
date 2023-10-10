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
	void fillArrayWithRndNumbers(float*, int);
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

	return 0;
}

void cleanup()
{

}

//cl.exe filename.cpp /I "C:/NVDIA toolkit/include" /Link /LIBPATH: "LIB/x64.../lib" OpenCL.lib /OUT:"filename.exe"