#include <iostream>
#include <GL/glut.h>
#include <cmath>

const int WIDTH = 1000;
const int HEIGHT = 800;
const int NUM_STARS = 1000;
const int SLICES = 50;
const int STACKS = 50;



struct Star {
    float x;
    float y;
    float z;
    float size;
};

Star stars[NUM_STARS];

void init()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, static_cast<float>(WIDTH) / static_cast<float>(HEIGHT), 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);

    // Generate random star positions and sizes
    for (int i = 0; i < NUM_STARS; ++i) {
        stars[i].x = (static_cast<float>(rand()) / RAND_MAX) * 100.0f - 50.0f;
        stars[i].y = (static_cast<float>(rand()) / RAND_MAX) * 100.0f - 50.0f;
        stars[i].z = -static_cast<float>(rand()) / RAND_MAX * 100.0f;
        stars[i].size = static_cast<float>(rand() % 5) + 1.0f;
    }

    
    

    
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    gluLookAt(0.0f, 0.0f, 5.0f,  // Eye position
        0.0f, 0.0f, 0.0f,  // Look-at point
        0.0f, 1.0f, 0.0f); // Up vector

    // Render stars
    glColor3f(1.0f, 1.0f, 1.0f); // White color

    glPointSize(2.0f); // Set the point size for stars

    glBegin(GL_POINTS);
    for (int i = 0; i < NUM_STARS; ++i) {
        glVertex3f(stars[i].x, stars[i].y, stars[i].z);
    }  

    glEnd();

    glFlush();
}

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, static_cast<float>(width) / static_cast<float>(height), 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("OpenGL: 3D Space Effect");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    init();
    glutMainLoop();
    return 0;
}
