#include "GL/freeglut.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#define _USE_MATH_DEFINES 1
#include <math.h>

struct point
{
    GLfloat x;
    GLfloat y;
};

struct point CircleCoord[100];
GLfloat CircleArray[200];
GLfloat triangle1[] = {1.0f, 0.0f, 0.0f, 0.0f, 0.5f, 0.0f,
                       0.0f, 1.0f, 0.0f, -0.5f, -0.5f, 0.0f,
                       0.0f, 0.f, 1.0f, 0.5f, -0.5f, 0.0f};

GLfloat rectangle[] = {1.0f, 0.0f, 0.0f, 0.5f, 0.5f,
                       0.0f, 1.0f, 0.0f, -0.5f, 0.5f,
                       0.0f, 0.0f, 1.0f, -0.5f, -0.5f,
                       0.5f, 0.5f, 0.0f, 0.5f, -0.5f};

void circle(GLfloat radius, GLfloat xCenter, GLfloat yCenter);

GLfloat yRot = 0;
void idle(void)
{
    yRot = yRot + 0.1f;

    glutPostRedisplay();
}

void main(int argc, char *argv[])
{
    // Function declarations
    void init(void);
    void display(void);
    void resize(int, int);
    void keyboard(unsigned char, int, int);
    void mouse(int, int, int, int);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(250, 250);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("MyWindow");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);

    glutMainLoop();
}

void init(void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}
void resize(int width, int height)
{
    circle(0.5, 0.0f, 0.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 1);

    glViewport(0, 0, width, height);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void circle(GLfloat radius, GLfloat xCenter, GLfloat yCenter)
{
    int i;
    GLfloat angle;
    for (i = 0; i < 100; i++)
    {
        angle = 2 * M_PI * (i / 100.0);
        CircleCoord[i].x = xCenter + radius * cos(angle);
        CircleCoord[i].y = yCenter + radius * sin(angle);
        CircleArray[i * 2] = CircleCoord[i].x;
        CircleArray[i * 2 + 1] = CircleCoord[i].y;

        // glVertex2f(xCenter + radius * cos(angle), yCenter + radius * sin(angle));
    }
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glColorPointer(3, GL_FLOAT, sizeof(GL_FLOAT) * 6, &triangle1[0]);
    glVertexPointer(3, GL_FLOAT, sizeof(GL_FLOAT) * 6, &triangle1[3]);

    // Method 1 ->glArrayElement
    glTranslatef(-0.5f, 0.0f, 0.0f);
    glRotatef(yRot, 1, 0, 0);
    glBegin(GL_TRIANGLES);
    glArrayElement(0);
    glArrayElement(1);
    glArrayElement(2);
    glEnd();

    // Method 2 -.glDrawElements()
    glColorPointer(3, GL_FLOAT, sizeof(GL_FLOAT) * 5, &rectangle[0]);
    glVertexPointer(2, GL_FLOAT, sizeof(GL_FLOAT) * 5, &rectangle[3]);

    GLuint indices[] = {0, 1, 2, 3};
    glLoadIdentity();
    glTranslatef(0.5f, 0.0f, 0.0f);
    glRotatef(yRot, 0, 1, 0);
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, indices);

    // Method 3 ->glDrawArrays()
    glLoadIdentity();
    glTranslatef(0.0f, -0.5f, 0.0f);
    glRotatef(yRot, 0, 0, 1);
    glDrawArrays(GL_QUADS, 0, 4);

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'e':
        glutIdleFunc(idle);
        break;

    case 'd':
        glutIdleFunc(NULL);
        break;
    }
}
void mouse(int key, int status, int x, int y)
{
}
