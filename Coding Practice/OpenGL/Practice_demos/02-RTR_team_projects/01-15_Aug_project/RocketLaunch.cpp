#include <GL/glut.h> // GLUT library
#include <math.h>

// Rocket properties
float rocket_x = 0.0f;
float rocket_y = -0.9f;
float rocket_speed = 0.001f;
float rocket_acceleration = 0.000001f;

// Function to draw the rocket
void drawRocket() {
    glColor3f(1.0f, 0.0f, 0.0f); // Set color to red
    glBegin(GL_TRIANGLES);
    glVertex2f(rocket_x, rocket_y); // Bottom vertex
    glVertex2f(rocket_x - 0.05f, rocket_y + 0.2f); // Top-left vertex
    glVertex2f(rocket_x + 0.05f, rocket_y + 0.2f); // Top-right vertex
    glEnd();
}

// Function to draw the background
void drawBackground() {
    // Implement your background drawing code here
    // You can draw stars, moon, sky, etc.
}

// Function to update the rocket position and velocity
void updateRocket() {
    rocket_speed += rocket_acceleration;
    rocket_y += rocket_speed;
}

// Function to handle keyboard events
void keyboardFunc(unsigned char key, int x, int y) {
    if (key == ' ') { // Space key to trigger launch
        rocket_speed = 0.1f; // Set initial upward velocity
    }
}

// Function to display (render) the scene
void displayFunc() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawBackground();
    drawRocket();
    glutSwapBuffers();
}

// Function to handle window resize events
void reshapeFunc(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

// Function to update the scene
void updateScene(int value) {
    updateRocket();
    glutPostRedisplay();
    glutTimerFunc(15, updateScene, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Rocket Launch");
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glutDisplayFunc(displayFunc);
    glutReshapeFunc(reshapeFunc);
    glutKeyboardFunc(keyboardFunc);
    glutTimerFunc(0, updateScene, 0);

    glutMainLoop();
    return 0;
}
