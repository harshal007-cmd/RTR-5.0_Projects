var canvas = null;
var gl = null;
var bFullscreen = false;
var canvas_original_width;
var canvas_original_height;

//Webgl related variables
const VertexAttributeEnum =
{
    AMC_ATTRIBUTE_POSITION:0,
    AMC_ATTRIBUTE_COLOR:1,
    AMC_ATTRIBUTE_NORMAL:2,
    AMC_ATTRIBUTE_TEXCOORD:3
};

var shaderProgramObject = null;

var VAO = null;
var VBO = null;
var mvpMatrixUniform;

var sphere = null;

var laUniform;		//light ambient
var ldUniform;		//light diffuse
var lsUniform;		//light specular
var lightPositionUniform;	//light position

//uniform
var modelMatrixUniform;
var viewMatrixUniform;
var projectionMatrixUniform;


//material
var kaUniform;	//material ambient
var kdUniform;	//material diffuse
var ksUniform;	//material specular
var shininessUniform;	//material shininess

//key pressed
var uKeyPressed; //key press for shader
//toggle light 
var bLight;


var perspectiveProjectionMatrix;


var requestAnimationFrame =
                            window.requestAnimationFrame ||         //chrome
                            window.webkitRequestAnimationFrame || //safari
                            window.mozRequestAnimationFrame ||     //moz
                            window.oRequestAnimationFrame ||        //opera
                            window.msRequestAnimationFrame;         //edge



//our main function
function main()
{
    //get canvas
    canvas = document.getElementById("HVS");
    if(canvas == null)
    {
        console.log("getting canvas failed");
    }
    else
    {
        console.log("getting canvas successeded");
    }

    //set canvas width and height for future use
    canvas_original_width = canvas.width;
    canvas_original_height = canvas.height;
    
    //register for keyboard events
    window.addEventListener("keydown", keyDown, false);

    //register for mouse events
    window.addEventListener("click", mouseDown, false);

    window.addEventListener("resize",resize, false);

    initialise();

    resize();

    display();
}

function keyDown(event)
{
    switch(event.keyCode)
    {
        case 81:
        case 113:
            uninitialise();
            window.close();
        
        case 70:
        case 102:
            toggleFullscreen();
            break;
        case 76:
            if (bLight == 0) {
                bLight = 1;
            }
            else {
                bLight = 0;
            }
            break;
        default:
            break;
    }

}

function mouseDown()
{
}

function toggleFullscreen()
{
    var fullscreen_element = 
                            document.fullscreenElement || 
                            document.webkitFullscreenElement ||
                            document.mozFullScreenElement ||
                            document.msFullscreenElement ||
                            null;

    //if not fullscreen
    if(fullscreen_element == null)
    {
        if(canvas.requestFullscreen)
            canvas.requestFullscreen();
        else if(canvas.webkitRequestFullscreen)
            canvas.webkitRequestFullscreen();
        else if(canvas.mozRequestFullScreen)
            canvas.mozRequestFullScreen();
        else if(canvas.msRequestFullscreen)
             canvas.msRequestFullscreen();

        bFullscreen = true;
    }
    else
    {
        if(document.exitFullscreen)
            document.exitFullscreen();
        else if(document.webkitExitFullscreen)
            document.webkitExitFullscreen();
        else if(document.mozCancelFullScreen)
            document.mozCancelFullScreen();
        else if(document.msExitFullscreen)
            document.msExitFullscreen();    
        
        bFullscreen = false;
    }
}

