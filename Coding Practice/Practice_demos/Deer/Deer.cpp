#include <GL/glut.h>

void drawDeer() {
    // Body
    glColor3f(0.6f, 0.4f, 0.2f);  // Brown color
    glBegin(GL_POLYGON);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(1.0f, 0.0f);
    glVertex2f(1.0f, 1.5f);
    glVertex2f(0.0f, 1.5f);
    glEnd();

    // Legs
    glColor3f(0.2f, 0.2f, 0.2f);  // Dark gray color
    glBegin(GL_POLYGON);
    glVertex2f(0.25f, 0.0f);
    glVertex2f(0.5f, 0.0f);
    glVertex2f(0.5f, -1.0f);
    glVertex2f(0.25f, -1.0f);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(0.75f, 0.0f);
    glVertex2f(1.0f, 0.0f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(0.75f, -1.0f);
    glEnd();

    // Head
    glColor3f(0.6f, 0.4f, 0.2f);  // Brown color
    glBegin(GL_POLYGON);
    glVertex2f(1.0f, 1.5f);
    glVertex2f(1.5f, 1.5f);
    glVertex2f(1.5f, 2.0f);
    glVertex2f(1.0f, 2.0f);
    glEnd();

    // Antlers
    glColor3f(0.4f, 0.2f, 0.0f);  // Dark brown color
    glBegin(GL_LINES);
    glVertex2f(1.1f, 2.0f);
    glVertex2f(1.1f, 2.3f);
    glVertex2f(1.4f, 2.0f);
    glVertex2f(1.4f, 2.3f);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // Translate the deer to the center of the screen
    glTranslatef(-0.5f, -0.5f, 0.0f);

    drawDeer();

    glFlush();
}

void reshape(int width, int height) {
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (GLdouble)width, 0.0, (GLdouble)height);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Deer Example");
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
