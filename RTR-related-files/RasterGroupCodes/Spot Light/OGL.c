// Windows Header Files
#include <windows.h>     //sdk win32api
#include <stdio.h>      //file io
#include <stdlib.h>     //exit()

//OpenGL Header File
#include <GL/gl.h>

#include <GL/glu.h>

#include "OGL.h"

//macors
#define WIN_WIDTH 800
#define WIN_HEIGHT 600

//link with opengl library
#pragma comment(lib,"opengl32.lib")

#pragma	comment(lib,"glu32.lib")

// Global Function Declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// Global Variable Declarations

// for fileIO
FILE *gpFILE = NULL;   

//for fullscreen
HWND ghwnd = NULL;  
DWORD dwStyle = 0;
WINDOWPLACEMENT wpPrev = { sizeof(WINDOWPLACEMENT) };
BOOL gbFullscreen = FALSE;

//for active/inactive
BOOL gbActiveWindow = FALSE;

//opengl related global variables
HDC ghdc = NULL;
HGLRC ghrc = NULL;

//variables for lights
BOOL bLight = FALSE;

GLfloat LightAmbiant[] = {0.1f, 0.1f, 0.1f, 1.0f};
GLfloat LightDefuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat LigthSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat LightPosition[] = {0.0f, 0.0f, 0.0f, 1.0f};
GLfloat light_direction[] = {0.0f, 0.0f, -1.0f};

GLfloat spotCutOff = 45.0f;
GLfloat spotExponent = 10.0f;

GLfloat materialAmbient[] = {0.0f, 0.0f, 0.0f, 1.0f};
GLfloat materialDefuse[] = {0.5f, 0.2f, 0.7f, 1.0f};
GLfloat materialSpecular[] = {0.7f, 0.7f, 0.7f, 1.0f};
GLfloat materialShininess[] = {128.0f};

GLUquadric *Quadric = NULL;

//Entry Point Function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	//fucntion declaration
	int initialize(void);
	void uninitialize(void);
	void display(void);
	void update(void);

	//Local Variable Declarations
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;                                                                                                                              
	TCHAR szAppName[] = TEXT(" ABCWindow ");

	int iResult = 0;

	BOOL bDone = FALSE;   //game loop

    //for centering
	int ScreenHeight;      
    int ScreenWidth;
    int WindowHeight = 600;
    int WindowWidth = 800;
    
    ScreenWidth = GetSystemMetrics(SM_CXSCREEN);
    ScreenHeight = GetSystemMetrics(SM_CYSCREEN);

    int X = ScreenWidth / 2 - WindowWidth / 2;
    int Y = ScreenHeight / 2 - WindowHeight / 2;


	//code
	gpFILE = fopen("Log.txt", "w");
	if (gpFILE == NULL)
	{
		MessageBox(NULL, TEXT("Log File Cannot Be Opend"), TEXT("Error"), MB_OK | MB_ICONERROR);
		exit(0);
	}
	fprintf(gpFILE, "Program Started Successfully\n");
	
	//WNDCEX initialization
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(BAT_ICON));
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(BAT_ICON));

	//Register WNDCLASSEX
	RegisterClassEx(&wndclass);

	//Create Window
	hwnd = CreateWindow(szAppName,
		TEXT("Abhay B. Chilka"),
	    WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE,
		X,
		Y,
		WIN_WIDTH,
		WIN_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL);

	ghwnd = hwnd;

	//Initialization
	iResult = initialize();
	if (iResult != 0)
	{
		MessageBox(hwnd, TEXT("initialize() failed"), TEXT("Error"), MB_OK | MB_ICONERROR);
		DestroyWindow(hwnd);
	}
	
	

	// Show The Window
	ShowWindow(hwnd, iCmdShow);
	SetForegroundWindow(hwnd);
	SetFocus(hwnd);

	// Paint/Re-Draw The Window
	//UpdateWindow(hwnd);

	// Message-loop
	//game-loop
	while (bDone == FALSE)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
				bDone = TRUE;
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			if (gbActiveWindow == TRUE)
			{
				//RENDER
				display();

				//UPDATE
				update();
			}
			
		}
	}
	uninitialize();

	return((int)msg.wParam);
}


