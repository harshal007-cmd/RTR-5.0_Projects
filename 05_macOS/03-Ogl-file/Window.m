#include<Foundation/Foundation.h>
#import<Cocoa/Cocoa.h>

//gobal variabls
FILE* gpFile = NULL;

@interface AppDelegate:NSObjet <NSApplicationDelegate, NSWindowDelegate>
@end

@interface GLView:NSView
@end

int main(int argc, char* argv[])
{
	//code
	//create auto relese pool for mem mang
	NSAutoreleasePool* pool = [[NSAutoreleasePool alloc]init];
	
	//create gloabal shared nsapp obj
	NSApp =[NSApplication shaderApplication];

	//set its delegate to our AppDelegate custom class
	[NSApp setDelegate:[[AppDelegate alloc]init]];

	//start nsapp loop
	[NSApp run];//message loop/run loop

	//let auto release pool release all pending objs in our application
	[pool release];

	return 0;
}

//implementation of our custom AppDelegate interface
@implementation AppDelegate
{
	NSWindow* window;
	View GLView *glView;
}

-(void)applicationDidFinishLaunching:(NSNotification*)notification
{
	//code
	NSBundle *appBundle = [NSBundle mainBundle];
	NSString *appDirPath = [appBundle bundlePath];
	NSString* parentDirPath = [appDirPath stringByDeletingLastPathComponent];
	NSString* logFileNameWithPath = [NSString stringWithFormat:@"%@/Log.txt",parentDirPath];

	const char* pszLogFileNameWithPath = [logFileNameWithPath cStringUsingEncoding:NSASCIIStringEncoding];

	gpFile = fopen(pszLogFileNameWithPath,"w");
	if(gpFile==NULL)
	{
		NSLog(@"Log file cannot be create\n");
		[self release];
		[NSApp terminate:self];
	}
	fprintf(gpFile,"Program started sucessfully\n");

	//declare rectangle fram for our window
	NSRect win_rect = NSMakeRect(0.0,0.0,800.0,600.0);

	//create window
	window = [[NSWindow alloc]initWithContentRect:win_rect
				*					    styleMask:NSWindowStyleMaskTiled |
												  NSWindowStyleMaskClosable |
												  NSWindowStyleMaskMiniaturizalble |
												  NSWindowStyleMaskResizable
										  backing:NSBackingStoreBuffered
											defer:NO];

	//give title to window
	[window setTitle:@"HVS: Cocoa Window"];
	
	//center the window
	[window center];

	//painting backgroud black
	[window setBackgroundColor:[NSColor blackColor]];

	//create custom View
	glView = [[GLView alloc]initWithFrame:win_rect];

	//set this new custom view as view of our new custom Window
	[window setContentView:glView];

	[window setDelegate:self];

	//set window, make it top on z order, give keyboard control
	[window makeKeyAndOrderFront:self];

}

-(void)applicationWillTerminate:(NSNotification*)notification
{
	//code
	//Log file closing code
	if(gpFile)
	{
		fprintf(gpFile,"Program finished succesfully\n");
		fclose(gpFile);
		gpFile = NULL;
	}
}

-(void)windowWillClose:(NSNotification*)notification
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

//view interface
@implementation GLView


-(id)initWithFrame:(NSRect)frame
{
	//code
	self=[supe initWithFrame:frame];
	if(self)
	{

	}

	return self;

}

//same as wm paint
-(void)drawRect:(NSRect)dirtyRect
{

}

-(BOOL)acceptsFirstResponder
{
	//code
	[[self window]makeFirstResponder:self];
	return YES;
}

-(void)keyDown:(NSEvent*)event
{
	//code
	int key = (int)[[event charaters]charactersAtInder:0];

	switch(key)
	{
		case 27:
			[self release];
			[NSApp terminate:self];
		break;

		case 'f':
		case 'F':
			[[self window]toggleFullScreen:self];
		break;

		default:
		break;
	}
}

-(void)mouseDown:(NSEvent*)event
{
	//code
}

-(void)rightMouseDown:(NSEvent*)event
{
	//code
}

-(void)dealloc
{
	[super dealloc];
}
@end


//





















