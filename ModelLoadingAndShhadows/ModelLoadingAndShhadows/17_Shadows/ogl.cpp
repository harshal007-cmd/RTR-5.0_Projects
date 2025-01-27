#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "ogl.h"

#include <GL/glew.h>
// #include <GL/wglew.h>
#include <GL/GL.h>
#include "vmath.h"

#pragma comment(lib, "glew32.lib")   // Loads OpenGL core library functions supported on the platform
#pragma comment(lib, "openGL32.lib") // OpenGL 1.1 version functions and wgl functions provided by windows Corp.

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "ShaderProgramObject.hpp"
#include "sphere.h"

#define WND_WIDTH 800
#define WND_HEIGHT 600

#define FBO_TEXTURE_WIDTH 2048
#define FBO_TEXTURE_HEIGHT 2048

BOOL bActive = FALSE;

// FILE io
FILE *gpFILE = NULL;

// FullScreen Of Window
HWND ghwnd;
DWORD dwStyle;
BOOL gbFullScreen = FALSE;
WINDOWPLACEMENT wpPrev = {sizeof(WINDOWPLACEMENT)};

// OpenGL
PIXELFORMATDESCRIPTOR pfd;
HDC ghdc;
HGLRC ghrc;
int iPixelType;

enum
{
    AMC_ATTRIBUTE_POSITION = 0,
    AMC_ATTRIBUTE_COLOR,
    AMC_ATTRIBUTE_TEXCOORDS,
    AMC_ATTRIBUTE_NORMALS

};

struct light
{
    vmath::vec3 ambient;
    vmath::vec3 diffuse;
    vmath::vec3 specular;
    vmath::vec4 position;
};

vmath::mat4 perspectiveProjectionMatrix;

light lightSourceA = {
    vmath::vec3(0.2f, 0.2f, 0.2f),
    vmath::vec3(1.0f, 1.0f, 1.0f),
    vmath::vec3(1.0f, 1.0f, 1.0f),
    vmath::vec4(5.0f, 2.0f, 0.0f, 1.0f),
};

GLuint vaoCube;
GLuint vaoSquare;

sphere *pSphere = 0;

// Programs
ShaderProgramObject *pFirstPassProgram = 0;
GLuint mvpMatrixUniform_FPP = 0;

ShaderProgramObject *pSecondPassProgram = 0;

ShaderProgramObject *pTestProgram = 0;
GLuint vaoTest;

ShaderProgramObject *simpleProgram = 0;

// FBO
GLuint fbo;
GLuint depthTexture;

GLuint winWidth, winHeight;

GLuint floorTexture;
GLuint boxTexture;

GLfloat eyeX, eyeY, eyeZ = -10.0f;
GLfloat lightX = 10, lightY = 10, lightZ;

