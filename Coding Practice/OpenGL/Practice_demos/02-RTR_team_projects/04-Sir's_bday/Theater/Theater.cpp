//xxxxxx OpenGL Starts.... First Code xxxxxx// 30th July
// Blue Screen code

//Common header files
#include<windows.h>//win32
#include"Window.h" //or OGL.h (if rename)
#include<stdio.h>///for file IO
#include<stdlib.h>//for exit() 
#include"Theater.h"
//#include"Poster.h"

#define ARRAY_LENGTH(arr) (sizeof(arr) / sizeof(arr[0]))

//OpenGL Header files
#include<GL/GL.h>
#include<GL/GLU.h>

//OpenGL related Global Variables
HDC ghdc = NULL;
HGLRC ghrc = NULL; //handle to GL Rendering Contex

//Macros
#define WIDTH 800
#define HEIGHT 600

//Link with OpenGL Lib
#pragma comment(lib,"openGL32.lib")
#pragma comment(lib,"glu32.lib")

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
//Entry point function

//points Array
float Harry1[] = {
9,45,
23,45,
21,47,
22,97,
23,100,
8,100,
10,97,
11,50

};
float Harry2[] = {
29,41,
40,41,
42,99,
43,102,
29,103,
32,98,
32,44

};
float Harry3[] = {
20,74,
34,68,
46,65,
20,79

};

float a1[] = {
69,59,
60,49,
50,53,
53,58,
60,55,
62,85,
69,79
};
float a2[] = {
60,64,
55,65,
49,72,
56,69


};
float a3[] = {
55,67,
59,81,
54,85,
49,72

};
float a4[] = {
56,82,
63,80,
63,84,
54,85

};

float r1[] = {
84,44,
73,50,
78,51,
78,80,
76,82,
88,82,
87,81,
85,47

};
float r2[] = {
95,56,
90,47,
84,49,
84,49,
86,49,
88,60

};
float r3[] = {
101,51,
97,50,
107,43,
110,80,
111,81,
99,83,
101,80


};
float r4[] = {
107,49,
113,46,
118,55,
112,60,
109,48

};

float y1[] = {
132,60,
122,61,
130,82,
134,72,
130,62

};
float y2[] = {
147,58,
138,57,
140,59,
123,91,
125,95

};
float y3[] = {
123,91,
125,95,
103,91,
109,90


};
float y4[] = {
107,85,
112,86,
108,89,
110,90,
110,92,
103,91

};

float p1[] = {
170,32,
176,68,
184,82,
182,32

};
float p2[] = {
170,61,
179,68,
181,100,
175,89

};
float p3[] = {
170,82,
177,89,
176,114

};
float p4[] = {
182,62,
188,68,
198,65,
200,45,
190,34,
181,37

};
float p5[] = {
183,40,
189,39,
192,44,
191,63,
183,60

};

float o1[] = {
203,63,
214,56,
222,62,
223,84,
219,89,
212,92,
202,85

};
float o2[] = {
209,65,
215,64,
216,85,
214,89,
210,87

};

float t1[] = {
230,59,
225,59,
237,44,
238,96,
230,96

};
float t2[] = {
246,101,
238,95,
228.5,95

};
float t3[] = {
235,55,
242,55,
242,58,
236,59

};

float t4[] = {
250,59,
245,59,
256,44,
257,55,
263,55,
263,58,
257,59,
258,95,
250,95

};
float t5[] = {
258,95,
265,101,
250,95

};

