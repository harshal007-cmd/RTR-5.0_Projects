#include <GL/glut.h>
#include <cmath>
#define M_PI 3.145
const int windowWidth = 800;
const int windowHeight = 600;

void drawSineWave(float amplitude, float frequency, float phase, float yOffset, float r, float g, float b) {
    glBegin(GL_LINE_STRIP);

    glColor3f(r, g, b);

    for (int x = 0; x < windowWidth; x++) {
        float xPos = static_cast<float>(x);
        float yPos = amplitude * sin(2 * M_PI * frequency * (xPos / windowWidth) + phase) + yOffset;
        glVertex2f(xPos, yPos);
    }

    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    drawSineWave(100.0f, 1.0f, 0.0f, windowHeight / 2, 1.0f, 0.0f, 0.0f);
    drawSineWave(75.0f, 2.0f, 0.0f, windowHeight / 2, 0.0f, 1.0f, 0.0f);
    drawSineWave(50.0f, 3.0f, 0.0f, windowHeight / 2, 0.0f, 0.0f, 1.0f);

    glutSwapBuffers();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Sine Waves using GLUT");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glutMainLoop();
    return 0;
}
