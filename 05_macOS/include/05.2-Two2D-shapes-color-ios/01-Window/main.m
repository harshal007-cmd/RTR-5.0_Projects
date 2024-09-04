//
//  main.m
//  01-Window
//
//  Created by Harshal Sali on 03/08/24.
//

#import<UIKit/UIKey.h>
#import"AppDelegate.h"

int main(int argc, char* argv[])
{
    //code
    NSAutoreleasePool* pool = [NSAutoreleasePool alloc];
    
    //get apdeleagate name in string
    NSString* delegateClassName = NSStringFromClass([AppDelegate class]);
    
    UIApplicationMain(argc, argv, nil, delegateClassName);
    
    [pool release];
    
    return 0;
}

