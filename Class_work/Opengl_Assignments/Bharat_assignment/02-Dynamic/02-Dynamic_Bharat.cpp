//xxxxxx OpenGL Starts.... First Code xxxxxx// 30th July
// Blue Screen code

//Common header files
#include<windows.h>//win32
#include"Window.h" //or OGL.h (if rename)
#include<stdio.h>///for file IO
#include<stdlib.h>//for exit() 

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

//color veriables
float r = 0.82;
float g = 0.82;
float b = 0.82;

//lerp values
float tBx = -1.0;
float tHx = 1.6;
float tHy = 1.6;
float tA1x = -1.6;
float tA1y = -1.6;
float tRx = 1.6;
float tRy = 1.6;
float tA2x = 1.6;
float tA2y = -1.6;
float tTx = 1.4;
float t = 0.0;
float t2 = 0.0;
//for plane

float p1 = -1.6;
float p2x = -1.9;
float p2y = 1.5;
float p3x = -1.9;
float p3y = -1.5;
float p2Angle;
float p3Angle;
//int flag = 0;
int year;


float lerp(float start, float end, float t)
{
	return start + t * (end - start);
}

GLUquadric* quadric = NULL;

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
		resize(LOWORD(lParam), HIWORD(lParam));
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
		gbFullScreen = TRUE;
	}
	else
	{
		SetWindowPlacement(ghwnd, &wpPrev);
		SetWindowLong(ghwnd, GWL_STYLE, dwstyle | WS_OVERLAPPEDWINDOW);
		SetWindowPos(ghwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_FRAMECHANGED);
		ShowCursor(TRUE);
		gbFullScreen = FALSE;
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
	
	//init quadric
	//quadric = gluNewQuadric();

	resize(WIDTH, HEIGHT);
	return 0;
}

void resize1(int width, int height)
{
	//code
	if (height <= 0)
	{
		height = 1;

	}

	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);//use GL_Projection from Matrix maths from OpenGL math lib
	glLoadIdentity();
	gluPerspective(40.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);

}


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


void B()
{
	glLoadIdentity();
	glTranslatef(tBx, 0.0f, -1.0f);
	glScalef(0.7, 0.7, 0.0);
	glBegin(GL_POLYGON);
	glColor3f(r, g, b);
		glVertex2f(0.25, 0.175);
		glVertex2f(0.175, 0.25);
		glVertex2f(-0.25, 0.25);
		glVertex2f(-0.25, 0.0);
		glVertex2f(0.25, 0.0);
	
	glEnd();
	glBegin(GL_POLYGON);
		glVertex2f(0.25, 0.00);
		glVertex2f(-0.25, 0.00);
		glVertex2f(-0.25, -0.25);
		glVertex2f(0.175, -0.25);
		glVertex2f(0.25, -0.175);
	glEnd();

	//black part
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON); //upper
	glVertex2f(0.175, 0.125);
	glVertex2f(0.125, 0.175);
	glVertex2f(-0.175, 0.175);
	glVertex2f(-0.175, 0.0325);
	glVertex2f(0.175, 0.0325);
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON); //upper
	glVertex2f(0.175, -0.0325);
	glVertex2f(-0.175, -0.0325);
	glVertex2f(-0.175, -0.175);
	glVertex2f(0.125, -0.175);
	glVertex2f(0.175, -0.125);
	glEnd();

	//------------

}

void H()
{
	glLoadIdentity();
	glTranslatef(tHx, tHy, -1.0f);
	glScalef(0.7, 0.7, 0.0);
	glBegin(GL_POLYGON);
	glColor3f(r, g, b);
	glVertex2f(0.25, 0.25);
		glVertex2f(-0.25, 0.25);
		glVertex2f(-0.25, 0.0);
		glVertex2f(0.25, 0.0);

	glEnd();
	glBegin(GL_POLYGON);
		glVertex2f(0.25, 0.00);
		glVertex2f(-0.25, 0.00);
		glVertex2f(-0.25, -0.25);
		glVertex2f(0.25, -0.25);
	glEnd();

	//black box
	//black part
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON); //upper
		glVertex2f(0.175, 0.25);
		glVertex2f(-0.175, 0.25);
		glVertex2f(-0.175, 0.0325);
		glVertex2f(0.175, 0.0325);
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON); //upper
		glVertex2f(0.175, -0.0325);
		glVertex2f(-0.175, -0.0325);
		glVertex2f(-0.175, -0.25);
		glVertex2f(0.175, -0.25);
	glEnd();


}

