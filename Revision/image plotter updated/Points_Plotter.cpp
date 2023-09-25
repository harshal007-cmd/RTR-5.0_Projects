//xxxxxx OpenGL Starts.... First Code xxxxxx// 30th July
// Blue Screen code

//Common header files
#include<windows.h>//win32
#include"Window.h" //or OGL.h (if rename)
#include<stdio.h>///for file IO
#include<stdlib.h>//for exit() 
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
//File io
FILE* gpFILE = NULL;


GLfloat EyeBrows[] = {
762,300,
778,305,
778,305,
791,311,
791,311,
799,324,
799,324,
801,340,
801,340,
801,356

};

GLfloat CrownLine2[] = {
796,255,
783,253,
772,250,
759,247,
746,247,
733,245,
720,245,
706,245,
693,247,
680,253,
675,253,
675,200,
688,197,
701,195,
714,192,
728,192,
743,195,
757,197,
770,197,
786,200

};

GLfloat Eye[] = {
762,316,
775,321,
786,332,
786,345,
786,353,
772,348,
762,334

};

GLfloat Eye2[] =
{
775,324,
780,329,
780,337,
770,340,
767,334

};

/*
GLfloat Trishul[] =
{
	672,65,
	617,300,
	654,353,
	651,366,
	611,356,
	543,369,
	564,250,
	535,113,
	519,255,
	495,406,
	593,393,
	651,395,
	651,469,
	551,435,
	551,564,
	648,532,
	648,762,
	675,762,
	677,390
};
*/

GLfloat Face[] = {
673,65,
696,84,
688,110,
714,123,
738,134,
759,145,
778,160,
788,187,
793,208,
793,208,
793,232,
796,253,
809,263,
828,279,
838,298,
846,313,
854,332,
857,350,
859,369,
859,387,
859,408,
854,427,
846,448,
838,466,
828,480,
815,493,
799,503,
783,511,
775,524,
767,538,
762,556,
762,575,
762,593,
770,609,
778,627,
791,640,
807,651,
825,659,
844,659,
859,654,
873,648,
865,667,
875,691,
862,693,
844,693,
822,691,
804,691,
786,685,
767,683,
751,677,
738,667,
722,659,
709,648,
696,638,
688,625,
677,611,
674,593

};

GLfloat Trishul[] =
{
	672,65,
	617,300,
	654,353,
	651,366,
	611,356,
	543,369,
	564,250,
	535,113,
	519,255,
	495,406,
	593,393,
	651,395,
	651,469,
	551,435,
	551,564,
	648,532,
	648,762,
	675,762,
	//677,390
};

GLfloat CrownTriangles[] = {
675,197,
698,171,
720,195,
743,168,
759,195,
780,168,
788,197
};

GLfloat Tila[] = {
807,279,
825,313,
825,313,
849,316
};

GLfloat Tila2[] = {
817,276,
833,303

};

GLfloat CrownTop[] = {
688,108,
677,105
};

GLfloat DamruString1[] = {
647,529,
640,553,
640,553,
627,572,
627,572,
609,582,
609,582,
588,590
};

GLfloat str1Pt[] = {
	588,590
};

GLfloat DamruString2[] = {
647,529,
648,548,
648,548,
640,567,
640,567,
630,585,
630,585,
619,601,
619,601,
606,609

};

GLfloat str2Pt[] = {
606,609

};

GLfloat Laddu[] = {
	880,667

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
	fprintf(gpFILE, "%lld", ARRAY_LENGTH(Trishul));
	fprintf(gpFILE, "%lld", ARRAY_LENGTH(Face));
	fprintf(gpFILE, "%lld", ARRAY_LENGTH(EyeBrows));

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

//global function declaration
LRESULT CALLBACK WndProg(HWND, UINT, WPARAM, LPARAM);


//global variable declaration
HWND ghwnd = NULL;
BOOL gbActive = FALSE;
DWORD dwstyle = 0;
WINDOWPLACEMENT wpPrev = { sizeof(WINDOWPLACEMENT) };
BOOL gbFullScreen = FALSE;

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

	ConvertToOpenGLSpace(Trishul, ARRAY_LENGTH(Trishul), 256, 256);
	ConvertToOpenGLSpace(Face, ARRAY_LENGTH(Face), 256, 256);
	ConvertToOpenGLSpace(EyeBrows, ARRAY_LENGTH(EyeBrows), 256, 256);
	ConvertToOpenGLSpace(Eye, ARRAY_LENGTH(Eye), 256, 256);
	ConvertToOpenGLSpace(CrownLine2, ARRAY_LENGTH(CrownLine2), 256, 256);
	ConvertToOpenGLSpace(Eye2, ARRAY_LENGTH(Eye2), 256, 256);
	ConvertToOpenGLSpace(CrownTriangles, ARRAY_LENGTH(CrownTriangles), 256, 256);
	ConvertToOpenGLSpace(Tila, ARRAY_LENGTH(Tila), 256, 256);
	ConvertToOpenGLSpace(Tila2, ARRAY_LENGTH(Tila2), 256, 256);
	ConvertToOpenGLSpace(CrownTop, ARRAY_LENGTH(CrownTop), 256, 256);
	ConvertToOpenGLSpace(DamruString1, ARRAY_LENGTH(DamruString1), 256, 256);
	ConvertToOpenGLSpace(str1Pt, ARRAY_LENGTH(str1Pt), 256, 256);
	ConvertToOpenGLSpace(str2Pt, ARRAY_LENGTH(str2Pt), 256, 256);
	ConvertToOpenGLSpace(DamruString2, ARRAY_LENGTH(DamruString2), 256, 256);
	ConvertToOpenGLSpace(Laddu, ARRAY_LENGTH(Laddu), 256, 256);

	//Set the Clear color of Window to Blue
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //here OpenGL starts

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
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
}

