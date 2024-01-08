// Header Files
#include<windows.h>
#include<stdio.h>
#include<stdlib.h>
#define _USE_MATH_DEFINES
#include<math.h>

// OpenGL Header Files
#include<gl/GL.h>
#include<GL/GLU.h>
#include"glcorearb.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define WIN_WIDTH 640
#define WIN_HEIGHT 360

// OpenGL Libraries
#pragma comment(lib,"OpenGL32.lib")
#pragma comment(lib,"glu32.lib")

// Global Variable
HWND ghwnd = NULL;
HDC ghdc = NULL;
HGLRC ghrc = NULL;
BOOL gbFullScreen = FALSE;
BOOL gbActiveWindow = FALSE;
FILE *gpFile = NULL;
TCHAR str[600];
GLuint texture_smiley;
GLuint texture_check;

GLfloat eyeX,eyeY,eyeZ,lookX,lookY,lookZ;
GLfloat mouseX,mouseY;
GLfloat angle = 0.0f;


PFNGLMULTITEXCOORD2FARBPROC glMultiTexCoord2f = NULL;
PFNGLACTIVETEXTUREPROC   glActiveTexture = NULL;

// Global Function Declarations
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

// Main Function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpszCmdLine,int iCmdShow)
{
    // Function Declaration
    int initialize(void);
    void display(void);
    void update(void);
    void uninitialize(void);
    // Variable Declaration
    WNDCLASSEX wndclass;
    HWND hwnd;
    MSG msg;
    TCHAR szAppName[] = TEXT("MyWindow");
    BOOL bDone = FALSE;
    int iRetVal = 0;

    // Code

    if(fopen_s(&gpFile,"Log.txt","w") != 0)
    {
        MessageBox(NULL,TEXT("Creation Of Log File Failed.\nExitting ..."),TEXT("File I/O Error"),MB_ICONERROR);
        exit(0);
    }
    else
    {
        fprintf(gpFile,"Creating Log File.\n");
    }

    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    int x = (screenWidth -  WIN_WIDTH) / 2;
    int y = (screenHeight - WIN_HEIGHT) / 2;

    // Initialization Of WNDCLASSEX Structure
    wndclass.cbSize         = sizeof(WNDCLASSEX);
    wndclass.style          = CS_HREDRAW|CS_VREDRAW|CS_OWNDC;
    wndclass.cbClsExtra     = 0;
    wndclass.cbWndExtra     = 0;
    wndclass.lpfnWndProc    = WndProc;
    wndclass.hInstance      = hInstance;
    wndclass.hbrBackground  = (HBRUSH)GetStockObject(BLACK_BRUSH); 
    wndclass.hIcon          = NULL;//LoadIcon(hInstance,MAKEINTRESOURCE(BAT_ICON));
    wndclass.hCursor        = LoadCursor(NULL,IDC_ARROW);
    wndclass.lpszClassName  = szAppName;
    wndclass.lpszMenuName   = NULL;
    wndclass.hIconSm        = NULL;//LoadIcon(hInstance,MAKEINTRESOURCE(BAT_ICON));

    // Registering Above WndClass
    RegisterClassEx(&wndclass);

    // Create Window
    hwnd = CreateWindowEx(  
                            WS_EX_APPWINDOW,
                            szAppName,
                            TEXT("MultiTexturing"),
                            WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE,
                            x,
                            y,
                            WIN_WIDTH,
                            WIN_HEIGHT,
                            NULL,
                            NULL,
                            hInstance,
                            NULL
                        );

    ghwnd = hwnd;

    iRetVal = initialize();

    if(iRetVal == -1)
    {
        fprintf(gpFile,"choose pixel format failed");
        uninitialize();
    }

    if(iRetVal == -2)
    {
        fprintf(gpFile,"set pixel format failed");
        uninitialize();        
    }

    if(iRetVal == -3)
    {
        fprintf(gpFile,"Create wgl context failed");
        uninitialize();        
    }

    if(iRetVal == -4)
    {
        fprintf(gpFile,"make current context failed");
        uninitialize();        
    }

    // Show window
    ShowWindow(hwnd,iCmdShow);

    // Foregrounding and Focusing The Window
    // ghwnd or hwnd will work but hwnd is for local functions.
    SetForegroundWindow(hwnd);

    SetFocus(hwnd);

    // Special loop
    while(!bDone)
    {
        if(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
        {
            if(msg.message == WM_QUIT)
                bDone = TRUE;
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            if(gbActiveWindow)
            {
                // Render The Scene
                display();
                // Update the Scene
                update();
            }
        }
    }
    uninitialize();
    return (int)msg.wParam;
}

// Callback Function
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    // Local Function Declaration
    void ToogleFullScreen(void);
    void resize(int,int);
    void uninitialize(void);

    // Local Variable 
    int oldMouseX, oldMouseY;
    //TCHAR str[] = TEXT("This Window Will Always Be At Center Of The Screen");
    // Code
    switch(iMsg)
    {
        case WM_CREATE:
            //fprintf(gpFile,"In WM_CREATE Message.\n");
            //sprintf(str,"!!! Press F To Enter FullScreen !!!");
        break;

        case WM_CHAR:
            switch(wParam)
            {
                case 'F':
                    case 'f':
                        fprintf(gpFile,"In ToogleFullscreen.\n");
                        ToogleFullScreen();
                break;
                default:
                break;
            }
        break;
        case WM_MOUSEMOVE:

            oldMouseX = mouseX;
            oldMouseY = mouseY;

            mouseX = LOWORD(lParam);
            mouseY = HIWORD(lParam);

            if(mouseY < 10)
                mouseY = 10;
            if(mouseY > 150)
                mouseY = 150;

            if((mouseX - oldMouseX) > 0)
                angle += 3.0f;
            else if((mouseX - oldMouseX) < 0)
                angle -= 3.0f;
                return 0;
        break;
        case WM_SETFOCUS:
            fprintf(gpFile,"Set Focus True.\n");
            gbActiveWindow = TRUE;
        break;

        case WM_KILLFOCUS:
            fprintf(gpFile,"Set Focus False.\n");
            //gbActiveWindow = FALSE;
        break;

        case WM_ERASEBKGND:
            return 0;
        break;

        case WM_KEYDOWN:
            if(wParam == VK_ESCAPE)
            {
                fprintf(gpFile,"Sending WM_CLOSE.\n");
                DestroyWindow(hwnd);
            }
        break;
        case WM_SIZE:
            //fprintf(gpFile,"In WM SIZE message.\n");
            resize(LOWORD(lParam),HIWORD(lParam));
        break; 

        case WM_CLOSE:
            fprintf(gpFile,"In WM CLOSE message.\n");
            DestroyWindow(hwnd);
        break;

        case WM_DESTROY:
            //uninitialize();
            PostQuitMessage(0);
        break;

        default:
            break;
    }
    return DefWindowProc(hwnd,iMsg,wParam,lParam);
}

