	//xxxxxx OpenGL PP Starts.... First Code xxxxxx//
//Common header files
#include<windows.h>//win32
#include"Window.h" //or OGL.h (if rename)
#include<stdio.h>///for file IO
#include<stdlib.h>//for exit()

//OpenGL Header files
#include"GL/glew.h"//this must be before gl.h
#include<GL/GL.h>

#include"vmath.h"
using namespace vmath;

#include<vector>

//OpenGL related Global Variables
HDC ghdc = NULL;
HGLRC ghrc = NULL; //handle to GL Rendering Contex

GLuint vertexShaderObject = 0;
GLuint fragmentShaderObject = 0;
GLuint shaderProgramObject = 0;
enum
{
	AMC_ATTRIBUTE_POSITION = 0,
	AMC_ATTRIBUTE_COLOR,

};

GLuint VAO = 0;
GLuint VBO_positions= 0;
GLuint VBO_color= 0;

GLuint mvpMatrixUniform, colorUniform;
mat4 perspectiveGraphicsProjectionMatrix;  //in vmath

std::vector<vmath::vec3>triangle_vertices;
GLuint vao_triangle;

std::vector<vmath::vec3>square_vertices;
GLuint vao_square;

std::vector<vmath::vec3>circle_vertices;
GLuint vao_circle;

std::vector<vmath::vec3>graph_vertices;
GLuint vao_graph;

char c;

//Macros
#define WIDTH 800
#define HEIGHT 600

