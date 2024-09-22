//Common header files
#include<windows.h>//win32
#include"Window.h" //or OGL.h (if rename)
#include<stdio.h>///for file IO
#include<stdlib.h>//for exit()

#define _USE_MATH_DEFINES 1
#include<math.h>

//OpenGL Header files
#include"GL/glew.h"//this must be before gl.h
#include<GL/GL.h>

#include"vmath.h"
using namespace vmath;

#include"Sphere.h"

//Link with OpenGL Lib
#pragma comment(lib,"glew32.lib")
#pragma comment(lib,"openGL32.lib")
#pragma comment(lib,"Sphere.lib")


//OpenGL related Global Variables
HDC ghdc = NULL;
HGLRC ghrc = NULL; //handle to GL Rendering Contex

GLuint vertexShaderObject_pf = 0;
GLuint fragmentShaderObject_pf = 0;
GLuint shaderProgramObject_pf = 0;

GLuint vertexShaderObject_pv = 0;
GLuint fragmentShaderObject_pv = 0;
GLuint shaderProgramObject_pv = 0;

enum
{
	AMC_ATTRIBUTE_POSITION = 0,
	AMC_ATTRIBUTE_NORMAL
};

GLuint VAO_Sphere = 0;
GLuint VBO_Sphere_Position = 0;
GLuint VBO_Normal_Sphere = 0;
GLuint VBO_Sphere_Element = 0;


GLuint VAO_Sphere2 = 0;
GLuint VBO_Sphere_Position2 = 0;
GLuint VBO_Normal_Sphere2 = 0;
GLuint VBO_Sphere_Element2 = 0;


//GLuint mvpMatrixUniform = 0;
GLuint modelViewMatrixUniform = 0;
GLuint projectionMatrixUniform = 0;
GLuint viewMatrixUniform = 0;

GLuint lightDiffuseUniform[3];
GLuint lightAmbientUniform[3];
GLuint lightSpecularUniform[3];
GLuint lightPositionUniform[3];

GLuint materialDiffuseUniform = 0;
GLuint materialAmbientUniform = 0;
GLuint materialSpecularUniform = 0;
GLuint materialShininessUniform = 0;
GLuint keyPressUniform = 0;



BOOL bLightingEnable = FALSE;
BOOL bAnimationEnable = FALSE;


GLfloat materialAmbient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat materialDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat materialSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat materialShiness = 150.0f;

struct Light {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	vec4 position;
};

struct Light light[3];
//Sphere related 
float sphere_vertices[1146];
float sphere_normals[1146];
float sphere_textures[764];
unsigned short sphere_elements[2280];

GLfloat X, Y, Z;
GLfloat rangle;

mat4 perspectiveProjetionMatrix;  //in vmath

char change = 'f';


