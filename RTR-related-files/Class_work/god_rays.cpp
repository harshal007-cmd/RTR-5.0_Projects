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

#include "sphere.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace vmath;

// MACROS
#define WIN_WIDTH 800
#define WIN_HEIGHT 600

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

GLuint firstPassShaderProgramObject = 0;
GLuint secondPassShaderProgramObject = 0;
GLuint godRaysShaderProgramObject = 0;

#define FBO_TEXTURE_WIDTH 1080
#define FBO_TEXTURE_HEIGHT 720

enum
{
	AMC_ATTRIBUTE_POSITION = 0,
	AMC_ATTRIBUTE_COLOR,
	AMC_ATTRIBUTE_TEXCOORDS,
	AMC_ATTRIBUTE_NORMAL,

};

// first Pass Uniforms
GLuint mvpMatrixUniformFirstPass = 0;
GLuint colorUniformFirstPass = 0;

GLuint fboOcclusingObjects = 0;
GLuint firstPassTexture = 0;

// Uniforms
GLuint modelViewMatrixUniform;
GLuint projectionMatrixUniform;

GLuint textureSamplerUniform;
GLuint lightPositionUniform;

// Vao and Vbo of objects
GLuint vaoSphere;
GLuint vboSpherePosition;
GLuint vboSphereNormals;
GLuint vboElementSphere;

// vao and vbo for screen quad
GLuint vaoScreenQuad;
GLuint vboScreenQuadPosition;
GLuint vboScreenQuadTexCoords;

vmath::mat4 perspectiveProjectionMatrix;

GLint windoWidth, windowHeight;

GLuint earthTexture;

GLfloat xMove = 0.0f;
GLfloat yMove = 0.0f;

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

		windoWidth = LOWORD(lParam);
		windowHeight = HIWORD(lParam);
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
		case 'f':
		case 'F':

			ToggleFullScreen();
			break;

		case 'a':
			xMove -= 0.01f;
			break;

		case 'd':
			xMove += 0.01f;
			break;

		case 'r':
			yMove += 0.01f;
			break;

		case 't':
			yMove -= 0.01f;
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

void firstPassShader()
{
	void uninitialise(void);

	// Step1 - Write Vertex Shader
	const GLchar *vertexShaderSourceCode =
		"#version 460 core"
		"\n"
		"in vec4 aPosition;"
		"uniform mat4 uMvpMatrix;"
		"void main(void)"
		"{"
		"	gl_Position = uMvpMatrix * aPosition;"
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
		"uniform vec4 uColor;"
		"out vec4 FragColor;"
		"void main(void)"
		"{"
		"	FragColor = uColor;"
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
	firstPassShaderProgramObject = glCreateProgram();

	// Attach vertex shader to program object
	glAttachShader(firstPassShaderProgramObject, vertexShaderObject);

	// Attach fragment shader to program object
	glAttachShader(firstPassShaderProgramObject, fragmentShaderObject);

	// Bind Attirbute Locations with Shader program Object
	glBindAttribLocation(firstPassShaderProgramObject, AMC_ATTRIBUTE_POSITION, "aPosition");

	// Link Shader Program
	glLinkProgram(firstPassShaderProgramObject);

	// Error Checking
	status = 0;
	infoLogLength = 0;
	szInfoLog = NULL;

	glGetProgramiv(firstPassShaderProgramObject, GL_LINK_STATUS, &status);

	if (status == GL_FALSE)
	{
		glGetProgramiv(firstPassShaderProgramObject, GL_INFO_LOG_LENGTH, &infoLogLength);
		if (infoLogLength > 0)
		{
			szInfoLog = (char *)malloc(infoLogLength + 1);
			if (szInfoLog != NULL)
			{
				glGetProgramInfoLog(firstPassShaderProgramObject, infoLogLength + 1, NULL, szInfoLog);
				fprintf(gpFILE, "Shader Program Linking Error Log  : %s\n", szInfoLog);
				free(szInfoLog);
				szInfoLog = NULL;
			}
		}
		uninitialise();
	}

	mvpMatrixUniformFirstPass = glGetUniformLocation(firstPassShaderProgramObject, "uMvpMatrix");
	colorUniformFirstPass = glGetUniformLocation(firstPassShaderProgramObject, "uColor");
}