function initialise()
{
    //code
    //get context from above canvas
    gl = canvas.getContext("webgl2");
    if(gl == null)
    {
        console.log("getting webgl2 context failed");
    }
    else
    {
        console.log("getting webgl2 context successeded");
    }
    
    //set webgl2 context view width and view height properties
    gl.viewportWidth = canvas.width;
    gl.viewportHeight = canvas.height;

    var vertexShader = 
        "#version 300 es\n" +
        "precision highp int;" +
        "precision highp float;"+
        "in vec4 aPosition;" +
        "in vec3 aNormal;" +
        "uniform mat4 uModelViewMatrix;" +
        "uniform mat4 uViewMatrix;" +
        "uniform mat4 uProjectionMatrix;" +
        "uniform vec4 uLightPosition;" +
        "\n"+
        "uniform int uKeyPress;" +
        "out vec3 oTransformedNormals;"+
        "out vec3 oLightDirection;"+
        "out vec3 oViewerVector;"+
        "void main(void)" +
        "{" +
        "if(uKeyPress == 1)"+
        "{"+
        "vec4 iCoordinates = uViewMatrix * uModelViewMatrix * aPosition;"+
        "oTransformedNormals = mat3(uViewMatrix * uModelViewMatrix) * aNormal;"+
        "oLightDirection = vec3(uLightPosition - iCoordinates);"+
        "oViewerVector = -iCoordinates.xyz;"+
        "}"+
        "else"+
        "{"+
        "oTransformedNormals = vec3(0.0, 0.0, 0.0);"+
        "oLightDirection = vec3(0.0, 0.0, 0.0);"+
        "oViewerVector = vec3(0.0, 0.0, 0.0);"+
        "}"+
        "gl_Position = uProjectionMatrix * uViewMatrix * uModelViewMatrix * aPosition;"+
        "}";

    /*
    //vertex shader
    var vertexShader =
        "#version 300 es" +
        "\n" +
        "precision highp int;"+
        "in vec4 aPosition;" +
        "in vec3 aNormal;" +
        "uniform mat4 uModelViewMatrix;" +
        "uniform mat4 uViewMatrix;" +
        "uniform mat4 uProjectionMatrix;" +
        "uniform vec3 uLightAmbient;" +
        "uniform vec3 uLightDiffuse;" 
        "uniform vec3 uLightSpecular;" +
        "uniform vec4 uLightPosition;" +
        "uniform vec3 uMaterialAmbient;" +
        "uniform vec3 uMaterialDiffuse;" +
        "uniform vec3 uMaterialSpecular;" +
        "uniform float uMaterialShininess;" +
        "uniform int uKeyPress;" +
        "out vec3 oPhongADSLight;" +
        "void main(void)" +
        "{" +
        "   if(uKeyPress == 1)"+
        "   {"+
        "       vec4 iCoordinates = uViewMatrix * uModelViewMatrix * aPosition;"+
        "       vec3 transformedNormals = normalize(mat3(uViewMatrix * uModelViewMatrix) * aNormal);"+
        "       vec3 lightDirection = normalize(vec3(uLightPosition - iCoordinates));"+
        "       vec3 reflectionVector = reflect(-lightDirection, transformedNormals);"+
        "       vec3 viewerVector = normalize(-iCoordinates.xyz);"+
        "       vec3 ambientLight = uLightAmbient * uMaterialAmbient;"+
        "       vec3 diffuseLight = uLightDiffuse * uMaterialDiffuse * max(dot(lightDirection, transformedNormals),0.0);"+
        "       vec3 lightSpecular = uLightSpecular * uMaterialSpecular * pow(max(dot(reflectionVector, viewerVector),0.0),uMaterialShininess);"+
        "       oPhongADSLight = ambientLight + diffuseLight + lightSpecular;"+
        "   }"+
        "   else"+
        "   {"+
        "       oPhongADSLight = vec3(0.0f, 0.0f, 0.0f);"+
        "   }"+
        "   gl_Position = uProjectionMatrix * uViewMatrix * uModelViewMatrix * aPosition;"+
        "}";
        */

    var vertexShaderObject = gl.createShader(gl.VERTEX_SHADER);
    gl.shaderSource(vertexShaderObject, vertexShader);
    gl.compileShader(vertexShaderObject);

    if (gl.getShaderParameter(vertexShaderObject, gl.COMPILE_STATUS) == false) {
        var error = gl.getShaderInfoLog(vertexShaderObject);
        if (error.length > 0) {
            var log = "Vertex shader compilation error: " + error;
            alert(log);
            uninitialise();
        }
    }
    else {
        console.log("Vertex shader compile done!\n");
    }

    var fragmentShader =
        "#version 300 es" +
        "\n" +
        "precision highp int;"+
        "precision highp float;" +
        "in vec3 oTransformedNormals;"+
        "in vec3 oLightDirection;" +
        "in vec3 oViewerVector; "+
        "uniform vec3 uLightAmbient;" +
        "uniform vec3 uLightDiffuse;" +
        "uniform vec3 uLightSpecular;" +
        "\n"+
        "uniform vec3 uMaterialAmbient;" +
        "uniform vec3 uMaterialDiffuse;" +
        "uniform vec3 uMaterialSpecular;" +
        "uniform float uMaterialShininess;" +
        "uniform int uKeyPress;" +
        "out vec4 FragColor;" +
        "void main(void)" +
        "{" +
        "vec3 phongADSLight;"+
        "if(uKeyPress == 1)"+
        "{"+
        "	vec3 normalizedTransformedNormal = normalize(oTransformedNormals);"+
        "	vec3 normalizedLightDirection = normalize(oLightDirection);"+
        "	vec3 normalizedViewerVector = normalize(oViewerVector);"+
        "	vec3 ambientLight = uLightAmbient * uMaterialAmbient;"+
        "	vec3 diffuseLight = uLightDiffuse * uMaterialDiffuse * max(dot(normalizedLightDirection, normalizedTransformedNormal), 0.0);"+
        "	vec3 reflectionVector = reflect(-normalizedLightDirection, normalizedTransformedNormal);"+
        "	vec3 lightSpecular = uLightSpecular * uMaterialSpecular * pow(max(dot(reflectionVector, normalizedViewerVector), 0.0), uMaterialShininess);"+
        "	phongADSLight = ambientLight + diffuseLight + lightSpecular;"+
        "}"+
        "else"+
        "{"+
        "	phongADSLight = vec3(1.0, 1.0, 1.0);"+
        "}"+
        "	FragColor = vec4(phongADSLight, 1.0);"+
        "}";


    
    var fragmentShaderObject = gl.createShader(gl.FRAGMENT_SHADER);
    gl.shaderSource(fragmentShaderObject, fragmentShader);
    gl.compileShader(fragmentShaderObject);

    if (gl.getShaderParameter(fragmentShaderObject, gl.COMPILE_STATUS) == false) {
        var error = gl.getShaderInfoLog(fragmentShaderObject);
        if (error.length > 0) {
            var log = "Fragment shader compilation error: " + error;
            alert(log);
            uninitialise();
        }
    }
    else {
        console.log("Fragment shader compile done!\n");
    }

    //shader program object
    shaderProgramObject = gl.createProgram();
    gl.attachShader(shaderProgramObject, vertexShaderObject);
    gl.attachShader(shaderProgramObject, fragmentShaderObject);
    gl.bindAttribLocation(shaderProgramObject, VertexAttributeEnum.AMC_ATTRIBUTE_POSITION, "aPosition");
    gl.bindAttribLocation(shaderProgramObject, VertexAttributeEnum.AMC_ATTRIBUTE_NORMAL, "aNormal");
    gl.linkProgram(shaderProgramObject);

    if (gl.getProgramParameter(shaderProgramObject, gl.LINK_STATUS) == false) {
        var error = gl.getProgramInfoLog(shaderProgramObject);
        if (error.length > 0) {
            var log = "Shader program linking error: " + error;
            alert(log);
            uninitialise();
        }
    }
    else {
        console.log("Shader program linking done!\n");
    }

    //mvpMatrixUniform = gl.getUniformLocation(shaderProgramObject,"uMvpMatrix");
    modelMatrixUniform = gl.getUniformLocation(shaderProgramObject, "uModelViewMatrix");
    viewMatrixUniform = gl.getUniformLocation(shaderProgramObject, "uViewMatrix");
    projectionMatrixUniform = gl.getUniformLocation(shaderProgramObject, "uProjectionMatrix");

    //lights
    laUniform = gl.getUniformLocation(shaderProgramObject, "uLightAmbient");		//light ambient
    ldUniform = gl.getUniformLocation(shaderProgramObject, "uLightDiffuse");		//light diffuse
    lsUniform = gl.getUniformLocation(shaderProgramObject, "uLightSpecular");		//light specular
    lightPositionUniform = gl.getUniformLocation(shaderProgramObject, "uLightPosition");	//light position

    //material
    kaUniform = gl.getUniformLocation(shaderProgramObject, "uMaterialAmbient");	//material ambient
    kdUniform = gl.getUniformLocation(shaderProgramObject, "uMaterialDiffuse");	//material diffuse
    ksUniform = gl.getUniformLocation(shaderProgramObject, "uMaterialSpecular");	//material specular
    shininessUniform = gl.getUniformLocation(shaderProgramObject, "uMaterialShininess");	//material shininess

    uKeyPressed = gl.getUniformLocation(shaderProgramObject, "uKeyPress"); //key press for shader


    //sphere
    sphere = new Mesh();
    makeSphere(sphere, 2.0, 50, 50);
    
    //depth
    gl.clearDepth(1.0);
    gl.enable(gl.DEPTH_TEST);
    gl.depthFunc(gl.LEQUAL);


    //set clear color
    gl.clearColor(0.0, 0.0, 0.0, 1.0);

    //init projection matrix
    perspectiveProjectionMatrix = mat4.create();

}

