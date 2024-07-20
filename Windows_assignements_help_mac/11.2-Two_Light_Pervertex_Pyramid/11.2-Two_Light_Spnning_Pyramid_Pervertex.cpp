	//xxxxxx OpenGL PP Starts.... First Code xxxxxx//
//Common header files
#include<windows.h>//win32
#include"Window.h" //or OGL.h (if rename)
#include<stdio.h>///for file IO
#include<stdlib.h>//for exit()

//OpenGL Header files
#include"GL\glew.h"//this must be before gl.h
#include<GL/GL.h>

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

GLuint VAO_Pyramid = 0;
GLuint VBO_positions_pyramid = 0;
GLuint VBO_Normal_Pyramid = 0;
GLuint VBO_Sphere_Element = 0;


GLuint projectionMatrixUniform = 0;
GLuint viewMatrixUniform = 0;
GLuint modelMatrixUniform = 0;

GLuint lightDiffuseUniform[2];
GLuint lightAmbientUniform[2];
GLuint lightSpecularUniform[2];
GLuint lightPositionUniform[2];

GLuint materialDiffuseUniform = 0;
GLuint materialAmbientUniform = 0;
GLuint materialSpecularUniform = 0;
GLuint materialShininessUniform = 0;
GLuint keyPressUniform = 0;

struct Light {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	vec4 position;
};

struct Light light[2];


//For light

GLfloat materialAmbient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat materialDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat materialSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat materialShiness = 128.0f;


vmath::mat4 perspectiveProjetionMatrix;

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


GLfloat pAngle = 0.0f;
GLfloat cAngle = 0.0f;

