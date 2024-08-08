//
//  AppDelegate.m
//  01-Window
//
//  Created by Mayur Sutar on 03/08/24.
//

#import "AppDelegate.h"
#import "ViewController.h"
#import "GLESView.h"

@implementation AppDelegate
{
@private
    UIWindow* window;
    ViewController* vController;
    GLESView* glesView;
    
}

-(BOOL)application:(UIApplication*)application didFinishLaunchingWithOptions:(NSDictionary*)launchOptions
{
    //code
    //get iphone screen rectangle
    CGRect screenRect = [[UIScreen mainScreen]bounds];
    
    //create window
    window = [[UIWindow alloc]initWithFrame:screenRect];
    
    //create view conroller
    vController = [[ViewController alloc]init];
    
    //set this viewcontroller as window's controller
    [window setRootViewController:vController];
    
    //Create our custome view
    glesView = [[GLESView alloc]initWithFrame:screenRect];
    
    //set this view as view of view controller
    [vController setView:glesView];
    
    //decrement refrence count of view which is incremnted my setView
    [glesView release];
    
    //set focus on this window and make is visible
    [window makeKeyAndVisible];
    
    //start display link
    [glesView startDisplayLink];
    
    return YES;
}


-(void)applicationWillResignActive:(UIApplication *)application
{
    //code
    [glesView stopDisplayLink];
}


-(void)applicationDidEnterBackground:(UIApplication *)application
{
    //code
    
}


-(void)applicationWillEnterForeground:(UIApplication *)application
{
    //code
    
}

-(void)applicationDidBecomeActive:(UIApplication *)application
{
    //code
    [glesView startDisplayLink];
    
}

-(void)applicationWillTerminate:(UIApplication *)application
{
    //code
    [glesView stopDisplayLink];
    
}

-(void)dealloc
{
    //code
    [super dealloc];
    [GLESView release];
    [ViewController release];
    [window release];
    
}
@end









