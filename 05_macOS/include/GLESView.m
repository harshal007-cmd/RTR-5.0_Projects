//
//  MyView.m
//  01-Window
//
//  Created by Harshal Sali on 04/08/24.
//
#import <OpenGLES/ES3/gl.h>
#import <OpenGLES/ES3/glext.h>
#import "GLESView.h"


@implementation GLESView
{
    EAGLContext* eaglCotext;
    
    GLuint customFrameBuffer;
    GLuint colorRenderBuffer;
    GLuint depthRenderBuffer;
    
    id displayLink;
    NSInteger framesPerSeconds;
    BOOL isDisplayLink;
    
}

-(id)initWithFrame:(CGRect)frame
{
    //code
    self = [super initWithFrame:frame];
    if(self)
    {
        //set background to black
        [self setBackgroundColor:[UIColor blackColor]];
        
        //Create EACGL layer
        CAEAGLLayer* eaglLayer = (CAEAGLLayer*)[super layer];
        [eaglLayer setOpaque:YES];
        NSDictionary* dictionary = [NSDictionary dictionaryWithObjectsAndKeys:[NSNumber numberWithBool:NO], kEAGLDrawablePropertyRetainedBacking, kEAGLColorFormatRGBA8, kEAGLDrawablePropertyColorFormat,nil];
        [eaglLayer setDrawableProperties:dictionary];
        
        //Create EAGL context
        eaglCotext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES3];
        if(eaglCotext==nil)
        {
            printf("OpenGLES context creation failed\n");
            [self uninitailize];
            [self release];
            return 0;
        }
        
        //Set this context as current context
        [EAGLContext setCurrentContext:eaglCotext];
        
        
        //Create custom frambuffer
        glGenFramebuffers(1, &customFrameBuffer);
        glBindBuffer(GL_FRAMEBUFFER, customFrameBuffer);
        
        //Create color render buffer
        glGenRenderbuffers(1, &colorRenderBuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, colorRenderBuffer);
        
        //Give storage to color render buffer by using IOS method
        [eaglCotext renderbufferStorage:GL_RENDERBUFFER fromDrawable:eaglLayer];
        
        //give above colorbuffer to custom frambuffer
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, colorRenderBuffer);
        
        //Depth render buffer
        //Find width of color buffer
        GLint width;
        glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, &width);
        GLint height;
        glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &height);
        
        //create and bind with depth render buffer
        glGenRenderbuffers(1, &depthRenderBuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, depthRenderBuffer);
        
        
        //give storage to depth render buffer using opengles funtion
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, width, height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthRenderBuffer);
        
        if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        {
            printf("Framwbuffer is not complete\n");
            [self uninitailize];
            return nil;
        }
        
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

//
+(Class)layerClass
{
    return [CAEAGLLayer class];
}

/*
-(void)drawRect:(CGRect)rect
{
    //code
    
}
*/

-(int)initialise
{
    //code
    [self printGLInfo];
    //Enabling depth
    glClearDepthf(1.0f);//depth buffer to 1
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);//check less than or equal to with 1.0f

    //Set the Clear color of Window to Blue
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f); //here OpenGL starts


    return 0;
}

-(void)printGLInfo
{
    printf("OpenGL Vendor    : \n");
    printf("OpenGL Renderer  : \n");
    printf("OpenGL Version   : \n");
    printf("OpenGL GLSL version\n");

}

-(void)resize:(int)width :(int)height
{
    //code
    //code
    if (height <= 0)
    {
        height = 1;

    }

    glViewport(0, 0, (GLsizei)width, (GLsizei)height);

}

-(void)display
{
    //code
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


}

-(void)myUpdate//our update, as mac has update function
{

}

-(void)uninitailize
{
    //code

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
    
    
}


-(void)onDoubleTap:(UITapGestureRecognizer*)gestureRecognizer
{
    //code
    
}

-(void)onSwipe:(UISwipeGestureRecognizer*)gestureRecognizer
{
    //code
    
    
}


-(void)onLongPress:(UILongPressGestureRecognizer*)gestureRecognizer
{
    //code
    
}

-(void)dealloc
{
    //code
    [super dealloc];
}
@end
