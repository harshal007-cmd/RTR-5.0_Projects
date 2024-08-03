//
//  AppDelegate.m
//  01-Window
//
//  Created by Mayur Sutar on 03/08/24.
//

#import "AppDelegate.h"
#import "ViewController.h"
#import "MyView.h"

@implementation AppDelegate
{
@private
    UIWindow* window;
    ViewController* vController;
    MyView* myView;
    
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
    myView = [[MyView alloc]initWithFrame:screenRect];
    
    //set this view as view of view controller
    [vController setView:myView];
    
    //decrement refrence count of view which is incremnted my setView
    [myView release];
    
    //set focus on this window and make is visible
    [window makeKeyAndVisible];
    
    return YES;
}


-(void)applicationWillResignActive:(UIApplication *)application
{
    //code
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
    
}

-(void)applicationWillTerminate:(UIApplication *)application
{
    //code
    
}

-(void)dealloc
{
    //code
    [super dealloc];
    [MyView release];
    [ViewController release];
    [window release];
    
}
@end









