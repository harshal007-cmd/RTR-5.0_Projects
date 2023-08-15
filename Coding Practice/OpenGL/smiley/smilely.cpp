#include <GL/glut.h>
#include<math.h>
// Function to draw a circle
void drawCircle(float cx, float cy, float r, int num_segments) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= num_segments; ++i) {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 1.0f, 0.0f); // Yellow color
    drawCircle(0.0f, 0.0f, 0.5f, 100); // Draw the face

    glColor3f(0.0f, 0.0f, 0.0f); // Black color

    // Draw the eyes
    drawCircle(-0.2f, 0.2f, 0.1f, 50);
    drawCircle(0.2f, 0.2f, 0.1f, 50);

    // Draw the mouth (smile)
    glBegin(GL_LINES);
    glVertex2f(-0.2f, -0.3f);
    glVertex2f(0.2f, -0.3f);
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Smiley Face");

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Clear background color to black
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