void godRaysShader()
{
	void uninitialise(void);

	// Step1 - Write Vertex Shader
	const GLchar *vertexShaderSourceCode =
		"#version 460 core"
		"\n"
		"in vec4 aPosition;"
		"in vec2 aTexCoords;"
		"out vec2 oTexCoords;"
		"void main(void)"
		"{"
		"	gl_Position = aPosition;"
		"	oTexCoords = aTexCoords;"
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
		"in vec2 oTexCoords;"
		"uniform sampler2D uSamplerTex;"
		"vec2 lightPositionOnScreen = vec2(0.5f,0.5f);"
		"out vec4 FragColor;"
		"void main(void)"
		"{"
		"	float decay = 0.968;"
		"	float exposure  = 0.3;"
		"	float density = 0.926;"
		"	float weight = 0.587;"
		"	int num_samples = 100;"
		"																		\n"
		"	vec2 tc = oTexCoords.xy;"
		"	vec2 deltaTexCoord = (tc - lightPositionOnScreen.xy);"
		"	deltaTexCoord *= (1.0 / float(num_samples)) * density;"
		"																		\n"
		"	float illuminationDecay = 1.0;"
		"	vec4 color = texture(uSamplerTex, tc.xy);"
		"																		\n"
		"	for(int i=0;i<num_samples;i++)"
		"	{"
		"		tc -= deltaTexCoord;"
		"		vec4 sample2  = texture(uSamplerTex,tc.xy);"
		//	"		sample2 *= illuminationDecay*weight;"
		"		color += sample2;"
		"		illuminationDecay *= decay;"
		"	}"
		"	FragColor = color;"
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
	godRaysShaderProgramObject = glCreateProgram();

	// Attach vertex shader to program object
	glAttachShader(godRaysShaderProgramObject, vertexShaderObject);

	// Attach fragment shader to program object
	glAttachShader(godRaysShaderProgramObject, fragmentShaderObject);

	// Bind Attirbute Locations with Shader program Object
	glBindAttribLocation(godRaysShaderProgramObject, AMC_ATTRIBUTE_POSITION, "aPosition");
	glBindAttribLocation(godRaysShaderProgramObject, AMC_ATTRIBUTE_TEXCOORDS, "aTexCoords");

	// Link Shader Program
	glLinkProgram(godRaysShaderProgramObject);

	// Error Checking
	status = 0;
	infoLogLength = 0;
	szInfoLog = NULL;

	glGetProgramiv(godRaysShaderProgramObject, GL_LINK_STATUS, &status);

	if (status == GL_FALSE)
	{
		glGetProgramiv(godRaysShaderProgramObject, GL_INFO_LOG_LENGTH, &infoLogLength);
		if (infoLogLength > 0)
		{
			szInfoLog = (char *)malloc(infoLogLength + 1);
			if (szInfoLog != NULL)
			{
				glGetProgramInfoLog(godRaysShaderProgramObject, infoLogLength + 1, NULL, szInfoLog);
				fprintf(gpFILE, "Shader Program Linking Error Log  : %s\n", szInfoLog);
				free(szInfoLog);
				szInfoLog = NULL;
			}
		}
		uninitialise();
	}

	textureSamplerUniform = glGetUniformLocation(godRaysShaderProgramObject, "uSamplerTex");
	// lightPositionUniform = glGetUniformLocation(godRaysShaderProgramObject, "lightPositionOnScreen");
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

	// Main shader Program
	void firstPassShader();
	firstPassShader();

	// god Rays Shader
	void godRaysShader();
	godRaysShader();

	// Declare position and color array
	sphereInit(1.0f, 50, 50);

	glGenVertexArrays(1, &vaoSphere);
	glBindVertexArray(vaoSphere);

	glGenBuffers(1, &vboSpherePosition);
	glBindBuffer(GL_ARRAY_BUFFER, vboSpherePosition);
	glBufferData(GL_ARRAY_BUFFER, sphere_vertices.size() * sizeof(float), sphere_vertices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(AMC_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(AMC_ATTRIBUTE_POSITION);

	glGenBuffers(1, &vboSphereNormals);
	glBindBuffer(GL_ARRAY_BUFFER, vboSphereNormals);
	glBufferData(GL_ARRAY_BUFFER, sphere_normals.size() * sizeof(float), sphere_normals.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(AMC_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(AMC_ATTRIBUTE_NORMAL);

	// vbo SPhere Indices
	glGenBuffers(1, &vboElementSphere);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboElementSphere);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned), indices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

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
	glVertexAttribPointer(AMC_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(AMC_ATTRIBUTE_POSITION);

	// Tecoords buffer
	glGenBuffers(1, &vboScreenQuadTexCoords);
	glBindBuffer(GL_ARRAY_BUFFER, vboScreenQuadTexCoords);
	glBufferData(GL_ARRAY_BUFFER, sizeof(screen_quad_texcoords), screen_quad_texcoords, GL_STATIC_DRAW);
	glVertexAttribPointer(AMC_ATTRIBUTE_TEXCOORDS, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(AMC_ATTRIBUTE_TEXCOORDS);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	void init_FBO();
	init_FBO();

	// Enabling Depth
	glClearDepth(1.0f);		 // Compulsory
	glEnable(GL_DEPTH_TEST); // Compulsory
	glDepthFunc(GL_LEQUAL);	 // Compulsory
	glEnable(GL_TEXTURE_2D);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	earthTexture = createTexture2D("box.jpg");

	// Initialise orthographic projection matrix
	perspectiveProjectionMatrix = vmath::mat4::identity();
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

	// Set Perspective Projection Matrix
	perspectiveProjectionMatrix = vmath::perspective(45.0f, (float)width / (float)height, 0.1f, 100.0f);
}

void display(void)
{
	vmath::mat4 modelMatrix;
	vmath::mat4 viewMatrix;
	vmath::mat4 mvpMatrix;

	// code
	// First Pass
	// Draw Occluding objects and Source of Light in texture

	glBindFramebuffer(GL_FRAMEBUFFER, fboOcclusingObjects);
	resize(FBO_TEXTURE_WIDTH, FBO_TEXTURE_HEIGHT);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(firstPassShaderProgramObject);

	modelMatrix = vmath::translate(0.0f, 0.0f, -20.0f);

	mvpMatrix = perspectiveProjectionMatrix * modelMatrix;

	// Draw Sun
	glUniformMatrix4fv(mvpMatrixUniformFirstPass, 1, GL_FALSE, mvpMatrix);
	glUniform4f(colorUniformFirstPass, 0.008, 0.008, 0.008, 1.0);

	glBindVertexArray(vaoSphere);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboElementSphere);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

	// Draw Occluding object
	modelMatrix = vmath::translate(xMove, yMove, -10.0f) * vmath::scale(0.3f, 0.3f, 0.3f);

	mvpMatrix = perspectiveProjectionMatrix * modelMatrix;

	glUniformMatrix4fv(mvpMatrixUniformFirstPass, 1, GL_FALSE, mvpMatrix);
	glUniform4f(colorUniformFirstPass, 0.0, 0.0, 0.0, 0.0);

	// Draw object
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboElementSphere);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	///////////////////////////////////////////////////////////////////
	// Second Pass
	resize(windoWidth, windowHeight);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDisable(GL_DEPTH_TEST);
	glUseProgram(firstPassShaderProgramObject);
	modelMatrix = vmath::translate(0.0f, 0.0f, -20.0f);

	mvpMatrix = perspectiveProjectionMatrix * modelMatrix;

	glUniformMatrix4fv(mvpMatrixUniformFirstPass, 1, GL_FALSE, mvpMatrix);
	glUniform4f(colorUniformFirstPass, 1.0, 1.0, 1.0, 1.0);

	// Draw Sun

	glBindVertexArray(vaoSphere);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

	// Draw Occluding object
	modelMatrix = vmath::translate(xMove, yMove, -10.0f) * vmath::scale(0.3f, 0.3f, 0.3f);

	mvpMatrix = perspectiveProjectionMatrix * modelMatrix;

	glUniformMatrix4fv(mvpMatrixUniformFirstPass, 1, GL_FALSE, mvpMatrix);
	glUniform4f(colorUniformFirstPass, 0.0, 0.0, 1.0, 1.0);

	// Draw object
	glBindVertexArray(vaoSphere);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

	glEnable(GL_DEPTH_TEST);

	//////////////////////////////////////////////////////////
	// Third Pass
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	glUseProgram(godRaysShaderProgramObject);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, firstPassTexture);
	glUniform1i(textureSamplerUniform, 0);

	glBindVertexArray(vaoScreenQuad);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	glDisable(GL_BLEND);

	SwapBuffers(ghdc);
}

void update(void)
{
	// code
}

vec4 mult(mat4 mat, vec4 v)
{
	vec4 res;

	res[0] = mat[0][0] * v[0] + mat[1][0] * v[1] + mat[2][0] * v[2] + mat[3][0] * v[3];
	res[1] = mat[0][1] * v[0] + mat[1][1] * v[1] + mat[2][1] * v[2] + mat[3][1] * v[3];
	res[2] = mat[0][2] * v[0] + mat[1][2] * v[1] + mat[2][2] * v[2] + mat[3][2] * v[3];
	res[3] = mat[0][3] * v[0] + mat[1][3] * v[1] + mat[2][3] * v[2] + mat[3][3] * v[3];

	return res;
}

void uninitialise(void)
{
	// Function Declaration
	void ToggleFullScreen(void);

	// code
	// Delete Shaders objects and Shader Program object
	/*
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
	/*
		// Delete VBO of Position
		if (vboScreenQuadPosition)
		{
			glDeleteBuffers(1, &vbo_color);
			vbo_color = 0;
		}

		if (vbo_position)
		{
			glDeleteBuffers(1, &vbo_position);
			vbo_position = 0;
		}

		// Delete VAO
		if (vao)
		{
			glDeleteVertexArrays(1, &vao);
			vao = 0;
		}
	*/
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
		fclose(stdout);
		FreeConsole();

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