//CallBack Function
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	// Function Declarations
	void ToggleFullScreen(void);
	void resize(int, int);

	// code
	switch (iMsg)
	{
	case WM_SETFOCUS:    
		gbActiveWindow = TRUE;
		break;

	case WM_KILLFOCUS:
		gbActiveWindow = FALSE;
		break;

	case WM_SIZE:
		resize(LOWORD(lParam), HIWORD(lParam));
		break;

    case WM_ERASEBKGND:
		return(0);
		break;

	case WM_KEYDOWN:
		switch (LOWORD(wParam))
		{
		case VK_ESCAPE:

			DestroyWindow(hwnd);
			break;

		}
		break; 
	
	case WM_CHAR:
		switch(LOWORD(wParam))
		{
		case 'F':
		case 'f':
			if(gbFullscreen == FALSE)
			{
				ToggleFullScreen();
				gbFullscreen = TRUE;
			}
			else
			{
				ToggleFullScreen();
				gbFullscreen = FALSE;
			}
			break;
		case 'L':
		case 'l':
			if (bLight == FALSE)
			{
				glEnable(GL_LIGHTING);
				bLight = TRUE;
			}
			else
			{
				glDisable(GL_LIGHTING);
				bLight = FALSE;
			}	
			break;

		case 'W':
		case 'w':
			spotCutOff += 1.0f;
		break;

		case 'S':
		case 's':
			if(spotCutOff < 0.0f) spotCutOff = 0.0f;
			spotCutOff -= 1.0f;
		break;

		case 'A':
		case 'a':
			if(spotExponent < 0.0) spotExponent  = 0.0f;
			spotCutOff -= 1.0f;
		break;

		case 'D':
		case 'd':
			spotExponent += 1.0f;
		break;
		default:
        break;
		}
	break;

	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;

	case WM_DESTROY :
		if (gpFILE)
		{
			fprintf(gpFILE,"Prgram Ended Successfully...\n");
			fclose(gpFILE);
			gpFILE = NULL;
		}
		
		PostQuitMessage(0);
		break;
	default :
		break;
	}

	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, spotCutOff);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, spotExponent);

	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

void ToggleFullScreen(void)
{
	// Local Variable Declarations
	MONITORINFO mi = { sizeof(MONITORINFO) };

	// Code
	if (gbFullscreen == FALSE)
	{
		dwStyle = GetWindowLong(ghwnd, GWL_STYLE); 

		if (dwStyle & WS_OVERLAPPEDWINDOW)
		{
			if (GetWindowPlacement(ghwnd, &wpPrev) && GetMonitorInfo(MonitorFromWindow(ghwnd, MONITORINFOF_PRIMARY), &mi)) 
			{
				SetWindowLong(ghwnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);  // ~Remove Contents
				SetWindowPos(ghwnd, HWND_TOP, mi.rcMonitor.left, mi.rcMonitor.top, mi.rcMonitor.right - mi.rcMonitor.left, mi.rcMonitor.bottom - mi.rcMonitor.top, SWP_NOZORDER | SWP_FRAMECHANGED);
			}
		}
		ShowCursor(FALSE);
	}
	else
	{
		SetWindowPlacement(ghwnd, &wpPrev);

		SetWindowLong(ghwnd, GWL_STYLE, dwStyle |  WS_OVERLAPPEDWINDOW);

		SetWindowPos(ghwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_FRAMECHANGED);

		ShowCursor(TRUE);
	}
}

