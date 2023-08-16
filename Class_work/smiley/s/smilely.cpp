#include <GL\freeglut.h>
#include<math.h>

bool bIsFullScreen = false;

void GridLines()
{

    //grid lines
    glBegin(GL_LINES);
    glColor3f(0.0, 0.8, 0.0);
    glVertex3f(-1.0, 0.0, 0.0);
    glVertex3f(1.0, 0.0, 0.0);
    glVertex3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, -1.0, 0.0);
    glEnd();

}

// Function to draw the curved line
void mouth() 
{
    glBegin(GL_LINES);
    glColor3f(0.0, 0.0, 0.0);
    glVertex2f(-0.25f, -0.25f);
    glVertex2f(0.25f, -0.25f);

    glEnd();

}
//circle
void circle(float cx, float cy, float r, int num_points) {
    
    glBegin(GL_TRIANGLE_FAN);
    //glColor3f(1.0, 0.0, 0.0);
    for (int i = 0; i < num_points; i++) {
        float angle = 2.0f * 3.1415926f * float(i) / float(num_points);  
        float x = r * cosf(angle);  
        float y = r * sinf(angle);  
        glVertex2f(cx + x, cy + y); 
    }
    glEnd();

    

}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 0.0f, 0.0f);  
    //face
    circle(0.0f, 0.0f, 0.5f, 100);  // Center at (0, 0), radius 0.5, 100 segments
    
    //eyes
    glColor3f(0.0f, 0.0f, 0.0f);  

    circle(-0.20,0.20,0.08,100);
    circle(0.20,0.20,0.08,100);

    mouth();
    GridLines();
    glutSwapBuffers();
}

int main(int argc, char** argv) 
{

    //function declarations
    void initialize(void);
    void resize(int, int);
    void display(void);
    void keyboard(unsigned char, int, int);
    void mouse(int, int, int, int);
    void uninitialize(void);
  
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Smiley");

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Clear background color to black
  
    glutDisplayFunc(display);


    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutCloseFunc(uninitialize);
    glutMainLoop();

    return 0;
}

void initialize(void)
{
    //code
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

}

void resize(int width, int height)
{
    //code
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glViewport(0, 0, (GLsizei)width, (GLsizei)height);

}


void keyboard(unsigned char key, int x, int y)
{
    //code
    switch (key)
    {
    case 27:
        glutLeaveMainLoop();
        break;

    case 'F':
    case 'f':
        if (bIsFullScreen == false)
        {
            glutFullScreen();
            bIsFullScreen = true;
        }
        else
        {
            glutLeaveFullScreen();
            bIsFullScreen = false;
        }
        break;

    default:
        break;
    }
}
void mouse(int button, int state, int x, int y)
{
    //code
    switch (button)
    {
    case GLUT_RIGHT_BUTTON:
        glutLeaveMainLoop();
        break;

    default:
        break;
    }
}

void uninitialize(void)
{
    //code 
}


