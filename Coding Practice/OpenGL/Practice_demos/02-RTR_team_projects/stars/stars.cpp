#include <GL/freeglut.h>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_POINTS);
    glColor3f(1.0, 1.0, 1.0); // White color

    int numPoints = 20;
    for (int i = 0; i < numPoints; ++i) {
        int x = rand() % (glutGet(GLUT_WINDOW_WIDTH) / 2);
        int y = (glutGet(GLUT_WINDOW_HEIGHT) / 2) + rand() % (glutGet(GLUT_WINDOW_HEIGHT) / 2);
        glVertex2i(x, y);
    }

    glEnd();

    glFlush();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0); // Black background
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, width, 0.0, height);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("20 Fixed Points in Second Quadrant");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();
    return 0;
}
