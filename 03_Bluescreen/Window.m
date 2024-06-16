//
//  Window.m
//  
//
//  Created by Rohan Satyamurthy
//
//  Program : Bluescreen
//

#import <Foundation/Foundation.h>       //This is like stdio.h very import
#import <Cocoa/Cocoa.h>                 //This is like widows.h or Xlib.h
#import <QuartzCore/CVDisplayLink.h>    //CV core video
#import <OpenGL/gl3.h>                  //gl.h

//callback function prototype
CVReturn MyDisplayLinkCallback(CVDisplayLinkRef ,const CVTimeStamp *,const CVTimeStamp *,CVOptionFlags , CVOptionFlags *,void *);

FILE *gpFile = NULL;                    //file handling

//NS NeXTSTEP
//declaration of class - In Objective C class are called as interface

/*
 AppDelegate inherits NSObject
 <NSApplicationDelegate-my method will be implemented by AppDelegate and NSApplicationDelegate works will be taken by AppDelegate, NSWindowDelegate - same with NSWindowDelegate>
    below syntax is forward declaration
 */
@interface AppDelegate:NSObject <NSApplicationDelegate, NSWindowDelegate>
@end


int main(int argc,char *argv[])
{
    //code
    //NSAutoreleasePool is like we are registering our objects here for memory and reclaim when the programs ends
    NSAutoreleasePool * pool = [[NSAutoreleasePool alloc]init];
    
    /*
        NSApp is global application object like document in WebGL in javascript
        NSApp here we are calling NSApplication's sharedApplication method which ,return NSApp like Hinstance in windows
    */
    NSApp = [NSApplication sharedApplication];
    
    /*
        setDelegate is method and after : is parameter but here we are creating object of AppDelegate
        NSApp will delegate AppDelegate will have all method of NSApp , so we can use AppDelegate for all methods of NSApp.
        NSApp Delegate set mean calling applicationDidFinishLaunching
        applicationDidFinishLaunching start your program , When NSApp terminated NSApp's applicationWillTerminate ~ WM_DESTROY
     */
    [NSApp setDelegate:[[AppDelegate alloc]init]]; //applicationDidFinishLaunching is like WM_CREATE
    
    [NSApp run];    /*this is called as run loop , message loop or event loop.*/
    [pool release]; /* all object gets reclamied here */
    //when application get terminated
    return(0);
}

//forward declaration of view
//@interface class name : superclass
@interface MyOpenGLView:NSOpenGLView
@end

/*@implementation class
    methods
 @end
*/

@implementation AppDelegate
{
    //class variables are common to all variables in class is like global variables in class
    @private
    NSWindow * window;
    MyOpenGLView * myOpenGLview;
}

/*  instance / object methods start with - , class method start with +
 
    -(void)method_name:(data type)variable name
    {
    }
 */
-(void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    
    //code
    
    NSBundle *appBundle = [NSBundle mainBundle];    //NSBundle class calls static method bundle
    
    //appBundle is object , bundlePath is a instance method and in appDirPath will return path
    //path:  root/User/rohan satyamurthy/Desktop/RTR2020/02_LogFile/Window.app
    NSString *appDirPath = [appBundle bundlePath];
    
    //this will delete the last path
    //path:  root/User/rohan satyamurthy/Desktop/RTR2020/02_LogFile
    NSString *parentDirPath = [appDirPath stringByDeletingLastPathComponent];
    
    // %@ will give parent dir path
    NSString *logFileNameWithPath = [NSString stringWithFormat:@"%@/Log.txt",parentDirPath];
    
    //NSASCIIStringEncoding - this is in Foundation.h
    const char * pzLogFileNameWithPath = [logFileNameWithPath cStringUsingEncoding:NSASCIIStringEncoding];
    
    gpFile = fopen(pzLogFileNameWithPath,"w");
    if(gpFile == NULL)
    {
        [self release];
        [NSApp terminate:self];
    }
    
    fprintf(gpFile,"Program started successfully\n");
    
    
    /*NSRect is internally is CG - core graphics.{x , y} are both NSPoint which is internally CG point
                                                 {w , h} = NSSize ~ CGSize struct
     styleMask ~ WS_OVERLAPPEDWINDOW
     
     */
    //                             x  y   w     h
    NSRect win_rect = NSMakeRect(0.0,0.0,800.0,600.0);      //as this is C library so it is C Style not Objective C
    window = [[NSWindow alloc]initWithContentRect:win_rect
                                        styleMask:NSWindowStyleMaskTitled |
                                                  NSWindowStyleMaskClosable |
                                                  NSWindowStyleMaskMiniaturizable |
                                                  NSWindowStyleMaskResizable
                                          backing:NSBackingStoreBuffered
                                            defer:NO];
    //setting window title
    [window setTitle:@"RS : OpenGL window"];
    [window center];        //bringing window to center
    
    myOpenGLview = [[MyOpenGLView alloc]initWithFrame:win_rect];  //initWithFrame is NSView method which we have implemented below
    
    [window setContentView:myOpenGLview];   //window set your content view from view
    [window setDelegate:self];      // self is like "this" when you close using x your window will close but it it wont go from dock
    [window makeKeyAndOrderFront:self];     //set  foreground window [SetFocus]
  
}