function resize()
{
    //code
    if(bFullscreen == true)
    {
        canvas.width = window.innerWidth;
        canvas.height = window.innerHeight;
    }
    else
    {
        canvas.width = canvas_original_width;
        canvas.height = canvas_original_height;
    }

    //set viewport
    gl.viewport(0, 0, canvas.width, canvas.height);

    //set perspective position
    mat4.perspective(perspectiveProjectionMatrix, 45.0, parseFloat(canvas.width) / parseFloat(canvas.height), 0.1, 100.0);

}

function display()
{
    //code
    gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);

    gl.useProgram(shaderProgramObject);

    //x-formation
    var modelViewMatrix = mat4.create();
    var viewMatrix = mat4.create();
    var projectionMatrix = mat4.create();
   
    mat4.translate(modelViewMatrix, modelViewMatrix, [0.0, 0.0, -5.0]);
   // mat4.multiply(modelViewProjectionMatrix, perspectiveProjectionMatrix, modelViewMatrix);

    //gl.uniformMatrix4fv(mvpMatrixUniform, false, modelViewProjectionMatrix);
    projectionMatrix = perspectiveProjectionMatrix;

    gl.uniformMatrix4fv(modelMatrixUniform, false, modelViewMatrix);
    gl.uniformMatrix4fv(viewMatrixUniform, false, viewMatrix);
    gl.uniformMatrix4fv(projectionMatrixUniform, false, projectionMatrix);

    if (bLight == 1) {
        gl.uniform1i(uKeyPressed, 1);

        var lightAmbient = [0.1, 0.1, 0.1];
        gl.uniform3fv(laUniform, lightAmbient);

        var lightDiffuse = [1.0, 1.0, 1.0];
        gl.uniform3fv(ldUniform, lightDiffuse);

        var lightSpecular = [1.0, 1.0, 1.0];
        gl.uniform3fv(lsUniform, lightSpecular);

        var lightPosition = [100.0, 100.0, 100.0, 1.0];
        gl.uniform4fv(lightPositionUniform, lightPosition);

        var materialAmbient = [0.0, 0.0, 0.0];
        gl.uniform3fv(kaUniform, materialAmbient);

        var materialDiffuse = [0.5, 0.2, 0.7];
        gl.uniform3fv(kdUniform, materialDiffuse);

        var materialSpecular = [0.7, 0.7, 0.7];
        gl.uniform3fv(ksUniform, materialSpecular);

        var materialShininess = 128.0;
        gl.uniform1f(shininessUniform, materialShininess);
    }
    else {
        gl.uniform1i(uKeyPressed, 0);
    }



    sphere.draw();
    //gl.bindVertexArray(null);
    gl.useProgram(null);

    //set double buffering
    requestAnimationFrame(display, canvas);
}

function update()
{
    //code
}

function uninitialise() {
    //code
    if (shaderProgramObject) {
        // !shaderProgramObject
        gl.useProgram(shaderProgramObject);
        var shaderObjects = gl.getAttachedShaders(shaderProgramObject);
        if (shaderObjects || shaderObjects.length > 0) {
            for (let i = 0; i < shaderObjects.length; ++i) {
                gl.detachShader(shaderProgramObject, shaderObjects[i]);
                gl.deleteShader(shaderObjects[i]);
                shaderObjects[i] = null;
            }
        }

        gl.useProgram(null);
        gl.deleteProgram(shaderProgramObject);
        shaderProgramObject = null;
    }

    if (sphere) {
        sphere.deallocate();
        sphere = null;
    }

    if (VBO) {
        gl.deleteBuffer(VBO);
        VBO = null;

    }

    if (VAO) {
        gl.deleteVertexArray(VAO);
        VAO = null;
    }
}


