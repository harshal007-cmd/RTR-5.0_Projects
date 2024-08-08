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
        
        //check status of new custome framebuffer
        GLenum frambuffer_status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        
        if(frambuffer_status != GL_FRAMEBUFFER_COMPLETE)
        {
            printf("Framebuffer is not complete\n");
            [self uninitailize];
            [self release];
            return 0;
        }
        
        //initialize frames per sec
        framesPerSeconds = 60;//value 60 is recomended from ios 8.2
        //opengl depecated from ios 11.4
        
        //initialze display link existance variable
        isDisplayLink = NO;
        
        //call our initialize method
        int result = [self initialise];
        
        if(result != 0)
        {
            printf("Initialize failed\n");
            [self uninitailize];
            [self release];
            exit(0);
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

-(void)drawView:(id)displayLink
{
    //code
    //set corrent context again
    [EAGLContext setCurrentContext:eaglCotext];
    
    //bind with fb again
    glBindBuffer(GL_FRAMEBUFFER, customFrameBuffer);
    
    //call our disply here
    [self display];
    [self myUpdate];
    
    //bind with color render buffer again
    glBindRenderbuffer(GL_RENDERBUFFER, colorRenderBuffer);
    
    //present this color buffer, which will do double buffering
    [eaglCotext presentRenderbuffer:GL_RENDERBUFFER];
    
    
}

//override layout subview method
-(void)layoutSubviews
{
    //code
    //bind with color render buffer again
    glBindRenderbuffer(GL_RENDERBUFFER, colorRenderBuffer);
    
    //create color renderbuffer storage again
    [eaglCotext renderbufferStorage:GL_RENDERBUFFER fromDrawable:(CAEAGLLayer*)[self layer]];
    
    GLint width;
    glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, &width);
    GLint height;
    glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &height);
    
    
    glGenRenderbuffers(1, &depthRenderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, depthRenderBuffer);
    
    
    //give storage to depth render buffer using opengles funtion
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthRenderBuffer);
    
    //check status of new custome framebuffer
    GLenum frambuffer_status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    
    if(frambuffer_status != GL_FRAMEBUFFER_COMPLETE)
    {
        printf("Framebuffer is not complete\n");
        [self uninitailize];
        [self release];
        exit(0);
    }
    
    // call out resize here
    [self resize:width :height];
    
    //it is recommended to call drawView here
    [self drawView:displayLink];
       
    
}

//start display link custom method which will called by appdelegate
-(void)startDisplayLink
{
    //code
    //create display link
    if(isDisplayLink==NO)
    {
        //create
        displayLink = [CADisplayLink displayLinkWithTarget:self selector:@selector(drawView:)];
        
        //set frames per sec
        [displayLink setPreferredFramesPerSecond:framesPerSeconds];
        
        //add this display link to our run loop
        [displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
        
        //set is displayLink to yes
        isDisplayLink = YES;
    }
    
    
}

//stop display link custom method which will called by Appdelegate
-(void)stopDisplayLink
{
    if(isDisplayLink==YES)
    {
        //remove display link from run loop by invalidating it
        [displayLink invalidate];
        displayLink = nil;
        
        isDisplayLink = NO;
    }
}


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
    printf("OpenGL Vendor    : %s\n",glGetString(GL_VENDOR));
    printf("OpenGL Renderer  : %s\n",glGetString(GL_RENDERER));
    printf("OpenGL Version   : %s\n",glGetString(GL_VERSION));
    printf("OpenGL GLSL version %s\n",glGetString(GL_SHADING_LANGUAGE_VERSION));

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
    if(depthRenderBuffer)
    {
        glDeleteRenderbuffers(1, &depthRenderBuffer);
        depthRenderBuffer = 0;
    }
    
    if(colorRenderBuffer)
    {
        glDeleteRenderbuffers(1, &colorRenderBuffer);
        colorRenderBuffer=0;
    }
    
    if(customFrameBuffer)
    {
        glDeleteRenderbuffers(1, &customFrameBuffer);
        customFrameBuffer=0;
    }
    
    if(eaglCotext && [EAGLContext currentContext] == eaglCotext)
    {
        
        [EAGLContext setCurrentContext:nil];
        [eaglCotext release];
        eaglCotext = nil;
        
    }
    
    
    
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
    [self uninitailize];
    [self release];
    exit(0);
    
    
}


-(void)onLongPress:(UILongPressGestureRecognizer*)gestureRecognizer
{
    //code
    
}

-(void)dealloc
{
    //code
    [self uninitailize];
    
    [super dealloc];
    
    //release displayLink
    if(displayLink)
    {
        [displayLink invalidate];
        [displayLink stop];
        [displayLink release];
        displayLink = nil;
    }
}
@end
