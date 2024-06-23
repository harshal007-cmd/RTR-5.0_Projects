// Standard Headers
#include <windows.h> //Win 32 API
#include <stdio.h>	 //FileIO
#include <stdlib.h>	 //exit()
#include "ogl.h"	 //For Icon resource

#include <iostream>
#include <fstream>

#include <vector>
#include <string>

// OpenGL Header Files
#include <GL/glew.h> //For Programmable Pipeline (Graphics Library Extension Wrangler) This must before gl.h header file
#include <gl/GL.h>

#include "vmath.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "sphere.h"
#include "loadModel.h"
#include "program.h"

// MACROS
#define WIN_WIDTH 800
#define WIN_HEIGHT 600

#define FBO_TEXTURE_WIDTH 1920
#define FBO_TEXTURE_HEIGHT 1080

// Link with OpenGl Library
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "opengl32.lib")

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

GLuint programObject;

enum
{
	GRP_ATTRIB_POSTITION,
	GRP_ATTRIB_COLOR,
	GRP_ATTRIB_TEXCOORDS
};

GLuint winWidth, winHeight;

//
GLuint vao_sphere;
GLuint vbo_sphere_position;
GLuint vbo_sphere_texCoords;
GLuint vbo_faceIndices;

GLuint textureCube, textureSmiley;
GLuint textureEarth;

GLuint mvUniformLocation, projUniformLocation, textureUniformLocation;

loadObjModel *pTreeModel = 0;
sphere *pSphere = 0;

program *pProgram = 0;		 // Second Pass
program *godRaysProgram = 0; // third Pass

program *colorUniformProgram = 0; // first Pass
GLuint colorUniformCUP = 0;
GLuint mvpUniformCUP = 0;

GLuint godRaysTextureUnform = 0;

GLuint fboOcclusingObjects = 0;
GLuint firstPassTexture = 0;

GLuint vaoScreenQuad = 0;
GLuint vboScreenQuadPosition = 0;
GLuint vboScreenQuadTexCoords = 0;

GLuint lightPositionOnScreenUniform = 0;

GLuint uniformLightPosition = 0;

vmath::vec4 lightPosition = vmath::vec4(0.0f, 0.0f, -30.0f, 1.0f);

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
	// gpFILE = fopen("Log.txt", "w");
	// fopen_s for windows

	if (!AttachConsole(ATTACH_PARENT_PROCESS))
	{
		AllocConsole();
	}

	freopen("CONOUT$", "w", stdout);

	std::cout << "Log On Console" << std::endl;

	if (fopen_s(&gpFILE, "Log.txt", "w") != 0)
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
		winWidth = LOWORD(lParam);
		winHeight = HIWORD(lParam);
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

		case 'w':
			lightPosition[1] += 0.1f;
			break;
		case 's':
			lightPosition[1] -= 0.1f;

			break;

		case 'a':
			lightPosition[0] -= 0.1f;
			break;

		case 'd':
			lightPosition[0] += 0.1f;
			break;

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

GLuint createTexture2D(const char *filename)
{
	unsigned char *data = NULL;
	int width, height, channels;

	stbi_set_flip_vertically_on_load(true);

	data = stbi_load(filename, &width, &height, &channels, 0);
	if (data == NULL)
	{
		std::cout << "Texture Loading Failed" << std::endl;
		return 0;
	}

	GLenum format = GL_RGBA;

	if (channels == STBI_grey)
	{
		format = GL_RED;
	}
	else if (channels == STBI_rgb)
	{
		format = GL_RGB;
	}
	else
	{
		format = GL_RGBA;
	}

	GLuint texture;

	glCreateTextures(GL_TEXTURE_2D, 1, &texture);
	// glTextureStorage2D(texture, 1, GL_RGBA8, width, height);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(data);
	data = NULL;

	return texture;
}

void init_FBO()
{
	// Create first pass FBO
	glGenFramebuffers(1, &fboOcclusingObjects);
	glBindFramebuffer(GL_FRAMEBUFFER, fboOcclusingObjects);

	// Color
	glGenTextures(1, &firstPassTexture);
	glBindTexture(GL_TEXTURE_2D, firstPassTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, FBO_TEXTURE_WIDTH, FBO_TEXTURE_HEIGHT);
	// glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,FBO_TEXTURE_WIDTH,FBO_TEXTURE_HEIGHT,0,GL_RGBA,GL_FLOAT,)
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, firstPassTexture, 0);

	// Depth
	GLuint depthTexture = 0;
	glGenTextures(1, &depthTexture);
	glBindTexture(GL_TEXTURE_2D, depthTexture);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH_COMPONENT16, FBO_TEXTURE_WIDTH, FBO_TEXTURE_HEIGHT);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthTexture, 0);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

