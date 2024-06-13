    package com.hvs.twoshapeswhite;
  
  
//opegles related

    import android.content.Context;
    import android.opengl.GLES32;
    import android.opengl.GLSurfaceView;
    import android.opengl.Matrix;
    import android.view.GestureDetector;
    import android.view.MotionEvent;

    import java.nio.ByteBuffer;
    import java.nio.ByteOrder;
    import java.nio.FloatBuffer;

    import javax.microedition.khronos.egl.EGLConfig;
    import javax.microedition.khronos.opengles.GL10;

public class GLESView extends GLSurfaceView implements GLSurfaceView.Renderer, GestureDetector.OnDoubleTapListener, GestureDetector.OnGestureListener
{
    private GestureDetector gestureDetector;

    //opengl related
    private int shaderProgramObject;

    private int[] VAO_Square = new int[1];
    private int[] VAO_Triangle = new int[1];
    private int[] VBO = new int[1];
    private int[] VBO_Square = new int[1];
   // private int[] VBO_Colored_Square = new int[1];
    private int[] VBO_Triangle = new int[1];
    //private int[] VBO_Colored_Triangle = new int[1];

    private int mvpMatrixUniform;
    private float[] perspectiveProjectionMatrix = new float[16];


    public GLESView(Context context){

        super(context);
        //Opengl Es related
        setEGLContextClientVersion(3);
        setRenderer(this);
        setRenderMode(GLSurfaceView.RENDERMODE_WHEN_DIRTY);

        //create and set Gesture detector object
        gestureDetector = new GestureDetector(context,this,null,false);
        gestureDetector.setOnDoubleTapListener(this);
    }

