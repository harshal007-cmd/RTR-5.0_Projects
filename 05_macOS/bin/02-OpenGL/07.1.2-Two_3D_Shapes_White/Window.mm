#include<Foundation/Foundation.h>
#import<Cocoa/Cocoa.h>
#import <QuartzCore/CVDisplayLink.h>    //CV core video
#import <OpenGL/gl3.h>                  //gl.h
#import <OpenGL/gl3ext.h>
#include"vmath.h" //#import also work
using namespace vmath;

#define WIDTH 800
#define HEIGHT 600


enum
{
    AMC_ATTRIBUTE_POSITION = 0,
    AMC_ATTRIBUTE_COLOR = 1,

};



//global function declaration
CVReturn MyDisplayLinkCallback(CVDisplayLinkRef ,const CVTimeStamp *,const CVTimeStamp *,CVOptionFlags , CVOptionFlags *,void *);

//gobal variabls
FILE* gpFILE = NULL;

@interface AppDelegate:NSObject <NSApplicationDelegate, NSWindowDelegate>
@end

@interface GLView:NSOpenGLView
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
    GLView *glView;
}

-(void)applicationDidFinishLaunching:(NSNotification*)notification
{
    //code
    NSBundle *appBundle = [NSBundle mainBundle];
    NSString *appDirPath = [appBundle bundlePath];
    NSString* parentDirPath = [appDirPath stringByDeletingLastPathComponent];
    NSString* logFileNameWithPath = [NSString stringWithFormat:@"%@/Log.txt",parentDirPath];

    const char* pszLogFileNameWithPath = [logFileNameWithPath cStringUsingEncoding:NSASCIIStringEncoding];

    gpFILE = fopen(pszLogFileNameWithPath,"w");
    if(gpFILE==NULL)
    {
        NSLog(@"Log file cannot be create\n");
        [self release];
        [NSApp terminate:self];
    }
    fprintf(gpFILE,"Program started sucessfully\n");

    //declare rectangle fram for our window
    NSRect win_rect = NSMakeRect(0.0,0.0,WIDTH,HEIGHT);

    //create window
    window = [[NSWindow alloc]initWithContentRect:win_rect
                                        styleMask:NSWindowStyleMaskTitled |
                                                  NSWindowStyleMaskClosable |
                                                    NSWindowStyleMaskResizable |
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
    if(gpFILE)
    {
        fprintf(gpFILE,"Program finished succesfully\n");
        fclose(gpFILE);
        gpFILE = NULL;
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
{
    CVDisplayLinkRef displayLink;
    
    GLuint vertexShaderObject;
    GLuint fragmentShaderObject;
    GLuint shaderProgramObject;

    GLuint VAO_pyramid;
    GLuint VBO_pyramid_position;
    GLuint VBO_pyramid_color;
    
    GLuint VAO_cube;
    GLuint VBO_cube_position;
    GLuint VBO_cube_color;
    


    GLuint mvpMatrixUniform;
    mat4 perspectiveProjectionMatrix;  //in vmath
    
    GLfloat cAngle;
    GLfloat pAngle;


}


-(id)initWithFrame:(NSRect)frame
{
    //code
    self=[super initWithFrame:frame];
    if(self)
    {
        //here we can init shader and other variables

        NSOpenGLPixelFormatAttribute attributes[] =
        {
            NSOpenGLPFAOpenGLProfile,NSOpenGLProfileVersion4_1Core,
            NSOpenGLPFAScreenMask,CGDisplayIDToOpenGLDisplayMask(kCGDirectMainDisplay),
            NSOpenGLPFAColorSize,24,
            NSOpenGLPFADepthSize,32,
            NSOpenGLPFAAlphaSize,8,
            NSOpenGLPFANoRecovery,//to tell mac to dont use low level context
            NSOpenGLPFAAccelerated,//hardware renderer
            NSOpenGLPFADoubleBuffer,
            0
        };
        
        //create pixel format using above attributes
        NSOpenGLPixelFormat *pixelFormat = [[[NSOpenGLPixelFormat alloc]initWithAttributes:attributes]autorelease];
        
        //if pixel format failed
        if(pixelFormat == nil)
        {
            fprintf(gpFILE,"Creating pixel format failed\n");
            [self uninitailize];
            [self release];
            [NSApp terminate:self];
        }

        NSOpenGLContext *glContext = [[[NSOpenGLContext alloc]initWithFormat:pixelFormat shareContext:nil]autorelease];
        if(glContext == nil)
        {
            fprintf(gpFILE,"Creating opengl context failed\n");
            [self uninitailize];
            [self release];
            [NSApp terminate:self];
        }

        //set pixel format
        [self setPixelFormat:pixelFormat];

        //set opengl context
        [self setOpenGLContext:glContext];
        
    }
    return self;

}

-(void)prepareOpenGL
{
    //code
    [super prepareOpenGL];
    [[self openGLContext]makeCurrentContext];
    
    //matching monitor retracing with double buffer swapin
    GLint swapInt = 1;
    [[self openGLContext]setValues:&swapInt forParameter:NSOpenGLCPSwapInterval];
    
    //our initialise
    [self initialise];


    //Create and start display link
    CVDisplayLinkCreateWithActiveCGDisplays(&displayLink);
    CVDisplayLinkSetOutputCallback(displayLink,&MyDisplayLinkCallback,self);
    CGLPixelFormatObj cglPixelFormat = (CGLPixelFormatObj)[[self pixelFormat]CGLPixelFormatObj];
    CGLContextObj cglContext = (CGLContextObj)[[self openGLContext]CGLContextObj];
    CVDisplayLinkSetCurrentCGDisplayFromOpenGLContext(displayLink,cglContext,cglPixelFormat);
    CVDisplayLinkStart(displayLink);
    

}

-(void)reshape
{
    //code
    [super reshape];
    [[self openGLContext]makeCurrentContext];
   
    CGLLockContext((CGLContextObj)[[self openGLContext]CGLContextObj]);
    NSRect rect = [self bounds];
    
    int width = rect.size.width;
    int height = rect.size.height;
    //our resize
    [self resize:width :height];
    
    CGLUnlockContext((CGLContextObj)[[self openGLContext]CGLContextObj]);
}


//same as wm paint
-(void)drawRect:(NSRect)dirtyRect
{
    //call rendering funtion here too to avoid flickering
    [self drawView];
}

//our function
-(void)drawView
{
    //code
    [[self openGLContext]makeCurrentContext];
    CGLLockContext((CGLContextObj)[[self openGLContext]CGLContextObj]);
    
    ///our display
    [self display];
        
    //like swap buffer
    CGLFlushDrawable((CGLContextObj)[[self openGLContext]CGLContextObj]);
    
    CGLUnlockContext((CGLContextObj)[[self openGLContext]CGLContextObj]);
}

//function return per fram
-(CVReturn)getFrameForTime:(const CVTimeStamp*)outputTime
{
    //code
    NSAutoreleasePool* pool = [[NSAutoreleasePool alloc]init];

    //call rendering function here too
    [self drawView];
    [self myUpdate];
    [pool release];

    return kCVReturnSuccess;

}

-(int)initialise
{
    //code
    [self printGLInfo];

        //Vertex Shader, version set to 410, locked in Mac
    const GLchar* vertexShaderCode =
        "#version 410 core" \
        "\n" \
        "in vec4 aPosition;" \
        "uniform mat4 uMvpMatrix;" \
        "void main(void)" \
        "{" \
        "    gl_Position = uMvpMatrix * aPosition;" \
        "}";

    vertexShaderObject = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderObject, 1, (const GLchar**)&vertexShaderCode, NULL);
    glCompileShader(vertexShaderObject);

    GLint status = 0;
    GLint infoLogLength = 0;
    GLchar* szInfoLog = NULL;

    glGetShaderiv(vertexShaderObject, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE)
    {
        glGetShaderiv(vertexShaderObject, GL_INFO_LOG_LENGTH, &infoLogLength);
        if (infoLogLength > 0)
        {
            szInfoLog = (GLchar*)malloc(infoLogLength);
            if (szInfoLog != NULL)
            {
                glGetShaderInfoLog(vertexShaderObject, infoLogLength, NULL, szInfoLog);
                fprintf(gpFILE, "Vertex Shader compilation error log: %s\n", szInfoLog);
                free(szInfoLog);
                szInfoLog = NULL;
                [self uninitailize];//exit is available in this function

                [self release];
                [NSApp terminate:self];
            }
        }
    }


    //Fragment shader
    const GLchar* fragmentShaderCode =
        "#version 410 core" \
        "\n" \
        "out vec4 FragColor;" \
        "void main(void)" \
        "{" \
        "    FragColor = vec4(1.0,1.0,1.0,1.0);" \
        "}";

    fragmentShaderObject = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderObject, 1, (const GLchar**)&fragmentShaderCode, NULL);
    glCompileShader(fragmentShaderObject);

    status = 0;
    infoLogLength = 0;
    szInfoLog = NULL;

    glGetShaderiv(fragmentShaderObject, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE)
    {
        glGetShaderiv(fragmentShaderObject, GL_INFO_LOG_LENGTH, &infoLogLength);
        if (infoLogLength > 0)
        {
            szInfoLog = (GLchar*)malloc(infoLogLength);
            if (szInfoLog != NULL)
            {
                glGetShaderInfoLog(fragmentShaderObject, infoLogLength, NULL, szInfoLog);
                fprintf(gpFILE, "Fragment shader compilation error log: %s\n", szInfoLog);
                free(szInfoLog);
                szInfoLog = NULL;
                [self uninitailize];//exit is available in this function

                [self release];
                [NSApp terminate:self];
            }
        }
    }

    //Create Shader program
    shaderProgramObject = glCreateProgram();
    glAttachShader(shaderProgramObject, vertexShaderObject);
    glAttachShader(shaderProgramObject, fragmentShaderObject);
    glBindAttribLocation(shaderProgramObject, AMC_ATTRIBUTE_POSITION, "aPosition");

    glLinkProgram(shaderProgramObject);
    status = 0;
    infoLogLength = 0;
    szInfoLog = NULL;

    glGetProgramiv(shaderProgramObject, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
    {
        glGetProgramiv(shaderProgramObject, GL_INFO_LOG_LENGTH, &infoLogLength);
        if (infoLogLength > 0)
        {
            szInfoLog = (GLchar*)malloc(infoLogLength);
            if (szInfoLog != NULL)
            {
                glGetProgramInfoLog(shaderProgramObject, infoLogLength, NULL, szInfoLog);
                fprintf(gpFILE, "Shader program linking error log : %s\n", szInfoLog);
                free(szInfoLog);
                szInfoLog = NULL;
                [self uninitailize];//exit is available in this function

                [self release];
                [NSApp terminate:self];
            }
        }
    }

    //Get shader uniform locations
    mvpMatrixUniform = glGetUniformLocation(shaderProgramObject, "uMvpMatrix");


    const GLfloat cube_position[] =
    {
            // top
               1.0f, 1.0f, -1.0f,
               -1.0f, 1.0f, -1.0f,
               -1.0f, 1.0f, 1.0f,
               1.0f, 1.0f, 1.0f,

               // bottom
               1.0f, -1.0f, -1.0f,
              -1.0f, -1.0f, -1.0f,
              -1.0f, -1.0f,  1.0f,
               1.0f, -1.0f,  1.0f,

               // front
               1.0f, 1.0f, 1.0f,
              -1.0f, 1.0f, 1.0f,
              -1.0f, -1.0f, 1.0f,
               1.0f, -1.0f, 1.0f,

               // back
               1.0f, 1.0f, -1.0f,
              -1.0f, 1.0f, -1.0f,
              -1.0f, -1.0f, -1.0f,
               1.0f, -1.0f, -1.0f,

               // right
               1.0f, 1.0f, -1.0f,
               1.0f, 1.0f, 1.0f,
               1.0f, -1.0f, 1.0f,
               1.0f, -1.0f, -1.0f,

                   // left
               -1.0f, 1.0f, 1.0f,
               -1.0f, 1.0f, -1.0f,
               -1.0f, -1.0f, -1.0f,
               -1.0f, -1.0f, 1.0f
    };
    
    const GLfloat pyramid_position[] =
    {
        // front
            0.0f, 1.0f, 0.0f,
            -1.0f, -1.0f, 1.0f,
            1.0f, -1.0f, 1.0f,

                // right
            0.0f, 1.0f, 0.0f,
            1.0f, -1.0f, 1.0f,
            1.0f, -1.0f, -1.0f,

                // back
            0.0f, 1.0f, 0.0f,
            1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,

                // left
            0.0f, 1.0f, 0.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f, 1.0f

    };
    
    


    //VAO_cube - vertex array object
    glGenVertexArrays(1, &VAO_cube);
    glBindVertexArray(VAO_cube);

    //VBO for position - vertex buffer object
    glGenBuffers(1, &VBO_cube_position);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_cube_position);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_position), cube_position, GL_STATIC_DRAW);
    glVertexAttribPointer(AMC_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(AMC_ATTRIBUTE_POSITION);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    
    //VAO_pyramid - vertex array object
    glGenVertexArrays(1, &VAO_pyramid);
    glBindVertexArray(VAO_pyramid);

    //VBO for position - vertex buffer object
    glGenBuffers(1, &VBO_pyramid_position);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_pyramid_position);
    glBufferData(GL_ARRAY_BUFFER, sizeof(pyramid_position), pyramid_position, GL_STATIC_DRAW);
    glVertexAttribPointer(AMC_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(AMC_ATTRIBUTE_POSITION);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    
    
    //VBO for colors,removed

    glBindVertexArray(0);


    //Enabling depth
    glClearDepth(1.0f);//depth buffer to 1
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);//check less than or equal to with 1.0f

    //Set the Clear color of Window to Blue
    glClearColor(0.0f, 0.0f, 0.1f, 1.0f); //here OpenGL starts
        
    //perspective projection matrix init
    perspectiveProjectionMatrix = vmath::mat4::identity();

    [self resize:WIDTH :HEIGHT];
    

    return 0;
}