void A1()
{
	glLoadIdentity();
	glTranslatef(tA1x, tA1y, -1.0f);
	glScalef(0.7, 0.7, 0.0);

	glBegin(GL_POLYGON);
	glColor3f(r, g, b);
	glVertex2f(0.25, 0.25);
	glVertex2f(-0.25, 0.25);
	glVertex2f(-0.25, 0.0);
	glVertex2f(0.25, 0.0);

	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f(0.25, 0.00);
	glVertex2f(-0.25, 0.00);
	glVertex2f(-0.25, -0.25);
	glVertex2f(0.25, -0.25);
	glEnd();

	//black part
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);//left
		glVertex2f(0.25, 0.25);
		glVertex2f(0.025, 0.25);
		glVertex2f(0.25, -0.25);
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);//right
		glVertex2f(-0.25, 0.25);
		glVertex2f(-0.025, 0.25);
		glVertex2f(-0.25, -0.25);
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);//lower part
		glVertex2f(0.075, -0.0325);
		glVertex2f(-0.075, -0.0325);
		glVertex2f(-0.175, -0.25);
		glVertex2f(0.175, -0.25);
	glEnd();
	
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);//upper part
		glVertex2f(0.01, 0.150);
		glVertex2f(-0.01, 0.150);
		glVertex2f(-0.05, 0.0325);
		glVertex2f(0.05, 0.0325);
		//glVertex2f(0.175, -0.25);
	glEnd();

}

void R()
{
	glLoadIdentity();
	glTranslatef(tRx, tRy, -1.0f);
	glScalef(0.7, 0.7, 0.0);

	glBegin(GL_POLYGON);
	glColor3f(r, g, b);
		glVertex2f(0.25, 0.175);
		glVertex2f(0.175, 0.25);
		glVertex2f(-0.25, 0.25);
		glVertex2f(-0.25, 0.0);
		glVertex2f(0.25, 0.0);
	glEnd();

	glColor3f(r, g, b);
	glBegin(GL_POLYGON);
		glVertex2f(0.25, 0.00);
		glVertex2f(-0.25, 0.00);
		glVertex2f(-0.25, -0.25);
		glVertex2f(0.25, -0.25);
	glEnd();

	//black part
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON); //upper
	glVertex2f(0.175, 0.125);
	glVertex2f(0.125, 0.175);
	glVertex2f(-0.175, 0.175);
	glVertex2f(-0.175, 0.0325);
	glVertex2f(0.125, 0.0325);
	glVertex2f(0.175, 0.075);
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
		glVertex2f(0.175, -0.25);
		glVertex2f(-0.175, -0.0325);
		glVertex2f(-0.175, -0.25);
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(0.25, -0.25);
	glVertex2f(0.25, -0.0325);
	glVertex2f(-0.075, -0.0325);
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(0.25, -0.0325);
	glVertex2f(0.25, 0.025);
	glVertex2f(0.175, -0.0325);
	glEnd();


}

void A2()
{
	glLoadIdentity();
	glTranslatef(tA2x, tA2y, -1.0f);
	glScalef(0.7, 0.7, 0.0);

	glBegin(GL_POLYGON);
	glColor3f(r, g, b);
		glVertex2f(0.25, 0.25);
		glVertex2f(-0.25, 0.25);
		glVertex2f(-0.25, 0.0);
		glVertex2f(0.25, 0.0);
	glEnd();

	glColor3f(r, g, b);
	glBegin(GL_POLYGON);
	glVertex2f(0.25, 0.00);
	glVertex2f(-0.25, 0.00);
	glVertex2f(-0.25, -0.25);
	glVertex2f(0.25, -0.25);
	glEnd();

	//black part
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);//left
	glVertex2f(0.25, 0.25);
	glVertex2f(0.025, 0.25);
	glVertex2f(0.25, -0.25);
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);//right
	glVertex2f(-0.25, 0.25);
	glVertex2f(-0.025, 0.25);
	glVertex2f(-0.25, -0.25);
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);//lower part
	glVertex2f(0.075, -0.0325);
	glVertex2f(-0.075, -0.0325);
	glVertex2f(-0.175, -0.25);
	glVertex2f(0.175, -0.25);
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);//upper part
	glVertex2f(0.01, 0.150);
	glVertex2f(-0.01, 0.150);
	glVertex2f(-0.05, 0.0325);
	glVertex2f(0.05, 0.0325);
	//glVertex2f(0.175, -0.25);
	glEnd();

}