-(void)applicationWillTerminate:(NSNotification *)aNotification
{
    //code
    
    //log file code
    if(gpFile)
    {
        fprintf(gpFile,"Program terminated successfully\n");
        fclose(gpFile);
        gpFile = NULL;
    }
}

-(void)windowWillClose:(NSNotification *)aNotification      //NSWindow method windowWillClose
{
    //code
    [NSApp terminate:self];
}

-(void)dealloc
{
    //code
    //inn sequence of destructor
    [myOpenGLview release];
    [window release];
    [super dealloc];

}
@end

//view implementation
@implementation MyOpenGLView
{
    @private
    CVDisplayLinkRef displayLink;
}

//which method return's object so we take return type as id
-(id)initWithFrame:(NSRect)frame
{
    //code
    self = [super initWithFrame:frame];
    
    if(self)
    {
     
        //similar to pixel format descriptor
        /*
         NSOpenGLPFAOpenGLProfile,NSOpenGLProfileVersion4_1Core,
         NSOpenGLPFAScreenMask,CGDisplayIDToOpenGLDisplayMask(kCGDirectMainDisplay), -> Multiple Display or Single , kCG -> hardware renderer
         NSOpenGLPFANoRecovery, -> shifting of hardware rendering to software rendering when hardware renndering not there NoRecovery means dont do
         NSOpenGLPFAAccelerated, -> hardware rendering
         NSOpenGLPFAColorSize,24,   -> RGB so 24 = 8 x 3
         NSOpenGLPFADepthSize,24,
         NSOpenGLPFAAlphaSize,8,
         NSOpenGLPFADoubleBuffer,
         0
         */
        NSOpenGLPixelFormatAttribute attributes[] =
        {
            NSOpenGLPFAOpenGLProfile,NSOpenGLProfileVersion4_1Core,
            NSOpenGLPFAScreenMask,CGDisplayIDToOpenGLDisplayMask(kCGDirectMainDisplay),
            NSOpenGLPFANoRecovery,
            NSOpenGLPFAAccelerated,
            NSOpenGLPFAColorSize,24,
            NSOpenGLPFADepthSize,24,
            NSOpenGLPFAAlphaSize,8,
            NSOpenGLPFADoubleBuffer,
            0
        };
        
        //autorelease is like when you feel like release it , i wont release in dealloc.
        NSOpenGLPixelFormat *pixelFormat = [[[NSOpenGLPixelFormat alloc]initWithAttributes:attributes]autorelease];
        
        //if pixel format failed
        if(pixelFormat == nil)
        {
            fprintf(gpFile,"ERROR:Cannot get pixel format\n");
            [self release];
            [NSApp terminate:self];
        }
        
        NSOpenGLContext *glContext = [[[NSOpenGLContext alloc]initWithFormat:pixelFormat shareContext:nil]autorelease];
        
        [self setPixelFormat:pixelFormat];
        [self setOpenGLContext:glContext];
        
    }
    
    return(self);
}

-(CVReturn)getFrameForTime:(const CVTimeStamp*)outputTime
{
    //code
    //Apple OpenGL is multi threaded support
    //NSAutoreleasePool is like we are registering our objects here for memory and reclaim when the programs ends
    NSAutoreleasePool * pool = [[NSAutoreleasePool alloc]init];
    [self drawView];
    
    [pool release];
    return(kCVReturnSuccess);
}