-(void)printGLInfo
{
    fprintf(gpFILE, "OpenGL Vendor    : %s\n", glGetString(GL_VENDOR));
    fprintf(gpFILE, "OpenGL Renderer  : %s\n", glGetString(GL_RENDERER));
    fprintf(gpFILE, "OpenGL Version   : %s\n", glGetString(GL_VERSION));
    fprintf(gpFILE, "OpenGL GLSL version : %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

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

    perspectiveProjectionMatrix = vmath::perspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);


}

-(void)display
{
    //code
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shaderProgramObject);

    //Pyramid
    //X-formation
    mat4 modelViewMatrix = mat4::identity();

    mat4 translationMatrix = mat4::identity();
    translationMatrix = vmath::translate(-1.5f, 0.0f, -6.0f);

    mat4 rotationMatrix = mat4::identity();
    rotationMatrix = vmath::rotate(pAngle, 0.0f, 1.0f, 0.0f);

    
    modelViewMatrix = translationMatrix * rotationMatrix;

    mat4 modelViewProjectionMatrix = mat4::identity();
    modelViewProjectionMatrix = perspectiveProjectionMatrix * modelViewMatrix;

    //Push above MVP info vertex shader's mvpUniform
    glUniformMatrix4fv(mvpMatrixUniform, 1, GL_FALSE, modelViewProjectionMatrix);

    glBindVertexArray(VAO_pyramid);

    glDrawArrays(GL_TRIANGLES, 0, 12);
    
    glBindVertexArray(0);
    
    
    
    //CUBE X-formation
    modelViewMatrix = mat4::identity();

    translationMatrix = mat4::identity();
    translationMatrix = vmath::translate(1.5f, 0.0f, -6.0f);

    mat4 scaleMatrix = mat4::identity();
    scaleMatrix = vmath::scale(0.75f, 0.75f, 0.75f);

    mat4 rotationMatrix1 = mat4::identity();
    rotationMatrix1 = vmath::rotate(cAngle, 1.0f, 0.0f, 0.0f);

    mat4 rotationMatrix2 = mat4::identity();
    rotationMatrix2 = vmath::rotate(cAngle, 0.0f, 1.0f, 0.0f);

    mat4 rotationMatrix3 = mat4::identity();
    rotationMatrix3 = vmath::rotate(cAngle, 0.0f, 0.0f, 1.0f);

    rotationMatrix = rotationMatrix1 * rotationMatrix2 * rotationMatrix3;

    modelViewMatrix = translationMatrix * scaleMatrix * rotationMatrix;

    modelViewProjectionMatrix = mat4::identity();
    modelViewProjectionMatrix = perspectiveProjectionMatrix * modelViewMatrix;

    //Push above MVP info vertex shader's mvpUniform
    glUniformMatrix4fv(mvpMatrixUniform, 1, GL_FALSE, modelViewProjectionMatrix);

    glBindVertexArray(VAO_cube);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        glDrawArrays(GL_TRIANGLE_FAN, 4, 4);
        glDrawArrays(GL_TRIANGLE_FAN, 8, 4);
        glDrawArrays(GL_TRIANGLE_FAN, 12, 4);
        glDrawArrays(GL_TRIANGLE_FAN, 16, 4);
        glDrawArrays(GL_TRIANGLE_FAN, 20, 4);

    glBindVertexArray(0);
    
    
    
    glUseProgram(0);

}