void T()
{
	glLoadIdentity();
	glTranslatef(tTx, 0.0f, -1.0f);
	glScalef(0.7, 0.7, 0.0);

	glBegin(GL_POLYGON);
	glColor3f(r, g, b);
		glVertex2f(0.25, 0.25);
		glVertex2f(-0.25, 0.25);
		glVertex2f(-0.25, 0.0);
		glVertex2f(0.25, 0.0);
	glEnd();


	glColor3f(r, g, b);
	glBegin(GL_POLYGON);
		glVertex2f(0.25, 0.00);
		glVertex2f(-0.25, 0.00);
		glVertex2f(-0.25, -0.25);
		glVertex2f(0.25, -0.25);
	glEnd();


	//black part
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
		glVertex2f(0.25, 0.175);
		glVertex2f(0.0325, 0.175);
		glVertex2f(0.0325, -0.250);
		glVertex2f(0.25, -0.250);
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
		glVertex2f(-0.0325, 0.175);
		glVertex2f(-0.25, 0.175);
		glVertex2f(-0.25, -0.250);
		glVertex2f(-0.0325, -0.250);

	glEnd();


}

void VerticalLines()
{
	float xPt1 = 0.025f;
	float xPt2 = -0.025f;

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

void plane1()
{
	glLoadIdentity();
	glTranslatef(p1, 0.0, 0.0);
	glScalef(0.45, 0.45, 0.45);
	glRotatef(90, 0.0, 0.0, -1.0);
	//exaust
	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_POLYGON);
		glVertex2f(0.025, -0.25);
		glVertex2f(-0.025, -0.25);
		glVertex2f(-0.025, -0.275);
		glVertex2f(0.025, -0.275);
	glEnd();
	//exaust fire
	glColor3f(1.0, 0.5, 0.0);
	glBegin(GL_TRIANGLES);
		glVertex2f(-0.025, -0.275);
		glVertex2f(0.025, -0.275);
		glVertex2f(0.0, -0.375);
	glEnd();



	glBegin(GL_POLYGON);//front
	glColor3f(0.3, 0.3, 0.3);
		glVertex2f(0.0, 0.45);
	glColor3f(0.5, 0.5, 0.5);
		glVertex2f(-0.075, 0.0);
		glVertex2f(0.075, 0.0);
	glEnd();

	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_POLYGON);//left wing
		glVertex2f(0.0, 0.125);
	glColor3f(0.3, 0.3, 0.3);
		glVertex2f(0.0, -0.125);
	glColor3f(0.5, 0.5, 0.5);
		glVertex2f(0.375, -0.175);
		glVertex2f(0.375, -0.125);
	glEnd();

	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_POLYGON);//right wing
		glVertex2f(0.0, 0.125);
	glColor3f(0.3, 0.3, 0.3);
		glVertex2f(0.0, -0.125);
		glVertex2f(-0.375, -0.175);
	glColor3f(0.5, 0.5, 0.5);
		glVertex2f(-0.375, -0.125);
	glEnd();


	glBegin(GL_POLYGON);//lower right
	glColor3f(0.3, 0.3, 0.3);
		glVertex2f(0.0, -0.110);
		glVertex2f(0.0, -0.25);
	glColor3f(0.5, 0.5, 0.5);
		glVertex2f(0.25, -0.275);
		glVertex2f(0.25, -0.25);
	glEnd();

	glBegin(GL_POLYGON);//lower left
	glColor3f(0.3, 0.3, 0.3);
		glVertex2f(0.0, -0.110);
		glVertex2f(0.0, -0.25);
	glColor3f(0.5, 0.5, 0.5);
		glVertex2f(-0.25, -0.275);
		glVertex2f(-0.25, -0.25);
	glEnd();

}