void ToogleFullScreen(void)
{
    // Varriable Declarations
    static DWORD dwStyle;
    static WINDOWPLACEMENT wp;
    MONITORINFO mi;

    // Code
    wp.length = sizeof(WINDOWPLACEMENT);
    if(gbFullScreen == FALSE)
    {
        dwStyle = GetWindowLong(ghwnd,GWL_STYLE);
        if(dwStyle & WS_OVERLAPPEDWINDOW)
        {
            mi.cbSize = sizeof(MONITORINFO);
            if(GetWindowPlacement(ghwnd,&wp) && GetMonitorInfo(MonitorFromWindow(ghwnd,MONITORINFOF_PRIMARY),&mi))
            {
                SetWindowLong(ghwnd,GWL_STYLE,(dwStyle & (~WS_OVERLAPPEDWINDOW)));
                SetWindowPos(   ghwnd,HWND_TOPMOST,mi.rcMonitor.left,mi.rcMonitor.top,
                                mi.rcMonitor.right - mi.rcMonitor.left,
                                mi.rcMonitor.bottom - mi.rcMonitor.top,
                                SWP_NOZORDER|SWP_FRAMECHANGED);
            }

            ShowCursor(FALSE);
            gbFullScreen = TRUE;
        }
    }
    else
    {
        SetWindowLong(ghwnd,GWL_STYLE,dwStyle|WS_OVERLAPPEDWINDOW);
        SetWindowPlacement(ghwnd,&wp);
        SetWindowPos(ghwnd,HWND_TOP,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE|SWP_NOOWNERZORDER|SWP_NOZORDER|SWP_FRAMECHANGED);
        ShowCursor(TRUE);
        gbFullScreen = FALSE;
    }
}

