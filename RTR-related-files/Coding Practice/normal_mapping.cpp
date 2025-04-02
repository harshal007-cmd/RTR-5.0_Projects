// Standard Headers
#include <windows.h> //Win 32 API
#include <stdio.h>	 //FileIO
#include <stdlib.h>	 //exit()
#include "ogl.h"	 //For Icon resource

#include <iostream>

// OpenGL Header Files
#include <GL/glew.h> //For Programmable Pipeline (Graphics Library Extension Wrangler) This must before gl.h header file
#include <gl/GL.h>

#include "vmath.h"

// For sphere
#include "sphere.hpp"

// for texture loading
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// MACROS
#define WIN_WIDTH 800
#define WIN_HEIGHT 600

// Link with OpenGl Library
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "Sphere.lib") // Import library For sphere.dll

// Global Function Declaration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// Gloabal Variable Declaration
FILE *gpFILE = NULL;
HWND ghwnd = NULL;
DWORD dwStyle;
BOOL gbFullScreen = FALSE;
WINDOWPLACEMENT wpPrev = {sizeof(WINDOWPLACEMENT)};
BOOL gbActive = FALSE;

// OpenGL Related Global Variables
PIXELFORMATDESCRIPTOR pfd;
int iPixelFormatIndex = 0;
HDC ghdc = NULL;
HGLRC ghrc = NULL;

GLuint shaderProgramObject = 0;

enum
{
	AMC_ATTRIBUTE_POSITION = 0,
	AMC_ATTRIBUTE_COLOR,
	AMC_ATTRIBUTE_TEXCOORDS,
	AMC_ATTRIBUTE_NORMAL,
	AMC_ATTRIBUTE_TANGENT
};

GLuint vaoSphere = 0;
GLuint vboPositionSphere = 0;
GLuint vboNormalSphere = 0;
GLuint vboElementSphere = 0;
GLuint vboTexCoordsSphere = 0;
GLuint vboTangentSphere = 0;

// vao And vbo for Square
GLuint vaoSquare = 0;
GLuint vboSquarePosition = 0;
GLuint vboSquareTexCorods = 0;
GLuint vboSquareNormals = 0;

// Uniform Location For Transformation
GLuint modelMatrixUniform = 0;
GLuint viewMatrixUniform = 0;
GLuint projectionMatrixUniform = 0;

// unifrom location for Lights Attributes
GLuint lightDiffuseUniform = 0;
GLuint lightAmbientUniform = 0;
GLuint lightSpecularUniform = 0;
GLuint lightPositionUniform = 0;

// unifrom location for Material Attributes
GLuint materialDiffuseUniform = 0;
GLuint materialAmbientUniform = 0;
GLuint materialSpecularUniform = 0;
GLuint materialShininessUniform = 0;

GLuint keyPressedUniform = 0;

// Uniforms for normal and texture map
GLuint textureMapUniform = 0;
GLuint normalMapUniform = 0;
GLuint normalMapEnableUniform = 0;

BOOL bLightingEnable = FALSE;
BOOL bNormalMapEnable = FALSE;

// Light Properties
GLfloat lightAmbient[] = {0.1f, 0.1f, 0.1f, 1.0f}; // grey ambient light
GLfloat lightDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f}; // White diffuse light (main Color of light)
GLfloat lightSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat lightPosition[] = {100.0f, 10.0f, 50.0f, 1.0f}; // Positional light

// Material properties
GLfloat materialAmbient[] = {0.0f, 0.0f, 0.0f, 1.0f};
GLfloat materialDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat materialSpecular[] = {0.8f, 0.8f, 0.8f, 1.0f};
GLfloat materialShininess = 70.0f;

vmath::mat4 perspectiveProjectionMatrix;

// For Sphere
GLuint gNumSphereElements;

// Texture
GLuint imageTexture = 0;
GLuint normalMapTexture = 0;

GLfloat fAngle = 0.0f;

float x, y, z;

