//
//  MyView.m
//  01-Window
//
//  Created by Harshal Sali on 04/08/24.
//
#import <OpenGLES/ES3/gl.h>
#import <OpenGLES/ES3/glext.h>
#import "GLESView.h"
#import "vmath.h"
using namespace vmath;

GLuint vertexShaderObject = 0;
GLuint fragmentShaderObject = 0;
GLuint shaderProgramObject = 0;

enum
{
    AMC_ATTRIBUTE_POSITION = 0,
    AMC_ATTRIBUTE_TEXCOORDS = 1,
    
};


@implementation GLESView
{
    EAGLContext* eaglCotext;
    
    GLuint customFrameBuffer;
    GLuint colorRenderBuffer;
    GLuint depthRenderBuffer;
    
    id displayLink;
    NSInteger framesPerSeconds;
    BOOL isDisplayLink;

    GLuint shaderProgramObject;
       GLuint VAO_cube;
       GLuint VBO_cube_positions;
    GLuint VBO_texcoord_cube;
        
        GLuint textureImage;
        GLuint textureSamplerUniform;


       GLuint mvpMatrixUniform;
    vmath::mat4 perspectiveProjectionMatrix;  //in vmath

    GLfloat pAngle;
    GLfloat cAngle;
    
    
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
        glBindFramebuffer(GL_FRAMEBUFFER, customFrameBuffer);
        
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
        //opengl depecated from ios 11.4–
        
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
    
    const GLchar* vertexShaderCode =
            "#version 300 core" \
            "\n" \
            "precision highp float;" \
            "in vec4 aPosition;" \
            "in vec2 aTexcoords;"\
            "out vec2 oTexcoords;"\
            "uniform mat4 uMvpMatrix;" \
            "void main(void)" \
            "{" \
            "    gl_Position = uMvpMatrix * aPosition;" \
            "   oTexcoords = aTexcoords;"\
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
                    printf("Vertex Shader compilation error log: %s\n", szInfoLog);
                    free(szInfoLog);
                    szInfoLog = NULL;
                    [self uninitailize];//exit is available in this function

                    [self release];
                    //[NSApp terminate:self];
                }
            }
        }


        //Fragment shader
        const GLchar* fragmentShaderCode =
            "#version 300 core" \
            "\n" \
            "precision highp float;" \
            "in vec2 oTexcoords;" \
            "uniform sampler2D uTextureSampler;"
            "out vec4 FragColor;" \
            "void main(void)" \
            "{" \
            "    FragColor = texture(uTextureSampler, oTexcoords);" \
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
                    printf("Fragment shader compilation error log: %s\n", szInfoLog);
                    free(szInfoLog);
                    szInfoLog = NULL;
                    [self uninitailize];//exit is available in this function

                    [self release];
                    //[NSApp terminate:self];
                }
            }
        }

        //Create Shader program
        shaderProgramObject = glCreateProgram();
        glAttachShader(shaderProgramObject, vertexShaderObject);
        glAttachShader(shaderProgramObject, fragmentShaderObject);
        glBindAttribLocation(shaderProgramObject, AMC_ATTRIBUTE_POSITION, "aPosition");
    textureSamplerUniform = glGetUniformLocation(shaderProgramObject, "uTextureSampler");


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
                    printf("Shader program linking error log : %s\n", szInfoLog);
                    free(szInfoLog);
                    szInfoLog = NULL;
                    [self uninitailize];//exit is available in this function

                    [self release];
                    //[NSApp terminate:self];
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
        
    const GLfloat cube_texcoords[] =
            {

                // front
                1.0f, 1.0f, // top-right of front
                0.0f, 1.0f, // top-left of front
                0.0f, 0.0f, // bottom-left of front
                1.0f, 0.0f, // bottom-right of front

                // right
                1.0f, 1.0f, // top-right of right
                0.0f, 1.0f, // top-left of right
                0.0f, 0.0f, // bottom-left of right
                1.0f, 0.0f, // bottom-right of right

                // back
                1.0f, 1.0f, // top-right of back
                0.0f, 1.0f, // top-left of back
                0.0f, 0.0f, // bottom-left of back
                1.0f, 0.0f, // bottom-right of back

                // left
                1.0f, 1.0f, // top-right of left
                0.0f, 1.0f, // top-left of left
                0.0f, 0.0f, // bottom-left of left
                1.0f, 0.0f, // bottom-right of left

                // top
                1.0f, 1.0f, // top-right of top
                0.0f, 1.0f, // top-left of top
                0.0f, 0.0f, // bottom-left of top
                1.0f, 0.0f, // bottom-right of top

                // bottom
                1.0f, 1.0f, // top-right of bottom
                0.0f, 1.0f, // top-left of bottom
                0.0f, 0.0f, // bottom-left of bottom
                1.0f, 0.0f, // bottom-right of bottom
            };


        //VAO_cube - vertex array object
        glGenVertexArrays(1, &VAO_cube);
        glBindVertexArray(VAO_cube);

        //VBO for position - vertex buffer object
        glGenBuffers(1, &VBO_cube_positions);
        glBindBuffer(GL_ARRAY_BUFFER, VBO_cube_positions);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cube_position), cube_position, GL_STATIC_DRAW);
        glVertexAttribPointer(AMC_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        glEnableVertexAttribArray(AMC_ATTRIBUTE_POSITION);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

    //Texture
        glGenBuffers(1, &VBO_texcoord_cube);
            glBindBuffer(GL_ARRAY_BUFFER, VBO_texcoord_cube);
            glBufferData(GL_ARRAY_BUFFER, sizeof(cube_texcoords), cube_texcoords, GL_STATIC_DRAW);
            glVertexAttribPointer(AMC_ATTRIBUTE_TEXCOORDS, 2, GL_FLOAT, GL_FALSE, 0, NULL);
            glEnableVertexAttribArray(AMC_ATTRIBUTE_TEXCOORDS);
            glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindVertexArray(0);

    textureImage = [self loadGLTextures:@"Kundali" :@"bmp"];
        
    
    //Enabling depth
    glClearDepthf(1.0f);//depth buffer to 1
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);//check less than or equal to with 1.0f

    //Set the Clear color of Window to Blue
    glClearColor(0.0f, 0.0f, 0.1f, 1.0f); //here OpenGL starts


    return 0;
}