void plane2()
{
	glLoadIdentity();
	
	glTranslatef(p2x, p2y, 0.0);
	glScalef(0.45, 0.45, 0.45);
	glRotatef(p2Angle, 0.0, 0.0, -1.0);
	//exaust
	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_POLYGON);
	glVertex2f(0.025, -0.25);
	glVertex2f(-0.025, -0.25);
	glVertex2f(-0.025, -0.275);
	glVertex2f(0.025, -0.275);
	glEnd();
	//exaust fire
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_TRIANGLES);
	glVertex2f(-0.025, -0.275);
	glVertex2f(0.025, -0.275);
	glVertex2f(0.0, -0.375);
	glEnd();



	glBegin(GL_POLYGON);//front
	glColor3f(0.3, 0.3, 0.3);
	glVertex2f(0.0, 0.45);
	glColor3f(0.5, 0.5, 0.5);
	glVertex2f(-0.075, 0.0);
	glVertex2f(0.075, 0.0);
	glEnd();

	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_POLYGON);//left wing
	glVertex2f(0.0, 0.125);
	glColor3f(0.3, 0.3, 0.3);
	glVertex2f(0.0, -0.125);
	glColor3f(0.5, 0.5, 0.5);
	glVertex2f(0.375, -0.175);
	glVertex2f(0.375, -0.125);
	glEnd();

	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_POLYGON);//right wing
	glVertex2f(0.0, 0.125);
	glColor3f(0.3, 0.3, 0.3);
	glVertex2f(0.0, -0.125);
	glVertex2f(-0.375, -0.175);
	glColor3f(0.5, 0.5, 0.5);
	glVertex2f(-0.375, -0.125);
	glEnd();


	glBegin(GL_POLYGON);//lower right
	glColor3f(0.3, 0.3, 0.3);
	glVertex2f(0.0, -0.110);
	glVertex2f(0.0, -0.25);
	glColor3f(0.5, 0.5, 0.5);
	glVertex2f(0.25, -0.275);
	glVertex2f(0.25, -0.25);
	glEnd();

	glBegin(GL_POLYGON);//lower left
	glColor3f(0.3, 0.3, 0.3);
	glVertex2f(0.0, -0.110);
	glVertex2f(0.0, -0.25);
	glColor3f(0.5, 0.5, 0.5);
	glVertex2f(-0.25, -0.275);
	glVertex2f(-0.25, -0.25);
	glEnd();



}

void plane3()
{
	glLoadIdentity();
	glTranslatef(p3x, p3y, 0.0);
	glScalef(0.45, 0.45, 0.45);
	glRotatef(p3Angle, 0.0, 0.0, -1.0);
	//exaust
	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_POLYGON);
	glVertex2f(0.025, -0.25);
	glVertex2f(-0.025, -0.25);
	glVertex2f(-0.025, -0.275);
	glVertex2f(0.025, -0.275);
	glEnd();
	//exaust fire
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_TRIANGLES);
	glVertex2f(-0.025, -0.275);
	glVertex2f(0.025, -0.275);
	glVertex2f(0.0, -0.375);
	glEnd();



	glBegin(GL_POLYGON);//front
	glColor3f(0.3, 0.3, 0.3);
	glVertex2f(0.0, 0.45);
	glColor3f(0.5, 0.5, 0.5);
	glVertex2f(-0.075, 0.0);
	glVertex2f(0.075, 0.0);
	glEnd();

	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_POLYGON);//left wing
	glVertex2f(0.0, 0.125);
	glColor3f(0.3, 0.3, 0.3);
	glVertex2f(0.0, -0.125);
	glColor3f(0.5, 0.5, 0.5);
	glVertex2f(0.375, -0.175);
	glVertex2f(0.375, -0.125);
	glEnd();

	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_POLYGON);//right wing
	glVertex2f(0.0, 0.125);
	glColor3f(0.3, 0.3, 0.3);
	glVertex2f(0.0, -0.125);
	glVertex2f(-0.375, -0.175);
	glColor3f(0.5, 0.5, 0.5);
	glVertex2f(-0.375, -0.125);
	glEnd();


	glBegin(GL_POLYGON);//lower right
	glColor3f(0.3, 0.3, 0.3);
	glVertex2f(0.0, -0.110);
	glVertex2f(0.0, -0.25);
	glColor3f(0.5, 0.5, 0.5);
	glVertex2f(0.25, -0.275);
	glVertex2f(0.25, -0.25);
	glEnd();

	glBegin(GL_POLYGON);//lower left
	glColor3f(0.3, 0.3, 0.3);
	glVertex2f(0.0, -0.110);
	glVertex2f(0.0, -0.25);
	glColor3f(0.5, 0.5, 0.5);
	glVertex2f(-0.25, -0.275);
	glVertex2f(-0.25, -0.25);
	glEnd();

}

