// Header Files
#include <GL/freeglut_std.h>
#include<GL/gl.h>
#include<stdbool.h>
#include<GL/freeglut.h>
#include<stdio.h>
#define _USE_MATH_DEFINES 1
#include<math.h>
#include"MyMath.h"

#define ARRAY_LEN(arr) (sizeof(arr)/sizeof(arr[0]))

vec2 triangle[3] = {
    {.data[0] = -0.5,.data[1] = -0.5},
    {.data[0] = 0.0,.data[1] = 0.5},
    {.data[0] = 0.5,.data[1] = -0.5}
};

vec2 color[3] = {
    {.data[0] = 0.0,.data[1] = 1.0,.data[2] = 0.0},
    {.data[0] = 1.0,.data[1] = 0.0,.data[2] = 0.0},
    {.data[0] = 0.0,.data[1] = 0.0,.data[2] = 1.0}
};

void Translate(vec2 vertices[], int size, GLfloat x, GLfloat y)
{
    for (int i = 0; i < size; i++)
    {
        vertices[i] = data[0] += x;
        vertices[i] = data[1] += y;
    }
}

void Scale(vec2 vertices[], int size, GLfloat x, GLfloat y)
{
    for (int i = 0; i < size; i++)
    {
        vertices[i].data[0] *= x;
        vertices[i].data[1] *= y;
    }
}

void Rotate(vec2 vertices[], int size, GLfloat deg)
{
    float radian = deg * (M_PI / 180.f);

    for (int i = 0; i < size; i++)
    {
        GLfloat x = vertices[i].data[0];
        GLfloat y = vertices[i].data[1];

        vertices[i].data[0] = x * cosf(radian) - y * sinf(radian);
        vertices[i].data[1] = x * sinf(radian) + y * cosf(radian);
    }
}

// global variables
bool b_FullScreen = false;
GLfloat fade = 0.0f;


// Entry-point Function
int main(int argc, char* argv[])
{
    // local function declarations
    void initialize(void);
    void resize(int,int);
    void display(void);
    void update(int val);
    void keyboard(unsigned char,int,int);
    void mouse(int,int,int,int);
    void uninitialize(void);

    // code
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);

    glutInitWindowSize(800,600);
    glutInitWindowPosition(100,100);
    glutCreateWindow("HSBC");

    initialize();

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
   // glutTimerFunc(1000/60, update, 0);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutCloseFunc(uninitialize);

    glutMainLoop();

    return 0;
}

void initialize(void)
{
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void resize(int width, int height)
{
    //code
    if (height <= 0)
    {
        height = 1;

    }
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    glMatrixMode(GL_PROJECTION);//use GL_Projection from Matrix maths from OpenGL math lib
    glLoadIdentity();

    if (width <= height)
    {
        glOrtho(-1.0f,
            1.0f,
            -1.0f * ((GLfloat)height / (GLfloat)width),
            1.0f * ((GLfloat)height / (GLfloat)width),
            -1.0f,
            1.0f);
    }
    else
    {
        glOrtho(-1.0f * ((GLfloat)width / (GLfloat)height),
            1.0f * ((GLfloat)width / (GLfloat)height),
            -1.0f,
            1.0f,
            -1.0f,
            1.0f);
    }
    

}
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glBegin(GL_TRIANGLES);
    
    for (int i = 0;i < ARRAY_LEN(triangle);i++)
    {
        glColor3fv(colors[i].data);
        glVertex3fv(triangle[i].data);
    }
    
    glEnd();

    glutSwapBuffers();
}

void update(int val){

    if(fade <= 1.0f)
        fade += 0.005f;
        
    glutPostRedisplay();
    glutTimerFunc(1000/60, update, 0);
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'w':
        Translate(triangle, ARRAY_LEN(triangle), 0.0, 0.5);
        break;

    case 's':
        Translate(triangle, ARRAY_LEN(triangle), 0.0, -0.5);

        break;

    case 'd':
        Translate(triangle, ARRAY_LEN(triangle), 0.5, 0.0);

        break;

    case 'a':
        Translate(triangle, ARRAY_LEN(triangle), -0.5, 0.0);

        break;

    case 'q':
        Scale(triangle, ARRAY_LEN(triangle), 1.5, 1.5);

        break;

    case 'e':
        Scale(triangle, ARRAY_LEN(triangle), 0.5, 0.5);

        break;
    case r:
        Rotate(triangle, ARRAY_LEN(triangle), 45.0);
        break;

    case '1':
        
        break;

    case '2':
        break;

    case '3':

        break;

    case '4':
        break;

    }
}

void mouse(int button,int state,int x,int y)
{
    switch(button)
    {
        case GLUT_LEFT_BUTTON:
            glutLeaveMainLoop();
        break;
        default:
        break;
    }
}

void uninitialize(void)
{

}