-(void)printGLInfo
{
    printf("OpenGL Vendor    : %s\n",glGetString(GL_VENDOR));
    printf("OpenGL Renderer  : %s\n",glGetString(GL_RENDERER));
    printf("OpenGL Version   : %s\n",glGetString(GL_VERSION));
    printf("OpenGL GLSL version %s\n",glGetString(GL_SHADING_LANGUAGE_VERSION));

}

-(GLuint)loadGLTextures:(NSString *)imageFileName :(NSString *)extension
{
    //code
    NSString *imageFileNameWithPath = [[NSBundle mainBundle]pathForResource:imageFileName ofType:extension];
    
    
    //get NSImage representation of imageFile
    UIImage *bmpImage = [[UIImage alloc]initWithContentsOfFile:imageFileNameWithPath];

    if(!bmpImage)
    {
        printf("NSImage conversion of image file failed\n");
        return(0);
    }

    //get CGImage representation of NSImage
    CGImageRef CGImage = [bmpImage CGImage];
    
    //get width & height of CGImage
    
    int imageWidth  = (int)CGImageGetWidth(CGImage);
    int imageHeight = (int)CGImageGetHeight(CGImage);
    
    //get core foundation representation data
    CFDataRef imageData = CGDataProviderCopyData(CGImageGetDataProvider(CGImage));
    
    //convert CFDataRefData into void* genericData.
    
    void *pixel = (void*)CFDataGetBytePtr(imageData);
    
    //OpenGL code
    GLuint texture;
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    //setting  texture parameter
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    //follwing call will actually push the data into graphic memory
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixel);
    glGenerateMipmap(GL_TEXTURE_2D);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    CFRelease(imageData);
    
    return(texture);
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
    
    perspectiveProjectionMatrix = vmath::perspective(45.0f, ((GLfloat)width / (GLfloat)height), 0.1f, 100.0f);
        

}

-(void)display
{
    //code
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shaderProgramObject);

    //X-formation
        mat4 modelViewMatrix = mat4::identity();

        mat4 translationMatrix = mat4::identity();
        translationMatrix = vmath::translate(0.0f, 0.0f, -4.0f);

        mat4 scaleMatrix = mat4::identity();
        scaleMatrix = vmath::scale(0.75f, 0.75f, 0.75f);

        mat4 rotationMatrix1 = mat4::identity();
        rotationMatrix1 = vmath::rotate(cAngle, 1.0f, 0.0f, 0.0f);

        mat4 rotationMatrix2 = mat4::identity();
        rotationMatrix2 = vmath::rotate(cAngle, 0.0f, 1.0f, 0.0f);

        mat4 rotationMatrix3 = mat4::identity();
        rotationMatrix3 = vmath::rotate(cAngle, 0.0f, 0.0f, 1.0f);

        mat4 rotationMatrix = rotationMatrix1 * rotationMatrix2 * rotationMatrix3;

        modelViewMatrix = translationMatrix * scaleMatrix * rotationMatrix;

        mat4 modelViewProjectionMatrix = mat4::identity();
        modelViewProjectionMatrix = perspectiveProjectionMatrix * modelViewMatrix;

        //Push above MVP info vertex shader's mvpUniform
        glUniformMatrix4fv(mvpMatrixUniform, 1, GL_FALSE, modelViewProjectionMatrix);

        glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, textureImage);
            glUniform1i(textureSamplerUniform, 0);

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
    cAngle += 0.8f;
            if (cAngle >= 360.0f)
            {
                cAngle = cAngle - 360.0f;
            }
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
