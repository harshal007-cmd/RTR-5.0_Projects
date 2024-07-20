	//xxxxxx OpenGL PP Starts.... First Code xxxxxx//
//Common header files
#include<windows.h>//win32
#include"Window.h" //or OGL.h (if rename)
#include<stdio.h>///for file IO
#include<stdlib.h>//for exit()
#include"Sphere.h"
//OpenGL Header files
#include"GL\glew.h"//this must be before gl.h
#include<GL/GL.h>

#include<stack>
#include"vmath.h"
using namespace vmath;




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
	AMC_ATTRIBUTE_NORMAL
};

GLuint VAO_Sphere = 0;
GLuint VBO_Sphere_Position = 0;
GLuint VBO_Normal_Sphere = 0;
GLuint VBO_Color_Sphere = 0;
GLuint VBO_Sphere_Element = 0;

//GLuint mvpMatrixUniform = 0;
GLuint modelViewMatrixUniform = 0;
GLuint viewMatrixUniform = 0;
GLuint projectionMatrixUniform = 0;
GLuint ldUniform = 0;
GLuint kdUniform = 0;
GLuint lightPositionUniform = 0;
GLuint keyPressUniform = 0;

BOOL bLightingEnable = FALSE;
BOOL bAnimationEnable = FALSE;

GLfloat lightDiffuse[] = { 1.0,1.0,1.0,1.0 };
GLfloat materialDiffuse[] = { 1.0f, 1.0f , 1.0f, 1.0f };
GLfloat lightPosition[]={1.6, 0.6, 0.0, 1.0};

//Sphere related 
float sphere_vertices[1146];
float sphere_normals[1146];
float sphere_textures[764];
unsigned short sphere_elements[2280];

std::stack<vmath::mat4> ModelStack;
static int year = 0, day = 0, moon = 0;

mat4 perspectiveProjetionMatrix;  //in vmath


//Macros
#define WIDTH 800
#define HEIGHT 600

//Link with OpenGL Lib
#pragma comment(lib,"glew32.lib")
#pragma comment(lib,"openGL32.lib")
#pragma comment(lib,"Sphere.lib")

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


GLfloat pAngle = 0.0f;
GLfloat cAngle = 0.0f;

GLuint gNumVertices;
GLuint gNumElements;

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

				if(bAnimationEnable == TRUE)
				{
					//Update
					update();
			
				}
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
		case 'Y':
			year = (year + 3) % 360;
			break;
		case 'y':
			year = (year - 3) % 360;
			break;
		case 'd':
			day = (day + 6) % 360;
			break;
		case 'D':
			day = (day - 6) % 360;
			break;
		case 'm':
			moon = (moon + 6) % 360;
			break;
		case 'M':
			moon = (moon - 6) % 360;
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
	"in vec3 aNormal;" \
    "uniform mat4 uModelViewMatrix;" \
	"uniform mat4 uProjectionMatrix;" \
	"uniform mat4 uViewMatrix;" \
	"uniform vec3 uLd;" \
	"uniform vec3 uKd;" \
	"uniform vec4 uLightPosition;" \
	"uniform int uKeyPress;" \
	"out vec3 oDiffuseLight;" \
	"void main(void)" \
	"{" \
	"if(uKeyPress == 1)"
	"{"
	"vec4 iPosition = uModelViewMatrix * uViewMatrix * aPosition;"
	"mat3 normalMatrix = mat3(transpose(inverse(uModelViewMatrix)));"
	"vec3 n = normalize(normalMatrix * aNormal);"
	"vec3 s = normalize(vec3(uLightPosition - iPosition));"
	"oDiffuseLight = uLd * uKd * max(dot(s, n),0);"
	"}"
	"else"
	"{"
	"oDiffuseLight = vec3(0.0, 0.0, 0.0);"
	"}"
	"gl_Position = uProjectionMatrix * uViewMatrix * uModelViewMatrix * aPosition;"
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
	"in vec3 oDiffuseLight;" \
	"uniform int uKeyPress;" \
	"out vec4 FragColor;" \
	"void main(void)" \
	"{" \
	"if(uKeyPress == 1)"
	"{"
	"FragColor = vec4(oDiffuseLight, 1.0);"
	"}"
	"else"
	"{"
	"FragColor = vec4(1.0, 1.0, 1.0, 1.0);"
	"}" 
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
	glBindAttribLocation(shaderProgramObject, AMC_ATTRIBUTE_NORMAL, "aNormal");
	//glBindAttribLocation(shaderProgramObject, AMC_ATTRIBUTE_COLOR, "aColor");

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

	modelViewMatrixUniform = glGetUniformLocation(shaderProgramObject, "uModelViewMatrix");
	projectionMatrixUniform = glGetUniformLocation(shaderProgramObject, "uProjectionMatrix");
	viewMatrixUniform = glGetUniformLocation(shaderProgramObject, "uViewMatrix");
	ldUniform = glGetUniformLocation(shaderProgramObject, "uLd");
	kdUniform = glGetUniformLocation(shaderProgramObject, "uKd");
	lightPositionUniform = glGetUniformLocation(shaderProgramObject, "uLightPosition");
	keyPressUniform = glGetUniformLocation(shaderProgramObject, "uKeyPress");



    getSphereVertexData(sphere_vertices, sphere_normals, sphere_textures, sphere_elements);
    gNumVertices = getNumberOfSphereVertices();
    gNumElements = getNumberOfSphereElements();


    //Sphere
	// vao
    glGenVertexArrays(1, &VAO_Sphere);
    glBindVertexArray(VAO_Sphere);

    // position vbo
    glGenBuffers(1, &VBO_Sphere_Position);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Sphere_Position);
    glBufferData(GL_ARRAY_BUFFER, sizeof(sphere_vertices), sphere_vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(AMC_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    glEnableVertexAttribArray(AMC_ATTRIBUTE_POSITION);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // normal vbo
    glGenBuffers(1, &VBO_Normal_Sphere);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Normal_Sphere);
    glBufferData(GL_ARRAY_BUFFER, sizeof(sphere_normals), sphere_normals, GL_STATIC_DRAW);

    glVertexAttribPointer(AMC_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    glEnableVertexAttribArray(AMC_ATTRIBUTE_NORMAL);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // element vbo
    glGenBuffers(1, &VBO_Sphere_Element);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO_Sphere_Element);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(sphere_elements), sphere_elements, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // unbind vao
    glBindVertexArray(0);


	//Enabling depth
	glClearDepth(1.0f);//depth buffer to 1
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);//check less than or equal to with 1.0f

	//Set the Clear color of Window to Blue
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //here OpenGL starts

	perspectiveProjetionMatrix = vmath::mat4::identity();

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
	perspectiveProjetionMatrix = vmath::perspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);

}