// Entry Point Function
int WINAPI
WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
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
	if (!AttachConsole(ATTACH_PARENT_PROCESS))
	{
		AllocConsole();
	}

	freopen("CONOUT$", "w", stdout);
	std::cout << "Log On Console" << std::endl;

	// gpFILE = fopen("Log.txt", "w");
	// fopen_s for windows
	if (fopen_s(&gpFILE, "Log.txt", "w") != 0)
	{
		MessageBox(NULL, TEXT("LOG FILE OPENING ERROR"), TEXT("ERROR"), MB_OK | MB_ICONERROR);
		exit(0);
	}

	fprintf(gpFILE, "Programme Started Successfully\n");
	fprintf(gpFILE, "------------------------------------------------------------\n\n");

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

			// Light enable-disable
		case 'l':
		case 'L':
			if (bLightingEnable)
				bLightingEnable = FALSE;
			else
				bLightingEnable = TRUE;
			break;

		case 'f':
		case 'F':

			ToggleFullScreen();
			break;

		case 'n':
		case 'N':
			bNormalMapEnable = !bNormalMapEnable;
			break;

		case 'w':
		case 'W':
			z--;
			break;

		case 's':
		case 'S':
			z++;
			break;

		case 'a':
		case 'A':
			x--;
			break;

		case 'd':
		case 'D':
			x++;
			break;

		case 'r':
		case 'R':
			y++;
			break;

		case 't':
		case 'T':
			y--;
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

GLuint createTexture2D(const char *filePath)
{
	stbi_set_flip_vertically_on_load(true);
	int width, height, channel;
	unsigned char *data = stbi_load(filePath, &width, &height, &channel, 0);

	if (!data)
	{
		fprintf(gpFILE, "Failed To Load %s Texture\n", filePath);
		return -1;
	}

	GLenum format = GL_RGBA;

	if (channel == STBI_grey)
		format = GL_RED;
	else if (channel == STBI_rgb)
		format = GL_RGB;
	else if (channel == STBI_rgb_alpha)
		format = GL_RGBA;

	GLuint texture;
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

	// glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(data);
	return texture;
}

