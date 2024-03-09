//Common header files
#include<windows.h>//win32
#include"Window.h" //or OGL.h (if rename)
#include<stdio.h>///for file IO
#include<stdlib.h>//for exit() 
#include<mmsystem.h>//for sound

#define _USE_MATH_DEFINES 1
#include<math.h>

//OpenGL Header files
#include<GL/GL.h>
#include<GL/GLU.h>
#include"first.h"
#include"second.h"
#include"third.h"
#include"fourth.h"
#include"fifth.h"
#include"extra.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


//OpenGL related Global Variables
HDC ghdc = NULL;
HGLRC ghrc = NULL; //handle to GL Rendering Contex

//Macros
#define WIDTH 800
#define HEIGHT 600

//Link with OpenGL Lib
#pragma comment(lib,"openGL32.lib")
#pragma comment(lib,"glu32.lib")
#pragma comment(lib, "winmm.lib")

//global function declaration
LRESULT CALLBACK WndProg(HWND, UINT, WPARAM, LPARAM);

//File io
FILE* gpFILE = NULL;

//global variable declaration
HWND ghwnd = NULL;
BOOL gbActive = FALSE;
DWORD dwstyle = 0;
WINDOWPLACEMENT wpPrev = { sizeof(WINDOWPLACEMENT) };
BOOL gbFullScreen = FALSE;


//time mang
LARGE_INTEGER frequency;
LARGE_INTEGER frameStart;
LARGE_INTEGER previousTime;
GLfloat deltaTime = 0.0;


//for gluPers var
GLfloat angle = 0.0;
GLfloat vnear = 0.0;
GLfloat vfar = 0.0;
GLfloat t = 0.0;

int change = 1;

float lerp(float start, float end, float t)
{
	return start + t * (end - start);
}

//Entry point function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	//function declarations
	int initialize(void);
	void uninitialize(void);
	void display(void);
	void update(void);

	//local variable declarations
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("WINDEV");
	int iResult = 0;
	BOOL bDone = FALSE;
	
	//Screen Size
	int xScreen, yScreen;
	xScreen = GetSystemMetrics(SM_CXSCREEN) / 2;
	yScreen = GetSystemMetrics(SM_CYSCREEN) / 2;

	//for File io
	gpFILE = fopen("Log.txt", "w");
	if (gpFILE == NULL)
	{
		MessageBox(NULL, TEXT("Log file cannot be open"), TEXT("Error"), MB_OK | MB_ICONERROR);
		exit(0);
	}
	fprintf(gpFILE, "Program Started Successfully\n");

	//code
	//WNDCLASSEX initialization
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProg;
	wndclass.hInstance = hInstance;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	//wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);


	//registration of WNDCLASSEX
	RegisterClassEx(&wndclass);

	//creating window
	hwnd = CreateWindowEx(WS_EX_APPWINDOW,
		szAppName,
		TEXT("HVS:DS Demo"),
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE,
		(xScreen - WIDTH / 2), (yScreen - HEIGHT / 2), WIDTH, HEIGHT,
		NULL, NULL,
		hInstance,
		NULL);

	ghwnd = hwnd;

	//Initialization
	iResult = initialize();
	if (iResult != 0)
	{
		MessageBox(hwnd, TEXT("initialize() Failed !!"), TEXT("Error"), MB_OK | MB_ICONERROR);
		DestroyWindow(hwnd);
	}

	//show window
	ShowWindow(hwnd, iCmdShow);

	SetForegroundWindow(hwnd);
	SetFocus(hwnd);

	//Game Loop
	while (bDone == FALSE)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				bDone = TRUE;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			if (gbActive == TRUE)
			{
				//Render
				display();

				//Update
				update();
			}
		}
	}

	//Uninitialization
	uninitialize();

	return((int)msg.wParam);

}

LRESULT CALLBACK WndProg(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	//Function declaration
	void ToogleFullScreen(void);
	void resize(int, int);
	
	//code
	switch (iMsg)
	{
	case WM_SETFOCUS:
		gbActive = TRUE;
		break;
	case WM_KILLFOCUS:
		gbActive = FALSE;
		break;
	case WM_SIZE:
		resize(LOWORD(lParam),HIWORD(lParam));
		break;
	/*
	case WM_ERASEBKGND:
		return 0;*/
	case WM_KEYDOWN:
		switch (LOWORD(wParam))
		{
		case VK_ESCAPE:
			DestroyWindow(hwnd);
			break;
		}
		break;
	case WM_CHAR:
		switch (LOWORD(wParam))
		{
		case 'F':
		case 'f':
			ToogleFullScreen();
			break;
		
		}
		break;
	
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));

}