int initialise(void)
{
	// Function Declarations

	void resize(int width, int height);
	void printGLInfo(void);

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
	// printGLInfo();

	// Shaders
	const char *vertexShaderSourceCode[] = {
		"#version 460 core \n"
		"\n"
		"layout(location = 0)in vec4 aPosition;"
		"layout(location = 3)in vec3 aNormal;"
		"uniform mat4 uModelViewMatrix;"
		"uniform mat4 uProjectionMatrix;"
		"vec3 uLd = vec3(1.0f,1.0f,1.0f);"
		"vec3 uKd = vec3(0.8f,0.8f,0.8f);"
		"vec3 lA = vec3(0.15f,0.15f,0.15f);"
		"uniform vec4 uLightPosition;"
		"out vec3 oDiffuseLight;"
		"void main(void)"
		"{"
		"	vec4 eyePosition = uModelViewMatrix * aPosition;"
		"	mat3 normalMatrix = mat3(transpose(inverse(uModelViewMatrix)));"
		"	vec3 n = normalize(normalMatrix * aNormal);"
		"	vec3 s = normalize(vec3(uLightPosition - eyePosition));"
		"	oDiffuseLight = lA + uLd * uKd * max(dot(s,n),0.0f);"
		"   gl_Position = uProjectionMatrix * uModelViewMatrix * aPosition;"
		"}"};

	// Fragment Shader ->Pass Through Shader
	const char *fragmentShaderSourceCode[] =
		{
			"#version 460 core\n"
			"in vec3 oDiffuseLight;\n"
			"out vec4 fColor;\n"
			"void main(void)\n"
			"{\n"
			" fColor = vec4(oDiffuseLight,1.0);\n"
			"}\n"};

	pProgram = new program(vertexShaderSourceCode, fragmentShaderSourceCode);

	mvUniformLocation = pProgram->getUniformLocation("uModelViewMatrix");
	projUniformLocation = pProgram->getUniformLocation("uProjectionMatrix");
	uniformLightPosition = pProgram->getUniformLocation("uLightPosition");

	// Step1 - Write Vertex Shader
	const GLchar *vs_colorUniformProgram[] =
		{
			"#version 460 core"
			"\n"
			"layout(location = 0) in vec4 aPosition;"
			"uniform mat4 uMvpMatrix;"
			"void main(void)"
			"{"
			"	gl_Position = uMvpMatrix * aPosition;"
			"}"};

	// Step6 - Write Source code Of Fragment Shader
	const GLchar *fs_colorUniformProgram[] = {
		"#version 460 core"
		"\n"
		"uniform vec4 uColor;"
		"out vec4 FragColor;"
		"void main(void)"
		"{"
		"	FragColor = uColor;"
		"}"};

	colorUniformProgram = new program(vs_colorUniformProgram, fs_colorUniformProgram);
	mvpUniformCUP = colorUniformProgram->getUniformLocation("uMvpMatrix");
	colorUniformCUP = colorUniformProgram->getUniformLocation("uColor");

	// GodRays Program
	//  Step1 - Write Vertex Shader
	const GLchar *vs_godRays[] =
		{
			"#version 460 core"
			"\n"
			"layout(location = 0) in vec4 aPosition;"
			"layout(location = 2) in vec2 aTexCoords;"
			"out vec2 oTexCoords;"
			"void main(void)"
			"{"
			"	gl_Position = aPosition;"
			"	oTexCoords = aTexCoords;"
			"}"};

	// Step6 - Write Source code Of Fragment Shader
	const GLchar *fs_godRays[] =
		{
			"#version 460 core"
			"\n"
			"in vec2 oTexCoords;"
			"uniform sampler2D uSamplerTex;"
			"uniform vec2 lightPositionOnScreen;"
			"out vec4 FragColor;"
			"void main(void)"
			"{"
			"	float decay = 0.9685f;"
			"	float exposure  = 0.3f;"
			"	float density = 0.926f;"
			"	float weight = 0.587f;"
			"	int num_samples = 80;"
			"																		\n"
			"	vec2 tc = oTexCoords.xy;"
			"	vec2 deltaTexCoord = (tc - vec2(lightPositionOnScreen));"
			"	deltaTexCoord *= (1.0 / float(num_samples)) * density;"
			"																		\n"
			"	float illuminationDecay = 1.0;"
			"	vec4 color = texture(uSamplerTex, tc.xy);"
			"																		\n"
			"	for(int i=0;i<num_samples;i++)"
			"	{"
			"		tc -= deltaTexCoord;"
			"		vec4 sample2  = texture(uSamplerTex,tc.xy);"
			"		sample2 *= illuminationDecay*weight;"
			"		color += sample2;"
			"		illuminationDecay *= decay;"
			"	}"
			"	FragColor = color;"
			"}"};
	// Light Position on screen must be in range 0 to 1

	godRaysProgram = new program(vs_godRays, fs_godRays);
	godRaysTextureUnform = godRaysProgram->getUniformLocation("uSamplerTex");
	lightPositionOnScreenUniform = godRaysProgram->getUniformLocation("lightPositionOnScreen");

	// Data
	// For scrren Quad
	const float screen_quad_position[] =
		{
			1.0f, 1.0f, 0.0f,
			-1.0f, 1.0f, 0.0f,
			-1.0f, -1.0f, 0.0f,
			1.0f, -1.0f, 0.0f};

	const float screen_quad_texcoords[] =
		{
			1.0f, 1.0f,
			0.0f, 1.0f,
			0.0f, 0.0f,
			1.0f, 0.0f

		};

	// vao screenQuad
	glGenVertexArrays(1, &vaoScreenQuad);
	glBindVertexArray(vaoScreenQuad);

	// Position buffer
	glGenBuffers(1, &vboScreenQuadPosition);
	glBindBuffer(GL_ARRAY_BUFFER, vboScreenQuadPosition);
	glBufferData(GL_ARRAY_BUFFER, sizeof(screen_quad_position), screen_quad_position, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	// Tecoords buffer
	glGenBuffers(1, &vboScreenQuadTexCoords);
	glBindBuffer(GL_ARRAY_BUFFER, vboScreenQuadTexCoords);
	glBufferData(GL_ARRAY_BUFFER, sizeof(screen_quad_texcoords), screen_quad_texcoords, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	// init Sphere Data
	pSphere = new sphere(1.0f, 50, 50);

	// Initilalise FBO
	init_FBO();

	fprintf(gpFILE, "Loading Model\n");
	// Initialise tree model

	pTreeModel = new loadObjModel("C:\\Users\\gpati\\OneDrive\\Desktop\\OpenGL\\02_OpenGL_PP\\03_PersonalAssignments\\models\\tree.txt");
	fprintf(gpFILE, "Loading model Successfull\n");

	// Depth
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClearDepth(1.0f);

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

vmath::mat4 projectionMatrix;

void resize(int width, int height)
{
	// code
	if (height <= 0)
		height = 1;

	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	projectionMatrix = vmath::perspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
}

GLfloat fAngle = 0.0f;

void display(void)
{

	vmath::mat4 modelViewMatrix;
	vmath::mat4 mvpMatrix;
	////////////////////////////////////////////////////////////////////////////////////
	// First Pass
	glBindFramebuffer(GL_FRAMEBUFFER, fboOcclusingObjects);

	resize(FBO_TEXTURE_WIDTH, FBO_TEXTURE_HEIGHT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	colorUniformProgram->useProgram();

	// Light Source
	modelViewMatrix = vmath::translate(lightPosition[0], lightPosition[1], lightPosition[2]);
	mvpMatrix = projectionMatrix * modelViewMatrix;

	glUniformMatrix4fv(mvpUniformCUP, 1, GL_FALSE, mvpMatrix);
	glUniform4f(colorUniformCUP, 0.2f, 0.18f, 0.08f, 1.0f);

	pSphere->draw();

	// Occluding Objects in black color
	modelViewMatrix = vmath::translate(0.0f, -3.5f, -10.0f);
	mvpMatrix = projectionMatrix * vmath::translate(0.0f, -3.5f, -10.0f) * vmath::rotate(fAngle, 0.0f, 1.0f, 0.0f);

	glUniformMatrix4fv(mvpUniformCUP, 1, GL_FALSE, mvpMatrix);
	glUniform4f(colorUniformCUP, 0.0f, 0.0f, 0.0f, 1.0f);

	pTreeModel->drawModel();

	glUseProgram(0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	/////////////////////////////////////////////////////////////
	// Second Pass
	resize(winWidth, winHeight);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	colorUniformProgram->useProgram();

	// Light Source
	modelViewMatrix = vmath::translate(lightPosition[0], lightPosition[1], lightPosition[2]);
	mvpMatrix = projectionMatrix * modelViewMatrix;

	glUniformMatrix4fv(mvpUniformCUP, 1, GL_FALSE, mvpMatrix);
	glUniform4f(colorUniformCUP, 0.7f, 0.7f, 0.70f, 1.0f);

	pSphere->draw();

	pProgram->useProgram();

	// Occluding Objects in color
	modelViewMatrix = vmath::translate(0.0f, -3.5f, -10.0f) * vmath::rotate(fAngle, 0.0f, 1.0f, 0.0f);

	glUniformMatrix4fv(mvUniformLocation, 1, GL_FALSE, modelViewMatrix);
	glUniformMatrix4fv(projUniformLocation, 1, GL_FALSE, projectionMatrix);

	glUniform4fv(uniformLightPosition, 1, lightPosition);

	// glUniform4f(colorUniformCUP, 0.5f, 0.6f, 0.5f, 1.0f);
	pTreeModel->drawModel();

	///////////////////////////////////////////////////////////////////////////
	// Third Pass
	// glDisable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	godRaysProgram->useProgram();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, firstPassTexture);
	glUniform1i(godRaysTextureUnform, 0);

	modelViewMatrix = vmath::translate(lightPosition[0], lightPosition[1], lightPosition[2]);
	mvpMatrix = projectionMatrix;

	vmath::vec4 toScreenPos(vmath::mat4 matrix, vmath::vec4 vector);

	vmath::vec4 lightPositionOnScreen = toScreenPos(projectionMatrix, lightPosition);

	// vmath::vec2 setScreenSpaceCoords(const vmath::mat4 m, const vmath::vec4 v);

	// vmath::vec2 asd = setScreenSpaceCoords(projectionMatrix, lightPosition);

	// std::cout << (lightPositionOnScreen[0]) << " " << (lightPositionOnScreen[1]) << std::endl;

	glUniform2f(lightPositionOnScreenUniform, lightPositionOnScreen[0], lightPositionOnScreen[1]);

	glBindVertexArray(vaoScreenQuad);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	glDisable(GL_BLEND);
	// glEnable(GL_DEPTH_TEST);

	SwapBuffers(ghdc);
}

void update(void)
{
	// code
	fAngle += 0.1f;
	if (fAngle >= 360.0f)
		fAngle -= 360.0f;
}

void uninitialise(void)
{
	// Function Declaration
	void ToggleFullScreen(void);

	// code
	int numShaders;
	glGetProgramiv(programObject, GL_ATTACHED_SHADERS, &numShaders);

	if (numShaders > 0)
	{
		GLuint *shaderObject = NULL;

		shaderObject = (GLuint *)malloc(sizeof(GLuint) * numShaders);

		glGetAttachedShaders(programObject, numShaders, NULL, shaderObject);

		for (int i = 0; i < numShaders; i++)
		{
			glDetachShader(programObject, shaderObject[i]);
			glDeleteShader(shaderObject[i]);
		}

		glDeleteProgram(programObject);
		programObject = 0;

		free(shaderObject);
		shaderObject = NULL;
	}

	if (vbo_sphere_texCoords)
	{
		glDeleteBuffers(1, &vbo_sphere_texCoords);
		vbo_sphere_texCoords = 0;
	}

	if (vbo_sphere_position)
	{
		glDeleteBuffers(1, &vbo_sphere_position);
		vbo_sphere_position = 0;
	}

	if (vao_sphere)
	{
		glDeleteVertexArrays(1, &vao_sphere);
		vao_sphere = 0;
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
		fprintf(gpFILE, "Programme Ended Successfully\n");
		fclose(gpFILE);
		gpFILE = NULL;
	}
}

vmath::vec4 toScreenPos(vmath::mat4 m, vmath::vec4 v)
{
	vmath::vec4 res = vmath::vec4(0.0f);

	for (int r = 0; r < 4; r++)
	{
		for (int c = 0; c < 4; c++)
		{
			res[r] += m[c][r] * v[c];
		}
	}

	// Perspective Division
	res[0] = res[0] / res[3];
	res[1] = res[1] / res[3];

	// from (-1 to 1) -> (0 to 1)
	res[0] = res[0] * 0.5 + 0.5;
	res[1] = res[1] * 0.5 + 0.5;

	return res;
}

vmath::vec2 setScreenSpaceCoords(const vmath::mat4 m, const vmath::vec4 v)
{

	vmath::vec4 out;
	out[0] = m[0][0] * v[0] + m[1][0] * v[1] + m[2][0] * v[2] + m[3][0] * v[3];
	out[1] = m[0][1] * v[0] + m[1][1] * v[1] + m[2][1] * v[2] + m[3][1] * v[3];
	out[2] = m[0][2] * v[0] + m[1][2] * v[1] + m[2][2] * v[2] + m[3][2] * v[3];
	out[3] = m[0][3] * v[0] + m[1][3] * v[1] + m[2][3] * v[2] + m[3][3] * v[3];
	// return out;

	vmath::vec4 ssPos = out;

	float ssX = ssPos[0] / ssPos[3];
	float ssY = ssPos[1] / ssPos[3];

	// map ssX and ssY from [-1, 1] to [0, 1]
	ssX = ssX * 0.5f + 0.5f;
	ssY = ssY * 0.5f + 0.5f;
	return vmath::vec2(ssX, ssY);
}
