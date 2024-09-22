// Standard Headers
#include <windows.h> //Win 32 API
#include <stdio.h>	 //FileIO
#include <stdlib.h>	 //exit()
#include "ogl.h"	 //For Icon resource

// OpenGL Header Files
#include <gl/GL.h>
#include <gl/glu.h>

#include "windowclock.h"
#include "HappyBdayText.h"
#include "SecondScene.h"
#include "scene1.h"
#include "MyTown.h"

#include <time.h>

#define _USE_MATH_DEFINES
#include <math.h>

// MACROS
#define WIN_WIDTH 800
#define WIN_HEIGHT 600

// Link with OpenGl Library
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "winmm.lib")
// Global Function Declaration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// Gloabal Variable Declaration
FILE *gpFILE = NULL;
HWND ghwnd = NULL;
DWORD dwStyle;
BOOL gbFullScreen = FALSE;
WINDOWPLACEMENT wpPrev = {sizeof(WINDOWPLACEMENT)};
BOOL gbActive = FALSE;

time_t start_time, end_time, delta_time;

// OpenGL Related Global Variables
PIXELFORMATDESCRIPTOR pfd;
int iPixelFormatIndex = 0;
HDC ghdc = NULL;
HGLRC ghrc = NULL;

// Entry Point Function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	// Function Declarations
	int initialise(void);
	void uninitialise(void);
	void display(void);
	void update(void);

	// Local Variable Declaration
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyWindow");
	int iResult = 0;
	BOOL bDone = FALSE;

	// code
	gpFILE = fopen("Log.txt", "w");

	if (gpFILE == NULL)
	{
		MessageBox(NULL, TEXT("LOG FILE OPENING ERROR"), TEXT("ERROR"), MB_OK | MB_ICONERROR);
		exit(0);
	}
	fprintf(gpFILE, "Programme Started Successfully\n");

	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MyIcon));
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hInstance = hInstance;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MyIcon));

	RegisterClassEx(&wndclass);

	hwnd = CreateWindowEx(
		WS_EX_APPWINDOW,
		szAppName,
		TEXT("MyWindow"),
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE,
		GetSystemMetrics(SM_CXSCREEN) / 2.0 - WIN_WIDTH / 2.0,
		GetSystemMetrics(SM_CYSCREEN) / 2.0 - WIN_HEIGHT / 2.0,
		WIN_WIDTH,
		WIN_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL);

	ghwnd = hwnd;

	// Initialisation
	iResult = initialise();

	if (iResult != 0)
	{
		MessageBox(hwnd, TEXT("Initialisation Failed"), TEXT("ERROR"), MB_OK | MB_ICONERROR);
		DestroyWindow(hwnd);
	}

	ShowWindow(hwnd, iCmdShow);
	SetForegroundWindow(hwnd);
	SetFocus(hwnd);

	// GameLoop
	while (bDone == FALSE)
	{

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{

			if (msg.message == WM_QUIT)
				bDone = TRUE;
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
				// Render
				display();

				// Update
				update();
			}
		}
	}

	// Uninitialisation
	uninitialise();

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	// Function Declarations
	void ToggleFullScreen(void);
	void resize(int, int);

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

		case VK_SPACE:
			start_time = time(0);
			PlaySound(TEXT("MamBdaySound2.wav"), NULL, SND_ASYNC | SND_FILENAME);

			break;
		}

		break;

	case WM_CHAR:

		switch (LOWORD(wParam))
		{
		case 'f':
		case 'F':

			ToggleFullScreen();
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

	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}

