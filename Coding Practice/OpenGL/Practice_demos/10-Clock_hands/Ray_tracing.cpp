#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include <ctime>

const int windowWidth = 800;
const int windowHeight = 800;

// Function to draw a clock hand
void drawClockHand(float angle, float length) {
    glPushMatrix();
    glRotatef(angle, 0.0f, 0.0f, 1.0f);
    glBegin(GL_LINES);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.0f, length);
    glEnd();
    glPopMatrix();
}

// Function to draw the clock
void drawClock() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f); // Set color to white

    // Get the current time
    time_t currentTime = time(NULL);
    struct tm* timeinfo = localtime(&currentTime);

    // Calculate the angles for the clock hands
    float secondsAngle = 90 - timeinfo->tm_sec * 6;
    float minutesAngle = 90 - (timeinfo->tm_min * 6 + timeinfo->tm_sec * 0.1);
    float hoursAngle = 90 - (timeinfo->tm_hour % 12 * 30 + timeinfo->tm_min * 0.5);

    // Draw clock hands
    drawClockHand(secondsAngle, 0.9f);
    drawClockHand(minutesAngle, 0.7f);
    drawClockHand(hoursAngle, 0.5f);

    glFlush();
}

// Function to handle window resizing
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Moving Clock Hand");

    glutDisplayFunc(drawClock);
    glutReshapeFunc(reshape);

    glutMainLoop();

    return 0;
}
