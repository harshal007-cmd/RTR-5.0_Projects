#include<Foundation/Foundation.h>
#import<Cocoa/Cocoa.h>
#import <QuartzCore/CVDisplayLink.h>    //CV core video
#import <OpenGL/gl3.h>                  //gl.h
#import <OpenGL/gl3ext.h>
#import "Sphere.h"

#import "vmath.h" //#import also work
using namespace vmath;

#include<math.h>

#define WIDTH 800
#define HEIGHT 600


enum
{
    AMC_ATTRIBUTE_POSITION = 0,
    AMC_ATTRIBUTE_NORMAL = 1

};

//For light
struct Light {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec4 position;
};

struct Light light[3];


GLfloat materialAmbient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat matrerialDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat materialSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat materialShiness = 128.0f;


float sphere_vertices[1146];
float sphere_normals[1146];
float sphere_textures[764];
unsigned short sphere_elements[2280];

GLuint gNumVertices;
GLuint gNumElements;
char change;

BOOL pv,pf;

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
    fprintf(gpFILE,"Program started successfully\n");

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
        fprintf(gpFILE,"Program finished successfully\n");
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

    GLuint vertexShaderObjectF;
    GLuint fragmentShaderObjectF;
    GLuint shaderProgramObjectF;

    GLuint VAO_sphere;
    GLuint VBO_sphere_position;
    GLuint VBO_sphere_normal;
    GLuint VBO_sphere_element;
    
    GLuint modelViewMatrixUniform;
    GLuint viewMatrixUniform;
    GLuint projectionMatrixUniform;

    GLuint lightDiffuseUniform[3];
    GLuint lightAmbientUniform[3];
    GLuint lightSpecularUniform[3];
    GLuint lightPositionUniform[3];

    
    GLuint materialDiffuseUniform;
    GLuint materialAmbientUniform;
    GLuint materialSpecularUniform;
    GLuint materialShininessUniform;
    
    
    GLuint keyPressUniform;
    GLuint keyPressUniformF;

    mat4 perspectiveProjectionMatrix;  //in vmath

    GLfloat X, Y, Z;
    GLfloat pAngle;
    GLfloat rangle;
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

    
    
    //---------------------------- PerVertex Light ----------------------------------
    //Vertex Shader, version set to 410, locked in Mac
    const GLchar* vertexShaderCode =
            "#version 410 core" \
            "\n" \
            "in vec4 aPosition;" \
            "in vec3 aNormal;" \
            "uniform mat4 uModelViewMatrix;" \
           "uniform mat4 uViewMatrix;" \
           "uniform mat4 uProjectionMatrix;" \
            "uniform vec3 uLightAmbient[3];" \
            "uniform vec3 uLightDiffuse[3];" \
            "uniform vec3 uLightSpecular[3];" \
            "uniform vec4 uLightPosition[3];" \
            "\n"\
           "uniform vec3 uMaterialAmbient;" \
           "uniform vec3 uMaterialDiffuse;" \
           "uniform vec3 uMaterialSpecular;" \
           "uniform float uMaterialShininess;" \
           "uniform int uKeyPress;" \
           "out vec3 oPhongADSLight;" \
           "void main(void)" \
           "{" \
            "if(uKeyPress == 1)"
            "{"
            "    vec3 reflectionVector[3];"
            "    vec3 ambientLight[3];"
            "    vec3 diffuseLight[3];"
            "    vec3 lightSpecular[3];"
            "    vec3 lightDirection[3];"
            "\n"
            "   vec4 iCoordinates = uViewMatrix * uModelViewMatrix * aPosition;"
            "   vec3 transformedNormals = normalize(mat3(uViewMatrix * uModelViewMatrix) * aNormal);"
            "   vec3 viewerVector = normalize(-iCoordinates.xyz);"
            "   for(int i=0;i<3;i++)"
            "   {"
            "        lightDirection[i] = normalize(vec3(uLightPosition[i] - iCoordinates));"
            "        reflectionVector[i] = reflect(-lightDirection[i], transformedNormals);"
            "        ambientLight[i] = uLightAmbient[i] * uMaterialAmbient;"
            "        diffuseLight[i] = uLightDiffuse[i] * uMaterialDiffuse * max(dot(lightDirection[i], transformedNormals),0.0);"
            "        lightSpecular[i] = uLightSpecular[i] * uMaterialSpecular * pow(max(dot(reflectionVector[i], viewerVector),0.0),uMaterialShininess);"
            "        oPhongADSLight = oPhongADSLight + ambientLight[i] + diffuseLight[i] + lightSpecular[i];"
            "   }"
            "}"
            "else"
            "{"
            "    oPhongADSLight = vec3(0.0f, 0.0f, 0.0f);"
            "}"
            "    gl_Position = uProjectionMatrix * uViewMatrix * uModelViewMatrix * aPosition;"
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
                    fprintf(gpFILE, "V Vertex Shader compilation error log: %s\n", szInfoLog);
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
            "in vec3 oPhongADSLight;" \
            "uniform int uKeyPress;" \
            "out vec4 FragColor;" \
            "void main(void)" \
            "{" \
            "      FragColor = vec4(oPhongADSLight, 1.0f);"
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
                    fprintf(gpFILE, "V Fragment shader compilation error log: %s\n", szInfoLog);
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
    
    modelViewMatrixUniform = glGetUniformLocation(shaderProgramObject, "uModelViewMatrix");
    viewMatrixUniform = glGetUniformLocation(shaderProgramObject, "uViewMatrix");
    projectionMatrixUniform = glGetUniformLocation(shaderProgramObject, "uProjectionMatrix");
    //---
    lightAmbientUniform[0] = glGetUniformLocation(shaderProgramObject, "uLightAmbient[0]");
    lightDiffuseUniform[0] = glGetUniformLocation(shaderProgramObject, "uLightDiffuse[0]");
    lightSpecularUniform[0] = glGetUniformLocation(shaderProgramObject, "uLightSpecular[0]");
    lightPositionUniform[0] = glGetUniformLocation(shaderProgramObject, "uLightPosition[0]");

    lightAmbientUniform[1] = glGetUniformLocation(shaderProgramObject, "uLightAmbient[1]");
    lightDiffuseUniform[1] = glGetUniformLocation(shaderProgramObject, "uLightDiffuse[1]");
    lightSpecularUniform[1] = glGetUniformLocation(shaderProgramObject, "uLightSpecular[1]");
    lightPositionUniform[1] = glGetUniformLocation(shaderProgramObject, "uLightPosition[1]");

    lightAmbientUniform[2] = glGetUniformLocation(shaderProgramObject, "uLightAmbient[2]");
    lightDiffuseUniform[2] = glGetUniformLocation(shaderProgramObject, "uLightDiffuse[2]");
    lightSpecularUniform[2] = glGetUniformLocation(shaderProgramObject, "uLightSpecular[2]");
    lightPositionUniform[2] = glGetUniformLocation(shaderProgramObject, "uLightPosition[2]");
    //---
    materialAmbientUniform = glGetUniformLocation(shaderProgramObject, "uMaterialAmbienr");
    materialDiffuseUniform = glGetUniformLocation(shaderProgramObject, "uMaterialDiffuse");
    materialSpecularUniform = glGetUniformLocation(shaderProgramObject, "uMaterialSpecular");
    materialShininessUniform = glGetUniformLocation(shaderProgramObject, "uMaterialShininess");

    keyPressUniform = glGetUniformLocation(shaderProgramObject, "uKeyPress");

    
    //--------------------------- Pervertx Light Ends -----------------------------

    //------------------------------ PerFragment Light ------------------------------------
        //Vertex Shader, version set to 410, locked in Mac
    const GLchar* vertexShaderCodeF =
        "#version 410 core" \
        "\n" \
        "in vec4 aPosition;" \
        "in vec3 aNormal;" \
        "uniform mat4 uModelViewMatrix;" \
        "uniform mat4 uViewMatrix;" \
        "uniform mat4 uProjectionMatrix;" \
        "uniform vec4 uLightPosition[3];" \
        "\n"\
        "uniform int uKeyPress;" \
        "out vec3 oTransformedNormals;"\
        "out vec3 oLightDirection[3];"\
        "out vec3 oViewerVector;"\
        "vec3 lightDirection[3];"
        "void main(void)" \
        "{" \
        "if(uKeyPress == 1)"
        "{"
        "vec4 iCoordinates = uViewMatrix * uModelViewMatrix * aPosition;"
        "oTransformedNormals = mat3(uViewMatrix * uModelViewMatrix) * aNormal;"
        "oViewerVector = -iCoordinates.xyz;"
        "    for(int i=0;i<3;i++)"
        "    {"
        "        lightDirection[i] = normalize(vec3(uLightPosition[i] - iCoordinates));"
        "        oLightDirection[i] = vec3(uLightPosition[i] - iCoordinates);"
        "    }"
        "}"
        "else"
        "{"
        "    oTransformedNormals = vec3(0.0, 0.0, 0.0); "
        "    for(int i=0;i<3;i++)"
        "    {"
        "        oLightDirection[i] = vec3(0.0, 0.0, 0.0);"
        "    }"
        "oViewerVector = vec3(0.0, 0.0, 0.0);"
        "}"
        "gl_Position = uProjectionMatrix * uViewMatrix * uModelViewMatrix * aPosition;"
        "}";

    vertexShaderObjectF = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderObjectF, 1, (const GLchar**)&vertexShaderCodeF, NULL);
    glCompileShader(vertexShaderObjectF);

    status = 0;
    infoLogLength = 0;
    szInfoLog = NULL;

    glGetShaderiv(vertexShaderObjectF, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE)
    {
        glGetShaderiv(vertexShaderObjectF, GL_INFO_LOG_LENGTH, &infoLogLength);
        if (infoLogLength > 0)
        {
            szInfoLog = (GLchar*)malloc(infoLogLength);
            if (szInfoLog != NULL)
            {
                glGetShaderInfoLog(vertexShaderObjectF, infoLogLength, NULL, szInfoLog);
                fprintf(gpFILE, "F Vertex Shader compilation error log: %s\n", szInfoLog);
                free(szInfoLog);
                szInfoLog = NULL;
                [self uninitailize];//exit is available in this function

                [self release];
                [NSApp terminate:self];
            }
        }
    }


    //Fragment shader
    const GLchar* fragmentShaderCodeF =
        "#version 410 core" \
        "\n" \
        "in vec3 oTransformedNormals;"\
        "in vec3 oLightDirection[3];" \
        "in vec3 oViewerVector; "
        "uniform vec3 uLightAmbient[3];" \
        "uniform vec3 uLightDiffuse[3];" \
        "uniform vec3 uLightSpecular[3];" \
        "\n"\
        "uniform vec3 uMaterialAmbient;" \
        "uniform vec3 uMaterialDiffuse;" \
        "uniform vec3 uMaterialSpecular;" \
        "uniform float uMaterialShininess;" \
        "uniform int uKeyPress;" \
        "out vec4 FragColor;" \
        "void main(void)" \
        "{" \
        "vec3 phongADSLight;"
        "if(uKeyPress == 1)"
        "{"
        "    vec3 reflectionVector[3];"
        "    vec3 ambientLight[3];"
        "    vec3 diffuseLight[3];"
        "    vec3 lightSpecular[3];"
        "\n"
        "    vec3 normalizedTransformedNormal = normalize(oTransformedNormals);"
        "    vec3 normalizedViewerVector = normalize(oViewerVector);"
        "    vec3 normalizedLightDirection[3];"
        "    for(int i = 0 ;i<3;i++)"
        "    {"
        "        normalizedLightDirection[i] = normalize(oLightDirection[i]);"
        "        ambientLight[i] = uLightAmbient[i] * uMaterialAmbient;"
        "        diffuseLight[i] = uLightDiffuse[i] * uMaterialDiffuse * max(dot(normalizedLightDirection[i], normalizedTransformedNormal), 0.0);"
        "        reflectionVector[i] = reflect(-normalizedLightDirection[i], normalizedTransformedNormal);"
        "        lightSpecular[i] = uLightSpecular[i] * uMaterialSpecular * pow(max(dot(reflectionVector[i], normalizedViewerVector), 0.0), uMaterialShininess);"
        "        phongADSLight = phongADSLight + ambientLight[i] + diffuseLight[i] + lightSpecular[i];"
        "    }"
        "}"
        "else"
        "{"
        "    phongADSLight = vec3(1.0, 1.0, 1.0);"
        "}"
        "    FragColor = vec4(phongADSLight, 1.0);"
        "}";

    fragmentShaderObjectF = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderObjectF, 1, (const GLchar**)&fragmentShaderCodeF, NULL);
    glCompileShader(fragmentShaderObjectF);

    status = 0;
    infoLogLength = 0;
    szInfoLog = NULL;

    glGetShaderiv(fragmentShaderObjectF, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE)
    {
        glGetShaderiv(fragmentShaderObjectF, GL_INFO_LOG_LENGTH, &infoLogLength);
        if (infoLogLength > 0)
        {
            szInfoLog = (GLchar*)malloc(infoLogLength);
            if (szInfoLog != NULL)
            {
                glGetShaderInfoLog(fragmentShaderObjectF, infoLogLength, NULL, szInfoLog);
                fprintf(gpFILE, "F Fragment shader compilation error log: %s\n", szInfoLog);
                free(szInfoLog);
                szInfoLog = NULL;
                [self uninitailize];//exit is available in this function

                [self release];
                [NSApp terminate:self];
            }
        }
    }

    
    //Create Shader program
    shaderProgramObjectF = glCreateProgram();
    glAttachShader(shaderProgramObjectF, vertexShaderObjectF);
    glAttachShader(shaderProgramObjectF, fragmentShaderObjectF);
    glBindAttribLocation(shaderProgramObjectF, AMC_ATTRIBUTE_POSITION, "aPosition");
    glBindAttribLocation(shaderProgramObjectF, AMC_ATTRIBUTE_NORMAL, "aNormal");
        

    glLinkProgram(shaderProgramObjectF);
    status = 0;
    infoLogLength = 0;
    szInfoLog = NULL;

    glGetProgramiv(shaderProgramObjectF, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
    {
        glGetProgramiv(shaderProgramObjectF, GL_INFO_LOG_LENGTH, &infoLogLength);
        if (infoLogLength > 0)
        {
            szInfoLog = (GLchar*)malloc(infoLogLength);
            if (szInfoLog != NULL)
            {
                glGetProgramInfoLog(shaderProgramObject, infoLogLength, NULL, szInfoLog);
                fprintf(gpFILE, "Fragment shader program linking error log : %s\n", szInfoLog);
                free(szInfoLog);
                szInfoLog = NULL;
                [self uninitailize];//exit is available in this function

                [self release];
                [NSApp terminate:self];
            }
        }
    }

    
    //Get shader uniform locations
        modelViewMatrixUniform = glGetUniformLocation(shaderProgramObjectF, "uModelViewMatrix");
        viewMatrixUniform = glGetUniformLocation(shaderProgramObjectF, "uViewMatrix");
        projectionMatrixUniform = glGetUniformLocation(shaderProgramObjectF, "uProjectionMatrix");
        //---
        lightAmbientUniform[0] = glGetUniformLocation(shaderProgramObjectF, "uLightAmbient[0]");
        lightDiffuseUniform[0] = glGetUniformLocation(shaderProgramObjectF, "uLightDiffuse[0]");
        lightSpecularUniform[0] = glGetUniformLocation(shaderProgramObjectF, "uLightSpecular[0]");
        lightPositionUniform[0] = glGetUniformLocation(shaderProgramObjectF, "uLightPosition[0]");

        lightAmbientUniform[1] = glGetUniformLocation(shaderProgramObjectF, "uLightAmbient[1]");
        lightDiffuseUniform[1] = glGetUniformLocation(shaderProgramObjectF, "uLightDiffuse[1]");
        lightSpecularUniform[1] = glGetUniformLocation(shaderProgramObjectF, "uLightSpecular[1]");
        lightPositionUniform[1] = glGetUniformLocation(shaderProgramObjectF, "uLightPosition[1]");

        lightAmbientUniform[2] = glGetUniformLocation(shaderProgramObjectF, "uLightAmbient[2]");
        lightDiffuseUniform[2] = glGetUniformLocation(shaderProgramObjectF, "uLightDiffuse[2]");
        lightSpecularUniform[2] = glGetUniformLocation(shaderProgramObjectF, "uLightSpecular[2]");
        lightPositionUniform[2] = glGetUniformLocation(shaderProgramObjectF, "uLightPosition[2]");
        //---
        materialAmbientUniform = glGetUniformLocation(shaderProgramObjectF, "uMaterialAmbienr");
        materialDiffuseUniform = glGetUniformLocation(shaderProgramObjectF, "uMaterialDiffuse");
        materialSpecularUniform = glGetUniformLocation(shaderProgramObjectF, "uMaterialSpecular");
        materialShininessUniform = glGetUniformLocation(shaderProgramObjectF, "uMaterialShininess");

        keyPressUniform = glGetUniformLocation(shaderProgramObjectF, "uKeyPress");

    //----------------------- PerFragment Light Ends -------------------------------
    
    
    
    

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
        
    light[0].ambient = vec3(0.0f, 0.0f, 0.0f);
    light[1].ambient = vec3(0.0f, 0.0f, 0.0f);
    light[2].ambient = vec3(0.0f, 0.0f, 0.0f);

    light[0].diffuse = vec3(1.0f, 0.0f, 0.0f);
    light[1].diffuse = vec3(0.0f, 0.0f, 1.0f);
    light[2].diffuse = vec3(0.0f, 1.0f, 0.0f);

    light[0].specular = vec3(1.0f, 0.0f, 1.0f);
    light[1].specular = vec3(0.0f, 0.0f, 1.0f);
    light[2].specular = vec3(0.0f, 1.0f, 0.0f);
    /*
    light[0].position = vec4(0.0f, Y = 5 * sin(angle), Z = 5 * cos(angle), 1.0f);
    light[1].position = vec4(X = 5 * sin(angle), 0.0f, Z = 5 * cos(angle), 1.0f);
    light[2].position = vec4(X = 5 * sin(angle), Y = 5 * cos(angle), 0.0f, 1.0f);
    */
    
    light[0].position = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    light[1].position = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    light[2].position = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    
    
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
    
    
    if(change == 'v')
    {
        glUseProgram(shaderProgramObject);
        
    }
    else
    {
        glUseProgram(shaderProgramObjectF);
       
    }
     
    //glUseProgram(shaderProgramObject);
    
    /*
    //X-formation
    mat4 modelViewMatrix = mat4::identity();
    mat4 viewMatrix = vmath::mat4::identity();

        mat4 translationMatrix = mat4::identity();
        translationMatrix = vmath::translate(0.0f, 0.0f, -1.5f);

        mat4 scaleMatrix = mat4::identity();
        scaleMatrix = vmath::scale(0.75f, 0.75f, 0.75f);

        modelViewMatrix = translationMatrix * scaleMatrix;

        mat4 modelViewProjectionMatrix = mat4::identity();
        modelViewProjectionMatrix = perspectiveProjectionMatrix * modelViewMatrix;
        */
    
        mat4 translationMatrix = vmath::translate(0.0f, 0.0f, -2.0f);
        mat4 viewMatrix = vmath::mat4::identity();
        mat4 modelMatrix = translationMatrix;


        //Push above MVP info vertex shader's mvpUniform
        glUniformMatrix4fv(modelViewMatrixUniform, 1, GL_FALSE, modelMatrix);
        glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, viewMatrix);
        glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, perspectiveProjectionMatrix);

        if (bLightingEnable == TRUE)
        {
            //glUseProgram(shaderProgramObject);
            
            glUniform1i(keyPressUniform, 1);
            
            glUniform3fv(lightDiffuseUniform[0], 1, light[0].diffuse);
            glUniform3fv(lightAmbientUniform[0], 1, light[0].ambient);
            glUniform3fv(lightSpecularUniform[0], 1, light[0].specular);
            glUniform4fv(lightPositionUniform[0], 1, light[0].position);

            glUniform3fv(lightDiffuseUniform[1], 1, light[1].diffuse);
            glUniform3fv(lightAmbientUniform[1], 1, light[1].ambient);
            glUniform3fv(lightSpecularUniform[1], 1, light[1].specular);
            glUniform4fv(lightPositionUniform[1], 1, light[1].position);

            glUniform3fv(lightDiffuseUniform[2], 1, light[2].diffuse);
            glUniform3fv(lightAmbientUniform[2], 1, light[2].ambient);
            glUniform3fv(lightSpecularUniform[2], 1, light[2].specular);
            glUniform4fv(lightPositionUniform[2], 1, light[2].position);

            glUniform3fv(materialDiffuseUniform, 1, matrerialDiffuse);
            glUniform3fv(materialAmbientUniform, 1, materialAmbient);
            glUniform3fv(materialSpecularUniform, 1, materialSpecular);
            glUniform1f(materialShininessUniform, materialShiness);

        }
        else
        {
            glUniform1i(keyPressUniform, 0);
           // glUniform1i(keyPressUniformF, 0);
        }

        // *** bind vao ***
        glBindVertexArray(VAO_sphere);

        // *** draw, either by glDrawTriangles() or glDrawArrays() or glDrawElements()
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO_sphere_element);
        glDrawElements(GL_TRIANGLES, gNumElements, GL_UNSIGNED_SHORT, 0);

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
    
    rangle += 0.01;
        

        light[0].position[0] = 2 * cos(rangle) + 2 * sin(rangle);
        light[0].position[1] = 0;
        light[0].position[2] = 2 * cos(rangle) - 2 * sin(rangle);
        light[0].position[3] = 1.0f;
        
        light[1].position[0] = 0;
        light[1].position[1] = 2 * cos(rangle) + 2 * sin(rangle);
        light[1].position[2] = 2 * cos(rangle) - 2 * sin(rangle);
        light[1].position[3] = 1.0f;

        light[2].position[0] = 2 * cos(rangle) + 2 * sin(rangle);
        light[2].position[1] = 2 * cos(rangle) - 2 * sin(rangle);
        light[2].position[2] = 0;
        light[2].position[3] = 1.0f;

    
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

        case 'e':
        case 'E':
            [[self window]toggleFullScreen:self];
        break;
        case 'L':
        case 'l':
            if (bLightingEnable == FALSE)
                bLightingEnable = TRUE;
            else
                bLightingEnable = FALSE;
            break;
        case 'v':
        case 'V':
            change = 'v';
            lightAmbientUniform[0] = glGetUniformLocation(shaderProgramObject, "uLightAmbient[0]");
            lightDiffuseUniform[0] = glGetUniformLocation(shaderProgramObject, "uLightDiffuse[0]");
            lightSpecularUniform[0] = glGetUniformLocation(shaderProgramObject, "uLightSpecular[0]");
            lightPositionUniform[0] = glGetUniformLocation(shaderProgramObject, "uLightPosition[0]");

            lightAmbientUniform[1] = glGetUniformLocation(shaderProgramObject, "uLightAmbient[1]");
            lightDiffuseUniform[1] = glGetUniformLocation(shaderProgramObject, "uLightDiffuse[1]");
            lightSpecularUniform[1] = glGetUniformLocation(shaderProgramObject, "uLightSpecular[1]");
            lightPositionUniform[1] = glGetUniformLocation(shaderProgramObject, "uLightPosition[1]");

            lightAmbientUniform[2] = glGetUniformLocation(shaderProgramObject, "uLightAmbient[2]");
            lightDiffuseUniform[2] = glGetUniformLocation(shaderProgramObject, "uLightDiffuse[2]");
            lightSpecularUniform[2] = glGetUniformLocation(shaderProgramObject, "uLightSpecular[2]");
            lightPositionUniform[2] = glGetUniformLocation(shaderProgramObject, "uLightPosition[2]");
            
            break;
            
        case 'f':
        case 'F':
            change = 'f';
            lightAmbientUniform[0] = glGetUniformLocation(shaderProgramObjectF, "uLightAmbient[0]");
            lightDiffuseUniform[0] = glGetUniformLocation(shaderProgramObjectF, "uLightDiffuse[0]");
            lightSpecularUniform[0] = glGetUniformLocation(shaderProgramObjectF, "uLightSpecular[0]");
            lightPositionUniform[0] = glGetUniformLocation(shaderProgramObjectF, "uLightPosition[0]");

            lightAmbientUniform[1] = glGetUniformLocation(shaderProgramObjectF, "uLightAmbient[1]");
            lightDiffuseUniform[1] = glGetUniformLocation(shaderProgramObjectF, "uLightDiffuse[1]");
            lightSpecularUniform[1] = glGetUniformLocation(shaderProgramObjectF, "uLightSpecular[1]");
            lightPositionUniform[1] = glGetUniformLocation(shaderProgramObjectF, "uLightPosition[1]");

            lightAmbientUniform[2] = glGetUniformLocation(shaderProgramObjectF, "uLightAmbient[2]");
            lightDiffuseUniform[2] = glGetUniformLocation(shaderProgramObjectF, "uLightDiffuse[2]");
            lightSpecularUniform[2] = glGetUniformLocation(shaderProgramObjectF, "uLightSpecular[2]");
            lightPositionUniform[2] = glGetUniformLocation(shaderProgramObjectF, "uLightPosition[2]");
            
            break;
        
        /*
        case 'F':
        case 'f':
            if(pf == TRUE)
            {
                pf = FALSE;
            }
            else
            {
                pf = TRUE;
            }
            break;
            
        case 'V':
        case 'v':
            if(pv == TRUE)
            {
                pv = FALSE;
            }
            else
            {
                pv = TRUE;
            }
            break;
        */
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
