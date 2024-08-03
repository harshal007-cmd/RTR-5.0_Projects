//
//  MyView.m
//  01-Window
//
//  Created by Harshal Sali on 04/08/24.
//

#import "MyView.h"

@implementation MyView
{
    NSString* string;
}

-(id)initWithFrame:(CGRect)frame
{
    //code
    self = [super initWithFrame:frame];
    if(self)
    {
        //set background to black
        [self setBackgroundColor:[UIColor blackColor]];
        
        //set string
        string = @"Hello World !!!";
        
        //single tap--------
        //create single tap grcz object
        UITapGestureRecognizer* singleTapGestureRecognizer = [[UITapGestureRecognizer alloc]initWithTarget:self action:@selector(onSingleTap:)];
        
        //set number of taps
        [singleTapGestureRecognizer setNumberOfTapsRequired:1];
        
        //set number of fingers
        [singleTapGestureRecognizer setNumberOfTouchesRequired:1];
        
        //set delegate as self
        [singleTapGestureRecognizer setDelegate:self];
        
        //add this gesture recoz to self
        [self addGestureRecognizer:singleTapGestureRecognizer];
        
        //Double tap similar to single tap----------
        UITapGestureRecognizer* doubleTapGestureRecognizer = [[UITapGestureRecognizer alloc]initWithTarget:self action:@selector(onDoubleTap:)];
        [doubleTapGestureRecognizer setNumberOfTapsRequired:2];
        [doubleTapGestureRecognizer setNumberOfTouchesRequired:1];
        [doubleTapGestureRecognizer setDelegate:self];
        [self addGestureRecognizer:doubleTapGestureRecognizer];
        
        //double should failed for two single tap
        [singleTapGestureRecognizer requireGestureRecognizerToFail:doubleTapGestureRecognizer];
        
    
        //Swipe action----------
        UISwipeGestureRecognizer* swipeGestureRecognizer = [[UISwipeGestureRecognizer alloc]initWithTarget:self action:@selector(onSwipe:)];
        [swipeGestureRecognizer setDelegate:self];
        [self addGestureRecognizer:swipeGestureRecognizer];
        
        //Long press -----------
        UILongPressGestureRecognizer* longPressGestureRecognizer = [[UILongPressGestureRecognizer alloc]initWithTarget:self action:@selector(onLongPress:)];
        [longPressGestureRecognizer setDelegate:self];
        [self addGestureRecognizer:longPressGestureRecognizer];
       
        
    }
    return self;
}

-(void)drawRect:(CGRect)rect
{
    //code
    //declare background color black
    UIColor* bgColor = [UIColor blackColor];

    //set this color
    [bgColor set];

    //fill window/dirtyrect from above black color
    UIRectFill(rect);

    ///create font for our screen
    UIFont *stringFont = [UIFont fontWithName:@"Helvetica" size:24];

    //Create string color
    UIColor* fgColor = [UIColor greenColor];

    //create dictionory for our string attibutes using above two
    NSDictionary *stringDictionary = [NSDictionary dictionaryWithObjectsAndKeys:stringFont,NSFontAttributeName,
                                                                              fgColor,NSForegroundColorAttributeName,nil];
    //create size of string according to size of font
    CGSize stringSize = [string sizeWithAttributes:stringDictionary];

    CGPoint point;
        point.x = (rect.size.width/2) - (stringSize.width/2);
        point.y = (rect.size.height/2) - (stringSize.height/2);
    
    //draw string hello World
    [string drawAtPoint:point withAttributes:stringDictionary];
}

-(BOOL)becomeFirstResponder
{
    //code
    return YES;
    
}

-(void)touchesBegan:(NSSet*)touches withEvent:(nullable UIEvent *)event
{
    //code
    
}

-(void)onSingleTap:(UITapGestureRecognizer*)gestureRecognizer
{
    //code
    string = @"Single Tap !!!";
    [self setNeedsDisplay];//to repaint
    
    
}


-(void)onDoubleTap:(UITapGestureRecognizer*)gestureRecognizer
{
    //code
    string = @"Double Tap !!!";
    [self setNeedsDisplay];
    
}

-(void)onSwipe:(UISwipeGestureRecognizer*)gestureRecognizer
{
    //code
    string = @"On Swipe !!!";
    [self setNeedsDisplay];
    
    
}


-(void)onLongPress:(UILongPressGestureRecognizer*)gestureRecognizer
{
    //code
    string = @"On Long Press !!!";
    [self setNeedsDisplay];
    
    
}

-(void)dealloc
{
    //code
    [super dealloc];
}
@end
