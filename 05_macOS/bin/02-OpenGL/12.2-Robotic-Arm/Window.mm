#include<Foundation/Foundation.h>
#import<Cocoa/Cocoa.h>
#import <QuartzCore/CVDisplayLink.h>    //CV core video
#import <OpenGL/gl3.h>                  //gl.h
#import <OpenGL/gl3ext.h>
#import "Sphere.h"
#include <stack>
#import "vmath.h" //#import also work
using namespace vmath;

#define WIDTH 800
#define HEIGHT 600


enum
{
    AMC_ATTRIBUTE_POSITION = 0,
    AMC_ATTRIBUTE_NORMAL = 1

};

GLfloat lightDiffuse[]={0.905,0.678,0.5254,1.0f};
GLfloat materialDiffuse[] = { 0.8f, 0.8f , 0.8f, 1.0f };
GLfloat lightPosition[]={0.0f, 0.0f, 2.0f, 1.0f};


float sphere_vertices[1146];
float sphere_normals[1146];
float sphere_textures[764];
unsigned short sphere_elements[2280];

GLuint gNumVertices;
GLuint gNumElements;

std::stack<vmath::mat4> ModelStack;
static int shoulder = 0, elbow = 0, wrist = 0;


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

    GLuint VAO_sphere;
    GLuint VBO_sphere_position;
    GLuint VBO_sphere_normal;
    GLuint VBO_sphere_element;
    
    GLuint modelViewMatrixUniform;
    GLuint viewMatrixUniform;
    GLuint projectionMatrixUniform;
    GLuint ldUniform;
    GLuint kdUniform;
    GLuint lightPositionUniform;
    GLuint keyPressUniform;

    mat4 perspectiveProjectionMatrix;  //in vmath

    
    GLfloat pAngle;
    GLfloat bLightingEnable;
    
    


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
        "in vec3 aNormal;" \
        "uniform mat4 uModelViewMatrix;" \
        "uniform mat4 uProjectionMatrix;" \
        "uniform vec3 uLd;" \
        "uniform vec3 uKd;" \
        "uniform vec4 uLightPosition;" \
        "uniform int uKeyPress;" \
        "out vec3 oDiffuseLight;" \
        "void main(void)" \
        "{" \
        "if(uKeyPress == 1)"
        "{"
        "vec4 iPosition = uModelViewMatrix * aPosition;"
        "mat3 normalMatrix = mat3(transpose(inverse(uModelViewMatrix)));"
        "vec3 n = normalize(normalMatrix * aNormal);"
        "vec3 s = normalize(vec3(uLightPosition - iPosition));"
        "oDiffuseLight = uLd * uKd * max(dot(s, n),0);"
        "}"
        "else"
        "{"
        "oDiffuseLight = vec3(0.0, 0.0, 0.0);"
        "}"
        "gl_Position = uProjectionMatrix * uModelViewMatrix * aPosition;"
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
        "in vec3 oDiffuseLight;" \
        "uniform int uKeyPress;" \
        "out vec4 FragColor;" \
        "void main(void)" \
        "{" \
        "if(uKeyPress == 1)"
        "{"
        "FragColor = vec4(oDiffuseLight, 1.0);"
        "}"
        "else"
        "{"
        "FragColor = vec4(1.0, 1.0, 1.0, 1.0);"
        "}"
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
    glBindAttribLocation(shaderProgramObject, AMC_ATTRIBUTE_NORMAL, "aNormal");
        

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
    modelViewMatrixUniform = glGetUniformLocation(shaderProgramObject, "uModelViewMatrix");
    projectionMatrixUniform = glGetUniformLocation(shaderProgramObject, "uProjectionMatrix");
    ldUniform = glGetUniformLocation(shaderProgramObject, "uLd");
    kdUniform = glGetUniformLocation(shaderProgramObject, "uKd");
    lightPositionUniform = glGetUniformLocation(shaderProgramObject, "uLightPosition");
    keyPressUniform = glGetUniformLocation(shaderProgramObject, "uKeyPress");


    getSphereVertexData(sphere_vertices, sphere_normals, sphere_textures, sphere_elements);
        gNumVertices = getNumberOfSphereVertices();
        gNumElements = getNumberOfSphereElements();
    /*
    [self getSphereVertexData:sphere_vertices:sphere_normals:sphere_textures:sphere_elements];
    gNumVertices = [self getNumberOfSphereVertices];
    gNumElements = [self getNumberOfSphereElements];
 */


    //VAO_sphere - vertex array object
    glGenVertexArrays(1, &VAO_sphere);
    glBindVertexArray(VAO_sphere);

    //VBO for position - vertex buffer object
    glGenBuffers(1, &VBO_sphere_position);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_sphere_position);
    glBufferData(GL_ARRAY_BUFFER, sizeof(sphere_vertices), sphere_vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(AMC_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(AMC_ATTRIBUTE_POSITION);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //VBO for normals
        glGenBuffers(1, &VBO_sphere_normal);
        glBindBuffer(GL_ARRAY_BUFFER, VBO_sphere_normal);
        glBufferData(GL_ARRAY_BUFFER, sizeof(sphere_normals), sphere_normals, GL_STATIC_DRAW);
        glVertexAttribPointer(AMC_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        glEnableVertexAttribArray(AMC_ATTRIBUTE_NORMAL);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

    
    // element vbo
        glGenBuffers(1, &VBO_sphere_element);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO_sphere_element);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(sphere_elements), sphere_elements, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    
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
    std::stack<vmath::mat4> modelMatrixStack;
        
    //code
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shaderProgramObject);

    mat4 viewMatrix = mat4::identity();

        vmath::mat4 modelMatrix = vmath::mat4::identity();
        modelMatrixStack.push(modelMatrix);

        modelMatrix = modelMatrixStack.top();
        modelMatrixStack.pop();
        modelMatrix = modelMatrix * vmath::translate(0.0f, 0.0f, -10.0f);

        modelMatrixStack.push(modelMatrix);

        modelMatrix = modelMatrix *
                        vmath::rotate((float)shoulder,0.0f, 0.0f, 1.0f) *
                        vmath::rotate((float)shoulder, 0.0f, 0.0f, 1.0f) *
                        vmath::translate(1.0f, 0.0f, 0.0f);

        modelMatrixStack.push(modelMatrix);

        modelMatrix = modelMatrix * vmath::scale(2.0f, 0.5f, 1.0f);

        //modelViewProjectionMatrix = perspectiveProjetionMatrix * modelViewMatrix;

        glUniformMatrix4fv(modelViewMatrixUniform, 1, GL_FALSE, modelMatrix);
        glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, viewMatrix);
        glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, perspectiveProjectionMatrix);

        //ARM---------------
        
        glUniform1i(keyPressUniform, 1);
        glUniform3fv(ldUniform, 1, lightDiffuse);
        glUniform3fv(kdUniform, 1, materialDiffuse);
        glUniform4fv(lightPositionUniform, 1, lightPosition);


        // *** bind vao ***
        glBindVertexArray(VAO_sphere);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO_sphere_element);
        glDrawElements(GL_TRIANGLES, gNumElements, GL_UNSIGNED_SHORT, 0);
        glBindVertexArray(0);

        modelMatrix = modelMatrixStack.top();
        modelMatrixStack.pop();

        modelMatrix = modelMatrix * vmath::translate(1.0f, 0.0f, 0.0f) *
            vmath::rotate((float)elbow, 0.0f, 0.0f, 1.0f) *
            vmath::translate(1.0f, 0.0f, 0.0f);

        modelMatrixStack.push(modelMatrix);

        modelMatrix = modelMatrix * vmath::scale(2.0f, 0.5f, 1.0f);
        glUniformMatrix4fv(modelViewMatrixUniform, 1, GL_FALSE, modelMatrix);

        
        
        //Elbow------------------------

        glBindVertexArray(VAO_sphere);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO_sphere_element);
        glDrawElements(GL_TRIANGLES, gNumElements, GL_UNSIGNED_SHORT, 0);
        glBindVertexArray(0);

        modelMatrix = modelMatrixStack.top();
        modelMatrixStack.pop();

        modelMatrix = modelMatrix * vmath::translate(1.0f, 0.0f, 0.0f) *
            vmath::rotate((float)wrist, 0.0f, 0.0f, 1.0f) *
            vmath::translate(0.4f, 0.0f, 0.0f);
                      
        modelMatrixStack.push(modelMatrix);

        modelMatrix = modelMatrix * vmath::scale(0.7f, 0.2f, 0.7f);
        glUniformMatrix4fv(modelViewMatrixUniform, 1, GL_FALSE, modelMatrix);

        
        //Wrist-------------------

        glBindVertexArray(VAO_sphere);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO_sphere_element);
        glDrawElements(GL_TRIANGLES, gNumElements, GL_UNSIGNED_SHORT, 0);
        glBindVertexArray(0);

        modelMatrix = modelMatrixStack.top();

        modelMatrix = modelMatrix * vmath::translate(0.45f, 0.0f, 0.15f);

        modelMatrixStack.push(modelMatrix);
        

    glBindVertexArray(0);
    glUseProgram(0);

}

-(void)myUpdate//our update, as mac has update function
{
    pAngle += 0.8f;
        if (pAngle >= 360.0f)
        {
            pAngle = pAngle - 360.0f;
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
    if (VBO_sphere_position)
    {
        glDeleteBuffers(1, &VBO_sphere_position);
        VBO_sphere_position = 0;
    }

    //delete VAO_sphere
    if (VAO_sphere)
    {
        glDeleteVertexArrays(1, &VAO_sphere);
        VAO_sphere = 0;
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
        case 'L':
        case 'l':
            if (bLightingEnable == FALSE)
                bLightingEnable = TRUE;
            else
                bLightingEnable = FALSE;
            break;
        case 'S':
            shoulder = (shoulder + 3) % 360;
            break;
        case 's':
            shoulder = (shoulder - 3) % 360;
            break;
        case 'E':
            elbow = (elbow + 3) % 360;
            break;
        case 'e':
            elbow = (elbow - 3) % 360;
            break;
        case 'W':
            wrist = (wrist + 3) % 360;
            break;
        case 'w':
            wrist = (wrist - 3) % 360;
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
