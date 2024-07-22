#include<Foundation/Foundation.h>
#import<Cocoa/Cocoa.h>

//gobal variabls
//FILE* gpFile = NULL;

@interface AppDelegate:NSObject <NSApplicationDelegate, NSWindowDelegate>
@end

@interface View:NSView
@end

int main(int argc, char* argv[])
{
	//code
	//create auto relese pool for mem mang
	NSAutoreleasePool* pool = [[NSAutoreleasePool alloc]init];
	
	//create gloabal shared nsapp obj
	NSApp =[NSApplication sharedApplication];

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
	View *view;
}

-(void)applicationDidFinishLaunching:(NSNotification*)notification
{
	//code
    /*
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
	fprintf(gpFile,"Program started successfully\n");
     */
	//declare rectangle fram for our window
	NSRect win_rect = NSMakeRect(0.0,0.0,800.0,600.0);

	//create window
	window = [[NSWindow alloc]initWithContentRect:win_rect
									    styleMask:NSWindowStyleMaskTitled |
												  NSWindowStyleMaskClosable |
												  NSWindowStyleMaskMiniaturizable |
												  NSWindowStyleMaskResizable
										  backing:NSBackingStoreBuffered
											defer:NO];

	//give title to window
	[window setTitle:@"HVS: Cocoa Window"];
	
	//center the window
	[window center];

	//create custom View
	view = [[View alloc]initWithFrame:win_rect];

	//set this new custom view as view of our new custom Window
	[window setContentView:view];

	[window setDelegate:self];

	//set window, make it top on z order, give keyboard control
	[window makeKeyAndOrderFront:self];

}

-(void)applicationWillTerminate:(NSNotification*)notification
{
	//code
	//Log file closing code
    /*
	if(gpFile)
	{
		fprintf(gpFile,"Program finished successfully\n");
		fclose(gpFile);
		gpFile = NULL;
	}
     */
}

-(void)windowWillClose:(NSNotification*)notification
{
	//code
	[NSApp terminate:self];
}

-(void)dealloc
{
	[super dealloc];
	[view release];
	[window release];

}
@end

//view interface
@implementation View
{
	NSString* string;
}

-(id)initWithFrame:(NSRect)frame
{
	//code
	self=[super initWithFrame:frame];
    /*
	if(self)
	{
		string=@"Hello World !!!";
	}
     */
	return self;

}

//same as wm paint
-(void)drawRect:(NSRect)dirtyRect
{
	//declare background color black
	NSColor* bgColor = [NSColor blackColor];

	//set this color
	[bgColor set];

	//fill window/dirtyrect from above black color
	NSRectFill(dirtyRect);

	///create font for our screen
	NSFont *stringFont = [NSFont fontWithName:@"Helvetica" size:32];

	//Create string color
	NSColor* fgColor = [NSColor greenColor];

	//create dictionory for our string attibutes using above two
	NSDictionary *stringDictionary = [NSDictionary dictionaryWithObjectsAndKeys:stringFont,NSFontAttributeName,
																			  fgColor,NSForegroundColorAttributeName,nil];
	//create size of string according to size of font
	NSSize stringSize = [string sizeWithAttributes:stringDictionary];

    //Create point for drawing of string
	NSPoint stringPoint = NSMakePoint((dirtyRect.size.width/2 - stringSize.width/2),
									  (dirtyRect.size.height/2 - stringSize.height/2));

	//draw string hello World
	[string drawAtPoint:stringPoint withAttributes:stringDictionary];
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
	int key = (int)[[event characters]characterAtIndex:0];

	switch(key)
	{
		case 27:
			[self release];
			[NSApp terminate:self];
		break;
        /*
		case 'f':
		case 'F':
			[[self window]toggleFullScreen:self];
		break;
         */
		default:
		break;
	}
}

-(void)mouseDown:(NSEvent*)event
{
	//code
	string = @"Left mouse button is clicked !";
	//similat invadiate rect in windows 
	[self setNeedsDisplay:YES];
}

-(void)rightMouseDown:(NSEvent*)event
{
	//code
	string = @"Right mouse button is clicked !";
	[self setNeedsDisplay:YES];
}

-(void)dealloc
{
	[super dealloc];
}
@end


//





















