//
//  Window.m
//  
//
//  Created by user247557 on 6/16/24.
//

#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>
#import <QuartzCore/CVDisplayLink.h>		
#import <OpenGL/gl3.h>
#import <OpenGL/gl3ext.h>

// global function declaration

CVReturn MyDisplayLinkCallback(CVDisplayLinkRef, const CVTimeStamp*, const CVTimeStamp*, CVOptionFlags, CVOptionFlags*, void*);

//global variable declarations
FILE *gpFile = NULL;

@interface AppDelegate:NSObject <NSApplicationDelegate, NSWindowDelegate>
@end

@interface GLView:NSOpenGLView
@end

// main function
int main(int argc, char* argv[])
{
    //code
    //create autorelease pool for memory management
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    
    //create shared NSapp
    NSApp = [NSApplication sharedApplication];
    
    //set its own delegate
    [NSApp setDelegate:[[AppDelegate alloc]init]];
    
    //start NSApp run loop
    [NSApp run];
    
    //Let autorelease pool release all pending objects in our application
    [pool release];
    return 0;
}

// implementation of our custom AppDelegate interface
@implementation AppDelegate
{
    NSWindow *window;
    GLView *glView;
}

-(void)applicationDidFinishLaunching:(NSNotification *)notification
{
    //code
    //log file opening code
    NSBundle *appBundle = [NSBundle mainBundle];
    NSString *appDirPath = [appBundle bundlePath];
    NSString *parentDirPath = [appDirPath stringByDeletingLastPathComponent];
    NSString *logFileNameWithPath = [NSString stringWithFormat:@"%@/Log.txt",parentDirPath];
    const char* pszLogFileNameWithPath = [logFileNameWithPath cStringUsingEncoding:NSASCIIStringEncoding];
    gpFile = fopen(pszLogFileNameWithPath, "w");
    if (gpFile == NULL)
    {
        NSLog(@"Log File can not be created\n");
        [self release];
        [NSApp terminate:self];
    }
    
    fprintf(gpFile, "Program started successfully\n");
    
    //declare frame of our window
    NSRect win_rect = NSMakeRect(0.0, 0.0, 800.0, 600.0);
    
    //create the window
    window = [[NSWindow alloc]initWithContentRect:win_rect
                                         styleMask:NSWindowStyleMaskTitled| NSWindowStyleMaskClosable|NSWindowStyleMaskMiniaturizable| NSWindowStyleMaskResizable
                                           backing:NSBackingStoreBuffered
                                             defer:NO];
    
    //Give title to the window
    [window setTitle:@"PPB:Cocoa Window"];
    [window center];
    
    //painting window background black
    [window setBackgroundColor:[NSColor blackColor]];
    
    //create the custom view
    glView = [[GLView alloc]initWithFrame:win_rect];
    
    //set this newly create custome view as our newly created custom window
    [window setContentView:glView];
    
    // close window
    [window setDelegate:self];
    
    // now actually show the window , give its keyboard focus and make it top in z order
    [window makeKeyAndOrderFront:self];
}

-(void)applicationWillTerminate:(NSNotification *)notification
{
    
    //log file closing code
    if (gpFile)
    {
        fprintf(gpFile, "program finished successfully");
        fclose(gpFile);
        gpFile = NULL;
    }
    
}

-(void)windowWillClose:(NSNotification *)notification
{
    //code
    [NSApp terminate:self];
}

-(void)dealloc
{
    [super dealloc];
    [glView release];
    [window release];
}
@end

//impleentation of custom view interface
@implementation GLView
{
    CVDisplayLinkRef displayLink;
    
}

-(id)initWithFrame:(NSRect)frame
{
    //code
    self = [super initWithFrame:frame];
    if (self)
    {
        NSOpenGLPixelFormatAttribute attributes[] =
        {
            
            NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion4_1Core,
            NSOpenGLPFAScreenMask, CGDisplayIDToOpenGLDisplayMask(kCGDirectMainDisplay),
            NSOpenGLPFAColorSize, 24,
            NSOpenGLPFADepthSize, 24,
            NSOpenGLPFAAlphaSize, 8,
            NSOpenGLPFANoRecovery,
            NSOpenGLPFAAccelerated,
            NSOpenGLPFADoubleBuffer,
            0
        };
        
        NSOpenGLPixelFormat *pixelFormat =
        [[[NSOpenGLPixelFormat alloc]initWithAttributes: attributes]autorelease];
        
        if (pixelFormat == nil)
        {
            fprintf(gpFile, "creating pixel format failed\n");
            [self uninitialize];
            [self release];
            
            [NSApp terminate:self];
        }
        
        NSOpenGLContext *glContext = [[[NSOpenGLContext alloc]initWithFormat:pixelFormat shareContext:nil]autorelease];
        if (glContext == nil)
        {
            fprintf(gpFile, "creating context failed\n");
            [self uninitialize];
            [self release];
            
            [NSApp terminate:self];
        }
        
        [self setPixelFormat:pixelFormat];
        [self setOpenGLContext:glContext];
        
    }
    
    return(self);
}

