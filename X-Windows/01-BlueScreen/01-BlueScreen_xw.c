#include<gl/glew.h>
#include<GL/glx.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


//X11 headers files
#include<X11/Xlib.h>  //for all x-windows api's
#include<X11/Xutil.h>  //for xvisual info and related api's
#include<X11/XKBlib.h>

//macros
#define WIN_WIDTH 800
#define WIN_HEIGHT 600

//global variable
Display *display = NULL;
Colormap colormap;
Window window; 
XVisualInfo *xvisualInfo; 

typedef glxContext(*glXCreateContextAttribsARBProc)(display*, GLXFBConfig, glxContext, Bool, cosnt int*);
glXCreateContextAttribsARBProc glXCreateContextAttribsARB = null;

GLXFBConfig glxfbConfig;

//opengl global variables
GLXContext glxContext = NULL; 

Bool bActiveWindow = False;
Bool bFullScreen = False;

int main()
{
    //local fun decl
    void initialize();
    void resize(int, int);
    void update();
    void draw();    
    void uninitialize(void);
    void toggleFullScreen(void);

    //local variable decl
    int defaultScreen;
    XSetWindowAttributes windowAttributes; //like wndClass in windows OS
    int styleMask;
    Atom windowManagerDelete;
    XEvent event;
    KeySym keySym;
    int frameBufferAttributes[]={GLX_DOUBLEBUFFER,True,
                                GLX_RGBA,
                                GLX_RED_SIZE, 8,
                                GLX_GREEN_SIZE, 8,
                                GLX_BLUE_SIZE, 8,
                                GLX_ALPHA_SIZE, 8, None};
    Bool bDone = False;

    char keys[26];
    int screenWidht,screenHeight;

    //for hello world
    static XFontStruct *pFontStruct=NULL;
    static int winWidth,winHeight;
    static GC gc;
    XColor greenColor;
    XGCValues gcValue;
    int stringLength;
    int stringWidht;
    int fontHeight;
    char str[]="Hello World !!!";
//code -------
    
    //1. Open connection with xserver and get interface
    display = XOpenDisplay(NULL);
    if(display==NULL)
    {
        printf("XOpenDisplay() Failed/n");
        uninitialize();
        exit(1);
    }

    //2. get default screen from above display
    defaultScreen = XDefaultScreen(display);

    //4. bridgeing api 
    xvisualInfo = glXChooseVisual(display, defaultScreen, frameBufferAttributes);
    
    if(xvisualInfo == NULL)
    {
        printf("glXChoseVisual() failed\n");
        uninitialize();
        exit(1);
    }



    //5. Set window attribute/properties
    memset((void*)&windowAttributes,0,sizeof(XSetWindowAttributes));
    
    windowAttributes.border_pixel = 0;
    windowAttributes.background_pixel = XBlackPixel(display,xvisualInfo->screen);
    windowAttributes.background_pixmap = 0;//for image or brush
    windowAttributes.colormap = XCreateColormap(display,
                                                XRootWindow(display,xvisualInfo->screen),
                                                xvisualInfo->visual,
                                                AllocNone);

    //6. Assign this color map to global Colormap
    colormap = windowAttributes.colormap;

    //7. Set style of window    //windows WS_overlapped window here is styleMask
    styleMask = CWBorderPixel | CWBackPixel | CWColormap | CWEventMask;

    //8. Create window
    window = XCreateWindow(display,
                           XRootWindow(display,xvisualInfo->screen),
                           0,
                           0,
                           WIN_WIDTH,
                           WIN_HEIGHT,
                           0,
                           xvisualInfo->depth,
                           InputOutput,
                           xvisualInfo->visual,
                           styleMask,
                           &windowAttributes);

    if(!window)
    {
        printf("XCreateWindow() Failed\n");
        uninitialize();
        exit(1);
    }

    //9. Specify to which event this window should respond
    XSelectInput(display,window,ExposureMask | //wm_paint
                                VisibilityChangeMask | //minimize maximise
                                StructureNotifyMask | //wm_size
                                KeyPressMask | //WM_Keydown or wm_char
                                ButtonPressMask | // wm_l-r button down
                                PointerMotionMask |
                                FocusChangeMask); //wm mouse move

    //10. Specify window manager delete ATOM
    windowManagerDelete = XInternAtom(display,"WM_DELETE_WINDOW",True);

    //11. Add/set above atom as protocol to window manager
    XSetWMProtocols(display,window,&windowManagerDelete,1);

    //12. Give caption to window
    XStoreName(display,window,"HVS-XWindow");//create window name

    //13. Show/Map window
    XMapWindow(display,window);

    screenWidht = XWidthOfScreen(XScreenOfDisplay(display,xvisualInfo->screen));
    screenHeight = XHeightOfScreen(XScreenOfDisplay(display,xvisualInfo->screen));
    XMoveWindow(display,window,(screenWidht-WIN_WIDTH)/2,(screenHeight-WIN_HEIGHT)/2);


    //Opengl init
    initialize();

    //14. Event loop
    while(bDone == False)
    {
        while (XPending(display)) ///how much messages are pending like peakmesssage
        {
            XNextEvent(display,&event);
            switch (event.type)
            {
            case MapNotify://show window in win32, treaded as WM_Create
                    //printf("MapNotify event is received\n");
                    pFontStruct = XLoadQueryFont(display,"fixed"); 
                    break;

            case FocusIn://set focus in win32
                    printf("FocuseIn event receive\n");
                    bActiveWindow = True;
                    break;

            case FocusOut://kill focus in win32
                    printf("FocusOut event receive\n");
                    bActiveWindow = False;
                    break;

            case ConfigureNotify:
                    //printf("Conf notify event receive\n");
                    winWidth = event.xconfigure.width;
                    winHeight = event.xconfigure.height;
                    resize(event.xconfigure.width, event.xconfigure.height);
                    break;

            case ButtonPress:
                    switch(event.xbutton.button)
                    {
                        case 1:
                            printf("Left Mouse button is clicked\n");
                            break;
                        case 2:
                            printf("Middle mouse button is clicked\n");
                            break;
                        case 3:
                            printf("Right mouse button is clicked\n");
                            break;
                        default:
                            break;
                    }
                    break;
            case KeyPress:
                keySym = XkbKeycodeToKeysym(display,event.xkey.keycode,0,0);
                switch (keySym)
                {
                case XK_Escape:
                    XUnloadFont(display, pFontStruct->fid);
                    XFreeGC(display, gc);
                    bDone = True;
                    break;
                
                default:
                    break;
                }
                XLookupString(&event.xkey,keys,sizeof(keys),NULL,NULL);
                switch(keys[0])
                {
                    case 'F':
                    case 'f':
                            if(bFullScreen == False)
                            {
                                toggleFullScreen();
                                bFullScreen = True;
                            }                
                            else
                            {
                                toggleFullScreen();
                                bFullScreen = False;
                            }
                    
                        break;
                    default:
                        break;
                }

                break;
            case 33:
                XUnloadFont(display, pFontStruct->fid);
                XFreeGC(display, gc);
                bDone = True;
                break; 

            default:
                break;
            }

        }
        //Rendering
        if(bActiveWindow == True)
        {
            draw();

            update();
        }

    }

    
    

    uninitialize();

    return 0;
}

