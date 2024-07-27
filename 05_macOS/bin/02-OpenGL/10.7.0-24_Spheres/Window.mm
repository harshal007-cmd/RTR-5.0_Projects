#include<Foundation/Foundation.h>
#import<Cocoa/Cocoa.h>
#import <QuartzCore/CVDisplayLink.h>    //CV core video
#import <OpenGL/gl3.h>                  //gl.h
#import <OpenGL/gl3ext.h>
#import "Sphere.h"

#import "vmath.h" //#import also work
using namespace vmath;

#define WIDTH 800
#define HEIGHT 600


enum
{
    AMC_ATTRIBUTE_POSITION = 0,
    AMC_ATTRIBUTE_NORMAL = 1

};

//For light
GLfloat lightAmbient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
GLfloat lightDiffuse[] = { 1.0f, 1.0f , 1.0f, 1.0f };
GLfloat lightSpecular[] = { 0.8f, 0.8f ,0.8f ,1.0f };
GLfloat lightPosition[4];

GLfloat materialAmbient[3];
GLfloat materialDiffuse[3];
GLfloat materialSpecular[3];
GLfloat materialShiness = 128.0f;


float sphere_vertices[1146];
float sphere_normals[1146];
float sphere_textures[764];
unsigned short sphere_elements[2280];

GLuint gNumVertices;
GLuint gNumElements;


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

    GLuint lightDiffuseUniform;
    GLuint lightAmbientUniform;
    GLuint lightSpecularUniform;
    GLuint lightPositionUniform;

    GLuint materialDiffuseUniform;
    GLuint materialAmbientUniform;
    GLuint materialSpecularUniform;
    GLuint materialShininessUniform;
    GLuint keyPressUniform;

    mat4 perspectiveProjectionMatrix;  //in vmath

    
    GLfloat lAngle;
    GLfloat bLightingEnable;
    
    BOOL x,y,z;
    
    


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
        "uniform mat4 uViewMatrix;" \
        "uniform mat4 uProjectionMatrix;" \
        "uniform vec4 uLightPosition;" \
        "\n"\
        "uniform int uKeyPress;" \
        "out vec3 oTransformedNormals;"\
        "out vec3 oLightDirection;"\
        "out vec3 oViewerVector;"\
        "void main(void)" \
        "{" \
        "if(uKeyPress == 1)"
        "{"
        "vec4 iCoordinates = uViewMatrix * uModelViewMatrix * aPosition;"
        "oTransformedNormals = mat3(uViewMatrix * uModelViewMatrix) * aNormal;"
        "oLightDirection = vec3(uLightPosition - iCoordinates);"
        "oViewerVector = -iCoordinates.xyz;"
        "}"
        "else"
        "{"
            "oTransformedNormals = vec3(0.0, 0.0, 0.0);"
            "oLightDirection = vec3(0.0, 0.0, 0.0);"
            "oViewerVector = vec3(0.0, 0.0, 0.0);"
        "}"
        "gl_Position = uProjectionMatrix * uViewMatrix * uModelViewMatrix * aPosition;"
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
        "in vec3 oTransformedNormals;"\
        "in vec3 oLightDirection;" \
        "in vec3 oViewerVector; "
        "uniform vec3 uLightAmbient;" \
        "uniform vec3 uLightDiffuse;" \
        "uniform vec3 uLightSpecular;" \
        "\n"\
        "uniform vec3 uMaterialAmbient;" \
        "uniform vec3 umaterialDiffuse;" \
        "uniform vec3 uMaterialSpecular;" \
        "uniform float uMaterialShininess;" \
        "uniform int uKeyPress;" \
        "out vec4 FragColor;" \
        "void main(void)" \
        "{" \
        "vec3 phongADSLight;"
        "if(uKeyPress == 1)"
        "{"
        "    vec3 normalizedTransformedNormal = normalize(oTransformedNormals);"
        "    vec3 normalizedLightDirection = normalize(oLightDirection);"
        "    vec3 normalizedViewerVector = normalize(oViewerVector);"
        "    vec3 ambientLight = uLightAmbient * uMaterialAmbient;"
        "    vec3 diffuseLight = uLightDiffuse * umaterialDiffuse * max(dot(normalizedLightDirection, normalizedTransformedNormal), 0.0);"
        "    vec3 reflectionVector = reflect(-normalizedLightDirection, normalizedTransformedNormal);"
        "    vec3 lightSpecular = uLightSpecular * uMaterialSpecular * pow(max(dot(reflectionVector, normalizedViewerVector), 0.0), uMaterialShininess);"
        "    phongADSLight = ambientLight + diffuseLight + lightSpecular;"
        "}"
        "else"
        "{"
        "    phongADSLight = vec3(1.0, 1.0, 1.0);"
        "}"
        "    FragColor = vec4(phongADSLight, 1.0);"
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
        viewMatrixUniform = glGetUniformLocation(shaderProgramObject, "uViewMatrix");
        projectionMatrixUniform = glGetUniformLocation(shaderProgramObject, "uProjectionMatrix");
        
        lightAmbientUniform = glGetUniformLocation(shaderProgramObject, "uLightAmbient");
        lightDiffuseUniform = glGetUniformLocation(shaderProgramObject, "uLightDiffuse");
        lightSpecularUniform = glGetUniformLocation(shaderProgramObject, "uLightSpecular");
        lightPositionUniform = glGetUniformLocation(shaderProgramObject, "uLightPosition");

        materialAmbientUniform = glGetUniformLocation(shaderProgramObject, "uMaterialAmbienr");
        materialDiffuseUniform = glGetUniformLocation(shaderProgramObject, "umaterialDiffuse");
        materialSpecularUniform = glGetUniformLocation(shaderProgramObject, "uMaterialSpecular");
        materialShininessUniform = glGetUniformLocation(shaderProgramObject, "uMaterialShininess");

        keyPressUniform = glGetUniformLocation(shaderProgramObject, "uKeyPress");


    getSphereVertexData(sphere_vertices, sphere_normals, sphere_textures, sphere_elements);
        //gNumVertices = getNumberOfSphereVertices();
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
    //code
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shaderProgramObject);
    const float factor = 20.0;
    
    //X-formation
    
    
        if (bLightingEnable == TRUE)
        {
            glUniform1i(keyPressUniform, 1);
            glUniform3fv(lightDiffuseUniform, 1, lightDiffuse);
            glUniform3fv(lightAmbientUniform, 1, lightAmbient);
            glUniform3fv(lightSpecularUniform, 1, lightSpecular);
           
            if(x == TRUE)
            {
                lightPosition[0] = 0.0f;
                lightPosition[1] = factor * sin(lAngle);
                lightPosition[2] = factor * cos(lAngle);
                lightPosition[3] = 1.0f;
            }
            else if(y == TRUE)
            {
                lightPosition[0] =  factor * sin(lAngle);
                lightPosition[1] =  0.0f;
                lightPosition[2] =  factor * cos(lAngle);
                lightPosition[3] =  1.0f;
            }
            else if(z == TRUE)
            {
                lightPosition[0] =  factor * sin(lAngle);
                lightPosition[1] =  factor * cos(lAngle);
                lightPosition[2] =  0.0f;
                lightPosition[3] =  1.0f;

            }
            glUniform4fv(lightPositionUniform, 1, (GLfloat*)lightPosition);

        }
        else
        {
            glUniform1i(keyPressUniform, 0);
        }

    
        //1st sphere
    mat4 modelViewMatrix = mat4::identity();
    mat4 viewMatrix = vmath::mat4::identity();
    mat4 translationMatrix = mat4::identity();
    mat4 projectionMatrix = mat4::identity();
    