void ToggleFullScreen(void)
{
	MONITORINFO mi = {sizeof(MONITORINFO)};

	// code
	if (gbFullScreen == FALSE)
	{ // 1
		// A
		dwStyle = GetWindowLong(ghwnd, GWL_STYLE);

		if (dwStyle & WS_OVERLAPPEDWINDOW)
		{
			// a b c
			if (GetWindowPlacement(ghwnd, &wpPrev) && GetMonitorInfo(MonitorFromWindow(ghwnd, MONITORINFOF_PRIMARY), &mi))
			{
				// i
				SetWindowLong(ghwnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);

				// ii
				SetWindowPos(ghwnd, HWND_TOP, mi.rcMonitor.left, mi.rcMonitor.top, mi.rcMonitor.right - mi.rcMonitor.left, mi.rcMonitor.bottom - mi.rcMonitor.top, SWP_NOZORDER | SWP_FRAMECHANGED);
			}
		}

		// B
		ShowCursor(FALSE);
		gbFullScreen = TRUE;
	}
	else
	{ // 2

		// A
		SetWindowPlacement(ghwnd, &wpPrev);

		// B
		SetWindowLong(ghwnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);

		// C
		SetWindowPos(ghwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE);

		// D
		ShowCursor(TRUE);

		gbFullScreen = FALSE;
	}
}

int initialise(void)
{
	// Function Declarations

	// code
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	// Initialisation of PIXELFORMATDESRIPTOR
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cRedBits = 8;
	pfd.cGreenBits = 8;
	pfd.cBlueBits = 8;
	pfd.cAlphaBits = 8;

	ghdc = GetDC(ghwnd);

	if (ghdc == NULL)
	{
		fprintf(gpFILE, "GetDC() Failed\n");
		return -1;
	}

	iPixelFormatIndex = ChoosePixelFormat(ghdc, &pfd);

	if (iPixelFormatIndex == 0)
	{
		fprintf(gpFILE, "ChoosePixelFormat()  Failed\n");
		return -2;
	}

	if (SetPixelFormat(ghdc, iPixelFormatIndex, &pfd) == FALSE)
	{
		fprintf(gpFILE, "SetPixelFormat() Failed\n");
		return -3;
	}

	// Create OpenGL context from device context
	ghrc = wglCreateContext(ghdc);

	if (ghrc == NULL)
	{
		fprintf(gpFILE, "wglCreateContext() Failed\n");
		return -4;
	}

	// Make Rendering Context Current
	if (wglMakeCurrent(ghdc, ghrc) == FALSE)
	{
		fprintf(gpFILE, "wglMakeCurrent() Failed\n");
		return -5;
	}

	// Here OpenGL Starts
	// Set The Clear Color Of Window To Blue
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return 0;
}

void resize(int width, int height)
{
	// code
	if (height <= 0)
		height = 1;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
}

GLfloat scene1x_scale = 1,
		scene1y_scale = 1;

GLfloat scene1x_translate = 0,
		scene1y_translate = 0;

GLfloat scene1_t = 0.5;

GLfloat scene2_t = 0.2;

GLfloat t1 = 0;
GLfloat t2 = 0.0;

void myscale()
{
	if (delta_time >= 90 && delta_time <= 120)
	{
		// glTranslatef(-(Scalex * 0.06) + 0.06, -(Scalex * 0.032) + 0.032, 0);
		glScalef(Scalex, Scaley, 1);
	}
}