    //Implementation 3 method of GLSurface view interface
    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config)
    {
        initialize(gl);
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height)
    {
        resize(width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl)
    {
        display();
    }


    //implementation of OnTouch event of view class
    @Override
    public boolean onTouchEvent(MotionEvent e){

        if(!gestureDetector.onTouchEvent(e))
        {
            super.onTouchEvent(e);
        }
        return true;
    }

    @Override
    public boolean onDoubleTap(MotionEvent e)
    {
        return true;
    }

    @Override
    public boolean onDoubleTapEvent(MotionEvent e)
    {
        return true;
    }

    @Override
    public boolean onSingleTapConfirmed(MotionEvent e)
    {
        return true;
    }

    //Implementation of 3 methods of on double tap listener interface
    @Override
    public boolean onDown(MotionEvent e)
    {
        return true;
    }

    @Override
    public boolean onFling(MotionEvent e1,MotionEvent e2,float velocityX,float velocityY)
    {
        return true;
    }

    @Override
    public void onLongPress(MotionEvent e)
    {
    }

    @Override
    public boolean onScroll(MotionEvent e1, MotionEvent e2, float distanceX, float distanceY)
    {
        uninitialize();

        System.exit(0);

        return  true;
    }

    @Override
    public void onShowPress(MotionEvent e)
    {

    }

    @Override
    public boolean onSingleTapUp(MotionEvent e)
    {
        return true;
    }

    //Implementation of Private methods
    private void initialize(GL10 gl)
    {
        printGLInfo(gl);

        //Vertex shader
        final String vertexShaderCode = String.format
                ("#version 320 es"+
                        "\n" +
                        "in vec4 aPosition;"+
                        "uniform mat4 uMvpMatrix;"+
                        "void main(void)"+
                        "{"+
                        "	gl_Position = uMvpMatrix * aPosition;"+
                        "}");

        int vertexShaderObject = GLES32.glCreateShader(GLES32.GL_VERTEX_SHADER);
        GLES32.glShaderSource(vertexShaderObject,vertexShaderCode);
        GLES32.glCompileShader(vertexShaderObject);

        int[] shaderCompileStatus = new int[1];
        int[] infoLogLength = new int[1];
        String infoLog = null;

        GLES32.glGetShaderiv(vertexShaderObject,GLES32.GL_COMPILE_STATUS,shaderCompileStatus,0);
        if(shaderCompileStatus[0]==GLES32.GL_FALSE)
        {
            GLES32.glGetShaderiv(vertexShaderObject,GLES32.GL_INFO_LOG_LENGTH,infoLogLength,0);
            if(infoLogLength[0]>0)
            {
                infoLog= GLES32.glGetShaderInfoLog(vertexShaderObject);
                System.out.println("HVS: Vertex shader compilation log: "+infoLog);
                uninitialize();
                System.exit(0);
            }
        }

        //Fragment shader
        final String fragmentShaderCode = String.format(
                "#version 320 es"+
                "\n" +
                "precision highp float;"+
                "out vec4 FragColor;" +
                "void main(void)" +
                "{" +
                "	FragColor = vec4(1.0f,1.0f,1.0f,1.0f);" +
                "}");

        int fragmentShaderObject = GLES32.glCreateShader(GLES32.GL_FRAGMENT_SHADER);
        GLES32.glShaderSource(fragmentShaderObject,fragmentShaderCode);
        GLES32.glCompileShader(fragmentShaderObject);

        shaderCompileStatus[0] = 0;
        infoLogLength[0] = 0;
        infoLog = null;

        GLES32.glGetShaderiv(fragmentShaderObject,GLES32.GL_COMPILE_STATUS,shaderCompileStatus,0);
        if(shaderCompileStatus[0]==GLES32.GL_FALSE)
        {
            GLES32.glGetShaderiv(fragmentShaderObject,GLES32.GL_INFO_LOG_LENGTH,infoLogLength,0);
            if(infoLogLength[0]>0)
            {
                infoLog= GLES32.glGetShaderInfoLog(fragmentShaderObject);
                System.out.println("HVS: Fragment shader compilation log: "+infoLog);
                uninitialize();
                System.exit(0);
            }
        }

        //Shader program
        shaderProgramObject = GLES32.glCreateProgram();
        GLES32.glAttachShader(shaderProgramObject,vertexShaderObject);
        GLES32.glAttachShader(shaderProgramObject,fragmentShaderObject);
        GLES32.glBindAttribLocation(shaderProgramObject, VertexAttributesEnum.AMC_ATTRIBUTE_POSITION,"aPosition");
        GLES32.glBindAttribLocation(shaderProgramObject, VertexAttributesEnum.AMC_ATTRIBUTE_COLOR,"aColor");

        GLES32.glLinkProgram(shaderProgramObject);
        int[] programLinkStatus = new int[1];
        infoLogLength[0] = 0;
        infoLog = null;

        GLES32.glGetProgramiv(shaderProgramObject,GLES32.GL_LINK_STATUS,programLinkStatus,0);
        if(programLinkStatus[0] == GLES32.GL_FALSE)
        {
            GLES32.glGetProgramiv(shaderProgramObject,GLES32.GL_INFO_LOG_LENGTH,infoLogLength,0);
            if(infoLogLength[0]>0)
            {
                infoLog= GLES32.glGetProgramInfoLog(shaderProgramObject);
                System.out.println("HVS: Fragment shader compilation log: "+infoLog);
                uninitialize();
                System.exit(0);
            }
        }

        mvpMatrixUniform = GLES32.glGetUniformLocation(shaderProgramObject,"uMvpMatrix");


        //Geometry/Shape
        final float[] square_positions= new float[]{
                1.0f, 1.0f, 0.0f,
                -1.0f, 1.0f, 0.0f,
                -1.0f, -1.0f, 0.0f,
                1.0f,-1.0f,0.0f
        };

        final float[] triangle_positions= new float[]{
                0.0f, 1.0f, 0.0f,
                -1.0f, -1.0f, 0.0f,
                1.0f, -1.0f, 0.0f
        };


        //VAO_Square
        GLES32.glGenVertexArrays(1,VAO_Square,0);
        GLES32.glBindVertexArray(VAO_Square[0]);

        //VBO Square
        GLES32.glGenBuffers(1,VBO_Square,0);
        GLES32.glBindBuffer(GLES32.GL_ARRAY_BUFFER,VBO_Square[0]);

        //Prepare triangle vertices array for glBuffer data
        ByteBuffer byteBuffer = ByteBuffer.allocateDirect(square_positions.length*4);
        byteBuffer.order(ByteOrder.nativeOrder());
        FloatBuffer positionBuffer = byteBuffer.asFloatBuffer();
        positionBuffer.put(square_positions);
        positionBuffer.position(0);

        GLES32.glBufferData(GLES32.GL_ARRAY_BUFFER,square_positions.length*4,positionBuffer,GLES32.GL_STATIC_DRAW);
        GLES32.glVertexAttribPointer(VertexAttributesEnum.AMC_ATTRIBUTE_POSITION,3, GLES32.GL_FLOAT,false,0,0);
        GLES32.glEnableVertexAttribArray(VertexAttributesEnum.AMC_ATTRIBUTE_POSITION);
        GLES32.glBindBuffer(GLES32.GL_ARRAY_BUFFER,0);


        //VAO_Triangle
        GLES32.glGenVertexArrays(1,VAO_Triangle,0);
        GLES32.glBindVertexArray(VAO_Triangle[0]);

        //VBO Triangle
        GLES32.glGenBuffers(1,VBO_Triangle,0);
        GLES32.glBindBuffer(GLES32.GL_ARRAY_BUFFER,VBO_Triangle[0]);

        //Prepare triangle vertices array for glBuffer data
        byteBuffer = ByteBuffer.allocateDirect(triangle_positions.length*4);
        byteBuffer.order(ByteOrder.nativeOrder());
        positionBuffer = byteBuffer.asFloatBuffer();
        positionBuffer.put(triangle_positions);
        positionBuffer.position(0);

        GLES32.glBufferData(GLES32.GL_ARRAY_BUFFER,triangle_positions.length*4,positionBuffer,GLES32.GL_STATIC_DRAW);
        GLES32.glVertexAttribPointer(VertexAttributesEnum.AMC_ATTRIBUTE_POSITION,3, GLES32.GL_FLOAT,false,0,0);
        GLES32.glEnableVertexAttribArray(VertexAttributesEnum.AMC_ATTRIBUTE_POSITION);
        GLES32.glBindBuffer(GLES32.GL_ARRAY_BUFFER,0);

        /*
        //VBO for Color
        GLES32.glGenBuffers(1,VBO_Square,0);
        GLES32.glBindBuffer(GLES32.GL_ARRAY_BUFFER,VBO_Square[0]);

        //prepare vbo color
        byteBuffer = ByteBuffer.allocateDirect(square_positions.length*4);
        byteBuffer.order(ByteOrder.nativeOrder());
        FloatBuffer colorBuffer = byteBuffer.asFloatBuffer();
        positionBuffer.put(triangle_color);
        positionBuffer.position(0);

        GLES32.glBufferData(GLES32.GL_ARRAY_BUFFER,triangle_color.length*4,positionBuffer,GLES32.GL_STATIC_DRAW);
        GLES32.glVertexAttribPointer(VertexAttributesEnum.AMC_ATTRIBUTE_COLOR,3,GLES32.GL_FLOAT,false,0,0);
        GLES32.glEnableVertexAttribArray(VertexAttributesEnum.AMC_ATTRIBUTE_COLOR);
        GLES32.glBindBuffer(GLES32.GL_ARRAY_BUFFER,0);
        */


        GLES32.glBindVertexArray(0);


        //Depth enable settings
        GLES32.glClearDepthf(1.0f);
        GLES32.glEnable(GLES32.GL_DEPTH_TEST);
        GLES32.glDepthFunc(GLES32.GL_LEQUAL);

        //Enable back face culling
        GLES32.glEnable(GLES32.GL_CULL_FACE);
		GLES32.glCullFace(GLES32.GL_BACK);

        //Clear color
        GLES32.glClearColor(0.0f,0.0f,0.0f,1.0f);
		
	
        Matrix.setIdentityM(perspectiveProjectionMatrix,0);

    }

    private void printGLInfo(GL10 gl)
    {
        System.out.println("HVS: OpenGL ES renderer: "+ gl.glGetString(GL10.GL_RENDERER));
        System.out.println("HVS: OpenGL-ES version: " +gl.glGetString(GL10.GL_VERSION));
        System.out.println("HVS: OpenGL-ES Shading Language Version: "+gl.glGetString(GLES32.GL_SHADING_LANGUAGE_VERSION));

    }

    private void resize(int width, int height)
    {
        if(height<=0)
            height=1;

        GLES32.glViewport((int) 0, (int) 0,width, height);

        Matrix.perspectiveM(perspectiveProjectionMatrix,0,45.0f,(float)width/(float)height,0.1f,100.0f);
    }

    private void display()
    {
        GLES32.glClear(GLES32.GL_COLOR_BUFFER_BIT | GLES32.GL_DEPTH_BUFFER_BIT);

        GLES32.glUseProgram(shaderProgramObject);
		
        //X-formations
        float[] modelViewMatrix = new float[16];
        float[] modelViewProjectionMatrix = new float[16];

        //Triangle
        Matrix.setIdentityM(modelViewMatrix,0);
        Matrix.setIdentityM(modelViewProjectionMatrix,0);

        Matrix.translateM(modelViewMatrix,0,-1.5f,0.0f,-5.0f);
        Matrix.multiplyMM(modelViewProjectionMatrix,0,perspectiveProjectionMatrix,0,modelViewMatrix,0);

        //Push
        GLES32.glUniformMatrix4fv(mvpMatrixUniform,1,false,modelViewProjectionMatrix,0);
		
        //Bind with VAO_Square
        GLES32.glBindVertexArray(VAO_Triangle[0]);
        GLES32.glDrawArrays(GLES32.GL_TRIANGLES,0,3);

        //Square
        //Triangle
        Matrix.setIdentityM(modelViewMatrix,0);
        Matrix.setIdentityM(modelViewProjectionMatrix,0);

        Matrix.translateM(modelViewMatrix,0,1.5f,0.0f,-5.0f);
        Matrix.multiplyMM(modelViewProjectionMatrix,0,perspectiveProjectionMatrix,0,modelViewMatrix,0);

        //Push
        GLES32.glUniformMatrix4fv(mvpMatrixUniform,1,false,modelViewProjectionMatrix,0);

        //Bind with VAO_Square
        GLES32.glBindVertexArray(VAO_Square[0]);

        GLES32.glDrawArrays(GLES32.GL_TRIANGLE_FAN,0,4);


        GLES32.glBindVertexArray(0);
        GLES32.glUseProgram(0);

        //Render
        requestRender();


    }

    private void uninitialize()
    {
        if(shaderProgramObject>0)
        {
            GLES32.glUseProgram(shaderProgramObject);
            int[] rateVal = new int[1];
            GLES32.glGetProgramiv(shaderProgramObject,GLES32.GL_ATTACHED_SHADERS,rateVal,0);
            if(rateVal[0]>0)
            {
                int numAttachedShader = rateVal[0];
                int[] shaderObjects = new int[numAttachedShader];

                GLES32.glGetAttachedShaders(shaderProgramObject,numAttachedShader,rateVal,0,shaderObjects,0);
                for(int i=0;i<numAttachedShader;++i)
                {
                    GLES32.glDetachShader(shaderProgramObject,shaderObjects[i]);
                    GLES32.glDeleteShader(shaderObjects[i]);
                    shaderObjects[i] = 0;
                }
            }

            GLES32.glUseProgram(0);
            GLES32.glDeleteProgram(shaderProgramObject);
            shaderProgramObject = 0;
        }

        if(VBO_Square[0]>0)
        {
            GLES32.glDeleteBuffers(1,VBO_Square,0);
            VBO_Square[0] = 0;
        }

        if(VAO_Square[0]>0)
        {
            GLES32.glDeleteVertexArrays(1,VAO_Square,0);
            VAO_Square[0] = 0;
        }

        if(VBO_Triangle[0]>0)
        {
            GLES32.glDeleteBuffers(1,VBO_Triangle,0);
            VBO_Triangle[0] = 0;
        }

        if(VAO_Triangle[0]>0)
        {
            GLES32.glDeleteVertexArrays(1,VAO_Triangle,0);
            VAO_Triangle[0] = 0;
        }
         

    }


}