int initialize(void)
{
	//function declarations
	void resize(int, int);
	//code
	//variable declaration
	PIXELFORMATDESCRIPTOR PFD;
	int iPixelFormatIndex = 0;

	//initializing PFD struct with 0
	ZeroMemory(&PFD, sizeof(PIXELFORMATDESCRIPTOR));

	//initialization of PixelFormatDescriptor
	PFD.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	PFD.nVersion = 1;
	PFD.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER; 
	PFD.iPixelType = PFD_TYPE_RGBA;
	PFD.cColorBits = 32; 
	PFD.cRedBits = 8;
	PFD.cGreenBits = 8;
	PFD.cBlueBits = 8;
	PFD.cAlphaBits = 8;
	PFD.cDepthBits = 32;

	
	//get dc
	ghdc = GetDC(ghwnd);
	if (ghdc == NULL)
	{
		fprintf(gpFILE, "GetDC Failed\n");
		return(-1);
	}

	//choosing pixel format which closlely matches to our initialised PFD
	iPixelFormatIndex = ChoosePixelFormat(ghdc, &PFD);

	if (iPixelFormatIndex == 0)
	{
		fprintf(gpFILE, "Choose PixelFormat function() failed");
		return(-2);
	}

	//set obtain PixelFormat
	if (SetPixelFormat(ghdc, iPixelFormatIndex, &PFD) == FALSE)
	{
		fprintf(gpFILE, "SetPixelFormat\n");
		return(-3);
	}
	
	//create opengl context from device context
	ghrc = wglCreateContext(ghdc);
	if (ghrc == NULL)
	{
		fprintf(gpFILE, "wglCreateContext() failed");
		return(-4);
	}
	
	//make rendering context current
	if (wglMakeCurrent(ghdc, ghrc) == FALSE)
	{
		fprintf(gpFILE, "wglMakeCurrent() Fialed\n");
		return(-5);
	}

	//here opengl starts

	// Enabling Depth
	glShadeModel(GL_SMOOTH);						   // Beautification Line (optional)
	glClearDepth(1.0f);								   // Compulsory
	glEnable(GL_DEPTH_TEST);						   // Compulsory
	glDepthFunc(GL_LEQUAL);							   // Compulsory
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Beuatification (optional)

	//light related initialisation
	glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbiant);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDefuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, LigthSpecular);
	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION,light_direction);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, spotCutOff);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, spotExponent);

	glEnable(GL_LIGHT0);  //by default is enable '0'

	//material properties
	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDefuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);
	glMaterialfv(GL_FRONT, GL_SHININESS, materialShininess);

	//initialise quadric
	Quadric = gluNewQuadric();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//set the clear color of window to blue
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	resize(WIN_WIDTH, WIN_HEIGHT);

	return(0);
}

void resize(int width, int height)
{
	//code
	if (height <= 0)
		height = 1;

	//resize
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);

	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

}

void display(void)
{
	//code
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
 
	for (int i = 0; i < 5; i++)
	{
		glPushMatrix();
		glTranslatef(i * 2.0f, 0.0f, -10.0f - (i * 3.0f));
		//creates all internally normals 
		gluSphere(Quadric, 1.0f, 50, 50);
		glPopMatrix();
	}
	
	SwapBuffers(ghdc);
}

void update(void)
{
	//code
}

void uninitialize(void)
{
	//fucntion declarations
	void ToggleFullScreen(void);

	//code
	//if application is exiting in fullscreen
	if (gbFullscreen == TRUE)
	{
		ToggleFullScreen();
		gbFullscreen = FALSE;
	}	

	//make the hdc as current context
	if (wglGetCurrentContext() == ghrc )
	{
		wglMakeCurrent(NULL, NULL);
	}

	//Delete rendering context
	if (ghrc)
	{
		wglDeleteContext(ghrc);
		ghrc = NULL;
	}

	//release the hdc
	if (ghdc)
	{
		ReleaseDC(ghwnd,ghdc);
		ghdc = NULL;
	}
	
	//DestroyWindow
	if (ghwnd)
	{
		DestroyWindow(ghwnd);
		ghwnd = NULL;
	}

	//close the log file
		if (gpFILE)
		{
			fprintf(gpFILE,"Program Ended Successfully...\n");
			fclose(gpFILE);
			gpFILE = NULL;
		}

	//delete quadric
	if (Quadric)
	{
		gluDeleteQuadric(Quadric);
		Quadric = NULL;
	}
}