void ConvertToOpenGLSpace(GLfloat* array, int len, GLfloat width, GLfloat height)
{
	GLfloat oldleft = 0;
	GLfloat oldtop = 0;
	GLfloat oldBottom = height;
	GLfloat oldRight = width;

	GLfloat newLeft = -1.0f;
	GLfloat newTop = 1.0f;
	GLfloat newBottom = -1.0f;
	GLfloat newRight = 1.0f;
	fprintf(gpFILE, "%lld", ARRAY_LENGTH(Harry1));
	
	for (int i = 0; i < len; i += 2)
	{
		GLfloat oldx = array[i];
		GLfloat oldy = array[i + 1];

		GLfloat newx = newLeft + (oldx - oldleft) / (oldRight - oldleft) * (newRight - newLeft);
		GLfloat newy = newTop + (oldy - oldtop) / (oldBottom - oldtop) * (newBottom - newTop);

		array[i] = newx;
		array[i + 1] = newy;
	}

}


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
		TEXT("HVS:Point_assignment"),
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
	case WM_ERASEBKGND:
		return 0;
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

	//Set the Clear color of Window to Blue
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //here OpenGL starts

	ConvertToOpenGLSpace(Harry1, ARRAY_LENGTH(Harry1), 256, 256);
	ConvertToOpenGLSpace(Harry2, ARRAY_LENGTH(Harry2), 256, 256);
	ConvertToOpenGLSpace(Harry3, ARRAY_LENGTH(Harry3), 256, 256);
	
	ConvertToOpenGLSpace(a1, ARRAY_LENGTH(a1), 256, 256);
	ConvertToOpenGLSpace(a2, ARRAY_LENGTH(a2), 256, 256);
	ConvertToOpenGLSpace(a3, ARRAY_LENGTH(a3), 256, 256);
	ConvertToOpenGLSpace(a4, ARRAY_LENGTH(a4), 256, 256);
	
	ConvertToOpenGLSpace(r1, ARRAY_LENGTH(r1), 256, 256);
	ConvertToOpenGLSpace(r2, ARRAY_LENGTH(r2), 256, 256); 
	ConvertToOpenGLSpace(r3, ARRAY_LENGTH(r3), 256, 256); 
	ConvertToOpenGLSpace(r4, ARRAY_LENGTH(r4), 256, 256); 
	
	ConvertToOpenGLSpace(y1, ARRAY_LENGTH(y1), 256, 256); 
	ConvertToOpenGLSpace(y2, ARRAY_LENGTH(y2), 256, 256); 
	ConvertToOpenGLSpace(y3, ARRAY_LENGTH(y3), 256, 256); 
	ConvertToOpenGLSpace(y4, ARRAY_LENGTH(y4), 256, 256); 
	
	ConvertToOpenGLSpace(p1, ARRAY_LENGTH(p1), 256, 256); 
	ConvertToOpenGLSpace(p2, ARRAY_LENGTH(p2), 256, 256); 
	ConvertToOpenGLSpace(p3, ARRAY_LENGTH(p3), 256, 256); 
	ConvertToOpenGLSpace(p4, ARRAY_LENGTH(p4), 256, 256); 
	ConvertToOpenGLSpace(p5, ARRAY_LENGTH(p5), 256, 256); 
	
	ConvertToOpenGLSpace(o1, ARRAY_LENGTH(o1), 256, 256); 
	ConvertToOpenGLSpace(o2, ARRAY_LENGTH(o2), 256, 256); 

	ConvertToOpenGLSpace(t1, ARRAY_LENGTH(t1), 256, 256); 
	ConvertToOpenGLSpace(t2, ARRAY_LENGTH(t2), 256, 256); 
	ConvertToOpenGLSpace(t3, ARRAY_LENGTH(t3), 256, 256); 
	ConvertToOpenGLSpace(t4, ARRAY_LENGTH(t4), 256, 256); 
	ConvertToOpenGLSpace(t5, ARRAY_LENGTH(t5), 256, 256); 

	resize(WIDTH, HEIGHT);
	return 0;
}

/*
void resize(int width, int height)
{
	//code
	if (height <= 0)
	{
		height = 1;
		
	}
	
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

}
*/

void resize(int width, int height)
{
	//code
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

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

}