void toggleFullScreen(void)
{
    //local var
    Atom windowManagerStateNormal;
    Atom windowManagerStateFullscreen;
    XEvent event;

    //code
    //1. take normal state's atom
    windowManagerStateNormal = XInternAtom(display,"_NET_WM_STATE",False);

    windowManagerStateFullscreen = XInternAtom(display,"_NET_WM_STATE_FULLSCREEN",False);

    //3. Fill struct of Event, memeset event struct and fill it above 2 atoms, ///msg structure as in win32
    memset((void*)&event,0,sizeof(XEvent));
    event.type = ClientMessage;
    event.xclient.window = window;
    event.xclient.message_type = windowManagerStateNormal;
    event.xclient.format = 32;
    event.xclient.data.l[0] = bFullScreen ? 0 : 1;
    event.xclient.data.l[1] = windowManagerStateFullscreen;

    //4. send event
    XSendEvent(display,
               XRootWindow(display,xvisualInfo->screen),
               False, //not for all child window
               SubstructureNotifyMask,
               &event);
    


}

void initialize()
{
    void uninitialize();
    void resize(int,int);
    //code
    //create opengl context
    glxContext = glXCreateContext(display, xvisualInfo, NULL, True);//true for hw rendering
 
    if(glxContext == NULL)
    {
        printf("glXCreateContext() failed\n");
        uninitialize();
        exit(1);
    }

    //make this context as current context
    if(glXMakeCurrent(display, window, glxContext) == False)
    {
        printf("In initialize glXMakeCurrent context() failed\n");
        uninitialize();
        exit(1);
    }//bool return value

    //usual opengl code
    glClearColor(0.0,0.0,1.0,1.0);

    //warmup resize, optional
    resize(WIN_WIDTH, WIN_HEIGHT);

}

void resize(int width, int height)
{
    //code
    if(height <= 0)
    {
        height = 1;
        
    }
    glViewport(0,0,(GLsizei)width, (GLsizei)height);
    glMatrixMode(GL_PROJECTION);//use GL_Projection from Matrix maths from OpenGL math lib
	glLoadIdentity();
	
}

void draw()
{
    //code
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

   glXSwapBuffers(display, window);

}

void update()
{
    //code
}

void uninitialize()
{
    //local var decl
    GLXContext currentGLXContext = NULL;

    //code
    if(xvisualInfo)
    {
        free(xvisualInfo);
        xvisualInfo = NULL;
    }

    //uncurrent the context
    currentGLXContext = glXGetCurrentContext();
    if(currentGLXContext != NULL || currentGLXContext == glxContext)
    {
        glXMakeCurrent(display, 0, 0);
    }    

    if(glxContext)
    {
        glXDestroyContext(display, glxContext);
        glxContext = NULL;
    }
     
    if(window)
    {
        XDestroyWindow(display,window);        
    }

    if(colormap)
    {
        XFreeColormap(display,colormap);
    }

    if(display)
    {
        XCloseDisplay(display);
        display=NULL;
    }



}