//Macros
#define WIDTH 800
#define HEIGHT 600


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
		TEXT("HVS: Programable Pipeline"),
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
		//	DestroyWindow(hwnd);
			ToogleFullScreen();
			break;
		}
		break;
	case WM_CHAR:
		switch (LOWORD(wParam))
		{
		case 'q':
		case 'Q':
			DestroyWindow(hwnd);
			break;
		case 'L':
		case 'l':
			if (bLightingEnable)
				bLightingEnable = FALSE;
			else
				bLightingEnable = TRUE;
			break;
		case 'v':
		case 'V':
			change = 'v';
			break;
		case 'f':
		case 'F':
			change = 'f';
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

	//Vertex shader PV-------------------------------------
	const GLchar* vertexShaderCode_pv =
		"#version 460 core" \
		"\n" \
		"in vec4 aPosition;" \
		"in vec3 aNormal;" \
		"uniform mat4 uModelViewMatrix;" \
		"uniform mat4 uViewMatrix;" \
		"uniform mat4 uProjectionMatrix;" \
		"uniform vec3 uLightAmbient[3];" \
		"uniform vec3 uLightDiffuse[3];" \
		"uniform vec3 uLightSpecular[3];" \
		"uniform vec4 uLightPosition[3];" \
		"\n"\
		"uniform vec3 uMaterialAmbient;" \
		"uniform vec3 uMaterialDiffuse;" \
		"uniform vec3 uMaterialSpecular;" \
		"uniform float uMaterialShininess;" \
		"uniform int uKeyPress;" \
		"out vec3 oPhongADSLight;" \
		"void main(void)" \
		"{" \
		"if(uKeyPress == 1)"
		"{"
		"	vec3 reflectionVector[3];"
		"	vec3 ambientLight[3];"
		"	vec3 diffuseLight[3];"
		"	vec3 lightSpecular[3];"
		"	vec3 lightDirection[3];"
		"\n"
		"vec4 iCoordinates = uViewMatrix * uModelViewMatrix * aPosition;"
		"vec3 transformedNormals = normalize(mat3(uViewMatrix * uModelViewMatrix) * aNormal);"
		"vec3 viewerVector = normalize(-iCoordinates.xyz);"
		"	for(int i=0;i<3;i++)"
		"	{"
		"		lightDirection[i] = normalize(vec3(uLightPosition[i] - iCoordinates));"
		"		reflectionVector[i] = reflect(-lightDirection[i], transformedNormals);"
		"		ambientLight[i] = uLightAmbient[i] * uMaterialAmbient;"
		"		diffuseLight[i] = uLightDiffuse[i] * uMaterialDiffuse * max(dot(lightDirection[i], transformedNormals),0.0);"
		"		lightSpecular[i] = uLightSpecular[i] * uMaterialSpecular * pow(max(dot(reflectionVector[i], viewerVector),0.0),uMaterialShininess);"
		"		oPhongADSLight = oPhongADSLight + ambientLight[i] + diffuseLight[i] + lightSpecular[i];"
		"	}"
		"}"
		"else"
		"{"
		"	oPhongADSLight = vec3(0.0f, 0.0f, 0.0f);"
		"}"
		"	gl_Position = uProjectionMatrix * uViewMatrix * uModelViewMatrix * aPosition;"
		"}";


	vertexShaderObject_pv = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderObject_pv, 1, (const GLchar**)&vertexShaderCode_pv, NULL);
	glCompileShader(vertexShaderObject_pv);

	GLint status = 0;
	GLint infoLogLength = 0;
	GLchar* szInfoLog = NULL;

	glGetShaderiv(vertexShaderObject_pv, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		glGetShaderiv(vertexShaderObject_pv, GL_INFO_LOG_LENGTH, &infoLogLength);
		if (infoLogLength > 0)
		{
			szInfoLog = (GLchar*)malloc(infoLogLength);
			if (szInfoLog != NULL)
			{
				glGetShaderInfoLog(vertexShaderObject_pv, infoLogLength, NULL, szInfoLog);
				fprintf(gpFILE, "Vertex Shader compilation error log: %s\n", szInfoLog);
				free(szInfoLog);
				szInfoLog = NULL;
				uninitialize();//exit is available in this function
			}
		}
	}

	
	//Fragment shader
	const GLchar* fragmentShaderCode_pv =
		"#version 460 core" \
		"\n" \
		"in vec3 oPhongADSLight;" \
		"uniform int uKeyPress;" \
		"out vec4 FragColor;" \
		"void main(void)" \
		"{" \
		"if(uKeyPress == 1)"
		"{"
		"FragColor = vec4(oPhongADSLight, 1.0f);"
		"}"
		"else"
		"{"
		"FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);"
		"}"
		"}";

	fragmentShaderObject_pv = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderObject_pv, 1, (const GLchar**)&fragmentShaderCode_pv, NULL);
	glCompileShader(fragmentShaderObject_pv);

	status = 0;
	infoLogLength = 0;
	szInfoLog = NULL;

	glGetShaderiv(fragmentShaderObject_pv, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		glGetShaderiv(fragmentShaderObject_pv, GL_INFO_LOG_LENGTH, &infoLogLength);
		if (infoLogLength > 0)
		{
			szInfoLog = (GLchar*)malloc(infoLogLength);
			if (szInfoLog != NULL)
			{
				glGetShaderInfoLog(fragmentShaderObject_pv, infoLogLength, NULL, szInfoLog);
				fprintf(gpFILE, "Fragment shader compilation error log: %s\n", szInfoLog);
				free(szInfoLog);
				szInfoLog = NULL;

			}
		}uninitialize();
	}

	shaderProgramObject_pv = glCreateProgram();
	glAttachShader(shaderProgramObject_pv, vertexShaderObject_pv);
	glAttachShader(shaderProgramObject_pv, fragmentShaderObject_pv);
	glBindAttribLocation(shaderProgramObject_pv, AMC_ATTRIBUTE_POSITION, "aPosition");
	glBindAttribLocation(shaderProgramObject_pv, AMC_ATTRIBUTE_NORMAL, "aNormal");
	//glBindAttribLocation(shaderProgramObject, AMC_ATTRIBUTE_COLOR, "aColor");

	glLinkProgram(shaderProgramObject_pv);
	status = 0;
	infoLogLength = 0;
	szInfoLog = NULL;


	glGetProgramiv(shaderProgramObject_pv, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		glGetProgramiv(shaderProgramObject_pv, GL_INFO_LOG_LENGTH, &infoLogLength);
		if (infoLogLength > 0)
		{
			szInfoLog = (GLchar*)malloc(infoLogLength);
			if (szInfoLog != NULL)
			{
				glGetProgramInfoLog(shaderProgramObject_pv, infoLogLength, NULL, szInfoLog);
				fprintf(gpFILE, "Shader program linking error log : %s\n", szInfoLog);
				free(szInfoLog);
				szInfoLog = NULL;
			}
		}
		uninitialize();
	}


	modelViewMatrixUniform = glGetUniformLocation(shaderProgramObject_pv, "uModelViewMatrix");
	viewMatrixUniform = glGetUniformLocation(shaderProgramObject_pv, "uViewMatrix");
	projectionMatrixUniform = glGetUniformLocation(shaderProgramObject_pv, "uProjectionMatrix");
	//---
	lightAmbientUniform[0] = glGetUniformLocation(shaderProgramObject_pv, "uLightAmbient[0]");
	lightDiffuseUniform[0] = glGetUniformLocation(shaderProgramObject_pv, "uLightDiffuse[0]");
	lightSpecularUniform[0] = glGetUniformLocation(shaderProgramObject_pv, "uLightSpecular[0]");
	lightPositionUniform[0] = glGetUniformLocation(shaderProgramObject_pv, "uLightPosition[0]");

	lightAmbientUniform[1] = glGetUniformLocation(shaderProgramObject_pv, "uLightAmbient[1]");
	lightDiffuseUniform[1] = glGetUniformLocation(shaderProgramObject_pv, "uLightDiffuse[1]");
	lightSpecularUniform[1] = glGetUniformLocation(shaderProgramObject_pv, "uLightSpecular[1]");
	lightPositionUniform[1] = glGetUniformLocation(shaderProgramObject_pv, "uLightPosition[1]");

	lightAmbientUniform[2] = glGetUniformLocation(shaderProgramObject_pv, "uLightAmbient[2]");
	lightDiffuseUniform[2] = glGetUniformLocation(shaderProgramObject_pv, "uLightDiffuse[2]");
	lightSpecularUniform[2] = glGetUniformLocation(shaderProgramObject_pv, "uLightSpecular[2]");
	lightPositionUniform[2] = glGetUniformLocation(shaderProgramObject_pv, "uLightPosition[2]");

	//---
	materialAmbientUniform = glGetUniformLocation(shaderProgramObject_pv, "uMaterialAmbient");
	materialDiffuseUniform = glGetUniformLocation(shaderProgramObject_pv, "uMaterialDiffuse");
	materialSpecularUniform = glGetUniformLocation(shaderProgramObject_pv, "uMaterialSpecular");
	materialShininessUniform = glGetUniformLocation(shaderProgramObject_pv, "uMaterialShininess");

	keyPressUniform = glGetUniformLocation(shaderProgramObject_pv, "uKeyPress");


		


	//Vertex Shader PF -----------------------------------------------
	const GLchar* vertexShaderCode_pf =
		"#version 460 core" \
		"\n" \
		"in vec4 aPosition;" \
		"in vec3 aNormal;" \
		"uniform mat4 uModelViewMatrix;" \
		"uniform mat4 uViewMatrix;" \
		"uniform mat4 uProjectionMatrix;" \
		"uniform vec4 uLightPosition[3];" \
		"\n"\
		"uniform int uKeyPress;" \
		"out vec3 oTransformedNormals;"\
		"out vec3 oLightDirection[3];"\
		"out vec3 oViewerVector;"\
		"vec3 lightDirection[3];"
		"void main(void)" \
		"{" \
		"if(uKeyPress == 1)"
		"{"
		"vec4 iCoordinates = uViewMatrix * uModelViewMatrix * aPosition;"
		"oTransformedNormals = mat3(uViewMatrix * uModelViewMatrix) * aNormal;"
		"oViewerVector = -iCoordinates.xyz;"
		"	for(int i=0;i<3;i++)"
		"	{"
		"		lightDirection[i] = normalize(vec3(uLightPosition[i] - iCoordinates));"
		"		oLightDirection[i] = vec3(uLightPosition[i] - iCoordinates);"
		"	}"
		"}"
		"else"
		"{"
		"	oTransformedNormals = vec3(0.0, 0.0, 0.0); "
		"	for(int i=0;i<3;i++)"
		"	{"
		"		oLightDirection[i] = vec3(0.0, 0.0, 0.0);"
		"	}"
		"oViewerVector = vec3(0.0, 0.0, 0.0);"
		"}"
		"gl_Position = uProjectionMatrix * uViewMatrix * uModelViewMatrix * aPosition;"
		"}";

	vertexShaderObject_pf = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderObject_pf, 1, (const GLchar**)&vertexShaderCode_pf, NULL);
	glCompileShader(vertexShaderObject_pf);

	status = 0;
	infoLogLength = 0;
	szInfoLog = NULL;

	glGetShaderiv(vertexShaderObject_pf, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		glGetShaderiv(vertexShaderObject_pf, GL_INFO_LOG_LENGTH, &infoLogLength);
		if (infoLogLength > 0)
		{
			szInfoLog = (GLchar*)malloc(infoLogLength);
			if (szInfoLog != NULL)
			{
				glGetShaderInfoLog(vertexShaderObject_pf, infoLogLength, NULL, szInfoLog);
				fprintf(gpFILE, "Vertex Shader compilation error log: %s\n", szInfoLog);
				free(szInfoLog);
				szInfoLog = NULL;
				uninitialize();//exit is available in this function
			}
		}
	}


	//Fragment shader
	const GLchar* fragmentShaderCode_pf =
		"#version 460 core" \
		"\n" \
		"in vec3 oTransformedNormals;"\
		"in vec3 oLightDirection[3];" \
		"in vec3 oViewerVector; "
		"uniform vec3 uLightAmbient[3];" \
		"uniform vec3 uLightDiffuse[3];" \
		"uniform vec3 uLightSpecular[3];" \
		"\n"\
		"uniform vec3 uMaterialAmbient;" \
		"uniform vec3 uMaterialDiffuse;" \
		"uniform vec3 uMaterialSpecular;" \
		"uniform float uMaterialShininess;" \
		"uniform int uKeyPress;" \
		"out vec4 FragColor;" \
		"void main(void)" \
		"{" \
		"vec3 phongADSLight;"
		"if(uKeyPress == 1)"
		"{"
		"	vec3 reflectionVector[3];"
		"	vec3 ambientLight[3];"
		"	vec3 diffuseLight[3];"
		"	vec3 lightSpecular[3];"
		"\n"
		"	vec3 normalizedTransformedNormal = normalize(oTransformedNormals);"
		"	vec3 normalizedViewerVector = normalize(oViewerVector);"
		"	for(int i;i<3;i++)"
		"	{"
		"		vec3 normalizedLightDirection = normalize(oLightDirection[i]);"
		"		ambientLight[i] = uLightAmbient[i] * uMaterialAmbient;"
		"		diffuseLight[i] = uLightDiffuse[i] * uMaterialDiffuse * max(dot(normalizedLightDirection, normalizedTransformedNormal), 0.0);"
		"		reflectionVector[i] = reflect(-normalizedLightDirection, normalizedTransformedNormal);"
		"		lightSpecular[i] = uLightSpecular[i] * uMaterialSpecular * pow(max(dot(reflectionVector[i], normalizedViewerVector), 0.0), uMaterialShininess);"
		"		phongADSLight = phongADSLight + ambientLight[i] + diffuseLight[i] + lightSpecular[i];"
		"	}"
		"}"
		"else"
		"{"
		"	phongADSLight = vec3(1.0, 1.0, 1.0);"
		"}"
		"	FragColor = vec4(phongADSLight, 1.0);"
		"}";

	fragmentShaderObject_pf = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderObject_pf, 1, (const GLchar**)&fragmentShaderCode_pf, NULL);
	glCompileShader(fragmentShaderObject_pf);

	status = 0;
	infoLogLength = 0;
	szInfoLog = NULL;

	glGetShaderiv(fragmentShaderObject_pf, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		glGetShaderiv(fragmentShaderObject_pf, GL_INFO_LOG_LENGTH, &infoLogLength);
		if (infoLogLength > 0)
		{
			szInfoLog = (GLchar*)malloc(infoLogLength);
			if (szInfoLog != NULL)
			{
				glGetShaderInfoLog(fragmentShaderObject_pf, infoLogLength, NULL, szInfoLog);
				fprintf(gpFILE, "Fragment shader compilation error log: %s\n", szInfoLog);
				free(szInfoLog);
				szInfoLog = NULL;
				uninitialize();
			}
		}
	}

	//Create Shader program
	shaderProgramObject_pf = glCreateProgram();
	glAttachShader(shaderProgramObject_pf, vertexShaderObject_pf);
	glAttachShader(shaderProgramObject_pf, fragmentShaderObject_pf);
	glBindAttribLocation(shaderProgramObject_pf, AMC_ATTRIBUTE_POSITION, "aPosition");
	glBindAttribLocation(shaderProgramObject_pf, AMC_ATTRIBUTE_NORMAL, "aNormal");
	//glBindAttribLocation(shaderProgramObject_pf, AMC_ATTRIBUTE_COLOR, "aColor");

	glLinkProgram(shaderProgramObject_pf);
	status = 0;
	infoLogLength = 0;
	szInfoLog = NULL;


	glGetProgramiv(shaderProgramObject_pf, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		glGetProgramiv(shaderProgramObject_pf, GL_INFO_LOG_LENGTH, &infoLogLength);
		if (infoLogLength > 0)
		{
			szInfoLog = (GLchar*)malloc(infoLogLength);
			if (szInfoLog != NULL)
			{
				glGetProgramInfoLog(shaderProgramObject_pf, infoLogLength, NULL, szInfoLog);
				fprintf(gpFILE, "Shader program linking error log : %s\n", szInfoLog);
				free(szInfoLog);
				szInfoLog = NULL;
				
			}
		}
		uninitialize();
	}


	modelViewMatrixUniform = glGetUniformLocation(shaderProgramObject_pf, "uModelViewMatrix");
	viewMatrixUniform = glGetUniformLocation(shaderProgramObject_pf, "uViewMatrix");
	projectionMatrixUniform = glGetUniformLocation(shaderProgramObject_pf, "uProjectionMatrix");
	//---	
	lightAmbientUniform[0] = glGetUniformLocation(shaderProgramObject_pf, "uLightAmbient[0]");
	lightDiffuseUniform[0] = glGetUniformLocation(shaderProgramObject_pf, "uLightDiffuse[0]");
	lightSpecularUniform[0] = glGetUniformLocation(shaderProgramObject_pf, "uLightSpecular[0]");
	lightPositionUniform[0] = glGetUniformLocation(shaderProgramObject_pf, "uLightPosition[0]");

	lightAmbientUniform[1] = glGetUniformLocation(shaderProgramObject_pf, "uLightAmbient[1]");
	lightDiffuseUniform[1] = glGetUniformLocation(shaderProgramObject_pf, "uLightDiffuse[1]");
	lightSpecularUniform[1] = glGetUniformLocation(shaderProgramObject_pf, "uLightSpecular[1]");
	lightPositionUniform[1] = glGetUniformLocation(shaderProgramObject_pf, "uLightPosition[1]");
	
	lightAmbientUniform[2] = glGetUniformLocation(shaderProgramObject_pf, "uLightAmbient[2]");
	lightDiffuseUniform[2] = glGetUniformLocation(shaderProgramObject_pf, "uLightDiffuse[2]");
	lightSpecularUniform[2] = glGetUniformLocation(shaderProgramObject_pf, "uLightSpecular[2]");
	lightPositionUniform[2] = glGetUniformLocation(shaderProgramObject_pf, "uLightPosition[2]");

	//---
	materialAmbientUniform = glGetUniformLocation(shaderProgramObject_pf, "uMaterialAmbient");
	materialDiffuseUniform = glGetUniformLocation(shaderProgramObject_pf, "uMaterialDiffuse");
	materialSpecularUniform = glGetUniformLocation(shaderProgramObject_pf, "uMaterialSpecular");
	materialShininessUniform = glGetUniformLocation(shaderProgramObject_pf, "uMaterialShininess");

	keyPressUniform = glGetUniformLocation(shaderProgramObject_pf, "uKeyPress");



    getSphereVertexData(sphere_vertices, sphere_normals, sphere_textures, sphere_elements);
	//  gNumVertices = getNumberOfSphereVertices();
    gNumElements = getNumberOfSphereElements();

	
	// VAO VBO for PF -----------------------------------------------------
	// vao PV
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


	/*
	//VBO for textures  //not using in this code just for further use
	glGenBuffers(1, &VBO_Texcoords);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_Texcoords);
	glBufferData(GL_ARRAY_BUFFER, sizeof(sphere_texcoords), sphere_texcoords, GL_STATIC_DRAW);
	glVertexAttribPointer(AMC_ATTRIBUTE_TEXCOORDS, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(AMC_ATTRIBUTE_TEXCOORDS);
	glBindBuffers(GL_ARRAY_BUFFERS, 0);
	*/


	//Enabling depth
	glClearDepth(1.0f);//depth buffer to 1
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);//check less than or equal to with 1.0f

	//Set the Clear color of Window to Blue
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //here OpenGL starts

	light[0].ambient = vec3(0.0f, 0.0f, 0.0f);
	light[1].ambient = vec3(0.0f, 0.0f, 0.0f);
	light[2].ambient = vec3(0.0f, 0.0f, 0.0f);

	light[0].diffuse = vec3(1.0f, 0.0f, 0.0f);
	light[1].diffuse = vec3(0.0f, 0.0f, 1.0f);
	light[2].diffuse = vec3(0.0f, 1.0f, 0.0f);

	light[0].specular = vec3(1.0f, 0.0f, 1.0f);
	light[1].specular = vec3(0.0f, 0.0f, 1.0f);
	light[2].specular = vec3(0.0f, 1.0f, 0.0f);

	/*
	light[0].position = vec4(0.0f, Y = 5 * sin(angle), Z = 5 * cos(angle), 1.0f);
	light[1].position = vec4(X = 5 * sin(angle), 0.0f, Z = 5 * cos(angle), 1.0f);
	light[2].position = vec4(X = 5 * sin(angle), Y = 5 * cos(angle), 0.0f, 1.0f);
	*/

	light[0].position = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	light[1].position = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	light[2].position = vec4(0.0f, 0.0f, 0.0f, 1.0f);

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

	
	if(change == 'v')
		glUseProgram(shaderProgramObject_pv);
	else
		glUseProgram(shaderProgramObject_pf);

		


	//Cube-----------
  //  mat4 modelViewMatrix = mat4::identity();
	
 //   vmath::mat4 translationMatrix = mat4::identity();
    vmath::mat4 translationMatrix = vmath::translate(0.0f, 0.0f, -1.5f);

	vmath::mat4 viewMatrix = vmath::mat4::identity();

    vmath::mat4 modelMatrix = translationMatrix;

   // mat4 modelViewProjectionMatrix = mat4::identity();
    //modelViewProjectionMatrix = perspectiveProjetionMatrix * modelMatrix;


    //Push above MVP info vertex shader's mvpUniform
    glUniformMatrix4fv(modelViewMatrixUniform, 1, GL_FALSE, modelMatrix);
    glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, viewMatrix);
	glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, perspectiveProjetionMatrix);

	if (bLightingEnable == TRUE)
	{
		glUniform1i(keyPressUniform, 1);

		glUniform3fv(lightDiffuseUniform[0], 1, light[0].diffuse);
		glUniform3fv(lightAmbientUniform[0], 1, light[0].ambient);
		glUniform3fv(lightSpecularUniform[0], 1, light[0].specular);
		glUniform4fv(lightPositionUniform[0], 1, light[0].position);

		glUniform3fv(lightDiffuseUniform[1], 1, light[1].diffuse);
		glUniform3fv(lightAmbientUniform[1], 1, light[1].ambient);
		glUniform3fv(lightSpecularUniform[1], 1, light[1].specular);
		glUniform4fv(lightPositionUniform[1], 1, light[1].position);

		glUniform3fv(lightDiffuseUniform[2], 1, light[2].diffuse);
		glUniform3fv(lightAmbientUniform[2], 1, light[2].ambient);
		glUniform3fv(lightSpecularUniform[2], 1, light[2].specular);
		glUniform4fv(lightPositionUniform[2], 1, light[2].position);

		glUniform3fv(materialDiffuseUniform, 1, materialDiffuse);
		glUniform3fv(materialAmbientUniform, 1, materialAmbient);
		glUniform3fv(materialSpecularUniform, 1, materialSpecular);
		glUniform1f(materialShininessUniform, materialShiness);

	
	}
	else	
	{
		glUniform1i(keyPressUniform, 0);
	}

	
	
	// *** bind vao ***
    glBindVertexArray(VAO_Sphere);

    // *** draw, either by glDrawTriangles() or glDrawArrays() or glDrawElements()
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO_Sphere_Element);
    glDrawElements(GL_TRIANGLES, gNumElements, GL_UNSIGNED_SHORT, 0);
	
	
	// *** unbind vao ***
    glBindVertexArray(0);

	glUseProgram(0);

	SwapBuffers(ghdc);


}

