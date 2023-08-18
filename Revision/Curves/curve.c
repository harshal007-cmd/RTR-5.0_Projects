// Header Files
#include<GL/freeglut_std.h>
#include<GL/gl.h>
#include<stdbool.h>
#include<GL/freeglut.h>
#include <stddef.h>
#include<stdio.h>
#include<math.h>

#include"MyMath.h"

#define  ARRAY_LENGTH(arr) (sizeof(arr) / sizeof(arr[0]))

// global variables
bool b_FullScreen = false;
static GLfloat t = 0.0f;

vec2 p0 = { -0.5f,-0.3f };
vec2 p1 = { -0.3f,0.2f };
vec2 p2 = { 0.3,0.2 };
vec2 p3 = { -0.5, -0.3 }; 
vec2 p;
vec2 a1, a2;
vec2 c1,c2,c3;
vec2* selected;

void vec2_translate(vec2* result, float x, float y)
{
    result->data[0] += x;
    result->data[1] += y;

}

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

    vec2_lerp(&c1, &p0, &p1, t);
    vec2_lerp(&c2, &p0, &p2, t);
    vec2_lerp(&c3, &p2, &p3, t);
    
    vec2_lerp(&a1 &c1, &c2, t);
    vec2_lerp(&a2, &c2, &c3, t);
    
    vec2_lerp(&p, &a1, &c3, t);


    glLineWidth(5.0);
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_LINES);
        glVertex2fv(p0.data);
        glVertex2fv(p1.data);

        glVertex2fv(p1.data);
        glVertex2fv(p2.data);

        glVertex2fv(p2.data);
        glVertex2fv(p3.data);

    glEnd();


    glPointSize(15.0);
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_POINTS);
        glColor3f(1.0, 0.0, 0.0);
        glVertex2fv(p0.data);
        glVertex2fv(p1.data);
        glVertex2fv(p2.data);
        glVertex2fv(p3.data);

        glColor3f(1.0, 0.0, 0.0);
        glVertex2fv(selected->data);

        glColor3f(1.0, 0.0, 0.0);
        glVertex2fv(p.data);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glColor3f(0.0, 0.0, 0.0);
    for (float i = 0;i <= 1.1;i += 0.1)
    {
        vec2_lerp(&c1, &p0, &p1, i);
        vec2_lerp(&c2, &p0, &p1, i);
        vec2_lerp(&c3, &p2, &p3, i);

        vec2_lerp(&a1 & c1, &c2, i);
        vec2_lerp(&a2, &c2, &c3, i);

        vec2_lerp(&p, &a1, &c3, i);
        glVertex2fv(f.data);
    }


    glEnd();
    glutSwapBuffers();
}

void update(int val){
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
        case 'W':
        case 'w':
            vec2_translate(selected, 0.0, 0.1);
        break;
        case 'S':
        case 's':
            vec2_translate(selected, 0.0, -0.1);
        break;
        case 'D':
        case 'd':
            vec2_translate(selected, 0.1, 0.0);
            break;
        case 'A':
        case 'a':
            vec2_translate(selected, -0.1, 0.0);
        break;
        case 'Q':
        case 'q':
            if (t < 1.0)
                t += 0.1;
        break;
        case 'E':
        case 'e':
            if (t < 0.1)
                t -= 0.1;
        break;
        case '1':
            selected = &p0;
            break;
        case '2':
            selected = &p1;
            break;
        case '3':
            selected = &p2;
            break;
        case '4':
            selected = &p4;
            break;

        case 'R':
        case 'r':
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
            //glutLeaveMainLoop();
        break;
        default:
        break;
    }
}

void uninitialize(void)
{

}