void ToogleFullScreen(void)
{
	//local variables
	MONITORINFO mi = { sizeof(MONITORINFO) };

	//code
	if (gbFullScreen == FALSE) //1 psudeo code
	{
		dwstyle = GetWindowLong(ghwnd, GWL_STYLE); //get window long style
		if (dwstyle & WS_OVERLAPPEDWINDOW)
		{
			if (GetWindowPlacement(ghwnd, &wpPrev) && GetMonitorInfo(MonitorFromWindow(ghwnd, MONITORINFOF_PRIMARY), &mi))
			{
				SetWindowLong(ghwnd, GWL_STYLE, dwstyle & ~WS_OVERLAPPEDWINDOW);
				SetWindowPos(ghwnd, HWND_TOP, mi.rcMonitor.left, mi.rcMonitor.top, mi.rcMonitor.right - mi.rcMonitor.left, mi.rcMonitor.bottom - mi.rcMonitor.top, SWP_NOZORDER | SWP_FRAMECHANGED); //rc=rect
			}
		}
		ShowCursor(FALSE);
		gbFullScreen=TRUE;
	}
	else
	{
		SetWindowPlacement(ghwnd, &wpPrev);
		SetWindowLong(ghwnd, GWL_STYLE, dwstyle | WS_OVERLAPPEDWINDOW);
		SetWindowPos(ghwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_FRAMECHANGED);
		ShowCursor(TRUE);
		gbFullScreen=FALSE;
	}
}

int initialize(void)
{
	//function declarations
	void resize(int, int);
//	BOOL LoadGLTexture(GLuint*, TCHAR[]);
	GLuint createTexture2D(const char*);
	//code
	PIXELFORMATDESCRIPTOR pFd;
	int iPixelFormatIndex = 0;

	ZeroMemory(&pFd, sizeof(PIXELFORMATDESCRIPTOR));//init to 0
	
	//init of pFd..using only 9 other put 0 using ZeroMemory..to create small image on memory (chota Bacchan)
	pFd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pFd.nVersion = 1;  //conventionally version is 1, to block OpenGL to this version
	pFd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER; //draw on window, now support opengl (immidiate mode), ____later___
	pFd.iPixelType = PFD_TYPE_RGBA;
	pFd.cColorBits = 32; //8 bits for each R G B A in above member
	pFd.cRedBits = 8;
	pFd.cGreenBits = 8;
	pFd.cBlueBits = 8;
	pFd.cAlphaBits = 8;
	pFd.cDepthBits = 32;//new

	//get DC
	ghdc = GetDC(ghwnd); //this use to get other paint from other engine
	if (ghdc == NULL)
	{
		fprintf(gpFILE, "GetDC() failed !!\n");
		return -1;
	}

	//tell os to choose closet pixel format and match with our pixelfomrat and give us its index
	iPixelFormatIndex = ChoosePixelFormat(ghdc, &pFd);
	if (iPixelFormatIndex == 0)// when success its +ve
	{
		fprintf(gpFILE, "ChoosePixelFormat() failed !!\n");
		return -2;
	}

	//Set pixelFormat obtained from OS
	if (SetPixelFormat(ghdc, iPixelFormatIndex, &pFd) == FALSE)
	{
		fprintf(gpFILE, "SetPixelFormat() Failed !!\n");
		return -3;
	}

	//Tell WGL to give us OpenGL compatible DC from this DC (ghdc)
	//Create OpenGL contex from DC
	ghrc = wglCreateContext(ghdc);
	if (ghrc == NULL)
	{
		fprintf(gpFILE, "wglCreateContext() Failed !!\n");
		return -4;
	}
	
	//Make Rendaring contex current
	if (wglMakeCurrent(ghdc, ghrc) == FALSE)
	{
		fprintf(gpFILE, "wglMakeCurrent() Failed !!\n");
		return -5;
	}


	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //here OpenGL starts

	//Enabling depth
	
	glShadeModel(GL_SMOOTH);//light, texture etc make it smooth
	glClearDepth(1.0f);//depth buffer to 1
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);//check less than or equal to with 1.0f
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	
	//texture
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHT0);
	texture_clouds = createTexture2D("C:\\Users\\gs-3228\\Desktop\\RTR-5.0_Projects\\RTR-5.0_Projects\\Class_work\\Opengl_Assignments\\DS_demo\\clouds1.jpg");
	texture_build1 = createTexture2D("C:\\Users\\gs-3228\\Desktop\\RTR-5.0_Projects\\RTR-5.0_Projects\\Class_work\\Opengl_Assignments\\DS_demo\\buildings_1.png");
	texture_fog1 = createTexture2D("C:\\Users\\gs-3228\\Desktop\\RTR-5.0_Projects\\RTR-5.0_Projects\\Class_work\\Opengl_Assignments\\DS_demo\\fog1.png");
	texture_build2 = createTexture2D("C:\\Users\\gs-3228\\Desktop\\RTR-5.0_Projects\\RTR-5.0_Projects\\Class_work\\Opengl_Assignments\\DS_demo\\buildings2.png");
	texture_fog2 = createTexture2D("C:\\Users\\gs-3228\\Desktop\\RTR-5.0_Projects\\RTR-5.0_Projects\\Class_work\\Opengl_Assignments\\DS_demo\\fog2.png");
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&previousTime);


	resize(WIDTH, HEIGHT);
	return 0;
}
///*
void resize(int width, int height)
{
	//code
	if (height <= 0)
	{
		height = 1;
		
	}
	
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);//use GL_Projection from Matrix maths from OpenGL math lib
	glLoadIdentity();
	gluPerspective(45.0, (GLfloat)width / (GLfloat)height, 0.1f, 300.0f);

}
//*/
/*
void resize(int width, int height)
{
	//code
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (width > height)
	{
		glOrtho((GLfloat)width / (GLfloat)height * -1.0f, (GLfloat)width / (GLfloat)height * 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
	}
	else
	{
		glOrtho(-1.0f, 1.0f, (GLfloat)height / (GLfloat)width * -1.0f, (GLfloat)height / (GLfloat)width * 1.0f, -1.0f, 1.0f);
	}
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);


}

//*/