void update(void)
{
	//code
	/*
	angle += 0.5f;
	if (angle >= 360.0f)
	{
		angle -= 360.0f;
	}
	*/	
	rangle += 0.01;
	

	light[0].position[0] = 2 * cos(rangle) + 2 * sin(rangle);
	light[0].position[1] = 0;
	light[0].position[2] = 2 * cos(rangle) - 2 * sin(rangle);
	light[0].position[3] = 1.0f;
	
	light[1].position[0] = 0;
	light[1].position[1] = 2 * cos(rangle) + 2 * sin(rangle);
	light[1].position[2] = 2 * cos(rangle) - 2 * sin(rangle);
	light[1].position[3] = 1.0f;

	light[2].position[0] = 2 * cos(rangle) + 2 * sin(rangle);
	light[2].position[1] = 2 * cos(rangle) - 2 * sin(rangle);
	light[2].position[2] = 0;
	light[2].position[3] = 1.0f;


}

void uninitialize(void)
{
	//function declarations
	void ToogleFullScreen(void);


	//code
	if (shaderProgramObject_pv)
	{
		glUseProgram(shaderProgramObject_pv);
		GLint numShader = 0;

		glGetProgramiv(shaderProgramObject_pv, GL_ATTACHED_SHADERS, &numShader);

		if (numShader > 0)
		{
			GLuint* pShaders = (GLuint*)malloc(numShader * sizeof(GLuint));
			if (pShaders != NULL)
			{
				glGetAttachedShaders(shaderProgramObject_pv, numShader, NULL, pShaders);
				for (GLint i = 0; i < numShader; ++i)
				{
					glDetachShader(shaderProgramObject_pv, pShaders[i]);
					glDeleteShader(pShaders[i]);
					pShaders[i] = 0;
				}
				free(pShaders);
				pShaders = NULL;
			}
		}
		glUseProgram(0);
		glDeleteProgram(shaderProgramObject_pv);
		shaderProgramObject_pf = 0;
	}



	if (shaderProgramObject_pf)
	{
		glUseProgram(shaderProgramObject_pf);
		GLint numShader = 0;

		glGetProgramiv(shaderProgramObject_pf, GL_ATTACHED_SHADERS, &numShader);

		if (numShader > 0)
		{
			GLuint* pShaders = (GLuint*)malloc(numShader * sizeof(GLuint));
			if (pShaders != NULL)
			{
				glGetAttachedShaders(shaderProgramObject_pf, numShader, NULL, pShaders);
				for (GLint i = 0; i < numShader; ++i)
				{
					glDetachShader(shaderProgramObject_pf, pShaders[i]);
					glDeleteShader(pShaders[i]);
					pShaders[i] = 0;
				}
				free(pShaders);
				pShaders = NULL;
			}
		}
		glUseProgram(0);
		glDeleteProgram(shaderProgramObject_pf);
		shaderProgramObject_pf = 0;
	}




	//sphere
	//delete VBO of position PV ----------------------------
	if (VBO_Sphere_Element)
	{
		glDeleteBuffers(1, &VBO_Sphere_Element);
		VBO_Sphere_Element = 0;
	}

	if (VBO_Normal_Sphere)
	{
		glDeleteBuffers(1, &VBO_Normal_Sphere);
		VBO_Normal_Sphere = 0;
	}

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
