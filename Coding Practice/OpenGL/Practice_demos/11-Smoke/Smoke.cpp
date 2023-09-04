#include <GL/freeglut.h>
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int NUM_PARTICLES = 200;
const float GRAVITY = 0.0005;
const float PARTICLE_SIZE = 0.02;
const float MAX_VELOCITY = 0.02;
const float INITIAL_VELOCITY = 0.01;

struct Particle {
    float x, y, z;
    float velocity;
};

std::vector<Particle> particles(NUM_PARTICLES);

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);

    for (int i = 0; i < NUM_PARTICLES; i++) {
        particles[i].x = static_cast<float>(rand() % WINDOW_WIDTH);
        particles[i].y = 0.0;
        particles[i].z = 0.0;
        particles[i].velocity = INITIAL_VELOCITY + static_cast<float>(rand()) / RAND_MAX * MAX_VELOCITY;
    }
}

void drawParticles() {
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_POINTS);
    for (int i = 0; i < NUM_PARTICLES; i++) {
        glVertex3f(particles[i].x, particles[i].y, particles[i].z);
    }
    glEnd();

    glutSwapBuffers();
}

void updateParticles(int value) {
    for (int i = 0; i < NUM_PARTICLES; i++) {
        particles[i].y += particles[i].velocity;
        particles[i].velocity -= GRAVITY;

        if (particles[i].y < 0.0) {
            particles[i].y = 0.0;
            particles[i].velocity = INITIAL_VELOCITY + static_cast<float>(rand()) / RAND_MAX * MAX_VELOCITY;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(16, updateParticles, 0);
}

int main(int argc, char** argv) {
    srand(static_cast<unsigned int>(time(NULL)));

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Smoke Effect");

    init();
    glutDisplayFunc(drawParticles);
    glutTimerFunc(0, updateParticles, 0);
    glutMainLoop();

    return 0;
}
