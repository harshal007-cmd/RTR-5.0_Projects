#include <GL/glut.h>
#include <cmath>
#define M_PI 3.14
const int numSlices = 50; // Number of slices for the cylinder
const float cylinderRadius = 0.5f; // Radius of the cylinder
const float cylinderHeight = 1.0f; // Height of the cylinder

void drawCylinder()
{
    // Compute the angle between slices
    const float angle = 2.0f * M_PI / numSlices;

    glBegin(GL_TRIANGLE_STRIP);
    for (int i = 0; i <= numSlices; i++)
    {
        // Compute the current angle for the slice
        float theta = i * angle;

        // Compute the x and z coordinates of the current vertex
        float x = cylinderRadius * cos(theta);
        float z = cylinderRadius * sin(theta);

        // Draw the bottom vertex
        glVertex3f(x, -cylinderHeight / 2.0f, z);

        // Draw the top vertex
        glVertex3f(x, cylinderHeight / 2.0f, z);
    }
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0.0f, 0.0f, -5.0f); // Move the cylinder away from the camera

    glColor3f(1.0f, 1.0f, 0.0f); // Set the color to red

    // Rotate the cylinder around the y-axis
    glRotatef(45.0f, 0.0f, 1.0f, 0.0f);

    // Draw the cylinder
    drawCylinder();

    glFlush();
}

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)width / (float)height, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("3D Cylinder");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glEnable(GL_DEPTH_TEST);

    glutMainLoop();

    return 0;
}