int initialize(void)
{
    // Function Declarations
    void resize(int,int);
    BOOL LoadGLTexture(GLuint*,TCHAR[]);
    GLuint createTexture2D(const char* filePath);
    // Variable Declarations
    PIXELFORMATDESCRIPTOR pfd;
    int iPixelFormatIndex = 0;

    // Code

    ZeroMemory(&pfd,sizeof(PIXELFORMATDESCRIPTOR));

    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.cRedBits = 8;
    pfd.cGreenBits = 8;
    pfd.cBlueBits = 8;
    pfd.cAlphaBits = 8;
    pfd.cDepthBits = 32; // 24 is also allowed

    // Get DC
    ghdc = GetDC(ghwnd);

    // Choose Pixel Format
    iPixelFormatIndex = ChoosePixelFormat(ghdc,&pfd);

    if(iPixelFormatIndex == 0)
        return -1;

    // Set The Choosen Pixel Format
    if(SetPixelFormat(ghdc,iPixelFormatIndex,&pfd) == FALSE)
        return -2;

    // Create OpenGL Rendering Index

    ghrc = wglCreateContext(ghdc);

    if(ghrc == NULL)
        return -3;

    // Make Rendering as current context and rendering context
    if(wglMakeCurrent(ghdc,ghrc) == FALSE)
        return -4;

    // Here Starts OpenGL Code :

    // Load OpenGL EXT Functions

    glActiveTexture = (PFNGLACTIVETEXTUREPROC)wglGetProcAddress("glActiveTextureARB");
    glMultiTexCoord2f = (PFNGLMULTITEXCOORD2FARBPROC)wglGetProcAddress("glMultiTexCoord2fARB");

    //clear screen using blue color:
    glClearColor(0.1f,0.1f,0.1f,1.0f);

    // Depth Related Changes
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_TEXTURE_2D);
    texture_smiley = createTexture2D("Smiley.bmp");
    texture_check = createTexture2D("chess.bmp");

    //warmup resize call
    resize(WIN_WIDTH,WIN_HEIGHT);
    return 0;
}

void resize(int width,int height)
{
    // Code
    // to avoid divide by 0 error later in codebase.
    if(height == 0)
        height = 1;
    
    glViewport(0,0,(GLsizei)width,(GLsizei)height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);
}

BOOL LoadGLTexture(GLuint* texture,TCHAR img_src[])
{
    HBITMAP hBitmap = NULL;
    BITMAP bmp;
    BOOL bResult = FALSE;
    hBitmap = (HBITMAP)LoadImage(GetModuleHandle(NULL),img_src,IMAGE_BITMAP,0,0,LR_CREATEDIBSECTION);

    if(hBitmap)
    {
        bResult = TRUE;
        GetObject(hBitmap,sizeof(BITMAP),&bmp);
        glPixelStorei(GL_UNPACK_ALIGNMENT,4);
        glGenTextures(1,texture);
        glBindTexture(GL_TEXTURE_2D,*texture);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);

        //Create Texture
        gluBuild2DMipmaps(GL_TEXTURE_2D,3,bmp.bmWidth,bmp.bmHeight,GL_BGR_EXT,GL_UNSIGNED_BYTE,bmp.bmBits);
        glBindTexture(GL_TEXTURE_2D,0);
        DeleteObject(hBitmap);        
    }
    return bResult;
}