-(void)myUpdate//our update, as mac has update function
{
    pAngle += 0.1f;
        if (pAngle >= 360.0f)
        {
            pAngle = pAngle - 360.0f;
        }
    
    cAngle += 0.1f;
        if (cAngle >= 360.0f)
        {
            cAngle = cAngle - 360.0f;
        }
}

-(void)uninitailize
{
    //code
    if (shaderProgramObject)
    {
        glUseProgram(shaderProgramObject);
        GLint numShader = 0;

        glGetProgramiv(shaderProgramObject, GL_ATTACHED_SHADERS, &numShader);

        if (numShader > 0)
        {
            GLuint* pShaders = (GLuint*)malloc(numShader * sizeof(GLuint));
            if (pShaders != NULL)
            {
                glGetAttachedShaders(shaderProgramObject, numShader, NULL, pShaders);
                for (GLint i = 0; i < numShader; ++i)
                {
                    glDetachShader(shaderProgramObject, pShaders[i]);
                    glDeleteShader(pShaders[i]);
                    pShaders[i] = 0;
                }
                free(pShaders);
                pShaders = NULL;
            }
        }
        glUseProgram(0);
        glDeleteProgram(shaderProgramObject);
        shaderProgramObject = 0;
    }


    //delete VBO of position
    if (VBO_cube_position)
    {
        glDeleteBuffers(1, &VBO_cube_position);
        VBO_cube_position = 0;
    }

    //delete VAO_cube
    if (VAO_cube)
    {
        glDeleteVertexArrays(1, &VAO_cube);
        VAO_cube = 0;
    }


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
            [self uninitailize];
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

    [self uninitailize];

    if(displayLink)
    {
        CVDisplayLinkStop(displayLink);
        CVDisplayLinkRelease(displayLink);
        
    }
    
}
@end


//defination of global callback function
CVReturn MyDisplayLinkCallback(CVDisplayLinkRef displayLink,const CVTimeStamp *now,const CVTimeStamp *outputTime, CVOptionFlags flagsIn, CVOptionFlags *flagsOut,void* displayLinkContext)
{
    //code
    CVReturn result = [(GLView*)displayLinkContext getFrameForTime:outputTime];
    
    return(result);
}
