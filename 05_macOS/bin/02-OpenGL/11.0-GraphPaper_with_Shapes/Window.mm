#include<Foundation/Foundation.h>
#import<Cocoa/Cocoa.h>
#import <QuartzCore/CVDisplayLink.h>    //CV core video
#import <OpenGL/gl3.h>                  //gl.h
#import <OpenGL/gl3ext.h>
#include"vmath.h" //#import also work
using namespace vmath;
#import <vector>
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

    GLuint VAO;
    GLuint VBO_positions;
    GLuint VBO_color;
    
    GLuint colorUniform;
    
    std::vector<vmath::vec3>triangle_vertices;
    GLuint vao_triangle;

    std::vector<vmath::vec3>square_vertices;
    GLuint vao_square;

    std::vector<vmath::vec3>circle_vertices;
    GLuint vao_circle;

    std::vector<vmath::vec3>graph_vertices;
    GLuint vao_graph;
    
    char c;
    


    GLuint mvpMatrixUniform;
    mat4 perspectiveProjectionMatrix;  //in vmath
    

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
        "uniform vec4 uColor;"\
        "void main(void)" \
        "{" \
        "    FragColor = uColor;" \
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
    colorUniform = glGetUniformLocation(shaderProgramObject, "uColor");



    //VAO - vertex array object
        glGenVertexArrays(1, &vao_graph);
        glBindVertexArray(vao_graph);
        {
            glGenBuffers(1, &VBO_positions);
            glBindBuffer(GL_ARRAY_BUFFER, VBO_positions);
            
            graph_vertices.push_back(vmath::vec3(-1.0f, 0.0f, 0.0f));
            graph_vertices.push_back(vmath::vec3(1.0f, 0.0f, 0.0f));

            graph_vertices.push_back(vmath::vec3(0.0f, 1.0f, 0.0f));
            graph_vertices.push_back(vmath::vec3(0.0f, -1.0f, 0.0f));

            float y = 0.0f;
            for (int i = 0; i < 20; ++i)
            {
                y += 0.05f;
                graph_vertices.push_back(vmath::vec3(-1.0f, y, 0.0f));
                graph_vertices.push_back(vmath::vec3(1.0f, y, 0.0f));
                graph_vertices.push_back(vmath::vec3(-1.0f, -y, 0.0f));
                graph_vertices.push_back(vmath::vec3(1.0f, -y, 0.0f));

                graph_vertices.push_back(vmath::vec3(y, 1.0f, 0.0f));
                graph_vertices.push_back(vmath::vec3(y, -1.0f, 0.0f));
                graph_vertices.push_back(vmath::vec3(-y, 1.0f, 0.0f));
                graph_vertices.push_back(vmath::vec3(-y, -1.0f, 0.0f));

            }
            glBufferData(GL_ARRAY_BUFFER, sizeof(vmath::vec3) * graph_vertices.size(), graph_vertices.data(), GL_STATIC_DRAW);
            glVertexAttribPointer(AMC_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
            glEnableVertexAttribArray(AMC_ATTRIBUTE_POSITION);
            
        }
        glBindBuffer(GL_ARRAY_BUFFER, 0);


        //For Square
        //VAO - vertex array object
        glGenVertexArrays(1, &vao_square);
        glBindVertexArray(vao_square);
        {
            glGenBuffers(1, &VBO_positions);
            glBindBuffer(GL_ARRAY_BUFFER, VBO_positions);

            square_vertices.push_back(vmath::vec3(-0.5f, 0.5f, 0.0f));
            square_vertices.push_back(vmath::vec3(0.5f, 0.5f, 0.0f));

            square_vertices.push_back(vmath::vec3(0.5f, -0.5f, 0.0f));
            square_vertices.push_back(vmath::vec3(-0.5f, -0.5f, 0.0f));

            square_vertices.push_back(vmath::vec3(-0.5f, 0.5f, 0.0f));
            square_vertices.push_back(vmath::vec3(-0.5f, -0.5f, 0.0f));

            square_vertices.push_back(vmath::vec3(0.5f, 0.5f, 0.0f));
            square_vertices.push_back(vmath::vec3(0.5f, -0.5f, 0.0f));

            glBufferData(GL_ARRAY_BUFFER, sizeof(vmath::vec3) * square_vertices.size(), square_vertices.data(), GL_STATIC_DRAW);
            glVertexAttribPointer(AMC_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
            glEnableVertexAttribArray(AMC_ATTRIBUTE_POSITION);

        }
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        
        //For Triangle
        //VAO - vertex array object
        glGenVertexArrays(1, &vao_triangle);
        glBindVertexArray(vao_triangle);
        {
            glGenBuffers(1, &VBO_positions);
            glBindBuffer(GL_ARRAY_BUFFER, VBO_positions);

            triangle_vertices.push_back(vmath::vec3(0.0f, 0.5f, 0.0f));
            triangle_vertices.push_back(vmath::vec3(-0.5f, -0.5f, 0.0f));

            triangle_vertices.push_back(vmath::vec3(-0.5f, -0.5f, 0.0f));
            triangle_vertices.push_back(vmath::vec3(0.5f, -0.5f, 0.0f));

            triangle_vertices.push_back(vmath::vec3(0.5f, -0.5f, 0.0f));
            triangle_vertices.push_back(vmath::vec3(0.0f, 0.5f, 0.0f));

            glBufferData(GL_ARRAY_BUFFER, sizeof(vmath::vec3) * triangle_vertices.size(), triangle_vertices.data(), GL_STATIC_DRAW);
            glVertexAttribPointer(AMC_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
            glEnableVertexAttribArray(AMC_ATTRIBUTE_POSITION);

        }
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        //Circle
        //VAO - vertex array object
        glGenVertexArrays(1, &vao_circle);
        glBindVertexArray(vao_circle);
        {
            glGenBuffers(1, &VBO_positions);
            glBindBuffer(GL_ARRAY_BUFFER, VBO_positions);

            for (int i = 0; i <= 100; ++i)
            {
                circle_vertices.push_back(vmath::vec3(0.0f + (0.5f * cosf(2 * M_PI * i / 100)), 0.0f + (0.5f * sinf(2 * M_PI * i / 100)), 0.0f));

            }
            
            glBufferData(GL_ARRAY_BUFFER, sizeof(vmath::vec3) * circle_vertices.size(), circle_vertices.data(), GL_STATIC_DRAW);
            glVertexAttribPointer(AMC_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
            glEnableVertexAttribArray(AMC_ATTRIBUTE_POSITION);

        }
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

-(void)graphPaper
{
    glUniform4fv(colorUniform, 1, vmath::vec4(1.0, 0.0, 0.0, 1.0));
        glBindVertexArray(vao_graph);
        glLineWidth(2.0f);
        glDrawArrays(GL_LINES, 0, 4);

        glLineWidth(1.0f);
        glUniform4fv(colorUniform, 1, vmath::vec4(0.0, 0.0, 1.0, 1.0));
        glDrawArrays(GL_LINES, 4, graph_vertices.size());

}

-(void)display
{
    //code
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shaderProgramObject);

    //X-formation
    mat4 modelViewMatrix = vmath::translate(0.0f, 0.0f, -4.0f);
    mat4 modelViewProjectionMatrix = perspectiveProjectionMatrix * modelViewMatrix;

    //Push above MVP info vertex shader's mvpUniform
    glUniformMatrix4fv(mvpMatrixUniform, 1, GL_FALSE, modelViewProjectionMatrix);

    switch (c)
        {
        case 'g':
            //for graph----------------------
                [self graphPaper];
            break;
        case 'c':
                [self graphPaper];
            //Circle------------
            glLineWidth(1.5f);
            glBindVertexArray(vao_circle);
            glUniform4fv(colorUniform, 1, vmath::vec4(0.0, 1.0, 0.0, 1.0));
            glDrawArrays(GL_LINE_LOOP, 0, circle_vertices.size());
            
            break;
        case 't':
                [self graphPaper];
            //Triangle------------
            glLineWidth(1.5f);
            glBindVertexArray(vao_triangle);
            glUniform4fv(colorUniform, 1, vmath::vec4(1.0, 0.0, 1.0, 1.0));
            glDrawArrays(GL_LINES, 0, triangle_vertices.size());

            break;
        case 's':
                [self graphPaper];
            //Square------------
            glLineWidth(1.5f);
            glBindVertexArray(vao_square);
            glUniform4fv(colorUniform, 1, vmath::vec4(1.0, 1.0, 0.0, 1.0));
            glDrawArrays(GL_LINES, 0, square_vertices.size());

            break;

        }
        
        
    glBindVertexArray(VAO);

    
    glBindVertexArray(0);
    glUseProgram(0);

}

-(void)myUpdate//our update, as mac has update function
{

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
    if (VBO_positions)
    {
        glDeleteBuffers(1, &VBO_positions);
        VBO_positions = 0;
    }

    //delete VAO
    if (VAO)
    {
        glDeleteVertexArrays(1, &VAO);
        VAO = 0;
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
        case 'g':
        case 'G':
            c = 'g';
            break;
        case 'c':
        case 'C':
            c = 'c';
            break;
        case 'T':
        case 't':
            c = 't';
            break;
        case 'S':
        case 's':
            c = 's';
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
