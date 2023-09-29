#include<stdio.h>
#include<stdlib.h>
#include<CL/opencl.h>

int main()
{
	cl_platform_id cid;
	cl_uint cnt;
	char info[512];

	clGetPlatformIds(1, &cid, NULL);
	clGetDeviceIds(cid, CL_DEVICE_TYPE_GPU, 0, NULL, &cnt);
	clGetPlatformInfo(cid, CL_PLATFROM_NAME, 500, &info);
	printf("OpenCL supporting GPU platform name :- %s\n", info);

	clGetPlatformInfo(cid, CL_PLATFROM_VERSION, 500, &info);
	printf("OpenCL supporting GPU platform version :- %s\n", info);

	printf("Number of OpenCL devices :- %d\n", cnt);

	return 0;
}

//cl.exe filename.cpp /I "C:/NVDIA toolkit/include" /Link /LIBPATH: "LIB/x64.../lib" OpenCL.lib /OUT:"filename.exe"