//Link with OpenGL Lib
#pragma comment(lib,"glew32.lib")
#pragma comment(lib,"openGL32.lib")

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
		TEXT("HVS:Perspective"),
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
		case 'g':
		case 'G':
			c = 'g';
			break;
		case 'c':
		case 'C':
			c = 'c';
			break;
		case 'T':
		case 't':
			c = 't';
			break;
		case 'S':
		case 's':
			c = 's';
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
	void printGLInfo();
	void uninitialize();
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

	//Init GLEW
	if (glewInit() != GLEW_OK)
	{
		fprintf(gpFILE, "glewInit() failed to initialize GLEW\n");
		return -6;
	}
	//PrintGL Info
	//printGLInfo();

	//Vertex Shader
	const GLchar* vertexShaderCode =
		"#version 460 core" \
		"\n" \
		"in vec4 aPosition;" \
		"uniform mat4 uMvpMatrix;" \
		"void main(void)" \
		"{" \
		"	gl_Position = uMvpMatrix * aPosition;" \
		"}";

	vertexShaderObject = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderObject, 1, (const GLchar**)&vertexShaderCode, NULL);
	glCompileShader(vertexShaderObject);

	GLint status = 0;
	GLint infoLogLength = 0;
	GLchar* szInfoLog = NULL;

	glGetShaderiv(vertexShaderObject, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		glGetShaderiv(vertexShaderObject, GL_INFO_LOG_LENGTH, &infoLogLength);
		if (infoLogLength > 0)
		{
			szInfoLog = (GLchar*)malloc(infoLogLength);
			if (szInfoLog != NULL)
			{
				glGetShaderInfoLog(vertexShaderObject, infoLogLength, NULL, szInfoLog);
				fprintf(gpFILE, "Vertex Shader compilation error log: %s\n", szInfoLog);
				free(szInfoLog);
				szInfoLog = NULL;
				uninitialize();//exit is available in this function
			}
		}
	}


	//Fragment shader
	const GLchar* fragmentShaderCode =
		"#version 460 core" \
		"\n" \
		"out vec4 FragColor;" \
		"uniform vec4 uColor;"\
		"void main(void)" \
		"{" \
		"	FragColor = uColor;" \
		"}";

	fragmentShaderObject = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderObject, 1, (const GLchar**)&fragmentShaderCode, NULL);
	glCompileShader(fragmentShaderObject);

	status = 0;
	infoLogLength = 0;
	szInfoLog = NULL;

	glGetShaderiv(fragmentShaderObject, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		glGetShaderiv(fragmentShaderObject, GL_INFO_LOG_LENGTH, &infoLogLength);
		if (infoLogLength > 0)
		{
			szInfoLog = (GLchar*)malloc(infoLogLength);
			if (szInfoLog != NULL)
			{
				glGetShaderInfoLog(fragmentShaderObject, infoLogLength, NULL, szInfoLog);
				fprintf(gpFILE, "Fragment shader compilation error log: %s\n", szInfoLog);
				free(szInfoLog);
				szInfoLog = NULL;
				uninitialize();
			}
		}
	}

	//Create Shader program
	shaderProgramObject = glCreateProgram();
	glAttachShader(shaderProgramObject, vertexShaderObject);
	glAttachShader(shaderProgramObject, fragmentShaderObject);
	glBindAttribLocation(shaderProgramObject, AMC_ATTRIBUTE_POSITION, "aPosition");
	glBindAttribLocation(shaderProgramObject, AMC_ATTRIBUTE_COLOR, "aColor");

	glLinkProgram(shaderProgramObject);
	status = 0;
	infoLogLength = 0;
	szInfoLog = NULL;

	glGetProgramiv(shaderProgramObject, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		glGetProgramiv(shaderProgramObject, GL_INFO_LOG_LENGTH, &infoLogLength);
		if (infoLogLength > 0)
		{
			szInfoLog = (GLchar*)malloc(infoLogLength);
			if (szInfoLog != NULL)
			{
				glGetProgramInfoLog(shaderProgramObject, infoLogLength, NULL, szInfoLog);
				fprintf(gpFILE, "Shader program linking error log : %s\n", szInfoLog);
				free(szInfoLog);
				szInfoLog = NULL;
				uninitialize();
			}
		}
	}

	//Get shader uniform locations
    mvpMatrixUniform = glGetUniformLocation(shaderProgramObject, "uMvpMatrix");
	colorUniform = glGetUniformLocation(shaderProgramObject, "uColor");

	
	//VAO - vertex array object
	glGenVertexArrays(1, &vao_graph);
	glBindVertexArray(vao_graph);
	{
		glGenBuffers(1, &VBO_positions);
		glBindBuffer(GL_ARRAY_BUFFER, VBO_positions);
		
		graph_vertices.push_back(vmath::vec3(-1.0f, 0.0f, 0.0f));
		graph_vertices.push_back(vmath::vec3(1.0f, 0.0f, 0.0f));

		graph_vertices.push_back(vmath::vec3(0.0f, 1.0f, 0.0f));
		graph_vertices.push_back(vmath::vec3(0.0f, -1.0f, 0.0f));

		float y = 0.0f;
		for (int i = 0; i < 20; ++i)
		{
			y += 0.05f;
			graph_vertices.push_back(vmath::vec3(-1.0f, y, 0.0f));
			graph_vertices.push_back(vmath::vec3(1.0f, y, 0.0f));
			graph_vertices.push_back(vmath::vec3(-1.0f, -y, 0.0f));
			graph_vertices.push_back(vmath::vec3(1.0f, -y, 0.0f));

			graph_vertices.push_back(vmath::vec3(y, 1.0f, 0.0f));
			graph_vertices.push_back(vmath::vec3(y, -1.0f, 0.0f));
			graph_vertices.push_back(vmath::vec3(-y, 1.0f, 0.0f));
			graph_vertices.push_back(vmath::vec3(-y, -1.0f, 0.0f));

		}
		glBufferData(GL_ARRAY_BUFFER, sizeof(vmath::vec3) * graph_vertices.size(), graph_vertices.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(AMC_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(AMC_ATTRIBUTE_POSITION);
		
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	//For Square
	//VAO - vertex array object
	glGenVertexArrays(1, &vao_square);
	glBindVertexArray(vao_square);
	{
		glGenBuffers(1, &VBO_positions);
		glBindBuffer(GL_ARRAY_BUFFER, VBO_positions);

		square_vertices.push_back(vmath::vec3(-0.5f, 0.5f, 0.0f));
		square_vertices.push_back(vmath::vec3(0.5f, 0.5f, 0.0f));

		square_vertices.push_back(vmath::vec3(0.5f, -0.5f, 0.0f));
		square_vertices.push_back(vmath::vec3(-0.5f, -0.5f, 0.0f));

		square_vertices.push_back(vmath::vec3(-0.5f, 0.5f, 0.0f));
		square_vertices.push_back(vmath::vec3(-0.5f, -0.5f, 0.0f));

		square_vertices.push_back(vmath::vec3(0.5f, 0.5f, 0.0f));
		square_vertices.push_back(vmath::vec3(0.5f, -0.5f, 0.0f));

		glBufferData(GL_ARRAY_BUFFER, sizeof(vmath::vec3) * square_vertices.size(), square_vertices.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(AMC_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(AMC_ATTRIBUTE_POSITION);

	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	
	//For Triangle
	//VAO - vertex array object
	glGenVertexArrays(1, &vao_triangle);
	glBindVertexArray(vao_triangle);
	{
		glGenBuffers(1, &VBO_positions);
		glBindBuffer(GL_ARRAY_BUFFER, VBO_positions);

		triangle_vertices.push_back(vmath::vec3(0.0f, 0.5f, 0.0f));
		triangle_vertices.push_back(vmath::vec3(-0.5f, -0.5f, 0.0f));

		triangle_vertices.push_back(vmath::vec3(-0.5f, -0.5f, 0.0f));
		triangle_vertices.push_back(vmath::vec3(0.5f, -0.5f, 0.0f));

		triangle_vertices.push_back(vmath::vec3(0.5f, -0.5f, 0.0f));
		triangle_vertices.push_back(vmath::vec3(0.0f, 0.5f, 0.0f));

		glBufferData(GL_ARRAY_BUFFER, sizeof(vmath::vec3) * triangle_vertices.size(), triangle_vertices.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(AMC_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(AMC_ATTRIBUTE_POSITION);

	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Circle
	//VAO - vertex array object
	glGenVertexArrays(1, &vao_circle);
	glBindVertexArray(vao_circle);
	{
		glGenBuffers(1, &VBO_positions);
		glBindBuffer(GL_ARRAY_BUFFER, VBO_positions);

		for (int i = 0; i <= 100; ++i)
		{
			circle_vertices.push_back(vmath::vec3(0.0f + (0.5f * cosf(2 * M_PI * i / 100)), 0.0f + (0.5f * sinf(2 * M_PI * i / 100)), 0.0f));

		}
		
		glBufferData(GL_ARRAY_BUFFER, sizeof(vmath::vec3) * circle_vertices.size(), circle_vertices.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(AMC_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(AMC_ATTRIBUTE_POSITION);

	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0);

	//Enabling depth
	glClearDepth(1.0f);//depth buffer to 1
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);//check less than or equal to with 1.0f

	//Set the Clear color of Window to Blue
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //here OpenGL starts

	//Init orhto proj matrix
	perspectiveGraphicsProjectionMatrix = vmath::mat4::identity();

    resize(WIDTH, HEIGHT);
	return 0;
}

void printGLInfo()
{
	//variable declaration
	GLint numExtensions;
	GLint i;

	//code
	fprintf(gpFILE, "OpenGL Vendor    : %s\n", glGetString(GL_VENDOR));
	fprintf(gpFILE, "OpenGL Renderer  : %s\n", glGetString(GL_RENDERER));
	fprintf(gpFILE, "OpenGL Version   : %s\n", glGetString(GL_VERSION));
	fprintf(gpFILE, "OpenGL GLSL version : %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

	//Supported extensions list
	glGetIntegerv(GL_NUM_EXTENSIONS, &numExtensions);
	for (i = 0; i < numExtensions; ++i)
	{
		fprintf(gpFILE, "%s\n", glGetStringi(GL_EXTENSIONS, i));
	}
}

void resize(int width, int height)
{
	//code
	if (height <= 0)
	{
		height = 1;

	}

	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

    //set perspective projection matrix
    perspectiveGraphicsProjectionMatrix = vmath::perspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);


}

void graphPaper()
{
	glUniform4fv(colorUniform, 1, vmath::vec4(1.0, 0.0, 0.0, 1.0));
	glBindVertexArray(vao_graph);
	glLineWidth(2.0f);
	glDrawArrays(GL_LINES, 0, 4);

	glLineWidth(1.0f);
	glUniform4fv(colorUniform, 1, vmath::vec4(0.0, 0.0, 1.0, 1.0));
	glDrawArrays(GL_LINES, 4, graph_vertices.size());

}

void display(void)
{
	//code
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(shaderProgramObject);

    //X-formation
    mat4 modelViewMatrix = vmath::translate(0.0f, 0.0f, -3.0f);
    mat4 modelViewProjectionMatrix = perspectiveGraphicsProjectionMatrix * modelViewMatrix;

    //Push above MVP info vertex shader's mvpUniform
    glUniformMatrix4fv(mvpMatrixUniform, 1, GL_FALSE, modelViewProjectionMatrix);

	switch (c)
	{
	case 'g':
		//for graph----------------------
		graphPaper();
		break;
	case 'c':
		graphPaper();
		//Circle------------
		glLineWidth(1.5f);
		glBindVertexArray(vao_circle);
		glUniform4fv(colorUniform, 1, vmath::vec4(0.0, 1.0, 0.0, 1.0));
		glDrawArrays(GL_LINE_LOOP, 0, circle_vertices.size());
		
		break;
	case 't':
		graphPaper();
		//Triangle------------
		glLineWidth(1.5f);
		glBindVertexArray(vao_triangle);
		glUniform4fv(colorUniform, 1, vmath::vec4(1.0, 0.0, 1.0, 1.0));
		glDrawArrays(GL_LINES, 0, triangle_vertices.size());

		break;
	case 's':
		graphPaper();
		//Square------------
		glLineWidth(1.5f);
		glBindVertexArray(vao_square);
		glUniform4fv(colorUniform, 1, vmath::vec4(1.0, 1.0, 0.0, 1.0));
		glDrawArrays(GL_LINES, 0, square_vertices.size());

		break;

	}
	
	


	glBindVertexArray(0);
	glUseProgram(0);

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
	if (shaderProgramObject)
	{
		glUseProgram(shaderProgramObject);
		GLint numShader = 0;

		glGetProgramiv(shaderProgramObject, GL_ATTACHED_SHADERS, &numShader);

		if (numShader > 0)
		{
			GLuint* pShaders = (GLuint*)malloc(numShader * sizeof(GLuint));
			if (pShaders != NULL)
			{
				glGetAttachedShaders(shaderProgramObject, numShader, NULL, pShaders);
				for (GLint i = 0; i < numShader; ++i)
				{
					glDetachShader(shaderProgramObject, pShaders[i]);
					glDeleteShader(pShaders[i]);
					pShaders[i] = 0;
				}
				free(pShaders);
				pShaders = NULL;
			}
		}
		glUseProgram(0);
		glDeleteProgram(shaderProgramObject);
		shaderProgramObject = 0;
	}


	//delete VBO of position
	if (VBO_positions)
	{
		glDeleteBuffers(1, &VBO_positions);
		VBO_positions = 0;
	}

	//delete VAO
	if (VAO)
	{
		glDeleteVertexArrays(1, &VAO);
		VAO = 0;
	}

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