//    mat4 perspectiveProjectionMatrix = vmath::mat4::identity();

    translationMatrix = vmath::translate(-4.0f, 3.5f, -12.0f);
    mat4 modelMatrix = mat4::identity();
    modelMatrix = translationMatrix;

        //Push above MVP info vertex shader's mvpUniform
        glUniformMatrix4fv(modelViewMatrixUniform, 1, GL_FALSE, modelMatrix);
        glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, viewMatrix);
        glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, perspectiveProjectionMatrix);

        materialAmbient[0] = 1.0215f;
        materialAmbient[1] = 0.1745f;
        materialAmbient[2] = 0.0215f;
        glUniform3fv(materialDiffuseUniform, 1, (GLfloat*)materialAmbient);

        materialDiffuse[0] = 1.07568f;
        materialDiffuse[1] = 0.61424f;
        materialDiffuse[2] = 0.07568f;
        glUniform3fv(materialAmbientUniform, 1, (GLfloat*)materialDiffuse);

        materialSpecular[0] = 0.633f;
        materialSpecular[1] = 0.727811f;
        materialSpecular[2] = 0.633f;
        glUniform3fv(materialSpecularUniform, 1, (GLfloat*)materialSpecular);

        materialShiness = 0.6 * 128;
        glUniform1f(materialShininessUniform, materialShiness);

        // *** bind vao ***
        glBindVertexArray(VAO_sphere);

        // *** draw, either by glDrawTriangles() or glDrawArrays() or glDrawElements()
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO_sphere_element);
        glDrawElements(GL_TRIANGLES, gNumElements, GL_UNSIGNED_SHORT, 0);

    glBindVertexArray(0);
    
    
    //2nd sphere
        modelMatrix = vmath::mat4::identity();    //model matrix
        viewMatrix = vmath::mat4::identity();
        projectionMatrix = vmath::mat4::identity();    //projection matrix
        translationMatrix = vmath::mat4::identity();    //translate matrix
        
        
        translationMatrix = vmath::translate(-4.0f, 2.0f, -12.0f);

        
        modelMatrix = translationMatrix;

        
        projectionMatrix = perspectiveProjectionMatrix;

        glUniformMatrix4fv(modelViewMatrixUniform, 1, GL_FALSE, modelMatrix);
        glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, viewMatrix);
        glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, projectionMatrix);

        //jade material
        materialAmbient[0] = 0.135f;
        materialAmbient[1] = 0.2225f;
        materialAmbient[2] = 0.1575f;
        glUniform3fv(materialAmbientUniform, 1, (GLfloat*)materialAmbient);

        materialDiffuse[0] = 0.54f;
        materialDiffuse[1] = 0.89f;
        materialDiffuse[2] = 0.63f;
        glUniform3fv(materialDiffuseUniform, 1, (GLfloat*)materialDiffuse);

        materialSpecular[0] = 0.316228f;
        materialSpecular[1] = 0.316228f;
        materialSpecular[2] = 0.316228f;
        glUniform3fv(materialSpecularUniform, 1, (GLfloat*)materialSpecular);

        materialShiness = 0.1 * 128;
        glUniform1f(materialShininessUniform, materialShiness);


        //** bind vao **
        glBindVertexArray(VAO_sphere);

            //** draw either by glDrawTriangles() or glDrawArrays() or glDrawElements()
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO_sphere_element);
            glDrawElements(GL_TRIANGLES, gNumElements, GL_UNSIGNED_SHORT, 0);    //3 (each with its x,y,z) vertices in triangle vertices array

        //** unbind vao **
        glBindVertexArray(0);

        //3rd Sphere

        modelMatrix = vmath::mat4::identity();    //model matrix
        viewMatrix = vmath::mat4::identity();
        projectionMatrix = vmath::mat4::identity();    //projection matrix
        translationMatrix = vmath::mat4::identity();    //translate matrix
        
        
        translationMatrix = vmath::translate(-4.0f, 0.50f, -12.0f);

        
        modelMatrix = translationMatrix;

        
        projectionMatrix = perspectiveProjectionMatrix;

        glUniformMatrix4fv(modelViewMatrixUniform, 1, GL_FALSE, modelMatrix);
        glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, viewMatrix);
        glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, projectionMatrix);

        ////obsidian material
        materialAmbient[0] = 0.05375;
        materialAmbient[1] = 0.05;
        materialAmbient[2] = 0.06625;
        glUniform3fv(materialAmbientUniform, 1, (GLfloat*)materialAmbient);

        materialDiffuse[0] = 0.18275;
        materialDiffuse[1] = 0.17;
        materialDiffuse[2] = 0.22525;
        glUniform3fv(materialDiffuseUniform, 1, (GLfloat*)materialDiffuse);

        materialSpecular[0] = 0.332741;
        materialSpecular[1] = 0.328634;
        materialSpecular[2] = 0.346435;
        glUniform3fv(materialSpecularUniform, 1, (GLfloat*)materialSpecular);

        materialShiness = 0.3 * 128;
        glUniform1f(materialShininessUniform, materialShiness);


        //** bind vao **
        glBindVertexArray(VAO_sphere);

        //** draw either by glDrawTriangles() or glDrawArrays() or glDrawElements()
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO_sphere_element);
        glDrawElements(GL_TRIANGLES, gNumElements, GL_UNSIGNED_SHORT, 0);    //3 (each with its x,y,z) vertices in triangle vertices array

        //** unbind vao **
        glBindVertexArray(0);


        //4th Sphere


        modelMatrix = vmath::mat4::identity();    //model matrix
        viewMatrix = vmath::mat4::identity();
        projectionMatrix = vmath::mat4::identity();    //projection matrix
        translationMatrix = vmath::mat4::identity();    //translate matrix
        
        
        translationMatrix = vmath::translate(-4.0f, -1.0f, -12.0f);

        
        modelMatrix = translationMatrix;

        
        projectionMatrix = perspectiveProjectionMatrix;

        glUniformMatrix4fv(modelViewMatrixUniform, 1, GL_FALSE, modelMatrix);
        glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, viewMatrix);
        glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, projectionMatrix);

        //Peral material
        materialAmbient[0] = 0.25;
        materialAmbient[1] = 0.20725;
        materialAmbient[2] = 0.20725;
        glUniform3fv(materialAmbientUniform, 1, (GLfloat*)materialAmbient);


        materialDiffuse[0] = 1.0;
        materialDiffuse[1] = 0.829;
        materialDiffuse[2] = 0.829;
        glUniform3fv(materialDiffuseUniform, 1, (GLfloat*)materialDiffuse);

        materialSpecular[0] = 0.296648;
        materialSpecular[1] = 0.296648;
        materialSpecular[2] = 0.296648;
        glUniform3fv(materialSpecularUniform, 1, (GLfloat*)materialSpecular);

        materialShiness = 0.088 * 128;
        glUniform1f(materialShininessUniform, materialShiness);


        //** bind vao **
        glBindVertexArray(VAO_sphere);

        //** draw either by glDrawTriangles() or glDrawArrays() or glDrawElements()
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO_sphere_element);
        glDrawElements(GL_TRIANGLES, gNumElements, GL_UNSIGNED_SHORT, 0);    //3 (each with its x,y,z) vertices in triangle vertices array

        //** unbind vao **
        glBindVertexArray(0);


        //5th Sphere


        modelMatrix = vmath::mat4::identity();    //model matrix
        viewMatrix = vmath::mat4::identity();
        projectionMatrix = vmath::mat4::identity();    //projection matrix
        translationMatrix = vmath::mat4::identity();    //translate matrix
        
        
        translationMatrix = vmath::translate(-4.0f, -2.50f, -12.0f);

        
        modelMatrix = translationMatrix;

        
        projectionMatrix = perspectiveProjectionMatrix;

        glUniformMatrix4fv(modelViewMatrixUniform, 1, GL_FALSE, modelMatrix);
        glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, viewMatrix);
        glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, projectionMatrix);

        ////ruby
        materialAmbient[0] = 0.1745;
        materialAmbient[1] = 0.01175;
        materialAmbient[2] = 0.01175;
        glUniform3fv(materialAmbientUniform, 1, (GLfloat*)materialAmbient);

        materialDiffuse[0] = 0.61424;
        materialDiffuse[1] = 0.04136;
        materialDiffuse[2] = 0.04136;
        glUniform3fv(materialDiffuseUniform, 1, (GLfloat*)materialDiffuse);

        materialSpecular[0] = 0.727811;
        materialSpecular[1] = 0.626959;
        materialSpecular[2] = 0.626959;
        glUniform3fv(materialSpecularUniform, 1, (GLfloat*)materialSpecular);

        materialShiness = 0.6 * 128;
        glUniform1f(materialShininessUniform, materialShiness);


        //** bind vao **
        glBindVertexArray(VAO_sphere);

        //** draw either by glDrawTriangles() or glDrawArrays() or glDrawElements()
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO_sphere_element);
        glDrawElements(GL_TRIANGLES, gNumElements, GL_UNSIGNED_SHORT, 0);    //3 (each with its x,y,z) vertices in triangle vertices array

        //** unbind vao **
        glBindVertexArray(0);



        //6th Sphere


        modelMatrix = vmath::mat4::identity();    //model matrix
        viewMatrix = vmath::mat4::identity();
        projectionMatrix = vmath::mat4::identity();    //projection matrix
        translationMatrix = vmath::mat4::identity();    //translate matrix
        
        
        translationMatrix = vmath::translate(-4.0f, -4.0f, -12.0f);

        
        modelMatrix = translationMatrix;

        
        projectionMatrix = perspectiveProjectionMatrix;

        glUniformMatrix4fv(modelViewMatrixUniform, 1, GL_FALSE, modelMatrix);
        glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, viewMatrix);
        glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, projectionMatrix);

        //turquoise
        materialAmbient[0] = 0.1;
        materialAmbient[1] = 0.18725;
        materialAmbient[2] = 0.1745;
        glUniform3fv(materialAmbientUniform, 1, (GLfloat*)materialAmbient);

        materialDiffuse[0] = 0.396;
        materialDiffuse[1] = 0.74151;
        materialDiffuse[2] = 0.69102;
        glUniform3fv(materialDiffuseUniform, 1, (GLfloat*)materialDiffuse);

        materialSpecular[0] = 0.297254;
        materialSpecular[1] = 0.30829;
        materialSpecular[2] = 0.306678;
        glUniform3fv(materialSpecularUniform, 1, (GLfloat*)materialSpecular);

        materialShiness = 0.1 * 128;
        glUniform1f(materialShininessUniform, materialShiness);


        //** bind vao **
        glBindVertexArray(VAO_sphere);

        //** draw either by glDrawTriangles() or glDrawArrays() or glDrawElements()
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO_sphere_element);
        glDrawElements(GL_TRIANGLES, gNumElements, GL_UNSIGNED_SHORT, 0);    //3 (each with its x,y,z) vertices in triangle vertices array

        //** unbind vao **
        glBindVertexArray(0);


        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //
        //                                2nd Column
        //
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


        //OpenGL Drawing
        modelMatrix = vmath::mat4::identity();    //model matrix
        viewMatrix = vmath::mat4::identity();
        projectionMatrix = vmath::mat4::identity();    //projection matrix
        translationMatrix = vmath::mat4::identity();    //translate matrix
        
        
        translationMatrix = vmath::translate(-2.0f, 3.50f, -12.0f);

        
        modelMatrix = translationMatrix;

        
        projectionMatrix = perspectiveProjectionMatrix;

        glUniformMatrix4fv(modelViewMatrixUniform, 1, GL_FALSE, modelMatrix);
        glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, viewMatrix);
        glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, projectionMatrix);

        //brass
        materialAmbient[0] = 0.329412;
        materialAmbient[1] = 0.223529;
        materialAmbient[2] = 0.027451;
        glUniform3fv(materialAmbientUniform, 1, (GLfloat*)materialAmbient);

        materialDiffuse[0] = 0.780392;
        materialDiffuse[1] = 0.568627;
        materialDiffuse[2] = 0.113725;
        glUniform3fv(materialDiffuseUniform, 1, (GLfloat*)materialDiffuse);

        materialSpecular[0] = 0.992157;
        materialSpecular[1] = 0.941176;
        materialSpecular[2] = 0.807843;
        glUniform3fv(materialSpecularUniform, 1, (GLfloat*)materialSpecular);

        materialShiness = 0.21794872 * 128;
        glUniform1f(materialShininessUniform, materialShiness);


        //** bind vao **
        glBindVertexArray(VAO_sphere);

        //** draw either by glDrawTriangles() or glDrawArrays() or glDrawElements()
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO_sphere_element);
        glDrawElements(GL_TRIANGLES, gNumElements, GL_UNSIGNED_SHORT, 0);    //3 (each with its x,y,z) vertices in triangle vertices array

        //** unbind vao **
        glBindVertexArray(0);


        //2nd sphere
        modelMatrix = vmath::mat4::identity();    //model matrix
        viewMatrix = vmath::mat4::identity();
        projectionMatrix = vmath::mat4::identity();    //projection matrix
        translationMatrix = vmath::mat4::identity();    //translate matrix
        
        
        translationMatrix = vmath::translate(-2.0f, 2.0f, -12.0f);

        
        modelMatrix = translationMatrix;

        
        projectionMatrix = perspectiveProjectionMatrix;

        glUniformMatrix4fv(modelViewMatrixUniform, 1, GL_FALSE, modelMatrix);
        glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, viewMatrix);
        glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, projectionMatrix);

        //bronze
        materialAmbient[0] = 0.2125;
        materialAmbient[1] = 0.1275;
        materialAmbient[2] = 0.054;
        glUniform3fv(materialAmbientUniform, 1, (GLfloat*)materialAmbient);

        materialDiffuse[0] = 0.714;
        materialDiffuse[1] = 0.4284;
        materialDiffuse[2] = 0.18144;
        glUniform3fv(materialDiffuseUniform, 1, (GLfloat*)materialDiffuse);

        materialSpecular[0] = 0.393548;
        materialSpecular[1] = 0.271906;
        materialSpecular[2] = 0.166721;
        glUniform3fv(materialSpecularUniform, 1, (GLfloat*)materialSpecular);

        materialShiness = 0.2 * 128;
        glUniform1f(materialShininessUniform, materialShiness);


        //** bind vao **
        glBindVertexArray(VAO_sphere);

        //** draw either by glDrawTriangles() or glDrawArrays() or glDrawElements()
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO_sphere_element);
        glDrawElements(GL_TRIANGLES, gNumElements, GL_UNSIGNED_SHORT, 0);    //3 (each with its x,y,z) vertices in triangle vertices array

        //** unbind vao **
        glBindVertexArray(0);

        //3rd Sphere

        modelMatrix = vmath::mat4::identity();    //model matrix
        viewMatrix = vmath::mat4::identity();
        projectionMatrix = vmath::mat4::identity();    //projection matrix
        translationMatrix = vmath::mat4::identity();    //translate matrix
        
        
        translationMatrix = vmath::translate(-2.0f, 0.50f, -12.0f);

        
        modelMatrix = translationMatrix;

        
        projectionMatrix = perspectiveProjectionMatrix;

        glUniformMatrix4fv(modelViewMatrixUniform, 1, GL_FALSE, modelMatrix);
        glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, viewMatrix);
        glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, projectionMatrix);

        //chrome
        materialAmbient[0] = 0.25;
        materialAmbient[1] = 0.25;
        materialAmbient[2] = 0.25;
        glUniform3fv(materialAmbientUniform, 1, (GLfloat*)materialAmbient);

        materialDiffuse[0] = 0.4;
        materialDiffuse[1] = 0.4;
        materialDiffuse[2] = 0.4;
        glUniform3fv(materialDiffuseUniform, 1, (GLfloat*)materialDiffuse);

        materialSpecular[0] = 0.774597;
        materialSpecular[1] = 0.774597;
        materialSpecular[2] = 0.774597;
        glUniform3fv(materialSpecularUniform, 1, (GLfloat*)materialSpecular);

        materialShiness = 0.6 * 128;
        glUniform1f(materialShininessUniform, materialShiness);


        //** bind vao **
        glBindVertexArray(VAO_sphere);

        //** draw either by glDrawTriangles() or glDrawArrays() or glDrawElements()
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO_sphere_element);
        glDrawElements(GL_TRIANGLES, gNumElements, GL_UNSIGNED_SHORT, 0);    //3 (each with its x,y,z) vertices in triangle vertices array

        //** unbind vao **
        glBindVertexArray(0);


        //4th Sphere


        modelMatrix = vmath::mat4::identity();    //model matrix
        viewMatrix = vmath::mat4::identity();
        projectionMatrix = vmath::mat4::identity();    //projection matrix
        translationMatrix = vmath::mat4::identity();    //translate matrix
        
        
        translationMatrix = vmath::translate(-2.0f, -1.0f, -12.0f);

        
        modelMatrix = translationMatrix;

        
        projectionMatrix = perspectiveProjectionMatrix;

        glUniformMatrix4fv(modelViewMatrixUniform, 1, GL_FALSE, modelMatrix);
        glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, viewMatrix);
        glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, projectionMatrix);

        //copper
        materialAmbient[0] = 0.19125;
        materialAmbient[1] = 0.0735;
        materialAmbient[2] = 0.0225;
        glUniform3fv(materialAmbientUniform, 1, (GLfloat*)materialAmbient);

        materialDiffuse[0] = 0.7038;
        materialDiffuse[1] = 0.27048;
        materialDiffuse[2] = 0.0828;
        glUniform3fv(materialDiffuseUniform, 1, (GLfloat*)materialDiffuse);

        materialSpecular[0] = 0.256777;
        materialSpecular[1] = 0.137622;
        materialSpecular[2] = 0.086014;
        glUniform3fv(materialSpecularUniform, 1, (GLfloat*)materialSpecular);

        materialShiness = 0.1 * 128;
        glUniform1f(materialShininessUniform, materialShiness);


        //** bind vao **
        glBindVertexArray(VAO_sphere);

        //** draw either by glDrawTriangles() or glDrawArrays() or glDrawElements()
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO_sphere_element);
        glDrawElements(GL_TRIANGLES, gNumElements, GL_UNSIGNED_SHORT, 0);    //3 (each with its x,y,z) vertices in triangle vertices array

        //** unbind vao **
        glBindVertexArray(0);


        //5th Sphere


        modelMatrix = vmath::mat4::identity();    //model matrix
        viewMatrix = vmath::mat4::identity();
        projectionMatrix = vmath::mat4::identity();    //projection matrix
        translationMatrix = vmath::mat4::identity();    //translate matrix
        
        
        translationMatrix = vmath::translate(-2.0f, -2.50f, -12.0f);

        
        modelMatrix = translationMatrix;

        
        projectionMatrix = perspectiveProjectionMatrix;

        glUniformMatrix4fv(modelViewMatrixUniform, 1, GL_FALSE, modelMatrix);
        glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, viewMatrix);
        glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, projectionMatrix);

        //gold
        materialAmbient[0] = 0.24725;
        materialAmbient[1] = 0.1995;
        materialAmbient[2] = 0.0745;
        glUniform3fv(materialAmbientUniform, 1, (GLfloat*)materialAmbient);

        materialDiffuse[0] = 0.75164;
        materialDiffuse[1] = 0.60648;
        materialDiffuse[2] = 0.22648;
        glUniform3fv(materialDiffuseUniform, 1, (GLfloat*)materialDiffuse);

        materialSpecular[0] = 0.628281;
        materialSpecular[1] = 0.555802;
        materialSpecular[2] = 0.366065;
        glUniform3fv(materialSpecularUniform, 1, (GLfloat*)materialSpecular);

        materialShiness = 0.4 * 128;
        glUniform1f(materialShininessUniform, materialShiness);


        //** bind vao **
        glBindVertexArray(VAO_sphere);

        //** draw either by glDrawTriangles() or glDrawArrays() or glDrawElements()
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO_sphere_element);
        glDrawElements(GL_TRIANGLES, gNumElements, GL_UNSIGNED_SHORT, 0);    //3 (each with its x,y,z) vertices in triangle vertices array

        //** unbind vao **
        glBindVertexArray(0);



        //6th Sphere


        modelMatrix = vmath::mat4::identity();    //model matrix
        viewMatrix = vmath::mat4::identity();
        projectionMatrix = vmath::mat4::identity();    //projection matrix
        translationMatrix = vmath::mat4::identity();    //translate matrix
        
        
        translationMatrix = vmath::translate(-2.0f, -4.0f, -12.0f);

        
        modelMatrix = translationMatrix;

        
        projectionMatrix = perspectiveProjectionMatrix;

        glUniformMatrix4fv(modelViewMatrixUniform, 1, GL_FALSE, modelMatrix);
        glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, viewMatrix);
        glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, projectionMatrix);

        //silver
        materialAmbient[0] = 0.19225;
        materialAmbient[1] = 0.19225;
        materialAmbient[2] = 0.19225;
        glUniform3fv(materialAmbientUniform, 1, (GLfloat*)materialAmbient);

        materialDiffuse[0] = 0.50754;
        materialDiffuse[1] = 0.50754;
        materialDiffuse[2] = 0.50754;
        glUniform3fv(materialDiffuseUniform, 1, (GLfloat*)materialDiffuse);

        materialSpecular[0] = 0.508273;
        materialSpecular[1] = 0.508273;
        materialSpecular[2] = 0.508273;
        glUniform3fv(materialSpecularUniform, 1, (GLfloat*)materialSpecular);

        materialShiness = 0.4 * 128;
        glUniform1f(materialShininessUniform, materialShiness);


        //** bind vao **
        glBindVertexArray(VAO_sphere);

        //** draw either by glDrawTriangles() or glDrawArrays() or glDrawElements()
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO_sphere_element);
        glDrawElements(GL_TRIANGLES, gNumElements, GL_UNSIGNED_SHORT, 0);    //3 (each with its x,y,z) vertices in triangle vertices array

        //** unbind vao **
        glBindVertexArray(0);



        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //
        //                                3rd Column
        //
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


        //OpenGL Drawing
        modelMatrix = vmath::mat4::identity();    //model matrix
        viewMatrix = vmath::mat4::identity();
        projectionMatrix = vmath::mat4::identity();    //projection matrix
        translationMatrix = vmath::mat4::identity();    //translate matrix
        
        
        translationMatrix = vmath::translate(0.0f, 3.50f, -12.0f);

        
        modelMatrix = translationMatrix;

        
        projectionMatrix = perspectiveProjectionMatrix;

        glUniformMatrix4fv(modelViewMatrixUniform, 1, GL_FALSE, modelMatrix);
        glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, viewMatrix);
        glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, projectionMatrix);


        materialAmbient[0] = 0.0;
        materialAmbient[1] = 0.0;
        materialAmbient[2] = 0.0;
        glUniform3fv(materialAmbientUniform, 1, (GLfloat*)materialAmbient);

        materialDiffuse[0] = 0.01;
        materialDiffuse[1] = 0.01;
        materialDiffuse[2] = 0.01;
        glUniform3fv(materialDiffuseUniform, 1, (GLfloat*)materialDiffuse);

        materialSpecular[0] = 0.50;
        materialSpecular[1] = 0.50;
        materialSpecular[2] = 0.50;
        glUniform3fv(materialSpecularUniform, 1, (GLfloat*)materialSpecular);

        materialShiness = 0.25 * 128;
        glUniform1f(materialShininessUniform, materialShiness);


        //** bind vao **
        glBindVertexArray(VAO_sphere);

        //** draw either by glDrawTriangles() or glDrawArrays() or glDrawElements()
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO_sphere_element);
        glDrawElements(GL_TRIANGLES, gNumElements, GL_UNSIGNED_SHORT, 0);    //3 (each with its x,y,z) vertices in triangle vertices array

        //** unbind vao **
        glBindVertexArray(0);


        //2nd sphere
        modelMatrix = vmath::mat4::identity();    //model matrix
        viewMatrix = vmath::mat4::identity();
        projectionMatrix = vmath::mat4::identity();    //projection matrix
        translationMatrix = vmath::mat4::identity();    //translate matrix
        
        
        translationMatrix = vmath::translate(0.0f, 2.0f, -12.0f);

        
        modelMatrix = translationMatrix;

        
        projectionMatrix = perspectiveProjectionMatrix;

        glUniformMatrix4fv(modelViewMatrixUniform, 1, GL_FALSE, modelMatrix);
        glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, viewMatrix);
        glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, projectionMatrix);

        //cyan
        materialAmbient[0] = 0.0;
        materialAmbient[1] = 0.1;
        materialAmbient[2] = 0.06;
        glUniform3fv(materialAmbientUniform, 1, (GLfloat*)materialAmbient);

        materialDiffuse[0] = 0.0;
        materialDiffuse[1] = 0.50980392;
        materialDiffuse[2] = 0.50980392;
        glUniform3fv(materialDiffuseUniform, 1, (GLfloat*)materialDiffuse);

        materialSpecular[0] = 0.50196078;
        materialSpecular[1] = 0.50196078;
        materialSpecular[2] = 0.50196078;
        glUniform3fv(materialSpecularUniform, 1, (GLfloat*)materialSpecular);

        materialShiness = 0.25 * 128;
        glUniform1f(materialShininessUniform, materialShiness);


        //** bind vao **
        glBindVertexArray(VAO_sphere);

        //** draw either by glDrawTriangles() or glDrawArrays() or glDrawElements()
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO_sphere_element);
        glDrawElements(GL_TRIANGLES, gNumElements, GL_UNSIGNED_SHORT, 0);    //3 (each with its x,y,z) vertices in triangle vertices array

        //** unbind vao **
        glBindVertexArray(0);

        //3rd Sphere

        modelMatrix = vmath::mat4::identity();    //model matrix
        viewMatrix = vmath::mat4::identity();
        projectionMatrix = vmath::mat4::identity();    //projection matrix
        translationMatrix = vmath::mat4::identity();    //translate matrix
        
        
        translationMatrix = vmath::translate(0.0f, 0.50f, -12.0f);

        
        modelMatrix = translationMatrix;

        
        projectionMatrix = perspectiveProjectionMatrix;

        glUniformMatrix4fv(modelViewMatrixUniform, 1, GL_FALSE, modelMatrix);
        glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, viewMatrix);
        glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, projectionMatrix);

        materialAmbient[0] = 0.0;
        materialAmbient[1] = 0.0;
        materialAmbient[2] = 0.0;
        glUniform3fv(materialAmbientUniform, 1, (GLfloat*)materialAmbient);

        materialDiffuse[0] = 0.1;
        materialDiffuse[1] = 0.35;
        materialDiffuse[2] = 0.1;
        glUniform3fv(materialDiffuseUniform, 1, (GLfloat*)materialDiffuse);

        materialSpecular[0] = 0.45;
        materialSpecular[1] = 0.55;
        materialSpecular[2] = 0.45;
        glUniform3fv(materialSpecularUniform, 1, (GLfloat*)materialSpecular);

        materialShiness = 0.25 * 128;
        glUniform1f(materialShininessUniform, materialShiness);


        //** bind vao **
        glBindVertexArray(VAO_sphere);

        //** draw either by glDrawTriangles() or glDrawArrays() or glDrawElements()
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO_sphere_element);
        glDrawElements(GL_TRIANGLES, gNumElements, GL_UNSIGNED_SHORT, 0);    //3 (each with its x,y,z) vertices in triangle vertices array

        //** unbind vao **
        glBindVertexArray(0);


        //4th Sphere


        modelMatrix = vmath::mat4::identity();    //model matrix
        viewMatrix = vmath::mat4::identity();
        projectionMatrix = vmath::mat4::identity();    //projection matrix
        translationMatrix = vmath::mat4::identity();    //translate matrix
        
        
        translationMatrix = vmath::translate(0.0f, -1.0f, -12.0f);

        
        modelMatrix = translationMatrix;

        
        projectionMatrix = perspectiveProjectionMatrix;

        glUniformMatrix4fv(modelViewMatrixUniform, 1, GL_FALSE, modelMatrix);
        glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, viewMatrix);
        glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, projectionMatrix);

        //copper
        materialAmbient[0] = 0.0;
        materialAmbient[1] = 0.0;
        materialAmbient[2] = 0.0;
        glUniform3fv(materialAmbientUniform, 1, (GLfloat*)materialAmbient);

        materialDiffuse[0] = 0.5;
        materialDiffuse[1] = 0.0;
        materialDiffuse[2] = 0.0;
        glUniform3fv(materialDiffuseUniform, 1, (GLfloat*)materialDiffuse);

        materialSpecular[0] = 0.7;
        materialSpecular[1] = 0.6;
        materialSpecular[2] = 0.6;
        glUniform3fv(materialSpecularUniform, 1, (GLfloat*)materialSpecular);

        materialShiness = 0.25 * 128;
        glUniform1f(materialShininessUniform, materialShiness);


        //** bind vao **
        glBindVertexArray(VAO_sphere);

        //** draw either by glDrawTriangles() or glDrawArrays() or glDrawElements()
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO_sphere_element);
        glDrawElements(GL_TRIANGLES, gNumElements, GL_UNSIGNED_SHORT, 0);    //3 (each with its x,y,z) vertices in triangle vertices array

        //** unbind vao **
        glBindVertexArray(0);


        //5th Sphere


        modelMatrix = vmath::mat4::identity();    //model matrix
        viewMatrix = vmath::mat4::identity();
        projectionMatrix = vmath::mat4::identity();    //projection matrix
        translationMatrix = vmath::mat4::identity();    //translate matrix
        
        
        translationMatrix = vmath::translate(0.0f, -2.50f, -12.0f);

        
        modelMatrix = translationMatrix;

        
        projectionMatrix = perspectiveProjectionMatrix;

        glUniformMatrix4fv(modelViewMatrixUniform, 1, GL_FALSE, modelMatrix);
        glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, viewMatrix);
        glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, projectionMatrix);


        materialAmbient[0] = 0.0;
        materialAmbient[1] = 0.0;
        materialAmbient[2] = 0.0;
        glUniform3fv(materialAmbientUniform, 1, (GLfloat*)materialAmbient);

        materialDiffuse[0] = 0.55;
        materialDiffuse[1] = 0.55;
        materialDiffuse[2] = 0.55;
        glUniform3fv(materialDiffuseUniform, 1, (GLfloat*)materialDiffuse);

        materialSpecular[0] = 0.70;
        materialSpecular[1] = 0.70;
        materialSpecular[2] = 0.70;
        glUniform3fv(materialSpecularUniform, 1, (GLfloat*)materialSpecular);

        materialShiness = 0.25 * 128;
        glUniform1f(materialShininessUniform, materialShiness);


        //** bind vao **
        glBindVertexArray(VAO_sphere);

        //** draw either by glDrawTriangles() or glDrawArrays() or glDrawElements()
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO_sphere_element);
        glDrawElements(GL_TRIANGLES, gNumElements, GL_UNSIGNED_SHORT, 0);    //3 (each with its x,y,z) vertices in triangle vertices array

        //** unbind vao **
        glBindVertexArray(0);



        //6th Sphere


        modelMatrix = vmath::mat4::identity();    //model matrix
        viewMatrix = vmath::mat4::identity();
        projectionMatrix = vmath::mat4::identity();    //projection matrix
        translationMatrix = vmath::mat4::identity();    //translate matrix
        
        
        translationMatrix = vmath::translate(0.0f, -4.0f, -12.0f);

        
        modelMatrix = translationMatrix;

        
        projectionMatrix = perspectiveProjectionMatrix;

        glUniformMatrix4fv(modelViewMatrixUniform, 1, GL_FALSE, modelMatrix);
        glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, viewMatrix);
        glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, projectionMatrix);

        //yellow plastic
        materialAmbient[0] = 0.0;
        materialAmbient[1] = 0.0;
        materialAmbient[2] = 0.0;
        glUniform3fv(materialAmbientUniform, 1, (GLfloat*)materialAmbient);

        materialDiffuse[0] = 0.5;
        materialDiffuse[1] = 0.5;
        materialDiffuse[2] = 0.0;
        glUniform3fv(materialDiffuseUniform, 1, (GLfloat*)materialDiffuse);

        materialSpecular[0] = 0.60;
        materialSpecular[1] = 0.60;
        materialSpecular[2] = 0.50;
        glUniform3fv(materialSpecularUniform, 1, (GLfloat*)materialSpecular);

        materialShiness = 0.4 * 128;
        glUniform1f(materialShininessUniform, materialShiness);


        //** bind vao **
        glBindVertexArray(VAO_sphere);

        //** draw either by glDrawTriangles() or glDrawArrays() or glDrawElements()
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO_sphere_element);
        glDrawElements(GL_TRIANGLES, gNumElements, GL_UNSIGNED_SHORT, 0);    //3 (each with its x,y,z) vertices in triangle vertices array

        //** unbind vao **
        glBindVertexArray(0);



        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //
        //                                4th Column
        //
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


        //OpenGL Drawing
        modelMatrix = vmath::mat4::identity();    //model matrix
        viewMatrix = vmath::mat4::identity();
        projectionMatrix = vmath::mat4::identity();    //projection matrix
        translationMatrix = vmath::mat4::identity();    //translate matrix
        
        
        translationMatrix = vmath::translate(2.0f, 3.50f, -12.0f);

        
        modelMatrix = translationMatrix;

        
        projectionMatrix = perspectiveProjectionMatrix;

        glUniformMatrix4fv(modelViewMatrixUniform, 1, GL_FALSE, modelMatrix);
        glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, viewMatrix);
        glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, projectionMatrix);

        //black
        materialAmbient[0] = 0.02;
        materialAmbient[1] = 0.02;
        materialAmbient[2] = 0.02;
        glUniform3fv(materialAmbientUniform, 1, (GLfloat*)materialAmbient);

        materialDiffuse[0] = 0.01;
        materialDiffuse[1] = 0.01;
        materialDiffuse[2] = 0.01;
        glUniform3fv(materialDiffuseUniform, 1, (GLfloat*)materialDiffuse);

        materialSpecular[0] = 0.40;
        materialSpecular[1] = 0.40;
        materialSpecular[2] = 0.40;
        glUniform3fv(materialSpecularUniform, 1, (GLfloat*)materialSpecular);

        materialShiness = 0.078125 * 128;
        glUniform1f(materialShininessUniform, materialShiness);


        //** bind vao **
        glBindVertexArray(VAO_sphere);

        //** draw either by glDrawTriangles() or glDrawArrays() or glDrawElements()
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO_sphere_element);
        glDrawElements(GL_TRIANGLES, gNumElements, GL_UNSIGNED_SHORT, 0);    //3 (each with its x,y,z) vertices in triangle vertices array

        //** unbind vao **
        glBindVertexArray(0);


        //2nd sphere
        modelMatrix = vmath::mat4::identity();    //model matrix
        viewMatrix = vmath::mat4::identity();
        projectionMatrix = vmath::mat4::identity();    //projection matrix
        translationMatrix = vmath::mat4::identity();    //translate matrix
        
        
        translationMatrix = vmath::translate(2.0f, 2.0f, -12.0f);

        
        modelMatrix = translationMatrix;

        
        projectionMatrix = perspectiveProjectionMatrix;

        glUniformMatrix4fv(modelViewMatrixUniform, 1, GL_FALSE, modelMatrix);
        glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, viewMatrix);
        glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, projectionMatrix);

        materialAmbient[0] = 0.0;
        materialAmbient[1] = 0.05;
        materialAmbient[2] = 0.05;
        glUniform3fv(materialAmbientUniform, 1, (GLfloat*)materialAmbient);

        materialDiffuse[0] = 0.04;
        materialDiffuse[1] = 0.5;
        materialDiffuse[2] = 0.5;
        glUniform3fv(materialDiffuseUniform, 1, (GLfloat*)materialDiffuse);

        materialSpecular[0] = 0.04;
        materialSpecular[1] = 0.7;
        materialSpecular[2] = 0.7;
        glUniform3fv(materialSpecularUniform, 1, (GLfloat*)materialSpecular);

        materialShiness = 0.078125 * 128;
        glUniform1f(materialShininessUniform, materialShiness);


        //** bind vao **
        glBindVertexArray(VAO_sphere);

        //** draw either by glDrawTriangles() or glDrawArrays() or glDrawElements()
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO_sphere_element);
        glDrawElements(GL_TRIANGLES, gNumElements, GL_UNSIGNED_SHORT, 0);    //3 (each with its x,y,z) vertices in triangle vertices array

        //** unbind vao **
        glBindVertexArray(0);

        //3rd Sphere

        modelMatrix = vmath::mat4::identity();    //model matrix
        viewMatrix = vmath::mat4::identity();
        projectionMatrix = vmath::mat4::identity();    //projection matrix
        translationMatrix = vmath::mat4::identity();    //translate matrix
        
        
        translationMatrix = vmath::translate(2.0f, 0.50f, -12.0f);

        
        modelMatrix = translationMatrix;

        
        projectionMatrix = perspectiveProjectionMatrix;

        glUniformMatrix4fv(modelViewMatrixUniform, 1, GL_FALSE, modelMatrix);
        glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, viewMatrix);
        glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, projectionMatrix);

        //chrome
        materialAmbient[0] = 0.0;
        materialAmbient[1] = 0.05;
        materialAmbient[2] = 0.0;
        glUniform3fv(materialAmbientUniform, 1, (GLfloat*)materialAmbient);

        materialDiffuse[0] = 0.4;
        materialDiffuse[1] = 0.5;
        materialDiffuse[2] = 0.4;
        glUniform3fv(materialDiffuseUniform, 1, (GLfloat*)materialDiffuse);

        materialSpecular[0] = 0.04;
        materialSpecular[1] = 0.7;
        materialSpecular[2] = 0.04;
        glUniform3fv(materialSpecularUniform, 1, (GLfloat*)materialSpecular);

        materialShiness = 0.078125 * 128;
        glUniform1f(materialShininessUniform, materialShiness);


        //** bind vao **
        glBindVertexArray(VAO_sphere);

        //** draw either by glDrawTriangles() or glDrawArrays() or glDrawElements()
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO_sphere_element);
        glDrawElements(GL_TRIANGLES, gNumElements, GL_UNSIGNED_SHORT, 0);    //3 (each with its x,y,z) vertices in triangle vertices array

        //** unbind vao **
        glBindVertexArray(0);


        //4th Sphere


        modelMatrix = vmath::mat4::identity();    //model matrix
        viewMatrix = vmath::mat4::identity();
        projectionMatrix = vmath::mat4::identity();    //projection matrix
        translationMatrix = vmath::mat4::identity();    //translate matrix
        
        
        translationMatrix = vmath::translate(2.0f, -1.0f, -12.0f);

        
        modelMatrix = translationMatrix;

        
        projectionMatrix = perspectiveProjectionMatrix;

        glUniformMatrix4fv(modelViewMatrixUniform, 1, GL_FALSE, modelMatrix);
        glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, viewMatrix);
        glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, projectionMatrix);

        materialAmbient[0] = 0.05;
        materialAmbient[1] = 0.0;
        materialAmbient[2] = 0.0;
        glUniform3fv(materialAmbientUniform, 1, (GLfloat*)materialAmbient);

        materialDiffuse[0] = 0.5;
        materialDiffuse[1] = 0.4;
        materialDiffuse[2] = 0.4;
        glUniform3fv(materialDiffuseUniform, 1, (GLfloat*)materialDiffuse);

        materialSpecular[0] = 0.7;
        materialSpecular[1] = 0.04;
        materialSpecular[2] = 0.04;
        glUniform3fv(materialSpecularUniform, 1, (GLfloat*)materialSpecular);

        materialShiness = 0.078125 * 128;
        glUniform1f(materialShininessUniform, materialShiness);


        //** bind vao **
        glBindVertexArray(VAO_sphere);

        //** draw either by glDrawTriangles() or glDrawArrays() or glDrawElements()
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO_sphere_element);
        glDrawElements(GL_TRIANGLES, gNumElements, GL_UNSIGNED_SHORT, 0);    //3 (each with its x,y,z) vertices in triangle vertices array

        //** unbind vao **
        glBindVertexArray(0);


        //5th Sphere


        modelMatrix = vmath::mat4::identity();    //model matrix
        viewMatrix = vmath::mat4::identity();
        projectionMatrix = vmath::mat4::identity();    //projection matrix
        translationMatrix = vmath::mat4::identity();    //translate matrix
        
        translationMatrix = vmath::translate(2.0f, -2.50f, -12.0f);

        modelMatrix = translationMatrix;

        projectionMatrix = perspectiveProjectionMatrix;

        glUniformMatrix4fv(modelViewMatrixUniform, 1, GL_FALSE, modelMatrix);
        glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, viewMatrix);
        glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, projectionMatrix);

        //gold
        materialAmbient[0] = 0.05;
        materialAmbient[1] = 0.05;
        materialAmbient[2] = 0.05;
        glUniform3fv(materialAmbientUniform, 1, (GLfloat*)materialAmbient);

        materialDiffuse[0] = 0.5;
        materialDiffuse[1] = 0.5;
        materialDiffuse[2] = 0.5;
        glUniform3fv(materialDiffuseUniform, 1, (GLfloat*)materialDiffuse);

        materialSpecular[0] = 0.70;
        materialSpecular[1] = 0.70;
        materialSpecular[2] = 0.70;
        glUniform3fv(materialSpecularUniform, 1, (GLfloat*)materialSpecular);

        materialShiness = 0.078125 * 128;
        glUniform1f(materialShininessUniform, materialShiness);


        //** bind vao **
        glBindVertexArray(VAO_sphere);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO_sphere_element);
        glDrawElements(GL_TRIANGLES, gNumElements, GL_UNSIGNED_SHORT, 0);    //3 (each with its x,y,z) vertices in triangle vertices array

        //** unbind vao **
        glBindVertexArray(0);



        //6th Sphere


        modelMatrix = vmath::mat4::identity();    //model matrix
        viewMatrix = vmath::mat4::identity();
        projectionMatrix = vmath::mat4::identity();    //projection matrix
        translationMatrix = vmath::mat4::identity();    //translate matrix
        
        
        translationMatrix = vmath::translate(2.0f, -4.0f, -12.0f);

        
        modelMatrix = translationMatrix;

        projectionMatrix = perspectiveProjectionMatrix;

        glUniformMatrix4fv(modelViewMatrixUniform, 1, GL_FALSE, modelMatrix);
        glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, viewMatrix);
        glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, projectionMatrix);

        //yellow rubber
        materialAmbient[0] = 0.05;
        materialAmbient[1] = 0.05;
        materialAmbient[2] = 0.0;
        glUniform3fv(materialAmbientUniform, 1, (GLfloat*)materialAmbient);

        materialDiffuse[0] = 0.5;
        materialDiffuse[1] = 0.5;
        materialDiffuse[2] = 0.4;
        glUniform3fv(materialDiffuseUniform, 1, (GLfloat*)materialDiffuse);

        materialSpecular[0] = 0.7;
        materialSpecular[1] = 0.7;
        materialSpecular[2] = 0.04;
        glUniform3fv(materialSpecularUniform, 1, (GLfloat*)materialSpecular);

        materialShiness = 0.078125 * 128;
        glUniform1f(materialShininessUniform, materialShiness);


        //** bind vao **
        glBindVertexArray(VAO_sphere);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO_sphere_element);
        glDrawElements(GL_TRIANGLES, gNumElements, GL_UNSIGNED_SHORT, 0);    //3 (each with its x,y,z) vertices in triangle vertices array

        //** unbind vao **
        glBindVertexArray(0);



    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    
    
    glUseProgram(0);

}

-(void)myUpdate//our update, as mac has update function
{
 
    lAngle += 0.05f;
    
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

        case 'X':
        case 'x':
            x = TRUE;
            y = FALSE;
            z = FALSE;
            break;
        case 'Y':
        case 'y':
            x = FALSE;
            y = TRUE;
            z = FALSE;
            break;
        case 'Z':
        case 'z':
            x = FALSE;
            y = FALSE;
            z = TRUE;
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