GLuint createTexture2D(const char* filePath)
{
    stbi_set_flip_vertically_on_load(true);
    int width, height, channel;
    unsigned char* data = stbi_load(filePath,&width, &height, &channel, 0);

    if(!data)
    {
        fprintf(gpFILE,"Failed To Load %s Texture\n",filePath);
        return -1;
    }	

    GLenum format = GL_RGBA;

    if(channel == STBI_grey)
        format = GL_RED;
    else if(channel == STBI_rgb)
        format = GL_RGB;
    else if(channel == STBI_rgb_alpha)
        format = GL_RGBA;

    GLuint texture;
    glPixelStorei(GL_UNPACK_ALIGNMENT,4);
    glGenTextures(1,&texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glBindTexture(GL_TEXTURE_2D,0);

    stbi_image_free(data);
    return texture;
}

BOOL LoadGLTexture(GLuint* texture, TCHAR img_src[])
{
	HBITMAP hBitmap = NULL;
	BITMAP bmp;
	BOOL bResult = FALSE;
	hBitmap = (HBITMAP)LoadImage(GetModuleHandle(NULL), img_src, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);

	if (hBitmap)
	{
		bResult = TRUE;
		GetObject(hBitmap, sizeof(BITMAP), &bmp);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
		glGenTextures(1, texture);
		glBindTexture(GL_TEXTURE_2D, *texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		//Create Texture
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, bmp.bmWidth, bmp.bmHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE, bmp.bmBits);
		glBindTexture(GL_TEXTURE_2D, 0);
		DeleteObject(hBitmap);
	}
	return bResult;
}

void display(void)
{
	//code
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	

//  gluLookAt(0.4f, 0.2f, 0.1f, 0.0f, 0.0f, -0.0f, 0.0f, 1.0f, -0.0f);
	//glTranslatef(0.0, 0.0, -2.4);
	//glScalef(0.2, 0.0, 0.0);
	
	
	switch (change)
	{
	case 1:
		glTranslatef(0.0, 0.0, -2.4);
		scene1();
		
		break;
	case 2:
	
		glTranslatef(0.0, 0.0, build1_t);
		build1_tex();
		fprintf(gpFILE, "build 1  = %f\n", build1_t);
		break;
	case 3:
		glLoadIdentity();
		glTranslatef(0.0, 0.0, fog1_t);
	    fog1_tex();
		fprintf(gpFILE, "fog t val = %f and Change = %d\n", fog1_t,change);
		break;

	case 4:
		glLoadIdentity();
		glTranslatef(0.0, 0.0, build2_t);
		build2_tex();
		fprintf(gpFILE, "build2 t val = %f\n", build2_t);

		break;
	case 5:
		glLoadIdentity();
		glTranslatef(0.0, 0.0, fog2_t);
		fog2_tex();
		fprintf(gpFILE, "fog2 t val = %f and Change = %d\n", fog2_t,change);
		break;

	default:
		change = 0;
		break;
	}
	
	glColor3f(1.0, 1.0, 1.0);

	SwapBuffers(ghdc);
	
}

void update(void)
{
	//code
	///*
	switch (change)
	{
	case 1:
		if (ot1 <= 1.0)
			ot1 += 0.007;

		oUpperY = lerp(0.0, 1.0, ot1);
		change = 2;
		break;
	case 2:
		if (ot2 <= 1.0)
		{
			ot2 += 0.001;
		}
		build1_t = lerp(-1.0, -3.1, ot2);
		change = 3;
		break;
	case 3:
		if (ot3 <= 1.0)
		{
			ot3 += 0.0003;
		}
		fog1_t = lerp(-1.0, -3.1, ot3);
		change = 4;
		break;
	case 4:
		if (ot4 <= 1.0)
		{
			ot4 += 0.0003;
		}
		build2_t = lerp(-1.0, -3.1, ot4);
		change = 4;
		break;
	case 5:
		if (ot5 <= 1.0)
		{
			ot5 += 0.0003;
		}
		fog2_t = lerp(-1.0, -3.1, ot5);
	
		break;
	default:
		break;
	}
	/*/


	/*
	if (ot1 <= 1.0)
		ot1 += 0.007;
	
	oUpperY = lerp(0.0, 1.0, ot1);


	if (oUpperY >= 1.0)
		change = 2;

	if (ot2 <= 1.0)
	{
		ot2 += 0.001;
	}
	build1_t = lerp(-1.0, -3.1, ot2);


	if (build1_t <= -3.1)
		change = 3;
		
	if (ot3 <= 1.0)
	{
		ot3 += 0.0003;
	}
	fog1_t = lerp(-1.0, -3.1, ot3);
	
	
	if (fog1_t <= -2.0)
		change = 4;
	
	if (ot4 <= 1.0)
	{
		ot4 += 0.0003;
	}
	build2_t = lerp(-1.0, -3.1, ot4);

	
	if (build2_t <= -3.0)
		change = 5;
	if (ot5 <= 1.0)
	{
		ot5 += 0.0003;
	}
	fog2_t = lerp(-1.0, -3.1, ot5);
	*/
		
	
}

void uninitialize(void)
{
	//function declarations
	void ToogleFullScreen(void);

	
	//code
	//If application is exiting in fullscreen:
	if (gbFullScreen == TRUE)
	{
		ToogleFullScreen();
		gbFullScreen = FALSE;
	}

	//Make HDC as Current contex
	if (wglGetCurrentContext() == ghrc)
	{
		wglMakeCurrent(NULL, NULL);
	}

	//Delete Rendaring Context
	if (ghrc)
	{
		wglDeleteContext(ghrc);
		ghrc = NULL;
	}

	//Relese HDC
	if (ghdc)
	{
		ReleaseDC(ghwnd, ghdc);
		ghdc = NULL;
	}


	//Destroywindow
	if (ghwnd)
	{
		DestroyWindow(ghwnd);
		ghwnd = NULL;
	}

	//close the Log file
	if (gpFILE)
	{
		fprintf(gpFILE, "Program Ended Successfully !!\n");
		fclose(gpFILE);
		gpFILE = NULL;
	}
}