void scene3()
{
	if (delta_time >= 90 && delta_time <= 125)
	{
		glTranslatef(-(Scalex * 0.06) + 0.06, -(Scalex * 0.032) + 0.032, 0);
		glScalef(Scalex, Scaley, 1);
	}

	if (delta_time <= 120)
	{

		Draw_Computer(scene2_t);
	}
	if (delta_time >= 0 && delta_time <= 125)
		glScalef(0.23f, 0.23f, 1.0f);

	if ((delta_time >= 0 && delta_time < 20) ||
		(delta_time >= 25 && delta_time < 30) ||
		(delta_time >= 35 && delta_time < 40) ||
		(delta_time >= 45 && delta_time < 50) ||
		(delta_time >= 55 && delta_time < 60) ||
		(delta_time >= 65 && delta_time < 70) ||
		(delta_time >= 75 && delta_time < 80))
	{
		Code(scene2_t);
	}
	else if (delta_time <= 125)
	{
		if (delta_time >= 20)
			Ground();

		if (delta_time >= 30)
			Sky();

		if (delta_time >= 40)
			Road();

		if (delta_time >= 50)
			Right_Houses();

		if (delta_time >= 60)
			Left_Houses();

		if (delta_time >= 70)
			Lamp();

		if (delta_time >= 80)
			Tree();
	}

	if (delta_time >= 120 && delta_time <= 125)
	{

		if (t1 < 1)
		{
			t1 = t1 + 0.0001;
		}

		glColor4f(1, 1, 0, t1);

		glBegin(GL_QUADS);
		glVertex2f(1, 1);
		glVertex2f(-1, 1);
		glVertex2f(-1, -1);
		glVertex2f(1, -1);

		glEnd();
	}

	if (delta_time >= 125)
	{

		if (t2 < 1)
			t2 = t2 + 0.0001;

		Base(t2);
		Rushikesh(delta_time, t2);
		GroupMembers(t2);
		CircleAnimation(t2);
	}

	if (delta_time >= 125 && delta_time <= 130)
	{
		if (t1 >= 0)
		{
			// trans_flag = 1;
			t1 = t1 - 0.0001;
		}

		glColor4f(1, 1, 0, t1);

		glBegin(GL_QUADS);
		glVertex2f(1, 1);
		glVertex2f(-1, 1);
		glVertex2f(-1, -1);
		glVertex2f(1, -1);

		glEnd();
	}
}

void display(void)
{
	// code
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_BLEND_DST);

	if (delta_time >= 5 && delta_time <= 15)
	{
		glTranslatef(scene1x_translate, 0, 0);

		glScalef(scene1x_scale, scene1y_scale, 1);
	}

	if (delta_time >= 0 && delta_time <= 15)
	{

		scene1();
	}

	if (delta_time > 12 && delta_time <= 13)
	{
		if (scene1_t <= 1)
		{
			scene1_t += 0.00001;
		}
		glColor4f(0.569, 0.275, 0.047, scene1_t);
		glBegin(GL_QUADS);
		glVertex3f(-1.0f, -1.0f, 0.0f);
		glVertex3f(-1.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, 0.0f);
		glEnd();
	}

	if (delta_time > 13 && delta_time <= 15)
	{
		if (scene1_t >= 0)
		{
			scene1_t -= 0.001;
		}
		glColor4f(0.569, 0.275, 0.047, scene1_t);
		glBegin(GL_QUADS);
		glVertex3f(-1.0f, -1.0f, 0.0f);
		glVertex3f(-1.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, 0.0f);
		glEnd();
	}

	glLoadIdentity();

	if (delta_time > 12)
	{
		if (delta_time <= 120)
		{

			if (scene2_t <= 1)
				scene2_t += 0.008;
			if (delta_time >= 90 && delta_time <= 120)
			{ //-(Scalex * 0.2) + 0.2
				// glTranslatef(+(Scalex * 0.003), +(Scalex * 0.004), 0);
				glScalef(Scalex, Scaley, 1);
			}
			scene2(scene2_t);

			glTranslatef(0.6, 0.55, 0);
			glScalef(0.55, 1.0, 1);

			Calender(scene2_t);

			glLoadIdentity();

			glTranslatef(0.2, -0.6, 0);
			glScalef(0.6, 0.8, 1);
			if (delta_time >= 90 && delta_time <= 120)
			{
				glTranslatef(-(Scalex * 0.06) + 0.06, -(Scalex * 0.8) + 0.8, 0);
				glScalef(Scalex, Scaley, 1);
			}
			Table(scene2_t);

			// Computer
			glLoadIdentity();

			glTranslatef(0.2, 0, 0);
			glScalef(0.75, 0.80, 1);
			// Draw_Computer(scene2_t);
		}
		scene3();

		if (delta_time <= 120)
		{

			glLoadIdentity();
			// mam
			glTranslatef(-0.36, -0.4, 0);
			glScalef(0.8, 0.95, 1);
			if (delta_time >= 90 && delta_time <= 120)
			{ //-(Scalex * 0.2) + 0.2
				// glTranslatef(-(Scalex * 0.55) + 0.55, -(Scalex * 0.8) + 0.8, 0);
				glTranslatef(-(Scalex * 0.7) + 0.7, -(Scalex * 0.65) + 0.65, 0);
				glScalef(Scalex, Scaley, 1);
			}
			mam(scene2_t);

			// chair
			glLoadIdentity();

			glTranslatef(0.20, -0.70, 0);
			glScalef(0.75, 0.80, 1);
			if (delta_time >= 90 && delta_time <= 120)
			{
				//+(Scalex * 0.05) + 0.05
				glTranslatef(0, -(Scalex * 1) + 1, 0);
				glScalef(Scalex, Scaley, 1);
			}
			Chair(scene2_t);

			glLoadIdentity();

			glTranslatef(-0.3f, -0.1f, 0.0f);
			glScalef(0.6, 0.6, 1);
			if (delta_time >= 90 && delta_time <= 120)
			{ //-(Scalex * 0.2) + 0.2
				glTranslatef(-(Scalex * 0.55) + 0.55, -(Scalex * 0.8) + 0.8, 0);
				glScalef(Scalex, Scaley, 1);
			}
			// Plant(scene2_t);

			glLoadIdentity();

			glTranslatef(-0.2f, 0.0f, 0.0f);
			if (delta_time >= 90 && delta_time <= 120)
			{ //-(Scalex * 0.2) + 0.2
				glTranslatef(-(Scalex * 0.4) + 0.4, +(Scalex * 0.02) + 0.02, 0);
				glScalef(Scalex, Scaley, 1);
			}
			watch_border(0.4f, 0.6f, 0.1f, 100, scene2_t);
			watch_on_Wall(0.4f, 0.6f, 0.1f, 100, scene2_t);
			ClockMinuteHandAngle += 0.003;

			if (t < 1.0)
				t += 0.00004f;

			glScalef(1.08f, 1.8f, 1.0f);

			window(scene2_t);
			stars(scene2_t);
			glLoadIdentity();
		}
	}

	SwapBuffers(ghdc);
}