void display(void)
{
	//code
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(shaderProgramObject);

	ModelStack.push(mat4::identity());	
	ModelStack.push(ModelStack.top() * vmath::translate(0.0f, 0.0f, -5.0f));
	//Cube-----------
    mat4 modelViewMatrix = mat4::identity();
	mat4 viewMatrix = mat4::identity();
	mat4 translationMatrix = mat4::identity();
	mat4 modelViewProjectionMatrix = mat4::identity();


    modelViewProjectionMatrix = perspectiveProjetionMatrix * modelViewMatrix;


    //Push above MVP info vertex shader's mvpUniform
    glUniformMatrix4fv(modelViewMatrixUniform, 1, GL_FALSE, ModelStack.top());
	glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, viewMatrix);
	glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, perspectiveProjetionMatrix);

	glUniform1i(keyPressUniform, 1);
	glUniform3fv(ldUniform, 1, lightDiffuse);
	glUniform3fv(kdUniform, 1, materialDiffuse);
	glUniform4fv(lightPositionUniform, 1, lightPosition);


	// *** bind vao ***
    glBindVertexArray(VAO_Sphere);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO_Sphere_Element);
    glDrawElements(GL_TRIANGLES, gNumElements, GL_UNSIGNED_SHORT, 0);

	//earth
	ModelStack.push(ModelStack.top() * vmath::rotate((GLfloat)year, 0.0f, 1.0f, 0.0f) * vmath::translate(1.5f, 0.0f, 0.0f) * vmath::rotate((GLfloat)day, 0.0f, 1.0f, 0.0f) * vmath::scale(0.75f, 0.75f, 0.75f));
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glUniformMatrix4fv(modelViewMatrixUniform, 1, GL_FALSE, ModelStack.top());
	glDrawElements(GL_TRIANGLES, gNumElements, GL_UNSIGNED_SHORT, 0);


	ModelStack.pop();
	ModelStack.push(ModelStack.top() * vmath::rotate((GLfloat)year, 0.0f, 1.0f, 0.0f) * vmath::translate(1.5f, 0.0f, 0.0f));
	ModelStack.push(ModelStack.top() * vmath::rotate((GLfloat)moon, 0.0f, 1.0f, 0.0f) * vmath::translate(0.8f, 0.0f, 0.0f) * vmath::scale(0.25f, 0.25f, 0.25f));

	glUniformMatrix4fv(modelViewMatrixUniform, 1, GL_FALSE, ModelStack.top());
	glDrawElements(GL_TRIANGLES, gNumElements, GL_UNSIGNED_SHORT, 0);

	ModelStack.pop();
	ModelStack.pop();

    // *** unbind vao ***
    glBindVertexArray(0);


	glUseProgram(0);

	SwapBuffers(ghdc);


}

void update(void)
{
	//code
	pAngle += 0.07f;
	if (pAngle >= 360.0f)
	{
		pAngle = pAngle - 360.0f;
	}

	cAngle += 0.07f;
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


	//Cube
	//delete VBO of position
	if (VBO_Sphere_Position)
	{
		glDeleteBuffers(1, &VBO_Sphere_Position);
		VBO_Sphere_Position = 0;
	}

	//delete VAO
	if (VAO_Sphere)
	{
		glDeleteVertexArrays(1, &VAO_Sphere);
		VAO_Sphere = 0;
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
