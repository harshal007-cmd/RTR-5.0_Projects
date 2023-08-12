#include <GL/glut.h> // GLUT library
#include <math.h>

// Rocket properties
float rocket_x = -0.65f;
float rocket_y = 0.0f;
float rocket_speed = 0.00039f;
float rocket_acceleration = 0.000001f;

void GridLines()
{
    //rocket symmetry line
    glBegin(GL_LINES);
    glColor3f(0.0, 0.7, 0.0);
    glVertex2f(-0.65, 0.0);
    glVertex2f(-0.65, 0.75);
    glEnd();

    //grid lines
    glBegin(GL_LINES);
    glColor3f(0.0, 0.8, 0.0);
    glVertex3f(-1.0, 0.0, 0.0);
    glVertex3f(1.0, 0.0, 0.0);
    glVertex3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, -1.0, 0.0);
    glEnd();

}

// Function to draw the rocket
void drawRocket() {
    
    //xxxxxxxxxxxxxxxxxxxxxx Middle Cylinder Starts xxxxxxxxxxxxxxxxxxxxxxxxxxxxx//

    glBegin(GL_POLYGON);
    glColor3f(0.0, 1.0, 0.0);  //green
    glVertex3f(rocket_x, rocket_y, 0.0);//bottom left

    glColor3f(1.0, 1.0, 1.0);  //white
    glVertex3f(rocket_x, rocket_y+0.3, 0.0);//top left
    
    glColor3f(1.0, 0.5, 0.0);  //green

    glVertex3f(rocket_x+ 0.045, rocket_y + 0.3, 0.0);//top right
    
    glColor3f(0.3, 0.8, 0.3);  
    glVertex3f(rocket_x+ 0.045, rocket_y, 0.0);//bottom right
    glEnd();

    //Middle Cylinder Head Triangle
    glBegin(GL_TRIANGLES);
    glColor3f(0.9, 0.9, 0.9);
    glVertex2f(rocket_x, rocket_y + 0.3);//bottom left
   
    glColor3f(1.0, 0.5, 0.0);
    glVertex2f(rocket_x + 0.0225, rocket_y + 0.36);  //top
    glVertex2f(rocket_x + 0.045, rocket_y + 0.3);  //bottom right
    glEnd();

    //Middle cylinder exaust cover
    glBegin(GL_POLYGON);
    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(rocket_x - 0.008, rocket_y - 0.02, 0.0);//bottom left
    glVertex3f(rocket_x, rocket_y, 0.0);//top left
    glVertex3f(rocket_x + 0.045, rocket_y, 0.0);//top right
    glVertex3f(rocket_x + 0.053, rocket_y - 0.02, 0.0);//bottom right
    glEnd();

    //Middle cylinder exaust fire
    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 0.9, 0.0);
    glVertex2f(rocket_x - 0.008, rocket_y - 0.02);//top left
    glVertex2f(rocket_x + 0.053, rocket_y - 0.02);  //top right

    glColor3f(0.8, 0.0, 0.0);
    glVertex2f(rocket_x + 0.0225, rocket_y - 0.092);  //down
    glEnd();

    //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx Middle Full Cylinder Ends xxxxxxxxxxxxxxxxxxxxxxxxxx


    //xxxxxxxxxxxxxxxxxxxxxx Left Cylinder Starts xxxxxxxxxxxxxxxxxxxxxxxxxxxxx//

    glBegin(GL_POLYGON);
    glColor3f(0.0, 1.0, 0.0); 
    glVertex3f(rocket_x - 0.03, rocket_y + 0.027, 0.0);//bottom left

    
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(rocket_x-0.03, rocket_y + 0.25, 0.0);//top left
   
    glColor3f(1.0, 0.5, 0.0);
    glVertex3f(rocket_x, rocket_y + 0.25, 0.0);//top right

    glColor3f(0.3, 0.8, 0.3);
    glVertex3f(rocket_x, rocket_y+0.027, 0.0);//bottom right
    glEnd();

    //Left Cylinder Head Triangle
    glBegin(GL_TRIANGLES);
    glColor3f(0.9, 0.9, 0.9);
    glVertex2f(rocket_x - 0.03, rocket_y + 0.25);//bottom left

    glColor3f(1.0, 0.5, 0.0);
    glVertex2f(rocket_x - 0.0150, rocket_y + 0.3);  //top
    glVertex2f(rocket_x, rocket_y + 0.25);  //bottom right
    glEnd();

    
    //Left cylinder exaust cover
    glBegin(GL_POLYGON);
    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(rocket_x - 0.035, rocket_y + 0.010, 0.0);//bottom left
    glVertex3f(rocket_x - 0.03, rocket_y + 0.027, 0.0);//top left
    glVertex3f(rocket_x, rocket_y + 0.027, 0.0);//top right
    glVertex3f(rocket_x + 0.005 , rocket_y + 0.010, 0.0);//bottom right
    glEnd();

    
    //Left cylinder exaust fire
    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 0.9, 0.0);
    glVertex2f(rocket_x - 0.035, rocket_y + 0.010);//top left
    glVertex2f(rocket_x + 0.005, rocket_y + 0.010);  //top right

    glColor3f(0.8, 0.0, 0.0);
    glVertex2f(rocket_x - 0.0150, rocket_y - 0.072);  //down
    glEnd();

    //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx Left Full Cylinder Ends xxxxxxxxxxxxxxxxxxxxxxxxxx
    

    
    //xxxxxxxxxxxxxxxxxxxxxx Right Cylinder Starts xxxxxxxxxxxxxxxxxxxxxxxxxxxxx//

    glBegin(GL_POLYGON);
    glColor3f(0.0, 1.0, 0.0); //green
    glVertex3f(rocket_x + 0.045, rocket_y + 0.027, 0.0);//bottom left

    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(rocket_x + 0.045, rocket_y + 0.25, 0.0);//top left
    
    glColor3f(1.0, 0.5, 0.0);
    glVertex3f(rocket_x+0.075, rocket_y + 0.25, 0.0);//top right
    
    glColor3f(0.3, 0.8, 0.3); //green
    glVertex3f(rocket_x+0.075, rocket_y + 0.027, 0.0);//bottom right
    glEnd();

    //Right Cylinder Head Triangle
    glBegin(GL_TRIANGLES);
    glColor3f(0.9, 0.9, 0.9);
    glVertex2f(rocket_x + 0.045, rocket_y + 0.25);//bottom left

    glColor3f(1.0, 0.5, 0.0);
    glVertex2f(rocket_x + 0.060, rocket_y + 0.3);  //top
    glVertex2f(rocket_x + 0.075, rocket_y + 0.25);  //bottom right
    glEnd();


    //Right cylinder exaust cover
    glBegin(GL_POLYGON);
    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(rocket_x + 0.040, rocket_y + 0.010, 0.0);//bottom left
    glVertex3f(rocket_x + 0.045, rocket_y + 0.027, 0.0);//top left
    glVertex3f(rocket_x + 0.075, rocket_y + 0.027, 0.0);//top right
    glVertex3f(rocket_x + 0.080, rocket_y + 0.010, 0.0);//bottom right
    glEnd();


    //Right cylinder exaust fire
    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 0.9, 0.0);
    glVertex2f(rocket_x + 0.040, rocket_y + 0.010);//top left
    glVertex2f(rocket_x + 0.080, rocket_y + 0.010);  //top right

    glColor3f(0.8, 0.0, 0.0);
    glVertex2f(rocket_x + 0.060, rocket_y - 0.072);  //down
    glEnd();

    //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx Right Full Cylinder Ends xxxxxxxxxxxxxxxxxxxxxxxxxx


    //xxxxxxxxxxx IND name xxxxxxxxxxxxxxxxxx//
    glBegin(GL_LINES);
    glColor3f(0.0, 0.0, 0.0);
    // I
    glVertex2f(rocket_x+0.007, rocket_y + 0.25); //upper left point
    glVertex2f(rocket_x + 0.037, rocket_y + 0.25); // upper right point
  
    glVertex2f(rocket_x + 0.0225, rocket_y + 0.25); //middle line upper point
    glVertex2f(rocket_x + 0.0225, rocket_y + 0.20); //middle line lower point
    
    glVertex2f(rocket_x + 0.007, rocket_y + 0.20); //lower left point
    glVertex2f(rocket_x + 0.037, rocket_y + 0.20); //lower right point

    glEnd();
   
    // N

    glBegin(GL_LINES);
    glColor3f(0.0, 0.0, 0.0);
  
    glVertex2f(rocket_x + 0.007, rocket_y + 0.18); //upper left point
    glVertex2f(rocket_x + 0.007, rocket_y + 0.12); // lower right point

    glVertex2f(rocket_x + 0.007, rocket_y + 0.18); //middle line upper point
    glVertex2f(rocket_x + 0.037, rocket_y + 0.12); //middle line lower point

    glVertex2f(rocket_x + 0.037, rocket_y + 0.12); //lower left point
    glVertex2f(rocket_x + 0.037, rocket_y + 0.18); //upper right point

    glEnd();

    
    // D
    glBegin(GL_LINES);
    glColor3f(0.0, 0.0, 0.0);

    glVertex2f(rocket_x + 0.007, rocket_y + 0.10); //upper left point
    glVertex2f(rocket_x + 0.037, rocket_y + 0.10); // upper right point

    glVertex2f(rocket_x + 0.018, rocket_y + 0.10); //middle line upper point
    glVertex2f(rocket_x + 0.018, rocket_y + 0.05); //middle line lower point

    glVertex2f(rocket_x + 0.007, rocket_y + 0.05); //lower left point
    glVertex2f(rocket_x + 0.037, rocket_y + 0.05); //upper right point
    
    glVertex2f(rocket_x + 0.037, rocket_y + 0.10); //right line of D
    glVertex2f(rocket_x + 0.037, rocket_y + 0.05); //right line of D


    glEnd();
 
    //xxxxxxxxxxxxxx  IND name End xxxxxxxxxxxx//
}


// Function to update the rocket position and velocity
void updateRocket() {
  //  rocket_speed += rocket_acceleratio;
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
    GridLines();
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