GLuint createTexture2D(const char* filePath)
{
    stbi_set_flip_vertically_on_load(true);
    int width, height, channel;
    unsigned char* data = stbi_load(filePath,&width, &height, &channel, 0);

    if(!data)
    {
        fprintf(gpFile,"Failed To Load %s Texture\n",filePath);
        return -1;
    }

    GLenum format = GL_RGBA;

    if(channel == STBI_grey)
        format = GL_RED;
    else if(channel == STBI_rgb)
        format = GL_RGB;
    else if(channel == STBI_rgb_alpha)
        format = GL_RGBA;

    GLuint texture;
    glPixelStorei(GL_UNPACK_ALIGNMENT,4);
    glGenTextures(1,&texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glBindTexture(GL_TEXTURE_2D,0);

    stbi_image_free(data);
    return texture;
}


void display(void)
{

    // camera calculation

    GLfloat radians = M_PI * (angle - 90.0f) / 180.0f;

    eyeX = lookX + sin(radians) * mouseY;
    eyeZ = lookZ + cos(radians) * mouseY;
    eyeY = lookY + mouseY / 2.0f;

    lookX = 0.0f;
    lookY = 0.0f;
    lookZ = 0.0f;

    // Code
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(eyeX,eyeY,eyeZ,lookX,lookY,lookZ,0.0f,1.0f,0.0f);
//    glTranslatef(0.0f,0.0f,-5.0f);

    glPushMatrix();
    glRotatef(angle,1.0f,1.0f,1.0f);
    glScalef(15.0f, 15.0f, 15.0f);
    glActiveTexture(GL_TEXTURE0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,texture_smiley);
    glActiveTexture(GL_TEXTURE1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,texture_check);
    glBegin(GL_QUADS);
        // Front Face
		glMultiTexCoord2f(GL_TEXTURE0, 1.0f, 0.0f);
		glMultiTexCoord2f(GL_TEXTURE1, 1.0f, 0.0f);
        glVertex3f(0.5f,0.5f,0.5f);
		glMultiTexCoord2f(GL_TEXTURE0, 1.0f, 1.0f);
		glMultiTexCoord2f(GL_TEXTURE1, 1.0f, 1.0f);
        glVertex3f(-0.5f,0.5f,0.5f);
		glMultiTexCoord2f(GL_TEXTURE0, 0.0f, 1.0f);
		glMultiTexCoord2f(GL_TEXTURE1, 0.0f, 1.0f);
        glVertex3f(-0.5f,-0.5f,0.5f);
		glMultiTexCoord2f(GL_TEXTURE0, 0.0f, 0.0f);
		glMultiTexCoord2f(GL_TEXTURE1, 0.0f, 0.0f);
        glVertex3f(0.5f,-0.5f,0.5f);  

        // Right Face
		glMultiTexCoord2f(GL_TEXTURE0, 1.0f, 0.0f);
		glMultiTexCoord2f(GL_TEXTURE1, 1.0f, 0.0f);
        glVertex3f(0.5f,0.5f,-0.5f);
		glMultiTexCoord2f(GL_TEXTURE0, 1.0f, 1.0f);
		glMultiTexCoord2f(GL_TEXTURE1, 1.0f, 1.0f);
        glVertex3f(0.5f,0.5f,0.5f);
		glMultiTexCoord2f(GL_TEXTURE0, 0.0f, 1.0f);
		glMultiTexCoord2f(GL_TEXTURE1, 0.0f, 1.0f);
        glVertex3f(0.5f,-0.5f,0.5f);
		glMultiTexCoord2f(GL_TEXTURE0, 0.0f, 0.0f);
		glMultiTexCoord2f(GL_TEXTURE1, 0.0f, 0.0f);
        glVertex3f(0.5f,-0.5f,-0.5f);

        // Back Face
		glMultiTexCoord2f(GL_TEXTURE0, 1.0f, 0.0f);
		glMultiTexCoord2f(GL_TEXTURE1, 1.0f, 0.0f);
        glVertex3f(-0.5f,0.5f,-0.5f);
		glMultiTexCoord2f(GL_TEXTURE0, 1.0f, 1.0f);
		glMultiTexCoord2f(GL_TEXTURE1, 1.0f, 1.0f);
        glVertex3f(0.5f,0.5f,-0.5f);
		glMultiTexCoord2f(GL_TEXTURE0, 0.0f, 1.0f);
		glMultiTexCoord2f(GL_TEXTURE1, 0.0f, 1.0f);
        glVertex3f(0.5f,-0.5f,-0.5f);
		glMultiTexCoord2f(GL_TEXTURE0, 0.0f, 0.0f);
		glMultiTexCoord2f(GL_TEXTURE1, 0.0f, 0.0f);
        glVertex3f(-0.5f,-0.5f,-0.5f);

        // Left Face
		glMultiTexCoord2f(GL_TEXTURE0, 1.0f, 0.0f);
		glMultiTexCoord2f(GL_TEXTURE1, 1.0f, 0.0f);
        glVertex3f(-0.5f,0.5f,0.5f);
		glMultiTexCoord2f(GL_TEXTURE0, 1.0f, 1.0f);
		glMultiTexCoord2f(GL_TEXTURE1, 1.0f, 1.0f);
        glVertex3f(-0.5f,0.5f,-0.5f);
		glMultiTexCoord2f(GL_TEXTURE0, 0.0f, 1.0f);
		glMultiTexCoord2f(GL_TEXTURE1, 0.0f, 1.0f);
        glVertex3f(-0.5f,-0.5f,-0.5f);
		glMultiTexCoord2f(GL_TEXTURE0, 0.0f, 0.0f);
		glMultiTexCoord2f(GL_TEXTURE1, 0.0f, 0.0f);
        glVertex3f(-0.5f,-0.5f,0.5f);

        // Top Face
		glMultiTexCoord2f(GL_TEXTURE0, 1.0f, 0.0f);
		glMultiTexCoord2f(GL_TEXTURE1, 1.0f, 0.0f);
        glVertex3f(0.5f,0.5f,-0.5f);
		glMultiTexCoord2f(GL_TEXTURE0, 1.0f, 1.0f);
		glMultiTexCoord2f(GL_TEXTURE1, 1.0f, 1.0f);
        glVertex3f(-0.5f,0.5f,-0.5f);
		glMultiTexCoord2f(GL_TEXTURE0, 0.0f, 1.0f);
		glMultiTexCoord2f(GL_TEXTURE1, 0.0f, 1.0f);       
        glVertex3f(-0.5f,0.5f,0.5f);
		glMultiTexCoord2f(GL_TEXTURE0, 0.0f, 0.0f);
		glMultiTexCoord2f(GL_TEXTURE1, 0.0f, 0.0f);
        glVertex3f(0.5f,0.5f,0.5f);

        // Bottom Face
		glMultiTexCoord2f(GL_TEXTURE0, 1.0f, 0.0f);
		glMultiTexCoord2f(GL_TEXTURE1, 1.0f, 0.0f);
        glVertex3f(0.5f,-0.5f,-0.5f);
		glMultiTexCoord2f(GL_TEXTURE0, 1.0f, 1.0f);
		glMultiTexCoord2f(GL_TEXTURE1, 1.0f, 1.0f);
        glVertex3f(-0.5f,-0.5f,-0.5f);
		glMultiTexCoord2f(GL_TEXTURE0, 0.0f, 1.0f);
		glMultiTexCoord2f(GL_TEXTURE1, 0.0f, 1.0f); 
        glVertex3f(-0.5f,-0.5f,0.5f);
		glMultiTexCoord2f(GL_TEXTURE0, 0.0f, 0.0f);
		glMultiTexCoord2f(GL_TEXTURE1, 0.0f, 0.0f);
        glVertex3f(0.5f,-0.5f,0.5f);
    glEnd();
    glPopMatrix();
    SwapBuffers(ghdc);
}

void update(void)
{
    // if(angle >= 360.0f)
    //     angle -= 360.0f;
    // angle += 0.5f;
}

void uninitialize(void)
{
    // Function Declarations

    void ToogleFullScreen(void);

    // Code

    if(gbFullScreen)
    {
        ToogleFullScreen();
    }

    if(wglGetCurrentContext() == ghrc)
    {
        wglMakeCurrent(NULL,NULL);
    }

    if(ghrc)
    {
        wglDeleteContext(ghrc);
        ghrc = NULL;
    }

    if(ghdc)
    {
        ReleaseDC(ghwnd,ghdc);
    }

    if(ghwnd)
    {
        DestroyWindow(ghwnd);
    }

    glDeleteTextures(1,&texture_smiley);
    glDeleteTextures(1,&texture_check);

    if(gpFile)
    {
        fprintf(gpFile,"Closing Log File.\n");
        fclose(gpFile);
        gpFile = NULL;
    }
}
