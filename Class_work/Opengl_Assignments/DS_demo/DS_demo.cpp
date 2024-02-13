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

//textre vars
GLuint texture_clouds = 0;

//update variables
GLfloat oUpperY = 0.0;
GLfloat oLowerY = 0.0;
GLfloat ot1 = 0.0;
GLfloat ot2 = 0.0;
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
	texture_clouds = createTexture2D("C:\\Users\\lenovo\\Desktop\\RTR_5_Course_Programming\\RTR-5.0_Projects\\Class_work\\Opengl_Assignments\\DS_demo\\clouds1.bmp");
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

void VerticalLines()
{
	float xPt1=0.025f;
	float xPt2=-0.025f;

	glLineWidth(3.2);
	glBegin(GL_LINES);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, -1.0, 0.0);
	glEnd();

	glColor3f(0.0, 0.0, 1.0);
	for (int i = 1; i <= 40; i++) 
	{
		if (i % 5 == 0) 
		{
			glLineWidth(2.2f);
		}
		else 
		{
			glLineWidth(1.0f);
		}

		glBegin(GL_LINES);
		
		glVertex2f(xPt1, 1.0);
		glVertex2f(xPt1, -1.0);
		
		xPt1 += 0.025;
		glEnd();
	}

	glColor3f(0.0, 0.0, 1.0);
	for (int j = 1; j <= 40; j++) 
	{
		if (j % 5 == 0) 
		{
			glLineWidth(2.2);
		}
		else
		{
			glLineWidth(1.0);
		}
			
		glBegin(GL_LINES);
		glVertex2f(xPt2, 1.0);
		glVertex2f(xPt2, -1.0);
		
		xPt2 -= 0.025f;
		glEnd();
	}
}

void HorizontalLines()
{
	float yPt1 = 0.025f;
	float yPt2 = -0.025f;

	glLineWidth(3.2);
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(-1.0, 0.0, 0.0);
	glVertex3f(1.0, 0.0, 0.0);
	glColor3f(0.0, 0.0, 1.0);
	glEnd();

	glColor3f(0.0, 0.0, 1.0);
	for (int i = 1; i <= 40; i++)
	{
		if (i % 5 == 0)
			glLineWidth(2.2);
		else
			glLineWidth(1.0);

		glBegin(GL_LINES);
		glVertex2f(-1.0f, yPt1);
		glVertex2f(1.0f, yPt1);

		yPt1 += 0.025;
		glEnd();
	}
	

	glColor3f(0.0, 0.0, 1.0);
	for (int j = 1; j <= 40; j++)
	{
		if (j % 5 == 0)
			glLineWidth(2.2);
		else
			glLineWidth(1.0);
		glBegin(GL_LINES);
		glVertex2f(-1.0f, yPt2);
		glVertex2f(1.0f, yPt2);

		yPt2 -= 0.025f;
		glEnd();
	}
}

void clouds_tex()
{
	glBindTexture(GL_TEXTURE_2D, texture_clouds);

	/*
	glBegin(GL_POLYGON);
	glVertex2f(1.0, 1.0);
	glVertex2f(-1.0, 1.0);
	glVertex2f(-1.0, -1.0);
	glVertex2f(1.0, -1.0);
	glEnd();
	*/
	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 1.0);//TRight
	glVertex2f(1.0, 1.0);

	glTexCoord2f(0.0, 1.0);
	glVertex2f(-1.0, 1.0);

	glTexCoord2f(0.0, 0.0);
	glVertex2f(-1.0, -1.0);

	glTexCoord2f(1.0, 0.0);
	glVertex2f(1.0, -1.0);

	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);

}

void opening()
{
	//opening, upper and lower
	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(0.0, oUpperY, 0.0);
	glBegin(GL_QUADS);
		glVertex2f(2.0, 2.0);
		glVertex2f(-2.0, 2.0);
		glVertex2f(-2.0, 0.0);
		glVertex2f(2.0, 0.0);
	glEnd();

	glPopMatrix();

	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(0.0, (-1) * oUpperY, 0.0);
	glBegin(GL_QUADS);
		glVertex2f(2.0, 0.0);
		glVertex2f(-2.0, 0.0);
		glVertex2f(-2.0, -2.0);
		glVertex2f(2.0, -2.0);
	glEnd();
	
}

