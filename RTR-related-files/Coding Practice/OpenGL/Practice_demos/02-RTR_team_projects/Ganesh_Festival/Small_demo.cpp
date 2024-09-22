#include <GL/glut.h>
#define _USE_MATH_DEFINES 1
#include <math.h>

void drawCircle(float cx, float cy, float r, int num_segments) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < num_segments; i++) {
        float theta = 2.0f * M_PI * float(i) / float(num_segments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

void drawGaneshaFace() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f); // Set color to white

    // Draw Ganesha's face
    drawCircle(0.0f, 0.0f, 0.5f, 100); // Head

    // Draw eyes
    drawCircle(-0.2f, 0.2f, 0.05f, 50); // Left eye
    drawCircle(0.2f, 0.2f, 0.05f, 50);  // Right eye

    // Draw the trunk (simple representation)
    glBegin(GL_TRIANGLES);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.1f, -0.3f);
    glVertex2f(-0.1f, -0.3f);
    glEnd();

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
    glutInitWindowSize(400, 400);
    glutCreateWindow("Ganesha Face");
    glutDisplayFunc(drawGaneshaFace);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
