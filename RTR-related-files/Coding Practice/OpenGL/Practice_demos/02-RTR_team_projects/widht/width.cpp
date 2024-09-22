#include <GL/glut.h>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Set line color to white
    glColor3f(0.0f, 0.0f, 1.0f);

    // Draw 20 horizontal lines
    for (int i = 0; i < 20; i++) {
        if (i % 5 == 0) {
            // Change line width for every 5th line
            glLineWidth(2.0f);
        }
        else {
            // Reset line width to the default value
            glLineWidth(1.0f);
        }

        glBegin(GL_LINES);
        glVertex2f(-1.0f, -0.9f + i * 0.1f); // Start point (left side)
        glVertex2f(1.0f, -0.9f + i * 0.1f);  // End point (right side)
        glEnd();
    }

    glFlush();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600); // Set your desired window size
    glutCreateWindow("Horizontal Lines");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black

    glutMainLoop();

    return 0;
}