void movie_name()
{
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	for (int i = 0; i < ARRAY_LENGTH(Harry1); i = i + 2)
	{
		glVertex2f(Harry1[i], Harry1[i + 1]);
	}
	glEnd();


	glBegin(GL_POLYGON);
	for (int i = 0; i < ARRAY_LENGTH(Harry2); i = i + 2)
	{
		glVertex2f(Harry2[i], Harry2[i + 1]);
	}
	glEnd();

	glBegin(GL_POLYGON);
	for (int i = 0; i < ARRAY_LENGTH(Harry3); i = i + 2)
	{
		glVertex2f(Harry3[i], Harry3[i + 1]);
	}
	glEnd();

	//---------------A---
	glBegin(GL_POLYGON);
	for (int i = 0; i < ARRAY_LENGTH(a1); i = i + 2)
	{
		glVertex2f(a1[i], a1[i + 1]);
	}
	glEnd();

	glBegin(GL_POLYGON);
	for (int i = 0; i < ARRAY_LENGTH(a2); i = i + 2)
	{
		glVertex2f(a2[i], a2[i + 1]);
	}
	glEnd();

	glBegin(GL_POLYGON);
	for (int i = 0; i < ARRAY_LENGTH(a3); i = i + 2)
	{
		glVertex2f(a3[i], a3[i + 1]);
	}
	glEnd();

	glBegin(GL_POLYGON);
	for (int i = 0; i < ARRAY_LENGTH(a4); i = i + 2)
	{
		glVertex2f(a4[i], a4[i + 1]);
	}
	glEnd();

	//-----------R----------
	glBegin(GL_POLYGON);
	for (int i = 0; i < ARRAY_LENGTH(r1); i = i + 2)
	{
		glVertex2f(r1[i], r1[i + 1]);
	}
	glEnd();

	glBegin(GL_POLYGON);
	for (int i = 0; i < ARRAY_LENGTH(r2); i = i + 2)
	{
		glVertex2f(r2[i], r2[i + 1]);
	}
	glEnd();

	glBegin(GL_POLYGON);
	for (int i = 0; i < ARRAY_LENGTH(r3); i = i + 2)
	{
		glVertex2f(r3[i], r3[i + 1]);
	}
	glEnd();

	glBegin(GL_POLYGON);
	for (int i = 0; i < ARRAY_LENGTH(r4); i = i + 2)
	{
		glVertex2f(r4[i], r4[i + 1]);
	}
	glEnd();

	//------------------Y -------------
	glBegin(GL_POLYGON);
	for (int i = 0; i < ARRAY_LENGTH(y1); i = i + 2)
	{
		glVertex2f(y1[i], y1[i + 1]);
	}
	glEnd();
	
	glBegin(GL_POLYGON);
	for (int i = 0; i < ARRAY_LENGTH(y2); i = i + 2)
	{
		glVertex2f(y2[i], y2[i + 1]);
	}
	glEnd();

	glBegin(GL_POLYGON);
	for (int i = 0; i < ARRAY_LENGTH(y3); i = i + 2)
	{
		glVertex2f(y3[i], y3[i + 1]);
	}
	glEnd();

	glBegin(GL_POLYGON);
	for (int i = 0; i < ARRAY_LENGTH(y4); i = i + 2)
	{
		glVertex2f(y4[i], y4[i + 1]);
	}
	glEnd();

	//-------------P --------
	glBegin(GL_POLYGON);
	for (int i = 0; i < ARRAY_LENGTH(p1); i = i + 2)
	{
		glVertex2f(p1[i], p1[i + 1]);
	}
	glEnd();

	glBegin(GL_POLYGON);
	for (int i = 0; i < ARRAY_LENGTH(p2); i = i + 2)
	{
		glVertex2f(p2[i], p2[i + 1]);
	}
	glEnd();

	glBegin(GL_POLYGON);
	for (int i = 0; i < ARRAY_LENGTH(p3); i = i + 2)
	{
		glVertex2f(p3[i], p3[i + 1]);
	}
	glEnd();

	glBegin(GL_POLYGON);
	for (int i = 0; i < ARRAY_LENGTH(p4); i = i + 2)
	{
		glVertex2f(p4[i], p4[i + 1]);
	}
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	for (int i = 0; i < ARRAY_LENGTH(p5); i = i + 2)
	{
		glVertex2f(p5[i], p5[i + 1]);
	}
	glEnd();

	//----------- O ----
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	for (int i = 0; i < ARRAY_LENGTH(o1); i = i + 2)
	{
		glVertex2f(o1[i], o1[i + 1]);
	}
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	for (int i = 0; i < ARRAY_LENGTH(o2); i = i + 2)
	{
		glVertex2f(o2[i], o2[i + 1]);
	}
	glEnd();


	//---------- T -----
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	for (int i = 0; i < ARRAY_LENGTH(t1); i = i + 2)
	{
		glVertex2f(t1[i], t1[i + 1]);
	}
	glEnd();

	glBegin(GL_POLYGON);
	for (int i = 0; i < ARRAY_LENGTH(t2); i = i + 2)
	{
		glVertex2f(t2[i], t2[i + 1]);
	}
	glEnd();

	glBegin(GL_POLYGON);
	for (int i = 0; i < ARRAY_LENGTH(t3); i = i + 2)
	{
		glVertex2f(t3[i], t3[i + 1]);
	}
	glEnd();

	glBegin(GL_POLYGON);
	for (int i = 0; i < ARRAY_LENGTH(t4); i = i + 2)
	{
		glVertex2f(t4[i], t4[i + 1]);
	}
	glEnd();

	glBegin(GL_POLYGON);
	for (int i = 0; i < ARRAY_LENGTH(t5); i = i + 2)
	{
		glVertex2f(t5[i], t5[i + 1]);
	}
	glEnd();

}


void display(void)
{
	//code
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();	
	//glScalef(1.0, 1.0, 0.0);
	//mainScreen();
	//Hall();
	movie_name();
	
	
	//VerticalLines();
	//HorizontalLines();
	SwapBuffers(ghdc);
}

void update(void)
{
	//code

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