-(void)prepareOpenGL
{
    [super prepareOpenGL];
    [[self openGLContext]makeCurrentContext];
    
    // matching monitor retracing with the double buffer swapping
    int swapInterval = 1;
    [[self openGLContext]setValues:&swapInterval forParameter:NSOpenGLCPSwapInterval];
    
    int result = [self initialize];
    
    //create and start display link
    CVDisplayLinkCreateWithActiveCGDisplays(&displayLink);
    CVDisplayLinkSetOutputCallback(displayLink, &MyDisplayLinkCallback, self);
    CGLPixelFormatObj cglPixelFormat = (CGLPixelFormatObj) [[self pixelFormat]CGLPixelFormatObj];
    CGLContextObj cglContext = (CGLContextObj)[[self openGlContext]CGLContextObj];
    CVDisplayLinkSetCurrentCGDisplayFromOpenGLContext(displayLink, cglContext, cglPixelFormat);
    CVDisplayLinkStart(displayLink);
}

-(void)reshape
{
    [super reshape];
    [[self openGLContext]makeCurrentContext];
    CGLLockContext((CGLContextObj)[[self openGlContext]CGLContextObj]);
    
    NSRect rect = [self bounds];
    int width = rect.size.width;
    int height = rect.size.height;
    [self resize:width :height];
    
    CGLUnlockContext((CGLContextObj)[[self openGlContext]CGLContextObj]);
}

-(void)drawRect:(NSRect)dirtyRect
{
    // call rendering function here too, to avoid flickering
    [self drawView];
    
}

// our rendering function
-(void) drawView
{
    
    [[self openGLContext]makeCurrentContext];
    CGLLockContext((CGLContextObj)[[self openGlContext]CGLContextObj]);
    
    [self display];
    
    CGLFlushDrawable((CGLContextObj)[[self openGlContext]CGLContextObj]);
    
    CGLUnlockContext((CGLContextObj)[[self openGlContext]CGLContextObj]);
    
}

// function called per frame using autorelease pool
-(CVReturn)getFrameForTime:(const CVTimeStamp *)outputTime
{
    //code
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    [self drawView];
    
    // call myupdate for animation
    [self myupdate];
    [pool release];
    
    return(kCVReturnSuccess);
    
}
-(int) initialize
{
    //code
    [self printGLInfo];
    
    //set depth
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    // set the clear color of window to blue
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);  // here actual opengl starts

    return 0;
    
}

-(void) printGLInfo
{
    
    fprintf(gpFile, "OpenGL Vendor : %s\n", glGetString(GL_VENDOR));
    fprintf(gpFile, "OpenGL Renderer : %s\n", glGetString(GL_RENDERER));
    fprintf(gpFile, "OpenGL Version : %s\n", glGetString(GL_VERSION));
    fprintf(gpFile, "OpenGL GLSL Version = %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
}

-(void) resize : (int)width : (int) height
{
    if (height <= 0)
        height = 1;
    
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    
}

-(void) display
{
    //code
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
}

-(void)myupdate
{
    
    //code
}

-(void) uninitialize
{
    //code
    
}
-(BOOL)acceptsFirstResponder
{
    [[self window]makeFirstResponder:self];
    return(YES);
}

-(void)keyDown:(NSEvent*)event
{
    int key= (int)[[event characters]characterAtIndex:0];
    switch (key) {
        case 27:
            [self uninitialize];
            [self release];
            [NSApp terminate:self];
            break;
        case 'F':
        case 'f':	
            [[self window]toggleFullScreen:self];
            break;
        default:
            break;
    }
}

-(void)mouseDown:(NSEvent *)event
{
    
}

-(void)rightMouseDown:(NSEvent*)event
{

}

-(void)dealloc
{
    [super dealloc];
    [self uninitialize];
    if (displayLink)
    {
        CVDisplayLinkStop(displayLink);
        CVDisplayLinkRelease(displayLink);
        displayLink  = nil;
    }
    
}
@end

//definition of global callback function
CVReturn MyDisplayLinkCallback(CVDisplayLinkRef displayLink, const CVTimeStamp *now, const CVTimeStamp *outputTime, CVOptionFlags flagsIn, CVOptionFlags *flagsOut, void *displayLinkContext)
{
    
    //code
    CVReturn result = [(GLView*)displayLinkContext getFrameForTime:outputTime];
    
    return result;
}


