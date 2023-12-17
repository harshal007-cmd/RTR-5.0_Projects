//xxxxxx OpenGL Starts.... First Code xxxxxx// 30th July
//Proceduaral texture, not using any image

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

GLfloat cAngle = 0.0;
GLuint texture_checkerBoard;
int texture_var = -1;
const unsigned int checkImageWidth = 64;
const unsigned int checkImageHeight = 64;
GLubyte checkImage[checkImageHeight][checkImageWidth][4];


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
		TEXT("HVS:3D Cube"),
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
	void loadGLTexture(void);

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

	//Enabling depth
	glShadeModel(GL_SMOOTH);//light, texture etc make it smooth
	glClearDepth(1.0f);//depth buffer to 1
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);//check less than or equal to with 1.0f
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	//Set the Clear color of Window to Blue
	glClearColor(0.75f, 0.75f, 0.75f, 1.0f); //here OpenGL starts

	loadGLTexture();
	glEnable(GL_TEXTURE_2D);

	resize(WIDTH, HEIGHT);
	return 0;
}



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
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);

}

void loadGLTexture()
{
	//local func decl
	void makeCheckImage();
	
	makeCheckImage();
	//get image data

	//create opengl texture obj
	glGenTextures(1, &texture_checkerBoard);

	//bind to gen tex
	glBindTexture(GL_TEXTURE_2D, texture_checkerBoard);

	//unpack and manage
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);//monochrome ahe hence 1 - coz its checkedboard

	//set
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, checkImageWidth, checkImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, (void*)checkImage);

	//Unbind
	glBindTexture(GL_TEXTURE_2D, 0);

	//Delete

	
}
void makeCheckImage()
{
	//var decl
	int i, j, c;

	//code
	for (i = 0;i < checkImageHeight;++i)
	{
		for (j = 0;j < checkImageWidth;++j)
		{
			c = (((i & 0x8) == 0) ^ ((j & 0x8) == 0)) * 255;

			checkImage[i][j][0] = (GLubyte)c;
			checkImage[i][j][1] = (GLubyte)c;
			checkImage[i][j][2] = (GLubyte)c;
			checkImage[i][j][3] = (GLubyte)255;
		}
	}

}

void display(void)
{
	//code
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	
	//3.Following lines should be used when modeling and viewing x-formation is to be done
	gluLookAt(0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, -3.6f);

	glBindTexture(GL_TEXTURE_2D, texture_checkerBoard);

	glBegin(GL_QUADS);
	//front face
	
	glTexCoord2f(1.0, 1.0);//tr
	glVertex3f(0.0, 1.0, 0.0);

	glTexCoord2f(0.0, 1.0);
	glVertex3f(-2.0, 1.0, 0.0);

	glTexCoord2f(0.0, 0.0);
	glVertex3f(-2.0, -1.0, 0.0);

	glTexCoord2f(1.0, 0.0);//br
	glVertex3f(0.0, -1.0, 0.0);

	//side quad
	glTexCoord2f(1.0, 1.0);//tr
	glVertex3f(2.41421, 1.0, -1.41421);

	glTexCoord2f(0.0, 1.0);
	glVertex3f(1.0, 1.0, 0.0);

	glTexCoord2f(0.0, 0.0);
	glVertex3f(1.0, -1.0, 0.0);

	glTexCoord2f(1.0, 0.0);//br
	glVertex3f(2.41421, -1.0, -1.41421);

	glEnd();
	
	glBindTexture(GL_TEXTURE_2D, 0);

	SwapBuffers(ghdc);


}

void update(void)
{
	//code
	cAngle += 0.05f;
	if (cAngle >= 360.0f)
	{
		cAngle = cAngle - 360.0f;
	}

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

	if (texture_checkerBoard) {
		glDeleteTextures(1, &texture_checkerBoard);
		texture_checkerBoard = NULL;
	}


	//close the Log file
	if (gpFILE)
	{
		fprintf(gpFILE, "Program Ended Successfully !!\n");
		fclose(gpFILE);
		gpFILE = NULL;
	}
}
