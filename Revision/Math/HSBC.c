// Header Files
#include <GL/freeglut_std.h>
#include<GL/gl.h>
#include<stdbool.h>
#include<GL/freeglut.h>
#include<stdio.h>
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

// global variables
bool b_FullScreen = false;
GLfloat fade = 0.0f;

float myrand(float min, float max)
{
    return min + (rand() / (RAND_MAX / (max -min)));
}

// liear interpolation // lerp // smoothstep
float lerp(float start, float end, float t){
    return start + t * (end - start);
}

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
    glutTimerFunc(1000/60, update, 0);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutCloseFunc(uninitialize);

    glutMainLoop();

    return 0;
}

void initialize(void)
{
    glClearColor(1.0f,1.0f,1.0f,1.0f);
    
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void resize(int width,int height)
{
    glViewport(0,0,width,height);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, lerp(1.0f,0.0f,fade),lerp(1.0f,0.0f,fade));
    // glColor4f(1.0f, 0.0f, 0.0f, 0.5f);

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

void keyboard(unsigned char key,int x,int y)
{
    switch(key)
    {
        case 27:
            glutLeaveMainLoop();
        break;
        case 'F':
        case 'f':
            if(b_FullScreen == false)
            {
                glutFullScreen();
                b_FullScreen = true;
            }else
            {
                glutLeaveFullScreen();
                b_FullScreen = false;
            }
        break;
        default:

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
