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
XVisualInfo xvisualInfo; 
   
Bool bFullScreen = False;

int main()
{
    //local fun decl
    void uninitialize(void);
    void toggleFullScreen(void);
    //local variable decl
    int defaultScreen;
    int defaultDepth;
    Status status;
    XSetWindowAttributes windowAttributes; //like wndClass in windows OS
    int styleMask;
    Atom windowManagerDelete;
    XEvent event;
    KeySym keySym;

    char keys[26];
    int screenWidht,screenHeight;

//code -------
    
    //1. Open connection with xserver and get interface
    display = XOpenDisplay(NULL);
    if(display==NULL)
    {
        printf("XOpenDisplay() Failed/n");
        uninitialize();
        exit(1);
    }

    //2. Get default screen from above display
    defaultScreen = XDefaultScreen(display);
    

    //3. Get default depth from above two
    defaultDepth = XDefaultDepth(display,defaultScreen);


    //4. Get visual info from above 3
    memset((void*)&xvisualInfo,0,sizeof(XVisualInfo));
    status = XMatchVisualInfo(display,defaultScreen,defaultDepth,TrueColor,&xvisualInfo);
    if(status == 0)
    {
        printf("XMatchVisualInfo() failed\n");
        uninitialize();
        exit(1);
    }

    //5. Set window attribute/properties
    memset((void*)&windowAttributes,0,sizeof(XSetWindowAttributes));
    
    windowAttributes.border_pixel = 0;
    windowAttributes.background_pixel = XBlackPixel(display,xvisualInfo.screen);
    windowAttributes.background_pixmap = 0;//for image or brush
    windowAttributes.colormap = XCreateColormap(display,
                                                XRootWindow(display,xvisualInfo.screen),
                                                xvisualInfo.visual,
                                                AllocNone);

    //6. Assign this color map to global Colormap
    colormap = windowAttributes.colormap;

    //7. Set style of window    //windows WS_overlapped window here is styleMask
    styleMask = CWBorderPixel | CWBackPixel | CWColormap | CWEventMask;

    //8. Create window
    window = XCreateWindow(display,
                           XRootWindow(display,xvisualInfo.screen),
                           0,
                           0,
                           WIN_WIDTH,
                           WIN_HEIGHT,
                           0,
                           xvisualInfo.depth,
                           InputOutput,
                           xvisualInfo.visual,
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
                                PointerMotionMask); //wm mouse move

    //10. Specify window manager delete ATOM
    windowManagerDelete = XInternAtom(display,"WM_DELETE_WINDOW",True);

    //11. Add/set above atom as protocol to window manager
    XSetWMProtocols(display,window,&windowManagerDelete,1);

    //12. Give caption to window
    XStoreName(display,window,"HVS-XWindow");//create window name

    //13. Show/Map window
    XMapWindow(display,window);

    screenWidht = XWidthOfScreen(XScreenOfDisplay(display,xvisualInfo.screen));
    screenHeight = XHeightOfScreen(XScreenOfDisplay(display,xvisualInfo.screen));
    XMoveWindow(display,window,(screenWidht-WIN_WIDTH)/2,(screenHeight-WIN_HEIGHT)/2);


    //14. Event loop
    while (1)
    {
        XNextEvent(display,&event);
        switch (event.type)
        {
        case KeyPress:
            keySym = XkbKeycodeToKeysym(display,event.xkey.keycode,0,0);
            switch (keySym)
            {
            case XK_Escape:
                uninitialize();
                exit(0);
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
            uninitialize();
            exit(0);
            break; 

        default:
            break;
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
               XRootWindow(display,xvisualInfo.screen),
               False, //not for all child window
               SubstructureNotifyMask,
               &event);


}

void uninitialize()
{
    //code
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

