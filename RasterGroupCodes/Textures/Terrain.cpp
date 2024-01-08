// Header Files
#include<windows.h>
#include<stdio.h>
#include<stdlib.h>
#define _USE_MATH_DEFINES
#include<math.h>

// OpenGL Header Files
#include<gl/GL.h>
#include<GL/GLU.h>
#include"glext.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define WIN_WIDTH 640
#define WIN_HEIGHT 360
#define MAP_X	32
#define MAP_Z	32
#define MAP_SCALE	20.0f

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

// Textures
GLuint texture_land;
GLuint texture_water;

// Mouse/Camera Variables
GLfloat eyeX,eyeY,eyeZ,lookX,lookY,lookZ;
GLfloat mouseX,mouseY;
GLfloat angle = 0.0f;
GLfloat radians = 0.0f;

// Terrain Data
GLfloat terrain[MAP_X][MAP_Z][3];
GLfloat waterHeight = 154.0f;
BOOL bPolygon = TRUE;
BOOL waterDir = TRUE;

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
                            TEXT("Terrain"),
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

			if (mouseY < 200)
				mouseY = 200;

			if (mouseY > 450)
				mouseY = 450;

			if ((mouseX - oldMouseX) > 0)		// mouse moved to the right
				angle += 3.0f;
			else if ((mouseX - oldMouseX) < 0)	// mouse moved to the left
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

            //ShowCursor(FALSE);
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

    //clear screen using blue color:
    glClearColor(0.1f,0.1f,0.1f,1.0f);

    // Depth Related Changes
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);

    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    glEnable(GL_TEXTURE_2D);
    texture_land = createTexture2D("land.bmp");
    texture_water = createTexture2D("water.bmp");

    // Create Terrain

    // Load Heightmap data
    int width, height, channel;
    unsigned char* data = stbi_load("Terrain2.bmp",&width, &height, &channel, 0);
    if(!data)
    {
        fprintf(gpFile,"Failed To Load %s Texture\n","Terrain2");
        return -1;
    }

    fprintf(gpFile,"%d %d %d\n",width, height, channel);

    //Fill Terrrain Array with height information
    for(int z = 0; z < MAP_Z; z++)
    {
        for(int x = 0; x < MAP_X; x++)
        {
            terrain[x][z][0] = GLfloat(x)*MAP_SCALE;
            terrain[x][z][1] = (GLfloat)data[(z*MAP_Z+x)*3];
            terrain[x][z][2] = -GLfloat(z)*MAP_SCALE;
        }
    }
    stbi_image_free(data);

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
    gluPerspective(54.0f,(GLfloat)width/(GLfloat)height,1.0f,1000.0f);

    glMatrixMode(GL_MODELVIEW);
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
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glBindTexture(GL_TEXTURE_2D,0);

    stbi_image_free(data);
    return texture;
}


void display(void)
{

    // camera calculation

    radians = GLfloat(M_PI * (angle - 90.0f) / 180.0f);

    eyeX = lookX + sin(radians) * mouseY;
    eyeZ = lookZ + cos(radians) * mouseY;
    eyeY = lookY + mouseY / 2.0f;

    lookX = (MAP_X*MAP_SCALE)/2.0f;
    lookY = 150.0f;
    lookZ = -(MAP_Z*MAP_SCALE)/2.0f;

    // Code
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    //gluLookAt(eyeX,eyeY,eyeZ,lookX,lookY,lookZ,0.0f,1.0f,0.0f);
    glTranslatef(0.0f,0.0f,250.0f);

    glBindTexture(GL_TEXTURE_2D,texture_land);
    for(int z = 0; z < MAP_Z-1; z++)
    {
        glBegin(GL_TRIANGLE_STRIP);
        for(int x = 0; x < MAP_X-1; x++)
        {
            // Vertex 0
            glTexCoord2f(0.0f, 0.0f);
			glColor3f(terrain[x][z][1]/255.0f, terrain[x][z][1]/255.0f, terrain[x][z][1]/255.0f);
			glVertex3f(terrain[x][z][0], terrain[x][z][1], terrain[x][z][2]);

            // Vertex 1
            glTexCoord2f(1.0f, 0.0f);
			glColor3f(terrain[x+1][z][1]/255.0f, terrain[x+1][z][1]/255.0f, terrain[x+1][z][1]/255.0f);
			glVertex3f(terrain[x+1][z][0], terrain[x+1][z][1], terrain[x+1][z][2]);

            // Vertex 2
            glTexCoord2f(0.0f, 1.0f);
			glColor3f(terrain[x][z+1][1]/255.0f, terrain[x][z+1][1]/255.0f, terrain[x][z+1][1]/255.0f);
			glVertex3f(terrain[x][z+1][0], terrain[x][z+1][1], terrain[x][z+1][2]);

            // Vertex 3
            glTexCoord2f(1.0f, 1.0f);
			glColor3f(terrain[x+1][z+1][1]/255.0f, terrain[x+1][z+1][1]/255.0f, terrain[x+1][z+1][1]/255.0f);
			glVertex3f(terrain[x+1][z+1][0], terrain[x+1][z+1][1], terrain[x+1][z+1][2]);
        }
        glEnd();
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glDepthMask(GL_FALSE);

    glColor4f(0.5f,0.5f,1.0f,0.7f);
    glBindTexture(GL_TEXTURE_2D, texture_water);

    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);
		glVertex3f(terrain[0][0][0], waterHeight, terrain[0][0][2]);

		glTexCoord2f(10.0f, 0.0f);
		glVertex3f(terrain[MAP_X-1][0][0], waterHeight, terrain[MAP_X-1][0][2]);

		glTexCoord2f(10.0f, 10.0f);
		glVertex3f(terrain[MAP_X-1][MAP_Z-1][0], waterHeight, terrain[MAP_X-1][MAP_Z-1][2]);

		glTexCoord2f(0.0f, 10.0f);
		glVertex3f(terrain[0][MAP_Z-1][0],waterHeight, terrain[0][MAP_Z-1][2]);
    glEnd();
	glDepthMask(GL_FALSE);
    glEnable(GL_BLEND);
    SwapBuffers(ghdc);
}

void update(void)
{
    // if(angle >= 360.0f)
    //     angle -= 360.0f;
    // angle += 0.5f;
    if(waterHeight > 155.0f)
        waterDir = FALSE;
    else if(waterHeight < 154.0f)
        waterDir = TRUE;
    
    if(waterDir)
        waterHeight += 0.01f;
    else
        waterHeight -= 0.01f;
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

    glDeleteTextures(1,&texture_land);
    glDeleteTextures(1,&texture_water);

    if(gpFile)
    {
        fprintf(gpFile,"Closing Log File.\n");
        fclose(gpFile);
        gpFile = NULL;
    }
}