void room()
{
	//floor
	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_QUADS);
		glVertex2f(2.0, -0.5);
		glVertex2f(-2.0, -0.5);
		glVertex2f(-2.0, -1.875);
		glVertex2f(2.0, -1.875);
	glEnd();

	//right wall
	glColor3f(0.3, 0.3, 0.3);
	glBegin(GL_QUADS);
		glVertex2f(2.0, 2.0);//upper right
		glVertex2f(0.625, 2.0);
		glVertex2f(0.625, -0.5);
		glVertex2f(2.0, -0.5);
	glEnd();

	//left wall
	glColor3f(0.3, 0.3, 0.3);
	glBegin(GL_QUADS);
		glVertex2f(-0.625, 2.0);//upper right
		glVertex2f(-2.0, 2.0);
		glVertex2f(-2.0, -0.5);
		glVertex2f(-0.625, -0.5);
	glEnd();


	//Gallary glass
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glColor4f(0.5, 0.5, 0.5, 0.4);
	glBegin(GL_QUADS);
		glVertex2f(0.625, -0.125);//upper right
		glVertex2f(-0.625, -0.125);
		glVertex2f(-0.625, -0.5);
		glVertex2f(0.625, -0.5);
	glEnd();
	glEnable(GL_BLEND);

	//glass border
	glEnable(GL_LINE_SMOOTH);
	glLineWidth(3.0);
	glColor3f(0.2, 0.2, 0.2);
	glBegin(GL_LINES);
		glVertex2f(0.625, -0.125);
		glVertex2f(-0.625, -0.125);
	glEnd();
	glDisable(GL_LINE_SMOOTH);

}

void watch_border(float cx, float cy, float r, int num_segments, GLfloat t1)
{
	// watch border

	glEnable(GL_LINE_SMOOTH);
	glLineWidth(4.0);
	glColor3f(1.0f * t1, 0.0f * t1, 0.0f * t1);
	glBegin(GL_LINE_LOOP);
	glVertex2f(cx, cy);
	for (int i = 0; i <= num_segments; ++i)
	{
		float theta = 2.0f * 3.1415926f * (float)i / (float)num_segments;
		float x = r * cosf(theta);
		float y = r * sinf(theta);
		glVertex2f(cx + x, cy + y);
	}
	glEnd();
	glDisable(GL_LINE_SMOOTH);
}

void watch_border(float cx, float cy, float r, int num_segments)
{
	// watch border

	glEnable(GL_LINE_SMOOTH);
	glLineWidth(4.0);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2f(cx, cy);
	for (int i = 0; i <= num_segments; ++i)
	{
		float theta = 2.0f * 3.1415926f * (float)i / (float)num_segments;
		float x = r * cosf(theta);
		float y = r * sinf(theta);
		glVertex2f(cx + x, cy + y);
	}
	glEnd();
	glDisable(GL_LINE_SMOOTH);
}

void watch_on_Wall(float cx, float cy, float r, int num_segments)
{
	// Watch background
	glColor3f(0.8f, 0.8f , 0.8f);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(cx, cy);
	float theta;
	for (int i = 0; i <= num_segments; ++i)
	{
		theta = 2.0f * 3.1415926f * (float)i / (float)num_segments;
		float x = r * cosf(theta);
		float y = r * sinf(theta);
		glVertex2f(cx + x, cy + y);
	}
	glEnd();

	
	// Moving clock hands --------------
	//  Moving clock hands --------------
	glColor3f(0.0, 0.0, 0.0);
	glPointSize(1.0);
	glLineWidth(1.5);
	glBegin(GL_LINES);

	glVertex2f(cx, cy);
	glVertex2f(cx + 0.06, cy + 0.02);

	glEnd();
	glColor3f(0.0, 0.0, 0.0);
	glPointSize(1.0);
	glLineWidth(1.5);
	glBegin(GL_LINES);

	glVertex2f(cx, cy);
	glVertex2f(cx + 0.05,cy + 0.05);

	glEnd();

}

void display(void)
{
	//code
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	

//  gluLookAt(0.4f, 0.2f, 0.1f, 0.0f, 0.0f, -0.0f, 0.0f, 1.0f, -0.0f);
	glTranslatef(0.0, 0.0, -2.4);
	//glScalef(0.2, 0.0, 0.0);
	clouds_tex();
	//glLoadIdentity();
	room();
	watch_border(1.0, 0.5, 0.1, 100);
	watch_on_Wall(1.0, 0.5, 0.1, 100);

	//opening();
	
	/*
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(0.1, 0.1);
	glVertex2f(-0.1, 0.1);
	glVertex2f(-0.1, -0.1);
	glVertex2f(0.1, -0.1);
	glEnd();
	*/
	glLoadIdentity();
	glTranslatef(0.0,0.0,-2.0);

	/*
	HorizontalLines();
	VerticalLines();
	//*/

	glColor3f(1.0, 1.0, 1.0);

	SwapBuffers(ghdc);
	
}

void update(void)
{
	//code
	if (ot1 <= 1.0)
	{
		ot1 += 0.0008;
	}
	
	oUpperY = lerp(0.0, 1.8, ot1);
	
	
	
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