int initialise(void)
{
	// Function Declarations

	void resize(int width, int height);
	void printGLInfo(void);
	void uninitialise(void);

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
	pfd.cDepthBits = 32;

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

	// Initialise GLEW - Must for PP
	if (glewInit() != GLEW_OK)
	{
		fprintf(gpFILE, "glewInit() Failed\n");
		return -6;
	}

	// Here OpenGL Starts
	// Set The Clear Color Of Window To Blue
	printGLInfo();

	fprintf(gpFILE, "------------------------------------------------------------------------------------\n\n");

	// Step1 - Write Vertex Shader
	const GLchar *vertexShaderSourceCode =
		"#version 460 core"
		"\n"
		"in vec4 aPosition;"
		"in vec2 aTexCoords;"
		"in vec3 aNormal;"
		"in vec3 aTangent;"
		"uniform vec4 uLightPosition;"
		"uniform mat4 uModelMatrix;"
		"uniform mat4 uViewMatrix;"
		"uniform mat4 uProjectionMatrix;"
		"uniform int uKeyPressed;"
		"out vec3 oTransformedNormals;"
		"out vec3 oLightDirection;"
		"out vec3 oViewerVector;"
		"out vec2 oTexCoords;"
		"out mat3 mvMatrix;"
		"out mat3 oTBN;"
		"void main(void)"
		"{"
		"	mvMatrix = mat3(uViewMatrix * uModelMatrix);"
		"	vec3 tN = normalize(mvMatrix * aNormal);"
		"	vec3 tT = normalize(mvMatrix * aTangent);"
		"	vec3 tB = normalize(cross(tN,tT));"
		"	mat3 tbn = mat3(tT,tB,tN);"
		"	if(uKeyPressed == 1)"
		"	{"
		"		vec4 eyeCoordinates = uViewMatrix * uModelMatrix * aPosition;"
		"		oTransformedNormals = mat3(uViewMatrix * uModelMatrix) * aNormal;"
		"		oLightDirection = vec3(uLightPosition - eyeCoordinates);"
		"		oViewerVector =  (-eyeCoordinates.xyz);"
		"	}"
		"	else"
		"	{"
		"		oTransformedNormals = vec3(0.0f,0.0f,0.0f);"
		"		oLightDirection = vec3(0.0f,0.0f,0.0f);"
		"		oViewerVector = vec3(0.0f,0.0f,0.0f);"
		"	}"
		"   gl_Position = uProjectionMatrix * uViewMatrix * uModelMatrix * aPosition;"
		"	oTexCoords = aTexCoords;"

		"	oTBN = tbn;"
		"}";

	// Step2 - Create Vertex Shader Object
	GLuint vertexShaderObject = glCreateShader(GL_VERTEX_SHADER);

	// Step3 - Assign Vertex Shader source code to Vertex shader object
	glShaderSource(vertexShaderObject, 1, (const char **)&vertexShaderSourceCode, NULL);

	// Step4 - Compile Vertex Shader
	glCompileShader(vertexShaderObject);

	// Step5 - check for vertex shader compilation errors if any
	//
	GLint status = 0;
	GLint infoLogLength = 0;
	GLchar *szInfoLog = NULL;

	glGetShaderiv(vertexShaderObject, GL_COMPILE_STATUS, &status);

	if (status == GL_FALSE)
	{
		glGetShaderiv(vertexShaderObject, GL_INFO_LOG_LENGTH, &infoLogLength);
		if (infoLogLength > 0)
		{
			szInfoLog = (char *)malloc(infoLogLength + 1);
			if (szInfoLog != NULL)
			{
				glGetShaderInfoLog(vertexShaderObject, infoLogLength + 1, NULL, szInfoLog);
				fprintf(gpFILE, "Vertex Shader Compilation Error Log : %s\n", szInfoLog);
				free(szInfoLog);
				szInfoLog = NULL;
			}
		}
		uninitialise();
	}

	// Step6 - Write Source code Of Fragment Shader
	const GLchar *fragmentShaderSourceCode =
		"#version 460 core"
		"\n"
		"in vec3 oTransformedNormals;"
		"in vec3 oLightDirection;"
		"in vec3 oViewerVector;"
		"in vec2 oTexCoords;"
		"in mat3 mvMatrix;"
		"in mat3 oTBN;"
		"uniform sampler2D uTexSampler;"
		"uniform sampler2D uNormalMapSampler;"
		"uniform vec3 uLightDiffuse;"
		"uniform vec3 uLightAmbient;"
		"uniform vec3 uLightSpecular;"
		"uniform vec3 uMaterialDiffuse;"
		"uniform vec3 uMaterialAmbient;"
		"uniform vec3 uMaterialSpecular;"
		"uniform float uMaterialShininess;"
		"uniform int uKeyPressed;"
		"uniform int uNormalMap;"
		"out vec4 FragColor;"
		"void main(void)"
		"{"
		"	vec3 phongADSLight;"
		"	vec3 normal = vec3(texture(uNormalMapSampler,oTexCoords)) * 2.0f - 1.0f;"
		"	vec3 trNormal = normalize(oTBN * normal);"
		"  if(uKeyPressed == 1)"
		"	{"
		"		vec3 normalisedTransformedNormals = normalize(trNormal);"
		"		vec3 normalisedLightDirection = normalize(oLightDirection);"
		"		vec3 normalisedViewerVector = normalize(oViewerVector);"
		"		vec3 reflectionVector = reflect(-normalisedLightDirection,normalisedTransformedNormals);"
		"		vec3 ambientLight = uLightAmbient * uMaterialAmbient;"
		"		vec3 diffuseLight = uLightDiffuse * vec3(texture(uTexSampler,oTexCoords)) * max(dot(normalisedLightDirection,normalisedTransformedNormals),0.0);"
		"		vec3 specularLight = uLightSpecular * uMaterialSpecular * pow(max(dot(reflectionVector,normalisedViewerVector),0.0),uMaterialShininess);"
		"		phongADSLight = ambientLight + diffuseLight + specularLight;"
		"	}"
		"  else"
		"	{"
		"		phongADSLight = vec3(1.0f,1.0f,1.0f);"
		"	}"
		"  FragColor = vec4(phongADSLight,1.0f);"
		"}";

	// Create Fragmnet Shader Object
	GLuint fragmentShaderObject = glCreateShader(GL_FRAGMENT_SHADER);

	// Assign Fragment shader source code fragment shader object
	glShaderSource(fragmentShaderObject, 1, (const GLchar **)&fragmentShaderSourceCode, NULL);

	// Compile Fragment shader object
	glCompileShader(fragmentShaderObject);

	// Compilation Error Checking
	status = 0;
	infoLogLength = 0;
	szInfoLog = NULL;

	glGetShaderiv(fragmentShaderObject, GL_COMPILE_STATUS, &status);

	if (status == GL_FALSE)
	{
		glGetShaderiv(fragmentShaderObject, GL_INFO_LOG_LENGTH, &infoLogLength);
		if (infoLogLength > 0)
		{
			szInfoLog = (char *)malloc(infoLogLength + 1);
			if (szInfoLog != NULL)
			{
				glGetShaderInfoLog(fragmentShaderObject, infoLogLength + 1, NULL, szInfoLog);
				fprintf(gpFILE, "Fragment Shader Compilation Error Log : %s\n", szInfoLog);
				free(szInfoLog);
				szInfoLog = NULL;
				// glDeleteShader(vertexShaderObject);
			}
		}
		uninitialise();
	}

	// Shader Program
	shaderProgramObject = glCreateProgram();

	// Attach vertex shader to program object
	glAttachShader(shaderProgramObject, vertexShaderObject);

	// Attach fragment shader to program object
	glAttachShader(shaderProgramObject, fragmentShaderObject);

	// Bind Attirbute Locations with Shader program Object
	glBindAttribLocation(shaderProgramObject, AMC_ATTRIBUTE_POSITION, "aPosition");
	glBindAttribLocation(shaderProgramObject, AMC_ATTRIBUTE_NORMAL, "aNormal");
	glBindAttribLocation(shaderProgramObject, AMC_ATTRIBUTE_TEXCOORDS, "aTexCoords");
	glBindAttribLocation(shaderProgramObject, AMC_ATTRIBUTE_TANGENT, "aTangent");

	// Link Shader Program
	glLinkProgram(shaderProgramObject);

	//  Error Checking
	status = 0;
	infoLogLength = 0;
	szInfoLog = NULL;

	glGetProgramiv(shaderProgramObject, GL_LINK_STATUS, &status);

	if (status == GL_FALSE)
	{
		glGetProgramiv(shaderProgramObject, GL_INFO_LOG_LENGTH, &infoLogLength);
		if (infoLogLength > 0)
		{
			szInfoLog = (char *)malloc(infoLogLength + 1);
			if (szInfoLog != NULL)
			{
				glGetProgramInfoLog(shaderProgramObject, infoLogLength + 1, NULL, szInfoLog);
				fprintf(gpFILE, "Shader Program Linking Error Log  : %s\n", szInfoLog);
				free(szInfoLog);
				szInfoLog = NULL;
			}
		}
		uninitialise();
	}

	// Get Shaders Uniform Locations
	modelMatrixUniform = glGetUniformLocation(shaderProgramObject, "uModelMatrix");
	viewMatrixUniform = glGetUniformLocation(shaderProgramObject, "uViewMatrix");
	projectionMatrixUniform = glGetUniformLocation(shaderProgramObject, "uProjectionMatrix");

	// Light uniform locations
	lightDiffuseUniform = glGetUniformLocation(shaderProgramObject, "uLightDiffuse");
	lightAmbientUniform = glGetUniformLocation(shaderProgramObject, "uLightAmbient");
	lightSpecularUniform = glGetUniformLocation(shaderProgramObject, "uLightSpecular");
	lightPositionUniform = glGetUniformLocation(shaderProgramObject, "uLightPosition");

	// material uniform locations
	materialDiffuseUniform = glGetUniformLocation(shaderProgramObject, "uMaterialDiffuse");
	materialAmbientUniform = glGetUniformLocation(shaderProgramObject, "uMaterialAmbient");
	materialSpecularUniform = glGetUniformLocation(shaderProgramObject, "uMaterialSpecular");
	materialShininessUniform = glGetUniformLocation(shaderProgramObject, "uMaterialShininess");

	keyPressedUniform = glGetUniformLocation(shaderProgramObject, "uKeyPressed");

	// Normal and texture map uniforms
	textureMapUniform = glGetUniformLocation(shaderProgramObject, "uTexSampler");
	normalMapUniform = glGetUniformLocation(shaderProgramObject, "uNormalMapSampler");
	normalMapEnableUniform = glGetUniformLocation(shaderProgramObject, "uNormalMap");

	sphereInit(1.0f, 50, 50);

	// Vao and vbo of sphere
	glGenVertexArrays(1, &vaoSphere);
	glBindVertexArray(vaoSphere);

	// vbo SPhere Position
	glGenBuffers(1, &vboPositionSphere);
	glBindBuffer(GL_ARRAY_BUFFER, vboPositionSphere);
	glBufferData(GL_ARRAY_BUFFER, sphere_vertices.size() * sizeof(float), sphere_vertices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(AMC_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(AMC_ATTRIBUTE_POSITION);

	// vbo SPhere TExcoords
	glGenBuffers(1, &vboTexCoordsSphere);
	glBindBuffer(GL_ARRAY_BUFFER, vboTexCoordsSphere);
	glBufferData(GL_ARRAY_BUFFER, sphere_texCoords.size() * sizeof(float), sphere_texCoords.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(AMC_ATTRIBUTE_TEXCOORDS, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(AMC_ATTRIBUTE_TEXCOORDS);

	// vbo SPhere Normals
	glGenBuffers(1, &vboNormalSphere);
	glBindBuffer(GL_ARRAY_BUFFER, vboNormalSphere);
	glBufferData(GL_ARRAY_BUFFER, sphere_normals.size() * sizeof(float), sphere_normals.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(AMC_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(AMC_ATTRIBUTE_NORMAL);

	// vbo SPhere Tangetns
	glGenBuffers(1, &vboTangentSphere);
	glBindBuffer(GL_ARRAY_BUFFER, vboTangentSphere);
	glBufferData(GL_ARRAY_BUFFER, sphere_tangent.size() * sizeof(float), sphere_tangent.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(AMC_ATTRIBUTE_TANGENT, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(AMC_ATTRIBUTE_TANGENT);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// vbo SPhere Indices
	glGenBuffers(1, &vboElementSphere);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboElementSphere);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned), indices.data(), GL_STATIC_DRAW);

	glBindVertexArray(0);

	// Square Data
	const float square_position[] =
		{
			1.0f, 1.0f, 0.0f,
			-1.0f, 1.0f, 0.0f,
			-1.0f, -1.0f, 0.0f,
			1.0f, -1.0f, 0.0f};

	const float square_texcoords[] =
		{
			1.0f, 1.0f,
			0.0f, 1.0f,
			0.0f, 0.0f,
			1.0f, 0.0f};

	const float square_normals[] =
		{
			0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f
	};

	const float square_tangents[] =
		{
			1.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f};

	// vao square
	glGenVertexArrays(1, &vaoSquare);
	glBindVertexArray(vaoSquare);

	// vbo posiiton
	glGenBuffers(1, &vboSquarePosition);
	glBindBuffer(GL_ARRAY_BUFFER, vboSquarePosition);
	glBufferData(GL_ARRAY_BUFFER, sizeof(square_position), square_position, GL_STATIC_DRAW);
	glVertexAttribPointer(AMC_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(AMC_ATTRIBUTE_POSITION);

	// vbo TexCoords
	glGenBuffers(1, &vboSquareTexCorods);
	glBindBuffer(GL_ARRAY_BUFFER, vboSquareTexCorods);
	glBufferData(GL_ARRAY_BUFFER, sizeof(square_texcoords), square_texcoords, GL_STATIC_DRAW);
	glVertexAttribPointer(AMC_ATTRIBUTE_TEXCOORDS, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(AMC_ATTRIBUTE_TEXCOORDS);

	// vbo Normals
	glGenBuffers(1, &vboSquareNormals);
	glBindBuffer(GL_ARRAY_BUFFER, vboSquareNormals);
	glBufferData(GL_ARRAY_BUFFER, sizeof(square_normals), square_normals, GL_STATIC_DRAW);
	glVertexAttribPointer(AMC_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(AMC_ATTRIBUTE_NORMAL);

	// vbo Tangent
	glGenBuffers(1, &vboTangentSphere);
	glBindBuffer(GL_ARRAY_BUFFER, vboTangentSphere);
	glBufferData(GL_ARRAY_BUFFER, sizeof(square_tangents), square_tangents, GL_STATIC_DRAW);
	glVertexAttribPointer(AMC_ATTRIBUTE_TANGENT, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(AMC_ATTRIBUTE_TANGENT);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Load textures
	imageTexture = createTexture2D("earth.jpg");
	normalMapTexture = createTexture2D("earthNormal.jpg");

	// Enabling Depth
	glClearDepth(1.0f);		 // Compulsory
	glEnable(GL_DEPTH_TEST); // Compulsory
	glDepthFunc(GL_LEQUAL);	 // Compulsory

	glEnable(GL_BACK_NORMALS_HINT_PGI);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	resize(WIN_WIDTH, WIN_HEIGHT);
	return 0;
}

void printGLInfo(void)
{
	// Variable Declarations
	GLint numExtensions;
	GLint i;
	// code
	// Vendor -> Implementor of OpenGL
	fprintf(gpFILE, "OpenGL Vendor   : %s\n", glGetString(GL_VENDOR));
	fprintf(gpFILE, "OpenGL Renderer : %s\n", glGetString(GL_RENDERER));
	fprintf(gpFILE, "OpenGL Version  : %s\n", glGetString(GL_VERSION));
	fprintf(gpFILE, "GLSL Version    : %s\n\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

	// Listing Of Supported Extensions
	glGetIntegerv(GL_NUM_EXTENSIONS, &numExtensions);

	for (i = 0; i < numExtensions; i++)
	{
		fprintf(gpFILE, "%s\n", glGetStringi(GL_EXTENSIONS, i));
	}
}

void resize(int width, int height)
{
	// code
	if (height <= 0)
		height = 1;

	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	perspectiveProjectionMatrix = vmath::perspective(45.0f, (float)width / (float)height, 0.1f, 100.0f);
}

void display(void)
{
	// code
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(shaderProgramObject);

	// Cube
	vmath::mat4 translationMatrix = vmath::translate(x, y, z - 5);
	vmath::mat4 rotZ = vmath::rotate(90.0f, 1.0f, 0.0f, 0.0f);
	vmath::mat4 rotationMatrix = vmath::rotate(fAngle, 0.0f, 1.0f, 0.0f);
	// View matrix
	vmath::mat4 viewMatrix = vmath::mat4::identity();

	// Model Matrix
	vmath::mat4 modelMatrix = translationMatrix * rotationMatrix * rotZ;

	// Push All Uniform values into vertex shader
	glUniformMatrix4fv(modelMatrixUniform, 1, GL_FALSE, modelMatrix);
	glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, viewMatrix);
	glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, perspectiveProjectionMatrix);

	if (bLightingEnable == TRUE)
	{
		glUniform1i(keyPressedUniform, 1); // Light uniforms
		glUniform3fv(lightDiffuseUniform, 1, lightDiffuse);
		glUniform3fv(lightAmbientUniform, 1, lightAmbient);
		glUniform3fv(lightSpecularUniform, 1, lightSpecular);
		glUniform4fv(lightPositionUniform, 1, lightPosition);

		// Material Uniforms
		glUniform3fv(materialDiffuseUniform, 1, materialDiffuse);
		glUniform3fv(materialAmbientUniform, 1, materialAmbient);
		glUniform3fv(materialSpecularUniform, 1, materialSpecular);
		glUniform1f(materialShininessUniform, materialShininess);
	}
	else
	{
		glUniform1i(keyPressedUniform, 0);
	}

	// Image texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, imageTexture);
	glUniform1i(textureMapUniform, 0);

	// Normal Texture
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, normalMapTexture);
	glUniform1i(normalMapUniform, 1);

	glBindVertexArray(vaoSphere);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboElementSphere);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	//	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	glBindVertexArray(0);

	glUseProgram(0);

	SwapBuffers(ghdc);
}

void update(void)
{
	// code
	fAngle += 0.01f;
	if (fAngle >= 360.0f)
		fAngle -= 360.0f;
}

void uninitialise(void)
{
	// Function Declaration
	void ToggleFullScreen(void);

	// code
	// Delete Shaders objects and Shader Program object

	FreeConsole();

	if (shaderProgramObject)
	{
		glUseProgram(shaderProgramObject);

		GLint numShaders;
		glGetProgramiv(shaderProgramObject, GL_ATTACHED_SHADERS, &numShaders);

		if (numShaders > 0)
		{
			GLuint *pShaders = (GLuint *)malloc(sizeof(GLuint) * numShaders);

			if (pShaders != NULL)
			{
				glGetAttachedShaders(shaderProgramObject, numShaders, NULL, pShaders);

				for (GLint i = 0; i < numShaders; i++)
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

	// Delete vbo position for Cube

	if (vboElementSphere)
	{
		glDeleteBuffers(1, &vboElementSphere);
		vboElementSphere = 0;
	}

	if (vboTexCoordsSphere)
	{
		glDeleteBuffers(1, &vboTexCoordsSphere);
		vboTexCoordsSphere = 0;
	}

	if (vboNormalSphere)
	{
		glDeleteBuffers(1, &vboNormalSphere);
		vboNormalSphere = 0;
	}

	if (vboPositionSphere)
	{
		glDeleteBuffers(1, &vboPositionSphere);
		vboPositionSphere = 0;
	}

	if (vaoSphere)
	{
		glDeleteVertexArrays(1, &vaoSphere);
		vaoSphere = 0;
	}

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
		fprintf(gpFILE, "------------------------------------------------------------------------------------\n\n");
		fprintf(gpFILE, "Programme Ended Successfully\n");
		fclose(gpFILE);
		gpFILE = NULL;
	}
}