void BackGround()
{
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.5, 0.0);
	glVertex2f(1.0, 0.5);

	glColor3f(0.0, 0.0, 255.0 / 255.0);
	glVertex2f(-1.0, 0.5);
	glVertex2f(-1.0, -1.0);

	glColor3f(1.0, 0.5, 0.0);
	glVertex2f(1.0, -1.0);
	glEnd();
}

void Trishul_Ganesh()
{
	glLoadIdentity();
	glLineWidth(2.8);
	glTranslatef(-1.3f, 0.5f, -3.0f);
	glScalef(0.3f, 0.3f, 0.3f);

	// glDrawArrays(GL_TRIANGLES, 0, 3);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < ARRAY_LENGTH(Trishul); i = i + 2)
	{
		glVertex2f(Trishul[i], Trishul[i + 1]);
	}
	glEnd();

	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < ARRAY_LENGTH(Face); i = i + 2)
	{
		glVertex2f(Face[i], Face[i + 1]);
	}
	glEnd();


	glBegin(GL_LINES);
	for (int i = 0; i < ARRAY_LENGTH(EyeBrows); i = i + 2)
	{
		glVertex2f(EyeBrows[i], EyeBrows[i + 1]);
	}
	glEnd();

	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < ARRAY_LENGTH(Eye); i = i + 2)
	{
		glVertex2f(Eye[i], Eye[i + 1]);
	}
	glEnd();

	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < ARRAY_LENGTH(CrownLine2); i = i + 2)
	{
		glVertex2f(CrownLine2[i], CrownLine2[i + 1]);
	}
	glEnd();

	glBegin(GL_POLYGON);
	for (int i = 0; i < ARRAY_LENGTH(Eye2); i = i + 2)
	{
		glVertex2f(Eye2[i], Eye2[i + 1]);
	}
	glEnd();

	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < ARRAY_LENGTH(CrownTriangles); i = i + 2)
	{
		glVertex2f(CrownTriangles[i], CrownTriangles[i + 1]);
	}
	glEnd();

	glBegin(GL_LINES);
	for (int i = 0; i < ARRAY_LENGTH(Tila); i = i + 2)
	{
		glVertex2f(Tila[i], Tila[i + 1]);
	}
	glEnd();

	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < ARRAY_LENGTH(Tila2); i = i + 2)
	{
		glVertex2f(Tila2[i], Tila2[i + 1]);
	}
	glEnd();

	glBegin(GL_LINES);
	for (int i = 0; i < ARRAY_LENGTH(CrownTop); i = i + 2)
	{
		glVertex2f(CrownTop[i], CrownTop[i + 1]);
	}
	glEnd();

	glBegin(GL_LINES);
	for (int i = 0; i < ARRAY_LENGTH(DamruString1); i = i + 2)
	{
		glVertex2f(DamruString1[i], DamruString1[i + 1]);
	}
	glEnd();

	glBegin(GL_LINES);
	for (int i = 0; i < ARRAY_LENGTH(DamruString2); i = i + 2)
	{
		glVertex2f(DamruString2[i], DamruString2[i + 1]);
	}
	glEnd();

	//	glLoadIdentity();
	glEnable(GL_POINT_SMOOTH);
	glPointSize(10.0);
	glBegin(GL_POINTS);
	for (int i = 0; i < ARRAY_LENGTH(str1Pt); i = i + 2)
	{
		glVertex2f(str1Pt[i], str1Pt[i + 1]);
	}
	glEnd();

	//glEnable(GL_POINT_SMOOTH);
	//glPointSize(10.0);
	glBegin(GL_POINTS);
	for (int i = 0; i < ARRAY_LENGTH(str1Pt); i = i + 2)
	{
		glVertex2f(str2Pt[i], str2Pt[i + 1]);
	}
	glEnd();

	glPointSize(16.5);
	glBegin(GL_POINTS);
	for (int i = 0; i < ARRAY_LENGTH(Laddu); i = i + 2)
	{
		glVertex2f(Laddu[i], Laddu[i + 1]);
	}
	glEnd();

}

void display(void)
{
	//code
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -1.0f);
	//	glScalef(0.3f, 0.3f, 0.3f);
	BackGround();

	Trishul_Ganesh();
	
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