//  Callback Function declaration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// Entry Point function defination
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
    // function declarations
    int initialise(void);
    void display(void);
    void update(void);
    void uninitialise(void);

    WNDCLASSEX wndclass;
    HWND hwnd;
    MSG msg;
    TCHAR szClassName[] = TEXT("MyClass");

    // Console Output
    if (!AttachConsole(ATTACH_PARENT_PROCESS))
    {
        AllocConsole();
    }

    freopen("CONOUT$", "w", stdout);
    std::cout << "Hello World!!!\n";

    // Log File Opening
    fopen_s(&gpFILE, "log.txt", "w");

    if (gpFILE == NULL)
    {
        MessageBox(NULL, TEXT("ERROR"), TEXT("File Opening Failed"), MB_OK);
        return -1;
    }

    fprintf(gpFILE, "Programme Started Successfully\n");

    wndclass.cbSize = sizeof(WNDCLASSEX);
    wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wndclass.hInstance = hInstance;
    wndclass.lpfnWndProc = WndProc;
    wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MyIcon));
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wndclass.lpszClassName = szClassName;
    wndclass.lpszMenuName = NULL;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MyIcon));

    RegisterClassEx(&wndclass);

    hwnd = CreateWindowEx(
        WS_EX_APPWINDOW,
        szClassName,
        TEXT("MyWindow"),
        WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE,
        GetSystemMetrics(SM_CXSCREEN) / 2 - WND_WIDTH / 2,
        GetSystemMetrics(SM_CYSCREEN) / 2 - WND_HEIGHT / 2,
        WND_WIDTH, WND_HEIGHT,
        NULL, NULL, hInstance, NULL);

    ghwnd = hwnd;

    if (initialise() < 0)
    {
        std::cout << "IniTialisation Failed" << std::endl;
        uninitialise();
        exit(EXIT_FAILURE);
    }

    ShowWindow(hwnd, iCmdShow);
    SetForegroundWindow(hwnd);
    SetFocus(hwnd);

    BOOL bDone = FALSE;
    while (bDone == FALSE)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message != WM_QUIT)
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
            else
            {
                bDone = TRUE;
            }
        }
        else
        {
            if (bActive == TRUE)
            {
                update();
                display();
            }
        }
    }

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
        bActive = TRUE;
        break;

    case WM_KILLFOCUS:
        bActive = FALSE;
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
            eyeZ += 0.1f;
            break;

        case 's':
            eyeZ -= 0.1f;
            break;

        case 'a':
            eyeX += 0.1f;
            break;
        case 'd':
            eyeX -= 0.1f;
            break;

        case 'r':
            eyeY += 0.1f;
            break;

        case 't':
            eyeY -= 0.1f;
            break;

        case 'i':
            lightZ += 0.1f;
            break;
        case 'k':
            lightZ -= 0.1f;
            break;

        case 'j':
            lightX += 0.1f;
            break;
        case 'l':
            lightX -= 0.1f;
            break;

        case 'u':
            lightY += 0.1f;
            break;
        case 'o':
            lightY -= 0.1f;

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

