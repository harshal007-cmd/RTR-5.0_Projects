//
//  Window.m
//  
//
//  Created by Rohan Satyamurthy
//
//  Creating log file
//

#import <Foundation/Foundation.h>   //This is like stdio.h very import
#import <Cocoa/Cocoa.h>             //This is like widows.h or Xlib.h

FILE *gpFile = NULL;

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
@interface MyView:NSView
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
    MyView * view;
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
    [window setTitle:@"RS : macOS window"];
    [window center];        //bringing window to center
    
    view = [[MyView alloc]initWithFrame:win_rect];  //initWithFrame is NSView method which we have implemented below
  
    [window setContentView:view];   //window set your content view from view
    [window setDelegate:self];      // self is like "this" when you close using x your window will close but it it wont go from dock
    [window makeKeyAndOrderFront:self];     //set  foreground window [SetFocus]
  
}

-(void)applicationWillTerminate:(NSNotification *)aNotification
{
    //code
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
    [view release];
    [window release];
    [super dealloc];

}
@end

//view implementation
@implementation MyView
{
    @private
}

//which method return's object so we take return type as id
-(id)initWithFrame:(NSRect)frame
{
    //code
    self = [super initWithFrame:frame];
    
    if(self)
    {
        
    }
    
    return(self);
}

-(void)drawRect:(NSRect)dirtyRect
{
   
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
    [super dealloc];
}
@end

/*
 mkdir -p Window.app/Contents/MacOS
 "-p if dir is absent then create in that full path"
 
 clang -o Window.app/Contents/MacOS/Window Window.m -framework Cocoa
 
 */