void display(void)
{
	//code
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//glLoadIdentity();

	//VerticalLines();
	//HorizontalLines();

//	plane();
	
	B();
	H();
	A1();
	R();
	A2();
	T();
	
	plane1();
	plane2();
	plane3();


	SwapBuffers(ghdc);
}

void update(void)
{

	static int flag = 0;
	//code
	if (t <= 1.0)
	{
	 	t += 0.00009;
	}

	
	tBx = lerp(-1.5, -1.0, t);
	tHx = lerp(-1.5, -0.6, t);
	tHy = lerp(1.5, 0.0, t);
	tA1x = lerp(1.5, -0.2, t);
	tA1y = lerp(-1.5, 0.0, t);
	tRx = lerp(1.6, 0.2, t);
	tRy = lerp(1.6, 0.0, t);
	tA2x = lerp(1.6, 0.6, t);
	tA2y = lerp(1.6, 0.0, t);
	tTx = lerp(1.9, 1.0, t);
	
	if (t2 <= 1.0)
	{
		t2 += 0.00006;
	}

	//if()

	//fprintf(gpFILE, "tBx = %f", tBx);
	
	if (tBx <= (-1.0));
	{
		p1 = lerp(-1.9, -1.2, t2);
		p2x = lerp(-1.9, -1.2, t2);
		p2y = lerp(1.4, 0.0, t2);
		p3x = lerp(-1.9, -1.2, t2);
		p3y = lerp(-1.4, 0.0, t2);
	}
    
	/*
	p1 = lerp(-1.7, -1.2, t);
	p2x = lerp(-1.9, -1.2, t);
	p2y = lerp(1.4, 0.0, t);
	p3x = lerp(-1.9, -1.2, t);
	p3y = lerp(-1.4, 0.0, t);
	*/

	if (p2y > 0.0)
		p2Angle = 140.0;
	else
		p2Angle = 90.0;

	if (p3y > 0.0)
	{
		p3Angle = 90.0;
	}
	else
		p3Angle = 40.0;


	//year = (year + 0) % 360;

	/*
	if (flag == 0)
	{
		tBx = lerp(-1.5, -1.0, t);
		t = 0.0;
     
	}
	else if (flag == 1)
	{
		tHx = lerp(-1.5, -0.6, t);
		tHy = lerp(1.5, 0.0, t);
		flag += 1;
		t = 0.0;
	}
	else if (flag == 2)
	{
		tA1x = lerp(1.5, -0.2, t);
		tA1y = lerp(-1.5, 0.0, t);
		flag += 1;
		t = 0.0;
	}
	else if (flag == 3)
	{
		tRx = lerp(1.6, 0.2, t);
		tRy = lerp(1.6, 0.0, t);
		flag += 1;
		t = 0.0;
	}
	else if (flag == 4)
	{
		tA2x = lerp(1.6, 0.6, t);
		tA2y = lerp(1.6, 0.0, t);
		flag += 1;
		t = 0.0;
	}
	else if (flag == 5)
	{
		tTx = lerp(1.9, 1.0, t);
		flag += 1;
		t = 0.0;
	}
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