void initFBO()
{
    glCreateFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    // Texture
    glGenTextures(1, &depthTexture);
    glBindTexture(GL_TEXTURE_2D, depthTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, FBO_TEXTURE_WIDTH, FBO_TEXTURE_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindTexture(GL_TEXTURE_2D, 0);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

GLuint createTexture2D(const char *filePath)
{
    stbi_set_flip_vertically_on_load(true);
    int width, height, channel;
    unsigned char *data = stbi_load(filePath, &width, &height, &channel, 0);

    if (!data)
    {
        fprintf(gpFILE, "Failed To Load %s Texture\n", filePath);
        return 0;
    }

    GLenum format = GL_RGBA;

    if (channel == STBI_grey)
        format = GL_RED;
    else if (channel == STBI_rgb)
        format = GL_RGB;
    else if (channel == STBI_rgb_alpha)
        format = GL_RGBA;

    GLuint texture;
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
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

    iPixelType = ChoosePixelFormat(ghdc, &pfd);

    if (iPixelType == 0)
    {
        fprintf(gpFILE, "ChoosePixelFormat()  Failed\n");
        return -2;
    }

    if (SetPixelFormat(ghdc, iPixelType, &pfd) == FALSE)
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

    // Shaders

    // Simple Shader
    const char *vs_simple[] =
        {
            "#version 460 core\n"
            "layout(location = 0) in vec4 aPosition;\n"
            "uniform mat4 mvpMatrix;\n"
            "void main(void)\n"
            "{"
            "   gl_Position = mvpMatrix * aPosition;\n"
            "}"};

    const char *fs_simple[] =
        {
            "#version 460 core\n"
            "out vec4 fragColor;\n"
            "void main(void)\n"
            "{\n"
            "   fragColor = vec4(1.0f);\n"
            "}\n"};

    simpleProgram = new ShaderProgramObject(vs_simple, fs_simple);

    // Test
    // test Shader
    const char *vs_test[] =
        {
            "#version 460 core\n"
            "layout(location = 0) in vec4 aPosition;\n"
            "layout(location = 2) in vec2 aTexCoords;\n"
            "out vec2 oTexCoords;\n"
            "void main(void)\n"
            "{\n"
            "   gl_Position = aPosition;\n"
            "   oTexCoords = aTexCoords;\n"
            "}\n"};

    const char *fs_test[] =
        {
            "#version 460 core\n"
            "in vec2 oTexCoords;\n"
            "uniform sampler2D texObj;\n"
            "out vec4 fragColor;\n"
            "void main(void)\n"
            "{\n"
            "   fragColor = vec4(vec3(texture(texObj,oTexCoords).r),1.0f);\n"
            "}\n"};

    pTestProgram = new ShaderProgramObject(vs_test, fs_test);

    // First Shader to get depth Values
    const char *vs_depth[] =
        {
            "#version 460 core\n"
            "layout(location = 0) in vec4 aPosition;\n"
            "uniform mat4 mvpMatrix;\n"
            "void main(void)\n"
            "{\n"
            "   gl_Position = mvpMatrix * aPosition;\n"
            "}\n"};

    const char *fs_depth[] =
        {
            "#version 460 core\n"
            "void main(void)\n"
            "{\n"
            "}\n"};

    pFirstPassProgram = new ShaderProgramObject(vs_depth, fs_depth);
    mvpMatrixUniform_FPP = pFirstPassProgram->getUniformLocation("mvpMatrix");

    // Second MAin Phong Lighitng Program
    const char *vs_Light[] =
        {
            "#version 460 core\n"
            "layout(location = 0) in vec4 aPosition;\n"
            "layout(location = 2) in vec2 aTexcoords;\n"
            "layout(location = 3) in vec3 aNormal;\n"
            "uniform mat4 modelMatrix;\n"
            "uniform mat4 viewMatrix;\n"
            "uniform mat4 pMatrix;\n"
            "uniform mat4 lightSpaceMVPMatrix;\n"
            "uniform vec4 lightPos;\n"
            "out vec2 oTexcoords;\n"
            "out vec3 oTranNormal;\n"
            "out vec3 oViewVector;\n"
            "out vec3 oLightDirection;\n"
            "out vec4 oLightSpaceFragPos;\n"
            "void main(void)\n"
            "{\n"
            "   oLightSpaceFragPos = lightSpaceMVPMatrix * aPosition;\n"
            "   vec4 eyePosition = viewMatrix * modelMatrix * aPosition;\n"
            "   mat3 normalMatrix = mat3(transpose(inverse(viewMatrix * modelMatrix)));\n"
            "   oTranNormal = mat3(viewMatrix * modelMatrix) * aNormal;\n"
            "   oLightDirection = vec3(viewMatrix * lightPos - eyePosition);\n"
            "   oViewVector =  -eyePosition.xyz;\n"
            "   gl_Position = pMatrix * viewMatrix * modelMatrix * aPosition;\n"
            "   oTexcoords = aTexcoords;\n"
            "}\n"};

    const char *fs_Light[] =
        {
            "#version 460 core\n"
            "in vec2 oTexcoords;\n"
            "in vec3 oTranNormal;\n"
            "in vec3 oViewVector;\n"
            "in vec3 oLightDirection;\n"
            "in vec4 oLightSpaceFragPos;\n"
            "uniform vec3 lightAmbient;\n"
            "uniform vec3 lightDiffuse;\n"
            "uniform vec3 lightSpecular;\n"
            "uniform vec3 matAmbient;\n"
            "uniform vec3 matSpecular;\n"
            "uniform float matShininess;\n"
            "uniform sampler2D diffuseTexture;\n"
            "uniform sampler2D depthTexture;\n"
            "out vec4 fragColor;\n"
            "\n"
            "float calculateShadow(vec4 lightSpaceFragPos)\n"
            "{\n"
            "   vec3 projCoords = lightSpaceFragPos.xyz / lightSpaceFragPos.w;\n"
            "   projCoords = projCoords * 0.5f + 0.5f;\n"
            "   float closestDepth = texture(depthTexture, projCoords.xy).r;\n"
            "   float currentDepth = projCoords.z;\n"
            "   float bias = max(0.05 * dot(normalize(oTranNormal),normalize(oLightDirection)),0.005f);"
            "   float shadow = currentDepth-0.005 > closestDepth  ? 1.0f : 0.0f;\n"
            "   return shadow;\n"
            "}\n"
            "void main(void)\n"
            "{\n"
            "   vec3 normNormal = normalize(oTranNormal);\n"
            "   vec3 normViewVector = normalize(oViewVector);\n"
            "   vec3 normLightDir = normalize(oLightDirection);\n"
            "   vec3 reflectionVector = reflect(-normLightDir,normNormal);\n"
            "   vec3 ambientLight = lightAmbient * texture(diffuseTexture,oTexcoords).rgb;\n"
            "   vec3 diffuseLight = texture(diffuseTexture,oTexcoords).rgb * lightDiffuse * max(dot(normNormal,normLightDir),0.0f);\n"
            "   vec3 specularLight = lightSpecular * matSpecular * pow(max(dot(reflectionVector,normViewVector),0.0f),matShininess);\n"
            "   float shadow =  calculateShadow(oLightSpaceFragPos);\n"
            "   fragColor = vec4((ambientLight + (diffuseLight + specularLight) * (1.0f - shadow )),1.0f);\n"
            "}\n"

        };

    pSecondPassProgram = new ShaderProgramObject(vs_Light, fs_Light);

    initFBO();

    // Object Data
    pSphere = new sphere(1.0f, 50, 50);

    // Cube
    GLfloat cubeVertices[] =
        {
            // front
            1.0f, 1.0f, 1.0f,   // top-right of front
            -1.0f, 1.0f, 1.0f,  // top-left of front
            -1.0f, -1.0f, 1.0f, // bottom-left of front
            1.0f, -1.0f, 1.0f,  // bottom-right of front

            // right
            1.0f, 1.0f, -1.0f,  // top-right of right
            1.0f, 1.0f, 1.0f,   // top-left of right
            1.0f, -1.0f, 1.0f,  // bottom-left of right
            1.0f, -1.0f, -1.0f, // bottom-right of right

            // back
            1.0f, 1.0f, -1.0f,   // top-right of back
            -1.0f, 1.0f, -1.0f,  // top-left of back
            -1.0f, -1.0f, -1.0f, // bottom-left of back
            1.0f, -1.0f, -1.0f,  // bottom-right of back

            // left
            -1.0f, 1.0f, 1.0f,   // top-right of left
            -1.0f, 1.0f, -1.0f,  // top-left of left
            -1.0f, -1.0f, -1.0f, // bottom-left of left
            -1.0f, -1.0f, 1.0f,  // bottom-right of left

            // top
            1.0f, 1.0f, -1.0f,  // top-right of top
            -1.0f, 1.0f, -1.0f, // top-left of top
            -1.0f, 1.0f, 1.0f,  // bottom-left of top
            1.0f, 1.0f, 1.0f,   // bottom-right of top

            // bottom
            1.0f, -1.0f, 1.0f,   // top-right of bottom
            -1.0f, -1.0f, 1.0f,  // top-left of bottom
            -1.0f, -1.0f, -1.0f, // bottom-left of bottom
            1.0f, -1.0f, -1.0f,  // bottom-right of bottom
        };

    GLfloat cubeTexcoords[] =
        {
            // front
            1.0f, 1.0f, // top-right of front
            0.0f, 1.0f, // top-left of front
            0.0f, 0.0f, // bottom-left of front
            1.0f, 0.0f, // bottom-right of front

            // right
            1.0f, 1.0f, // top-right of right
            0.0f, 1.0f, // top-left of right
            0.0f, 0.0f, // bottom-left of right
            1.0f, 0.0f, // bottom-right of right

            // back
            1.0f, 1.0f, // top-right of back
            0.0f, 1.0f, // top-left of back
            0.0f, 0.0f, // bottom-left of back
            1.0f, 0.0f, // bottom-right of back

            // left
            1.0f, 1.0f, // top-right of left
            0.0f, 1.0f, // top-left of left
            0.0f, 0.0f, // bottom-left of left
            1.0f, 0.0f, // bottom-right of left

            // top
            1.0f, 1.0f, // top-right of top
            0.0f, 1.0f, // top-left of top
            0.0f, 0.0f, // bottom-left of top
            1.0f, 0.0f, // bottom-right of top

            // bottom
            1.0f, 1.0f, // top-right of bottom
            0.0f, 1.0f, // top-left of bottom
            0.0f, 0.0f, // bottom-left of bottom
            1.0f, 0.0f, // bottom-right of bottom
        };

    GLfloat cubeNormals[] =
        {
            // front surface
            0.0f, 0.0f, 1.0f, // top-right of front
            0.0f, 0.0f, 1.0f, // top-left of front
            0.0f, 0.0f, 1.0f, // bottom-left of front
            0.0f, 0.0f, 1.0f, // bottom-right of front

            // right surface
            1.0f, 0.0f, 0.0f, // top-right of right
            1.0f, 0.0f, 0.0f, // top-left of right
            1.0f, 0.0f, 0.0f, // bottom-left of right
            1.0f, 0.0f, 0.0f, // bottom-right of right

            // back surface
            0.0f, 0.0f, -1.0f, // top-right of back
            0.0f, 0.0f, -1.0f, // top-left of back
            0.0f, 0.0f, -1.0f, // bottom-left of back
            0.0f, 0.0f, -1.0f, // bottom-right of back

            // left surface
            -1.0f, 0.0f, 0.0f, // top-right of left
            -1.0f, 0.0f, 0.0f, // top-left of left
            -1.0f, 0.0f, 0.0f, // bottom-left of left
            -1.0f, 0.0f, 0.0f, // bottom-right of left

            // top surface
            0.0f, 1.0f, 0.0f, // top-right of top
            0.0f, 1.0f, 0.0f, // top-left of top
            0.0f, 1.0f, 0.0f, // bottom-left of top
            0.0f, 1.0f, 0.0f, // bottom-right of top

            // bottom surface
            0.0f, -1.0f, 0.0f, // top-right of bottom
            0.0f, -1.0f, 0.0f, // top-left of bottom
            0.0f, -1.0f, 0.0f, // bottom-left of bottom
            0.0f, -1.0f, 0.0f, // bottom-right of bottom
        };

    glCreateVertexArrays(1, &vaoCube);
    glBindVertexArray(vaoCube);

    // cube position
    GLuint vbo;
    glCreateBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(AMC_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(AMC_ATTRIBUTE_POSITION);

    // TexCoords
    glCreateBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeTexcoords), cubeTexcoords, GL_STATIC_DRAW);
    glVertexAttribPointer(AMC_ATTRIBUTE_TEXCOORDS, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(AMC_ATTRIBUTE_TEXCOORDS);

    // Normals
    glCreateBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeNormals), cubeNormals, GL_STATIC_DRAW);
    glVertexAttribPointer(AMC_ATTRIBUTE_NORMALS, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(AMC_ATTRIBUTE_NORMALS);

    // Square Data
    const GLfloat squareVertices[] =
        {
            10.0f, 0.0f, -10.0f,
            -10.0f, 0.0f, -10.0f,
            -10.0f, 0.0f, 10.0f,
            10.0f, 0.0f, 10.0f};

    const GLfloat squareTexCoords[] =
        {
            1.0f, 1.0f,
            0.0f, 1.0f,
            0.0f, 0.0f,
            1.0f, 0.0f

        };

    const GLfloat squareNormals[] =
        {
            0.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 0.0f

        };

    glCreateVertexArrays(1, &vaoSquare);
    glBindVertexArray(vaoSquare);

    // Square position

    glCreateBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(squareVertices), squareVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(AMC_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(AMC_ATTRIBUTE_POSITION);

    // TexCoords
    glCreateBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(squareTexCoords), squareTexCoords, GL_STATIC_DRAW);
    glVertexAttribPointer(AMC_ATTRIBUTE_TEXCOORDS, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(AMC_ATTRIBUTE_TEXCOORDS);

    // Normals
    glCreateBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(squareNormals), squareNormals, GL_STATIC_DRAW);
    glVertexAttribPointer(AMC_ATTRIBUTE_NORMALS, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(AMC_ATTRIBUTE_NORMALS);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //////Testing Object
    const GLfloat squareVerticesTest[] =
        {
            1.0f, 1.0f, 0.0f,
            -1.0f, 1.0f, 0.0f,
            -1.0f, -1.0f, 0.0f,
            1.0f, -1.0f, 0.0f};

    const GLfloat squareTexCoordsTest[] =
        {
            1.0f, 1.0f,
            0.0f, 1.0f,
            0.0f, 0.0f,
            1.0f, 0.0f

        };

    glCreateVertexArrays(1, &vaoTest);
    glBindVertexArray(vaoTest);

    // Square position

    glCreateBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(squareVerticesTest), squareVerticesTest, GL_STATIC_DRAW);
    glVertexAttribPointer(AMC_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(AMC_ATTRIBUTE_POSITION);

    // TexCoords
    glCreateBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(squareTexCoordsTest), squareTexCoordsTest, GL_STATIC_DRAW);
    glVertexAttribPointer(AMC_ATTRIBUTE_TEXCOORDS, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(AMC_ATTRIBUTE_TEXCOORDS);

    // Load Texture Images
    boxTexture = createTexture2D("box.jpg");
    if (boxTexture == 0)
    {
        fprintf(gpFILE, "Texture Laodng Failed For box.jpg\n");
        return -1;
    }
    else
    {
        fprintf(gpFILE, "Texture Laodng SUCCESS For box.jpg %d\n", boxTexture);
    }

    floorTexture = createTexture2D("woodTiles.png");
    if (floorTexture == 0)
    {
        fprintf(gpFILE, "Texture Laodng Failed For woodTiles.png\n");
        return -1;
    }
    else
    {
        fprintf(gpFILE, "Texture Laodng SUCCESS For woodTiles.jpg %d\n", floorTexture);
    }

    // Enabling Depth
    glClearDepth(1.0f);      // Compulsory
    glEnable(GL_DEPTH_TEST); // Compulsory
    glDepthFunc(GL_LEQUAL);  // Compulsory

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Initialise orthographic projection matrix
    perspectiveProjectionMatrix = vmath::mat4::identity();
    resize(WND_WIDTH, WND_HEIGHT);
    return 0;
}

void resize(int width, int height)
{
    if (height < 0)
        height = 1;

    glViewport(0, 0, (GLsizei)width, (GLsizei)height);

    perspectiveProjectionMatrix = vmath::perspective(45.0f, (float)width / (float)height, 1.0f, 100.0f);
}

void display(void)
{
    void drawCube();
    void drawSquare();

    // code
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    vmath::mat4 modelMatrix;
    vmath::mat4 cameraViewMatrix;
    vmath::mat4 lightViewMatrix;
    vmath::mat4 cameraMVPMatrix;
    vmath::mat4 lightMVPMatrix;
    vmath::mat4 lightVPMatrix;

    vmath::mat4 lightSpaceMatrix;
    vmath::mat4 orthoMatrix;

    lightSourceA.position = vmath::vec4(lightX, lightY, lightZ, 1.0f);

    // First Pass to get Depth Values from lights Perspective
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    // glEnable(GL_POLYGON_OFFSET_FILL);
    // glPolygonOffset(0.2f, 0.2f);

    resize(FBO_TEXTURE_WIDTH, FBO_TEXTURE_HEIGHT);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    pFirstPassProgram->useProgram();
    lightViewMatrix = vmath::lookat(vmath::vec3(lightSourceA.position[0], lightSourceA.position[1], lightSourceA.position[2]), vmath::vec3(0.0f, 0.0f, 0.0f), vmath::vec3(0.0f, 1.0f, 0.0f));

    // viewMatrix = vmath::mat4::identity();
    orthoMatrix = vmath::ortho(-10.0f, 10.0f, -10.0f, 10.0f, -80.0f, 80.0f);

    lightVPMatrix = orthoMatrix * lightViewMatrix;

    modelMatrix = vmath::translate(0.0f, -3.0f, 0.0f);
    lightMVPMatrix = lightVPMatrix * modelMatrix;
    glUniformMatrix4fv(mvpMatrixUniform_FPP, 1, GL_FALSE, lightMVPMatrix);
    drawSquare();

    modelMatrix = vmath::translate(0.0f, 0.0f, 0.0f);
    lightMVPMatrix = lightVPMatrix * modelMatrix;
    glUniformMatrix4fv(mvpMatrixUniform_FPP, 1, GL_FALSE, lightMVPMatrix);
    drawCube();

    modelMatrix = vmath::translate(-2.0f, -1.0f, 3.0f);
    lightMVPMatrix = lightVPMatrix * modelMatrix;
    glUniformMatrix4fv(mvpMatrixUniform_FPP, 1, GL_FALSE, lightMVPMatrix);
    drawCube();

    modelMatrix = vmath::translate(2.0f, -2.0f, 1.0f);
    lightMVPMatrix = lightVPMatrix * modelMatrix;
    glUniformMatrix4fv(mvpMatrixUniform_FPP, 1, GL_FALSE, lightMVPMatrix);
    pSphere->draw();

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // Testing
    /*
    resize(winWidth, winHeight);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    pTestProgram->useProgram();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, depthTexture);
    glUniform1i(pTestProgram->getUniformLocation("texObj"), 0);

    glBindVertexArray(vaoTest);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
*/

    // Second Pass
    glDisable(GL_POLYGON_OFFSET_FILL);

    resize(winWidth, winHeight);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    pSecondPassProgram->useProgram();
    cameraViewMatrix = vmath::lookat(vmath::vec3(eyeX, eyeY, eyeZ), vmath::vec3(0.0f, 0.0f, 0.0f), vmath::vec3(0.0f, 1.0f, 0.0f));

    /*
        "uniform mat4 modelMatrix;\n"
        "uniform mat4 viewMatrix;\n"
        "uniform mat4 pMatrix;\n"
        "uniform mat4 lightSpaceMatrix;\n"
        "uniform vec4 lightPos;\n"

         "uniform vec3 lightAmbient;\n"
            "uniform vec3 lightDiffuse;\n"
            "uniform vec3 lightSpecular;\n"
            "uniform vec4 lightPos;\n"
            "uniform vec3 matAmbient;\n"
            "uniform vec3 matSpecular;\n"
            "uniform float matShininess;\n"
            "uniform sampler2D diffuseTexture;\n"
            "uniform smapler2D depthTexture;\n"

            lightSpaceMVPMatrix
*/

    // view and Projection Matrix
    glUniformMatrix4fv(pSecondPassProgram->getUniformLocation("viewMatrix"), 1, GL_FALSE, cameraViewMatrix);
    glUniformMatrix4fv(pSecondPassProgram->getUniformLocation("pMatrix"), 1, GL_FALSE, perspectiveProjectionMatrix);

    // Light Uniforms
    glUniform3fv(pSecondPassProgram->getUniformLocation("lightAmbient"), 1, lightSourceA.ambient);
    glUniform3fv(pSecondPassProgram->getUniformLocation("lightDiffuse"), 1, lightSourceA.diffuse);
    glUniform3fv(pSecondPassProgram->getUniformLocation("lightSpecular"), 1, lightSourceA.specular);
    glUniform4fv(pSecondPassProgram->getUniformLocation("lightPos"), 1, lightSourceA.position);

    // Depth Texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, depthTexture);
    glUniform1i(pSecondPassProgram->getUniformLocation("depthTexture"), 0);

    //////////Objects ////////////////////
    // Draw Floor
    modelMatrix = vmath::translate(0.0f, -3.0f, 0.0f);
    lightMVPMatrix = lightVPMatrix * modelMatrix;
    glUniformMatrix4fv(pSecondPassProgram->getUniformLocation("lightSpaceMVPMatrix"), 1, GL_FALSE, lightMVPMatrix);
    glUniformMatrix4fv(pSecondPassProgram->getUniformLocation("modelMatrix"), 1, GL_FALSE, modelMatrix);

    // Floor Material Properties
    //  glUniform3fv(pSecondPassProgram->getUniformLocation("matAmbient"), 1, lightSourceA.ambient);
    glUniform3fv(pSecondPassProgram->getUniformLocation("matSpecular"), 1, lightSourceA.specular);
    glUniform1f(pSecondPassProgram->getUniformLocation("matShininess"), 20.0f);

    // floor Texture
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, floorTexture);
    glUniform1i(pSecondPassProgram->getUniformLocation("diffuseTexture"), 1);
    drawSquare();

    // Draw Cube
    modelMatrix = vmath::translate(0.0f, 0.0f, 0.0f);
    lightMVPMatrix = lightVPMatrix * modelMatrix;
    glUniformMatrix4fv(pSecondPassProgram->getUniformLocation("lightSpaceMVPMatrix"), 1, GL_FALSE, lightMVPMatrix);
    glUniformMatrix4fv(pSecondPassProgram->getUniformLocation("modelMatrix"), 1, GL_FALSE, modelMatrix);

    // Floor Material Properties
    //   glUniform3fv(pSecondPassProgram->getUniformLocation("matAmbient"), 1, lightSourceA.ambient);
    glUniform3fv(pSecondPassProgram->getUniformLocation("matSpecular"), 1, lightSourceA.specular);
    glUniform1f(pSecondPassProgram->getUniformLocation("matShininess"), 20.0f);

    // box Texture
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, boxTexture);
    glUniform1i(pSecondPassProgram->getUniformLocation("diffuseTexture"), 1);
    drawCube();

    // Draw Cube
    modelMatrix = vmath::translate(-2.0f, -1.0f, 3.0f);
    lightMVPMatrix = lightVPMatrix * modelMatrix;
    glUniformMatrix4fv(pSecondPassProgram->getUniformLocation("lightSpaceMVPMatrix"), 1, GL_FALSE, lightMVPMatrix);
    glUniformMatrix4fv(pSecondPassProgram->getUniformLocation("modelMatrix"), 1, GL_FALSE, modelMatrix);

    // Floor Material Properties
    //   glUniform3fv(pSecondPassProgram->getUniformLocation("matAmbient"), 1, lightSourceA.ambient);
    glUniform3fv(pSecondPassProgram->getUniformLocation("matSpecular"), 1, lightSourceA.specular);
    glUniform1f(pSecondPassProgram->getUniformLocation("matShininess"), 20.0f);

    // floor Texture
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, boxTexture);
    glUniform1i(pSecondPassProgram->getUniformLocation("diffuseTexture"), 1);
    drawCube();

    // Draw sphere
    modelMatrix = vmath::translate(2.0f, -2.0f, 1.0f);
    lightMVPMatrix = lightVPMatrix * modelMatrix;
    glUniformMatrix4fv(pSecondPassProgram->getUniformLocation("lightSpaceMVPMatrix"), 1, GL_FALSE, lightMVPMatrix);
    glUniformMatrix4fv(pSecondPassProgram->getUniformLocation("modelMatrix"), 1, GL_FALSE, modelMatrix);

    // Floor Material Properties
    //   glUniform3fv(pSecondPassProgram->getUniformLocation("matAmbient"), 1, lightSourceA.ambient);
    glUniform3fv(pSecondPassProgram->getUniformLocation("matSpecular"), 1, lightSourceA.specular);
    glUniform1f(pSecondPassProgram->getUniformLocation("matShininess"), 120.0f);

    // floor Texture
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, boxTexture);
    glUniform1i(pSecondPassProgram->getUniformLocation("diffuseTexture"), 1);
    pSphere->draw();

    // Draw Light Source
    simpleProgram->useProgram();
    modelMatrix = vmath::translate(lightX, lightY, lightZ) * vmath::scale(0.2f, 0.2f, 0.2f);
    cameraMVPMatrix = perspectiveProjectionMatrix * cameraViewMatrix * modelMatrix;

    glUniformMatrix4fv(simpleProgram->getUniformLocation("mvpMatrix"), 1, GL_FALSE, cameraMVPMatrix);
    pSphere->draw();

    glUseProgram(0);

    SwapBuffers(ghdc);
}

void update(void)
{
}

void uninitialise(void)
{

    FreeConsole();

    if (wglGetCurrentContext() == ghrc)
    {
        wglMakeCurrent(NULL, NULL);
    }
    if (ghrc)
    {
        wglDeleteContext(ghrc);
        ghrc = NULL;
    }

    if (ghdc)
    {
        ReleaseDC(ghwnd, ghdc);
        ghdc = NULL;
    }
    if (ghwnd)
    {
        DestroyWindow(ghwnd);
        ghwnd = NULL;
    }

    if (gpFILE)
    {
        fprintf(gpFILE, "Programme Ended SuucessFully\n");
        fclose(gpFILE);
        gpFILE = NULL;
    }
}

void drawCube()
{
    glBindVertexArray(vaoCube);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glDrawArrays(GL_TRIANGLE_FAN, 4, 4);
    glDrawArrays(GL_TRIANGLE_FAN, 8, 4);
    glDrawArrays(GL_TRIANGLE_FAN, 12, 4);
    glDrawArrays(GL_TRIANGLE_FAN, 16, 4);
    glDrawArrays(GL_TRIANGLE_FAN, 20, 4);
}

void drawSquare()
{
    glBindVertexArray(vaoSquare);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}