/*
    in Objective C get methods are not written getMethod its direct Methodname , but set are written full setMethodname
 */
-(void)prepareOpenGL
{
    //code
    [super prepareOpenGL];
    [[self openGLContext]makeCurrentContext];
    
    //swap interval
    GLint swapInt = 1;
    [[self openGLContext]setValues:&swapInt forParameter:NSOpenGLCPSwapInterval];
    
    //write your OpenGL code for Vao ,Vbo , texture ,normal etc
    /*
        #version 410 core
        
        uninitailize -> [self release]
        exit -> [NSApp terminate:self]
     */
        
    glClearColor(0.0f,0.0f,1.0f,1.0f);
    
    //cv & cgl
    CVDisplayLinkCreateWithActiveCGDisplays(&displayLink);
    CVDisplayLinkSetOutputCallback(displayLink,&MyDisplayLinkCallback,self);
    //return type                                                  method name
    CGLContextObj cglContext = (CGLContextObj)[[self openGLContext]CGLContextObj];
    CGLPixelFormatObj cglPixelFormat = (CGLPixelFormatObj)[[self pixelFormat]CGLPixelFormatObj];
    CVDisplayLinkSetCurrentCGDisplayFromOpenGLContext(displayLink,cglContext,cglPixelFormat);
    CVDisplayLinkStart(displayLink);
    

}

-(void)reshape
{
    //code
    [super reshape];
    CGLLockContext((CGLContextObj)[[self openGLContext]CGLContextObj]);
    NSRect rect = [self bounds];
    
    if(rect.size.height < 0)
    {
        rect.size.height = 1;
    }
    
    glViewport(0,0,(GLsizei)rect.size.width,(GLsizei)rect.size.height);
    CGLUnlockContext((CGLContextObj)[[self openGLContext]CGLContextObj]);
}

-(void)drawRect:(NSRect)dirtyRect
{
    
}

-(void)drawView
{
    //code
    [[self openGLContext]makeCurrentContext];
    CGLLockContext((CGLContextObj)[[self openGLContext]CGLContextObj]);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //drawing code here
    
    
    //update or animation here
        
    //like swap buffer
    CGLFlushDrawable((CGLContextObj)[[self openGLContext]CGLContextObj]);
    
    CGLUnlockContext((CGLContextObj)[[self openGLContext]CGLContextObj]);
}

//how to shift the control from keyboard and mouse NSWindow to NSView
//acceptsFirstResponder is method of NSResponder is a subclass of NSObject
-(BOOL)acceptsFirstResponder
{
    //code        makeFirstResponder
    [[self window]makeFirstResponder:self];
    return(YES);
}

-(void)keyDown:(NSEvent*)theEvent
{
    //code
    int key = [[theEvent characters]characterAtIndex:0];
    
    switch(key)
    {
        case 27:
        case 'x':
        case 'X':
        case ' ':
            [self release];
            [NSApp terminate:self];
            break;
            
        case 'f':
        case 'F':
            [[self window]toggleFullScreen:self];
            break;
    }
}

//left mouse down
-(void)mouseDown:(NSEvent*)theEvent
{
    //code
}

//right mouse
-(void)rightMouseDown:(NSEvent*)theEvent
{
    //code
    
}

-(void)otherMouseDown:(NSEvent*)theEvent
{
    //code
    
}

-(void)dealloc
{
    //code
    CVDisplayLinkStop(displayLink);
    CVDisplayLinkRelease(displayLink);
    
    //write uninitialize code here
    
    [super dealloc];
    
}
@end

//As callback function is C style so its called in global space
/*
 
 displayLinkContext - MyOpenGLView
 
 [displayLinkContext getFrameForTime:outputTime];
 
*/

CVReturn MyDisplayLinkCallback(CVDisplayLinkRef displayLink,const CVTimeStamp *now,const CVTimeStamp *outputTime, CVOptionFlags flagsIn, CVOptionFlags *flagsOut,void* displayLinkContext)
{
    //code
    CVReturn result = [(MyOpenGLView*)displayLinkContext getFrameForTime:outputTime];
    
    return(result);
}
                               
                               

/*
 mkdir -p Window.app/Contents/MacOS
 "-p if dir is absent then create in that full path"
 
 clang -o Window.app/Contents/MacOS/Window Window.m -framework Cocoa
 
 */