BOOL bLightingEnable = FALSE;


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
		case 'L':
		case 'l':
			if (bLightingEnable)
				bLightingEnable = FALSE;
			else
				bLightingEnable = TRUE;
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
		"uniform mat4 uViewMatrix;" \
		"uniform mat4 uProjectionMatrix;" \
		"uniform vec3 uLightAmbient[2];" \
		"uniform vec3 uLightDiffuse[2];" \
		"uniform vec3 uLightSpecular[2];" \
		"uniform vec4 uLightPosition[2];" \
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
		"vec4 iCoordinates = uViewMatrix * uModelViewMatrix * aPosition;"
		"vec3 transformedNormals = normalize(mat3(uViewMatrix * uModelViewMatrix) * aNormal);"
		"vec3 viewerVector = normalize(-iCoordinates.xyz);"
		"vec3 lightDirection[2];"
		"vec3 reflectionVector[2];"
		"vec3 ambientLight[2];"
		"vec3 diffuseLight[2];"
		"vec3 lightSpecular[2];"
		"	for(int i=0;i<2;i++)"
		"	{"
		"		lightDirection[i] = normalize(vec3(uLightPosition[i] - iCoordinates));"
		"		reflectionVector[i] = reflect(-lightDirection[i], transformedNormals);"
		"		ambientLight[i] = uLightAmbient[i] * uMaterialAmbient;"
		"		diffuseLight[i] = uLightDiffuse[i] * uMaterialDiffuse * max(dot(lightDirection[i], transformedNormals),0.0);"
		"		lightSpecular[i] = uLightSpecular[i] * uMaterialSpecular * pow(max(dot(reflectionVector[i], viewerVector),0.0),uMaterialShininess);"
		"		oPhongADSLight = oPhongADSLight + ambientLight[i] + diffuseLight[i] + lightSpecular[i]; "	
		"	}"
		"}"
		"else"
		"{"
		"	oPhongADSLight = vec3(0.0f, 0.0f, 0.0f);"
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
				
			}
		}
		uninitialize();//exit is available in this function
	}


	//Fragment shader
	const GLchar* fragmentShaderCode =
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
				
			}
		}
		uninitialize();
	}

	modelMatrixUniform = glGetUniformLocation(shaderProgramObject, "uModelViewMatrix");
	viewMatrixUniform = glGetUniformLocation(shaderProgramObject, "uViewMatrix");
	projectionMatrixUniform = glGetUniformLocation(shaderProgramObject, "uProjectionMatrix");
	//----
	lightAmbientUniform[0] = glGetUniformLocation(shaderProgramObject, "uLightAmbient[0]");
	lightDiffuseUniform[0] = glGetUniformLocation(shaderProgramObject, "uLightDiffuse[0]");
	lightSpecularUniform[0] = glGetUniformLocation(shaderProgramObject, "uLightSpecular[0]");
	lightPositionUniform[0] = glGetUniformLocation(shaderProgramObject, "uLightPosition[0]");

	lightAmbientUniform[1] = glGetUniformLocation(shaderProgramObject, "uLightAmbient[1]");
	lightDiffuseUniform[1] = glGetUniformLocation(shaderProgramObject, "uLightDiffuse[1]");
	lightSpecularUniform[1] = glGetUniformLocation(shaderProgramObject, "uLightSpecular[1]");
	lightPositionUniform[1] = glGetUniformLocation(shaderProgramObject, "uLightPosition[1]");
	//----
	materialAmbientUniform = glGetUniformLocation(shaderProgramObject, "uMaterialAmbienr");
	materialDiffuseUniform = glGetUniformLocation(shaderProgramObject, "uMaterialDiffuse");
	materialSpecularUniform = glGetUniformLocation(shaderProgramObject, "uMaterialSpecular");
	materialShininessUniform = glGetUniformLocation(shaderProgramObject, "uMaterialShininess");

	keyPressUniform = glGetUniformLocation(shaderProgramObject, "uKeyPress");




	const GLfloat pyramid_position[] =
	{

		// front
		   0.0f, 1.0f, 0.0f,	// front-top
		   -1.0f, -1.0f, 1.0f, // front-left
		   1.0f, -1.0f, 1.0f,	// front-right

		   // right
		   0.0f, 1.0f, 0.0f,	// right-top
		   1.0f, -1.0f, 1.0f,	// right-left
		   1.0f, -1.0f, -1.0f, // right-right

		   // back
		   0.0f, 1.0f, 0.0f,	 // back-top
		   1.0f, -1.0f, -1.0f,	 // back-left
		   -1.0f, -1.0f, -1.0f, // back-right

		   // left
		   0.0f, 1.0f, 0.0f,	 // left-top
		   -1.0f, -1.0f, -1.0f, // left-left
		   -1.0f, -1.0f, 1.0f	 // left-right


    };

	
	const GLfloat pyramid_normals[] = {

		// front
		   0.000000f, 0.447214f, 0.894427f, // front-top
		   0.000000f, 0.447214f, 0.894427f, // front-left
		   0.000000f, 0.447214f, 0.894427f, // front-right

		   // right
		   0.894427f, 0.447214f, 0.000000f, // right-top
		   0.894427f, 0.447214f, 0.000000f, // right-left
		   0.894427f, 0.447214f, 0.000000f, // right-right

		   // back
		   0.000000f, 0.447214f, -0.894427f, // back-top
		   0.000000f, 0.447214f, -0.894427f, // back-left
		   0.000000f, 0.447214f, -0.894427f, // back-right

		   // left
		   -0.894427f, 0.447214f, 0.000000f, // left-top
		   -0.894427f, 0.447214f, 0.000000f, // left-left
		   -0.894427f, 0.447214f, 0.000000f  // left-right


	};

	
    //Pyramid
	//VAO - vertex array object
	glGenVertexArrays(1, &VAO_Pyramid);
	glBindVertexArray(VAO_Pyramid);

	//Triangle

	//VBO for position - vertex buffer object
	glGenBuffers(1, &VBO_positions_pyramid);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_positions_pyramid);
	glBufferData(GL_ARRAY_BUFFER, sizeof(pyramid_position), pyramid_position, GL_STATIC_DRAW);
	glVertexAttribPointer(AMC_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(AMC_ATTRIBUTE_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//VBO for colors
	glGenBuffers(1, &VBO_Normal_Pyramid);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_Normal_Pyramid);
	glBufferData(GL_ARRAY_BUFFER, sizeof(pyramid_normals), pyramid_normals, GL_STATIC_DRAW);
	glVertexAttribPointer(AMC_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(AMC_ATTRIBUTE_NORMAL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0);


	//Enabling depth
	glClearDepth(1.0f);//depth buffer to 1
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);//check less than or equal to with 1.0f

	//Set the Clear color of Window to Blue
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //here OpenGL starts

	light[0].ambient = vec3(0.0f, 0.0f, 0.0f);
	light[1].ambient = vec3(0.0f, 0.0f, 0.0f);

	light[0].diffuse = vec3(1.0f, 0.0f, 0.0f);
	light[1].diffuse = vec3(0.0f, 0.0f, 1.0f);
	
	light[0].specular = vec3(1.0f, 0.0f, 1.0f);
	light[1].specular = vec3(0.0f, 0.0f, 1.0f);
	
	light[0].position = vec4(-2.0f, 0.0f, 0.0f, 1.0f);
	light[1].position = vec4(2.0f, 0.0f, 0.0f, 1.0f);

//	perspectiveProjetionMatrix = vmath::mat4::identity();

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


	// Pyramid
	// Transformations
	vmath::mat4 viewMatrix = vmath::mat4::identity();
	vmath::mat4 modelMatrix = vmath::mat4::identity();

	vmath::mat4 translationMatrix = vmath::mat4::identity();
	translationMatrix = vmath::translate(0.0f, 0.0f, -4.0f);

	// model matrix
	vmath::mat4 rotationMatrix = vmath::mat4::identity();
	rotationMatrix = vmath::rotate(pAngle, 0.0f, 1.0f, 0.0f);
	modelMatrix = translationMatrix * rotationMatrix;

	// Push above ModelView Projection matrix into vertex shader's mvpUniform
	glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, perspectiveProjetionMatrix);
	glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, viewMatrix);
	glUniformMatrix4fv(modelMatrixUniform, 1, GL_FALSE, modelMatrix);


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

		glUniform3fv(materialDiffuseUniform, 1, materialDiffuse);
		glUniform3fv(materialAmbientUniform, 1, materialAmbient);
		glUniform3fv(materialSpecularUniform, 1, materialSpecular);
		glUniform1f(materialShininessUniform, materialShiness);

	}
	else
	{
		glUniform1i(keyPressUniform, 0);
	}


	glBindVertexArray(VAO_Pyramid);

	glDrawArrays(GL_TRIANGLES, 0, 12);

	glBindVertexArray(0);


	glUseProgram(0);

	printGLInfo();
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





	//Triangle
	//delete VBO of color
	if (VBO_Normal_Pyramid)
	{
		glDeleteBuffers(1, &VBO_Normal_Pyramid);
		VBO_Normal_Pyramid = 0;
	}

	//delete VBO of position
	if (VBO_positions_pyramid)
	{
		glDeleteBuffers(1, &VBO_positions_pyramid);
		VBO_positions_pyramid = 0;
	}

	//delete VAO
	if (VAO_Pyramid)
	{
		glDeleteVertexArrays(1, &VAO_Pyramid);
		VAO_Pyramid = 0;
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