void update(void)
{
	// code

	if (start_time != 0)
	{
		end_time = time(0);
	}
	delta_time = end_time - start_time;

	if (delta_time > 5)
	{
		scene1x_scale += 0.0004;
		scene1y_scale += 0.0004;

		scene1x_translate -= 0.000205;
		scene1y_translate -= 0.000205;
	}
	if (delta_time >= 90 && delta_time <= 120)
	{

		// Scalex += 0.0005;
		// Scaley += 0.0005;

		Scalex += 0.0025; // 0.0015
		Scaley += 0.0025;
	}
}

void uninitialise(void)
{
	// Function Declaration
	void ToggleFullScreen(void);

	// code
	// If Application is Exiting in fullScreen
	if (gbFullScreen == TRUE)
		ToggleFullScreen();

	// Make the ghdc as current Dc
	if (wglGetCurrentContext() == ghrc)
	{
		wglMakeCurrent(NULL, NULL);
	}
	// Destroy Rendering context
	if (ghrc)
	{
		wglDeleteContext(ghrc);
		ghrc = NULL;
	}

	// Relase ghdc
	if (ghdc)
	{
		ReleaseDC(ghwnd, ghdc);
		ghdc = NULL;
	}

	// Destroy Window
	if (ghwnd)
	{
		DestroyWindow(ghwnd);
		ghwnd = NULL;
	}

	// close the log File
	if (gpFILE)
	{
		fprintf(gpFILE, "Programme Ended Successfully\n");
		fclose(gpFILE);
		gpFILE = NULL;
	}
}
