#include <GL/freeglut.h> // GLUT library
#define _USE_MATH_DEFINES

#include <math.h>
bool bIsFullScreen = false;

// Rocket properties
float rocket_x = -0.65f;
float rocket_y = -0.2f;
float rocket_speed = 0.00041f;
float rocket_acceleration = 0.000001f;

void Flag1()
{
    float xCenter = 0.01f, yCenter = 0.4f;
    float radius = 0.015f;
    float len = 0.1f;

    float x = 0.01, y;

    glColor3f(1.0f, 0.5f, 0);//orange

    for (int j = 0; j < 3; j++)
    {
        glBegin(GL_TRIANGLE_STRIP);
        for (int i = 0; i < 300; i++)
        {
            x = x + 0.001;
            y = yCenter + (0.01) * sin(2 * M_PI * (i / 300.0));
            glVertex2f(x, y);
            glVertex2f(x, y + 0.1);
        }
        glEnd();


        yCenter -= 0.1;
        x = 0.01;
        if (j == 0)
        {
            glColor3f(1, 1, 1); //white

        }

        if (j == 1)
        {
            glColor3f(0, 1, 0); //blue

        }
    }

    // Orange
    /*glBegin(GL_QUADS);

    glColor3f(1.0f, 0.5f, 0.0f); // color (orange)
    glVertex2f(0.01f, 0.5f);
    glVertex2f(0.3f, 0.5f);
    glVertex2f(0.3f, 0.4f);
    glVertex2f(0.01f, 0.4f);
    glEnd();

    // White
    glBegin(GL_QUADS);

    glColor3f(1.0f, 1.0f, 1.0f); // color (white)
    glVertex2f(0.01f, 0.4f);
    glVertex2f(0.3f, 0.4f);
    glVertex2f(0.3f, 0.3f);
    glVertex2f(0.01f, 0.3f);
    glEnd(); */

    // Ashoka Chakra
    float x_center = 0.15f;
    float y_center = 0.35f;
    glColor3f(0.0f, 0.0f, 1.0f); // color(Dark Blue)
    glBegin(GL_LINE_LOOP);

    for (int i = 0; i < 100; i++)
    {
        float angle = 2.0f * M_PI * i / 100;
        glVertex2f(x_center + 0.05 * cos(angle), y_center + 0.05 * sin(angle));
    }
    glEnd();

    glBegin(GL_LINES);

    for (int i = 0; i < 24; i++)
    {
        float angle = 2.0f * M_PI * i / 24;
        glVertex2f(x_center, y_center);
        glVertex2f(x_center + 0.05 * cos(angle), y_center + 0.05 * sin(angle));
    }
    glEnd();

    // Green
    /*glBegin(GL_QUADS);

    glColor3f(0.0f, 0.39f, 0.0f); // color (Green)
    glVertex2f(0.01f, 0.3f);
    glVertex2f(0.3f, 0.3f);
    glVertex2f(0.3f, 0.2f);
    glVertex2f(0.01f, 0.2f);
    glEnd(); */

    // Flag Pole
    glBegin(GL_POLYGON);

    glColor3f(0.67f, 0.67f, 0.67f); // color (grey) 
    glVertex2f(-0.01f, 0.5f);
    glVertex2f(0.01f, 0.5f);
    glVertex2f(0.01f, -0.5f);
    glVertex2f(-0.01f, -0.5f);
    glEnd();

    //Base
    glBegin(GL_QUADS);

    glColor3f(0.50f, 0.50f, 0.50f);
    glVertex2f(-0.09f, -0.5f);
    glVertex2f(0.09f, -0.5f);
    glVertex2f(0.09f, -0.55f);
    glVertex2f(-0.09f, -0.55f);
    glEnd();

    //Base 02
    glBegin(GL_QUADS);

    glColor3f(0.41f, 0.41, 0.41f);
    glVertex2f(-0.11f, -0.55f);
    glVertex2f(0.11f, -0.55f);
    glVertex2f(0.11f, -0.6f);
    glVertex2f(-0.11f, -0.6f);
    glEnd();

}

void Flag2()
{
    float xCenter = 0.01f, yCenter = 0.4f;
    float radius = 0.015f;
    float len = 0.1f;

    float x = 0.01, y;

    glColor3f(1.0f, 0.5f, 0);//orange

    for (int j = 0; j < 3; j++)
    {
        glBegin(GL_TRIANGLE_STRIP);
        for (int i = 0; i < 300; i++)
        {
            x = x + 0.001;
            y = yCenter + (0.01) * sin(2 * M_PI * (i / 300.0));
            glVertex2f(x, y);
            glVertex2f(x, y + 0.1);
        }
        glEnd();


        yCenter -= 0.1;
        x = 0.01;
        if (j == 0)
        {
            glColor3f(1, 1, 1); //white

        }

        if (j == 1)
        {
            glColor3f(0, 1, 0); //blue

        }
    }

    // Orange
    /*glBegin(GL_QUADS);

    glColor3f(1.0f, 0.5f, 0.0f); // color (orange)
    glVertex2f(0.01f, 0.5f);
    glVertex2f(0.3f, 0.5f);
    glVertex2f(0.3f, 0.4f);
    glVertex2f(0.01f, 0.4f);
    glEnd();

    // White
    glBegin(GL_QUADS);

    glColor3f(1.0f, 1.0f, 1.0f); // color (white)
    glVertex2f(0.01f, 0.4f);
    glVertex2f(0.3f, 0.4f);
    glVertex2f(0.3f, 0.3f);
    glVertex2f(0.01f, 0.3f);
    glEnd(); */

    // Ashoka Chakra
    float x_center = 0.15f;
    float y_center = 0.35f;
    glColor3f(0.0f, 0.0f, 1.0f); // color(Dark Blue)
    glBegin(GL_LINE_LOOP);

    for (int i = 0; i < 100; i++)
    {
        float angle = 2.0f * M_PI * i / 100;
        glVertex2f(x_center + 0.05 * cos(angle), y_center + 0.05 * sin(angle));
    }
    glEnd();

    glBegin(GL_LINES);

    for (int i = 0; i < 24; i++)
    {
        float angle = 2.0f * M_PI * i / 24;
        glVertex2f(x_center, y_center);
        glVertex2f(x_center + 0.05 * cos(angle), y_center + 0.05 * sin(angle));
    }
    glEnd();

    // Green
    /*glBegin(GL_QUADS);

    glColor3f(0.0f, 0.39f, 0.0f); // color (Green)
    glVertex2f(0.01f, 0.3f);
    glVertex2f(0.3f, 0.3f);
    glVertex2f(0.3f, 0.2f);
    glVertex2f(0.01f, 0.2f);
    glEnd(); */

    // Flag Pole
    glBegin(GL_POLYGON);

    glColor3f(0.67f, 0.67f, 0.67f); // color (grey) 
    glVertex2f(-0.01f, 0.5f);
    glVertex2f(0.01f, 0.5f);
    glVertex2f(0.01f, -0.5f);
    glVertex2f(-0.01f, -0.5f);
    glEnd();

    //Base
    glBegin(GL_QUADS);

    glColor3f(0.50f, 0.50f, 0.50f);
    glVertex2f(-0.09f, -0.5f);
    glVertex2f(0.09f, -0.5f);
    glVertex2f(0.09f, -0.55f);
    glVertex2f(-0.09f, -0.55f);
    glEnd();

    //Base 02
    glBegin(GL_QUADS);

    glColor3f(0.41f, 0.41, 0.41f);
    glVertex2f(-0.11f, -0.55f);
    glVertex2f(0.11f, -0.55f);
    glVertex2f(0.11f, -0.6f);
    glVertex2f(-0.11f, -0.6f);
    glEnd();

}


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

void StreetLamp1(void)
{
    glBegin(GL_QUADS);

    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-0.036f, 0.84f);
    glVertex2f(0.036f, 0.84f);
    glVertex2f(0.036f, 0.82f);
    glVertex2f(-0.036f, 0.82f);
    glEnd();

    //Trapezium above Yellow Part's Block
    glBegin(GL_POLYGON);

    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-0.04f, 0.82f);
    glVertex2f(0.04f, 0.82f);
    glVertex2f(0.086f, 0.72f);
    glVertex2f(-0.086f, 0.72f);
    glEnd();


    //Block Above Yellow Part
    glBegin(GL_QUADS);

    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-0.09f, 0.72f);
    glVertex2f(0.09f, 0.72f);
    glVertex2f(0.09f, 0.7f);
    glVertex2f(-0.09f, 0.7f);
    glEnd();

    //Yellow Part(Light)
    glBegin(GL_POLYGON);

    glColor3f(1.0f, 3.22f, 0.0f);
    glVertex2f(-0.09f, 0.7f);
    glVertex2f(0.09f, 0.7f);
    glVertex2f(0.05f, 0.5f);
    glVertex2f(-0.05f, 0.5f);
    glEnd();

    glBegin(GL_LINE_LOOP);

    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-0.09f, 0.7f);
    glVertex2f(0.09f, 0.7f);
    glVertex2f(0.05f, 0.5f);
    glVertex2f(-0.05f, 0.5f);
    glEnd();

    // Line On Top Of Block 
    glBegin(GL_POLYGON);

    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-0.005f, 0.7f);
    glVertex2f(0.005f, 0.7f);
    glVertex2f(0.005f, 0.5f);
    glVertex2f(-0.005f, 0.5f);
    glEnd();

    //Block on top of Light Pole
    glBegin(GL_QUADS);

    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-0.05f, 0.5f);
    glVertex2f(0.05f, 0.5f);
    glVertex2f(0.05f, 0.48f);
    glVertex2f(-0.05f, 0.48f);
    glEnd();

    // Light Pole
    glBegin(GL_POLYGON);

    glColor3f(0.0f, 0.0f, 0.0f); // color (grey) 
    glVertex2f(-0.007f, 0.5f);
    glVertex2f(0.007f, 0.5f);
    glVertex2f(0.007f, -0.5f);
    glVertex2f(-0.007f, -0.5f);
    glEnd();

    //Block Above Pole
    glBegin(GL_QUADS);

    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-0.04f, -0.3f);
    glVertex2f(0.04f, -0.3f);
    glVertex2f(0.04f, -0.52f);
    glVertex2f(-0.04f, -0.52f);
    glEnd();

    // Base
    glBegin(GL_QUADS);

    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-0.09f, -0.5f);
    glVertex2f(0.09f, -0.5f);
    glVertex2f(0.09f, -0.55f);
    glVertex2f(-0.09f, -0.55f);
    glEnd();
}

void StreetLamp2(void)
{
    glBegin(GL_QUADS);

    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-0.036f, 0.84f);
    glVertex2f(0.036f, 0.84f);
    glVertex2f(0.036f, 0.82f);
    glVertex2f(-0.036f, 0.82f);
    glEnd();

    //Trapezium above Yellow Part's Block
    glBegin(GL_POLYGON);

    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-0.04f, 0.82f);
    glVertex2f(0.04f, 0.82f);
    glVertex2f(0.086f, 0.72f);
    glVertex2f(-0.086f, 0.72f);
    glEnd();


    //Block Above Yellow Part
    glBegin(GL_QUADS);

    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-0.09f, 0.72f);
    glVertex2f(0.09f, 0.72f);
    glVertex2f(0.09f, 0.7f);
    glVertex2f(-0.09f, 0.7f);
    glEnd();

    //Yellow Part(Light)
    glBegin(GL_POLYGON);

    glColor3f(1.0f, 3.22f, 0.0f);
    glVertex2f(-0.09f, 0.7f);
    glVertex2f(0.09f, 0.7f);
    glVertex2f(0.05f, 0.5f);
    glVertex2f(-0.05f, 0.5f);
    glEnd();

    glBegin(GL_LINE_LOOP);

    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-0.09f, 0.7f);
    glVertex2f(0.09f, 0.7f);
    glVertex2f(0.05f, 0.5f);
    glVertex2f(-0.05f, 0.5f);
    glEnd();

    // Line On Top Of Block 
    glBegin(GL_POLYGON);

    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-0.005f, 0.7f);
    glVertex2f(0.005f, 0.7f);
    glVertex2f(0.005f, 0.5f);
    glVertex2f(-0.005f, 0.5f);
    glEnd();

    //Block on top of Light Pole
    glBegin(GL_QUADS);

    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-0.05f, 0.5f);
    glVertex2f(0.05f, 0.5f);
    glVertex2f(0.05f, 0.48f);
    glVertex2f(-0.05f, 0.48f);
    glEnd();

    // Light Pole
    glBegin(GL_POLYGON);

    glColor3f(0.0f, 0.0f, 0.0f); // color (grey) 
    glVertex2f(-0.007f, 0.5f);
    glVertex2f(0.007f, 0.5f);
    glVertex2f(0.007f, -0.5f);
    glVertex2f(-0.007f, -0.5f);
    glEnd();

    //Block Above Pole
    glBegin(GL_QUADS);

    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-0.04f, -0.3f);
    glVertex2f(0.04f, -0.3f);
    glVertex2f(0.04f, -0.52f);
    glVertex2f(-0.04f, -0.52f);
    glEnd();

    // Base
    glBegin(GL_QUADS);

    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-0.09f, -0.5f);
    glVertex2f(0.09f, -0.5f);
    glVertex2f(0.09f, -0.55f);
    glVertex2f(-0.09f, -0.55f);
    glEnd();
}

void Ground(void)
{
    //Ground

    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.5, 0.0);

    glVertex3f(-1.0, -1.0, 0.0); //BL
    glVertex3f(-1.0, -0.3, 0.0); //TL
    glVertex3f(1.0, -0.3, 0.0); //TR
    glVertex3f(1.0, -1.0, 0.0); //BR
    glEnd();

    //xxxxx Streetlamp xxxxxxxxxx//
   
    glPushMatrix();
    glScalef(0.22, 0.22, 0.0);
    glTranslatef(0.0,-3.0, 0.0);
    StreetLamp1();
    glPopMatrix();
   
    glPushMatrix();
    glScalef(0.22, 0.22, 0.0);
    glTranslatef(2.65, -3.0, 0.0);
    StreetLamp2();
    glPopMatrix();



    //xxxxx Streetlamp End xxxxxxxxx//

//xxxxx ROAD and Divider xxxxx//
    glPushMatrix();
    glTranslatef(0.3, 0.0, 0.0);
    //road
    glBegin(GL_POLYGON);
    glColor3f(0.5f, 0.5f, 0.5f);
    glVertex3f(-0.15f, -0.38f, 0.0f);
    glVertex3f(0.15f, -0.38f, 0.0f);
    glVertex3f(0.3f, -1.0f, 0.0f);
    glVertex3f(-0.3f, -1.0f, 0.0f);
    glEnd();

    //divider
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(-0.0015f, -0.5f, 0.0f);
    glVertex3f(0.0015f, -0.5f, 0.0f);
    glVertex3f(0.0015f, -0.65f, 0.0f);
    glVertex3f(-0.0015f, -0.65f, 0.0f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(-0.0015f, -0.67f, 0.0f);
    glVertex3f(0.0015f, -0.67f, 0.0f);
    glVertex3f(0.0018f, -0.85f, 0.0f);
    glVertex3f(-0.0018f, -0.85f, 0.0f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(-0.0018f, -0.87f, 0.0f);
    glVertex3f(0.0018f, -0.87f, 0.0f);
    glVertex3f(0.002f, -1.0f, 0.0f);
    glVertex3f(-0.002f, -1.0f, 0.0f);
    glEnd();

    glPopMatrix();

//xxxx ROAD DIVIDER ENDS xxxxxxxxxxx//
   
    // left bench 1
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.7f, 0.0f);
    glVertex3f(-0.9f, -0.4f, 0.0f);
    glVertex3f(-0.7f, -0.4f, 0.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(-0.7f, -0.42f, 0.0f);
    glVertex3f(-0.9f, -0.42f, 0.0f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.7f, 0.0f);
    glVertex3f(-0.9f, -0.43f, 0.0f);
    glVertex3f(-0.7f, -0.43f, 0.0f);
    //glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(-0.7f, -0.45f, 0.0f);
    glVertex3f(-0.9f, -0.45f, 0.0f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.6f, 0.0f);
    glVertex3f(-0.9f, -0.47f, 0.0f);
    glVertex3f(-0.7f, -0.47f, 0.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(-0.7f, -0.48f, 0.0f);
    glVertex3f(-0.9f, -0.48f, 0.0f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.6f, 0.0f);
    glVertex3f(-0.89f, -0.485f, 0.0f);
    glVertex3f(-0.71f, -0.485f, 0.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(-0.71f, -0.495f, 0.0f);
    glVertex3f(-0.89f, -0.495f, 0.0f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.6f, 0.0f);
    glVertex3f(-0.89f, -0.505f, 0.0f);
    glVertex3f(-0.71f, -0.505f, 0.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(-0.71f, -0.515f, 0.0f);
    glVertex3f(-0.89f, -0.515f, 0.0f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.6f, 0.0f);
    glVertex3f(-0.89f, -0.48f, 0.0f);
    glVertex3f(-0.88f, -0.48f, 0.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(-0.88f, -0.525f, 0.0f);
    glVertex3f(-0.89f, -0.525f, 0.0f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.6f, 0.0f);
    glVertex3f(-0.71f, -0.48f, 0.0f);
    glVertex3f(-0.72f, -0.48f, 0.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(-0.71f, -0.525f, 0.0f);
    glVertex3f(-0.72f, -0.525f, 0.0f);
    glEnd();

    // right bench 1
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.7f, 0.0f);
    glVertex3f(0.9f, -0.4f, 0.0f);
    glVertex3f(0.7f, -0.4f, 0.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.7f, -0.42f, 0.0f);
    glVertex3f(0.9f, -0.42f, 0.0f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.7f, 0.0f);
    glVertex3f(0.9f, -0.43f, 0.0f);
    glVertex3f(0.7f, -0.43f, 0.0f);
    //glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.7f, -0.45f, 0.0f);
    glVertex3f(0.9f, -0.45f, 0.0f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.6f, 0.0f);
    glVertex3f(0.9f, -0.47f, 0.0f);
    glVertex3f(0.7f, -0.47f, 0.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.7f, -0.48f, 0.0f);
    glVertex3f(0.9f, -0.48f, 0.0f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.6f, 0.0f);
    glVertex3f(0.89f, -0.485f, 0.0f);
    glVertex3f(0.71f, -0.485f, 0.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.71f, -0.495f, 0.0f);
    glVertex3f(0.89f, -0.495f, 0.0f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.6f, 0.0f);
    glVertex3f(0.89f, -0.505f, 0.0f);
    glVertex3f(0.71f, -0.505f, 0.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.71f, -0.515f, 0.0f);
    glVertex3f(0.89f, -0.515f, 0.0f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.6f, 0.0f);
    glVertex3f(0.89f, -0.48f, 0.0f);
    glVertex3f(0.88f, -0.48f, 0.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.88f, -0.525f, 0.0f);
    glVertex3f(0.89f, -0.525f, 0.0f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.6f, 0.0f);
    glVertex3f(0.71f, -0.48f, 0.0f);
    glVertex3f(0.72f, -0.48f, 0.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.71f, -0.525f, 0.0f);
    glVertex3f(0.72f, -0.525f, 0.0f);
    glEnd();
}



void BackgroundSky()
{
    //xxxxxxx Background Sky xxxxxxx//
    glBegin(GL_QUADS);
    glColor3f(0.529, 0.908, 0.922); //some blue shade
    glVertex3f(-1.0, -0.3, 0.0); //bottom left

    glColor3f(0.5, 0.8, 1.0); //sky blue
    glVertex3f(-1.0, 1.0, 0.0); //top left
    glVertex3f(1.0, 1.0, 0.0); //top right

    glColor3f(0.529, 0.908, 0.922); //some blue shade
    glVertex3f(1.0, -0.3, 0.0); //bottom right


    glEnd();

    //xxxxxxx Background Sky Ends xxxxxxx//

}

//Clouds
void cloud()
{
    glScalef(0.5f, 0.5f, 0.0f);

    glColor3f(0.8, 0.8, 0.8); // SkyBlue

    glBegin(GL_QUADS); // Rectangle 

    glVertex3f(-0.3f, -0.18f, 0.0f);		// Q3
    glVertex3f(-0.3f, 0.15f, 0.0f);			// Q2
    glVertex3f(0.3f, 0.15f, 0.0f);			// Q1
    glVertex3f(0.3f, -0.18f, 0.0f);			// Q4

    glEnd();

    glBegin(GL_POLYGON);			// Circle 1

    float radius_1 = 0.18f;
    float x_centre_1 = -0.30f;
    float y_centre_1 = 0.00f;
    for (int i = 0; i < 1000; i++)
    {
        float angle = 2.0f * M_PI * i / 1000;
        glVertex2f(x_centre_1 + radius_1 * cos(angle), y_centre_1 + radius_1 * sin(angle));
        glColor3f(0.8, 0.8, 0.8); // SkyBlue
    }
    glEnd();

    glBegin(GL_POLYGON);			// Circle 2

    float radius_2 = 0.15f;
    float x_centre_2 = -0.10f;
    float y_centre_2 = 0.20f;
    for (int i = 0; i < 1000; i++)
    {
        float angle = 2.0f * M_PI * i / 1000;
        glVertex2f(x_centre_2 + radius_2 * cos(angle), y_centre_2 + radius_2 * sin(angle));
        glColor3f(0.8, 0.8, 0.8); // SkyBlue
    }
    glEnd();

    glBegin(GL_POLYGON);			// Circle 3

    float radius_3 = 0.20f;
    float x_centre_3 = 0.16f;
    float y_centre_3 = 0.26f;
    for (int i = 0; i < 1000; i++)
    {
        float angle = 2.0f * M_PI * i / 1000;
        glVertex2f(x_centre_3 + radius_3 * cos(angle), y_centre_3 + radius_3 * sin(angle));
        glColor3f(0.8, 0.8, 0.8); // SkyBlue
    }
    glEnd();

    glBegin(GL_POLYGON);			// Circle 4

    float radius_4 = 0.18f;
    float x_centre_4 = 0.30f;
    float y_centre_4 = 0.00f;
    for (int i = 0; i < 1000; i++)
    {
        float angle = 2.0f * M_PI * i / 1000;
        glVertex2f(x_centre_4 + radius_4 * cos(angle), y_centre_4 + radius_4 * sin(angle));
        glColor3f(0.8, 0.8, 0.8); // SkyBlue
    }
    glEnd();
}

//India Name
void india(void)
{

    glColor3f(0, 0, 0);
    //I
    glBegin(GL_QUADS);
    glVertex2f(-0.9f, 0.5f);
    glVertex2f(-0.9f, -0.5f);
    glVertex2f(-0.8f, -0.5f);
    glVertex2f(-0.8f, 0.5f);
    glEnd();

    //N
    glBegin(GL_QUADS);
    glVertex2f(-0.6f, 0.5f);
    glVertex2f(-0.6f, -0.5f);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(-0.5f, 0.5f);


    glVertex2f(-0.6f, 0.5f);
    glVertex2f(-0.5f, 0.5f);
    glVertex2f(-0.2f, -0.5f);
    glVertex2f(-0.3f, -0.5f);

    /*
    glVertex2f(-0.5f, 0.5f);
    glVertex2f(-0.3f, -0.4f);
    glVertex2f(-0.3f, -0.5f);
    glVertex2f(-0.5f, 0.4f);
    */
    glVertex2f(-0.3f, 0.5f);
    glVertex2f(-0.3f, -0.5f);
    glVertex2f(-0.2f, -0.5f);
    glVertex2f(-0.2f, 0.5f);
    glEnd();

    //D
    glBegin(GL_QUADS);
    glVertex2f(-0.0f, 0.5f);
    glVertex2f(-0.0f, -0.5f);
    glVertex2f(0.1f, -0.5f);
    glVertex2f(0.1f, 0.5f);

    glVertex2f(0.1f, 0.5f);
    glVertex2f(0.3f, 0.3f);
    glVertex2f(0.4f, 0.2f);
    glVertex2f(0.1f, 0.4f);

    glVertex2f(0.3f, 0.3f);
    glVertex2f(0.3f, -0.3f);
    glVertex2f(0.4f, -0.2f);
    glVertex2f(0.4f, 0.2f);


    glVertex2f(0.4f, -0.2f);
    glVertex2f(0.3f, -0.3f);
    glVertex2f(0.1f, -0.5f);
    glVertex2f(0.1f, -0.4f);
    glEnd();

    //I
    glBegin(GL_QUADS);
    glVertex2f(0.5f, 0.5f);
    glVertex2f(0.6f, 0.5f);
    glVertex2f(0.6f, -0.5f);
    glVertex2f(0.5f, -0.5f);
    glEnd();

    //A
    glBegin(GL_QUADS);
    glVertex2f(1.0f, 0.5f);
    glVertex2f(0.9f, 0.5f);
    glVertex2f(0.7f, -0.5f);
    glVertex2f(0.8f, -0.5f);

    glVertex2f(1.0f, 0.5f);
    glVertex2f(0.9f, 0.5f);
    glVertex2f(1.1f, -0.5f);
    glVertex2f(1.2f, -0.5f);

    glVertex2f(0.86, 0.00);
    glVertex2f(0.96, 0.00);
    glVertex2f(1.1, -0.1);
    glVertex2f(0.86, -0.1);
    glEnd();
}



//Indiagate
void IndiaGate()
{
    float x = 314.0f, y = -399.0f;
    int i = 0;
    glColor3f(187.0f / 255.0f, 136.0f / 255.0f, 85.0f / 255.0f);

    glBegin(GL_POLYGON);

    for (i = 0; i <= 50; i++)
    {
        float ang = M_PI * i / 50.0;

        glVertex2f((156.0f / x) + 17.0 / x * cos(ang), (19.0f / y) + 10.0 / x * sin(ang));
    }


    glEnd();

    glBegin(GL_QUADS);
    //1st
    glVertex2f(100.0f / x, 25.0f / y);
    glVertex2f(215.0f / x, 25.0f / y);
    glVertex2f(215.0f / x, 33.0f / y);
    glVertex2f(100.0f / x, 33.0f / y);

    //2nd 
    glVertex2f(50.0f / x, 33.0f / y);
    glVertex2f(265.0f / x, 33.0f / y);
    glVertex2f(265.0f / x, 52.0f / y);
    glVertex2f(50.0f / x, 52.0f / y);

    //3rd
    glVertex2f(47.0f / x, 52.0f / y);
    glVertex2f(267.0f / x, 52.0f / y);
    glVertex2f(267.0f / x, 85.0f / y);
    glVertex2f(47.0f / x, 85.0f / y);

    //4th
    glVertex2f(23.0f / x, 85.0f / y);
    glVertex2f(291.0f / x, 85.0f / y);
    glVertex2f(291.0f / x, 105.0f / y);
    glVertex2f(23.0f / x, 105.0f / y);

    //5th
    glVertex2f(18.0f / x, 105.0f / y);
    glVertex2f(296.0f / x, 105.0f / y);
    glVertex2f(296.0f / x, 134.0f / y);
    glVertex2f(18.0f / x, 134.0f / y);

    //6th
    glVertex2f(19.0f / x, 142.0f / y);
    glVertex2f(110.0f / x, 142.0f / y);
    glVertex2f(110.0f / x, 395.0f / y);
    glVertex2f(19.0f / x, 395.0f / y);
    /*
    //7th
    glVertex2f(105.0f / x, 142.0f / y);
    glVertex2f(204.0f / x, 142.0f / y);
    glVertex2f(204.0f / x, 213.0f / y);
    glVertex2f(105.0f / x, 213.0f / y);
    */
    //8th
    glVertex2f(204.0f / x, 142.0f / y);
    glVertex2f(297.0f / x, 142.0f / y);
    glVertex2f(297.0f / x, 395.0f / y);
    glVertex2f(204.0f / x, 395.0f / y);

    //9th
    glVertex2f(140.0f / x, 19.0f / y);
    glVertex2f(174.0f / x, 19.0f / y);
    glVertex2f(193.0f / x, 25.0f / y);
    glVertex2f(124.0f / x, 25.0f / y);

    //10th
    glVertex2f(1.0f / x, 134.0f / y);
    glVertex2f(313.0f / x, 134.0f / y);
    glVertex2f(310.0f / x, 138.0f / y);
    glVertex2f(4.0f / x, 138.0f / y);

    //11th
    glVertex2f(4.0f / x, 138.0f / y);
    glVertex2f(310.0f / x, 138.0f / y);
    glVertex2f(310.0f / x, 142.0f / y);
    glVertex2f(4.0f / x, 142.0f / y);


    //Small Quads
    //A
    glVertex2f(16.0f / x, 162.0f / y);
    glVertex2f(99.0f / x, 162.0f / y);
    glVertex2f(97.0f / x, 164.0f / y);
    glVertex2f(19.0f / x, 164.0f / y);

    //B
    glVertex2f(19.0f / x, 164.0f / y);
    glVertex2f(97.0f / x, 164.0f / y);
    glVertex2f(97.0f / x, 168.0f / y);
    glVertex2f(19.0f / x, 168.0f / y);

    //C
    glVertex2f(216.0f / x, 162.0f / y);
    glVertex2f(300.0f / x, 162.0f / y);
    glVertex2f(297.0f / x, 164.0f / y);
    glVertex2f(219.0f / x, 164.0f / y);

    //D
    glVertex2f(219.0f / x, 164.0f / y);
    glVertex2f(297.0f / x, 164.0f / y);
    glVertex2f(297.0f / x, 168.0f / y);
    glVertex2f(219.0f / x, 168.0f / y);


    glEnd();

    //BLACK LINES AROUND THE QUADS
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(1);

    glBegin(GL_LINE_LOOP);

    for (i = 0; i <= 50; i++)
    {
        float ang = M_PI * i / 50.0;

        glVertex2f((156.0f / x) + 17.0 / x * cos(ang), (19.0f / y) + 10.0 / x * sin(ang));
    }
    glEnd();


    //Left circle
    glBegin(GL_LINE_LOOP);

    for (i = 0; i <= 50; i++)
    {
        float ang = 2 * M_PI * i / 50.0;

        glVertex2f((97.0f / x) + 10.0 / x * cos(ang), (66.0f / y) + 10.0 / x * sin(ang));
    }
    glEnd();

    //India Box
    glBegin(GL_LINE_LOOP);
    glVertex2f(107.0f / x, 53.0f / y);
    glVertex2f(209.0f / x, 53.0f / y);
    glVertex2f(209.0f / x, 78.0f / y);
    glVertex2f(185.0f / x, 78.0f / y);
    glVertex2f(185.0f / x, 79.0f / y);
    glVertex2f(132.0f / x, 79.0f / y);
    glVertex2f(132.0f / x, 78.0f / y);
    glVertex2f(107.0f / x, 78.0f / y);
    glEnd();

    //right circle
    glBegin(GL_LINE_LOOP);

    for (i = 0; i <= 50; i++)
    {
        float ang = 2 * M_PI * i / 50.0;

        glVertex2f((219.0f / x) + 10.0 / x * cos(ang), (66.0f / y) + 10.0 / x * sin(ang));
    }
    glEnd();

    glBegin(GL_LINE_LOOP);
    //1st
    glVertex2f(100.0f / x, 25.0f / y);
    glVertex2f(215.0f / x, 25.0f / y);
    glVertex2f(215.0f / x, 33.0f / y);
    glVertex2f(100.0f / x, 33.0f / y);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //2nd 
    glVertex2f(50.0f / x, 33.0f / y);
    glVertex2f(265.0f / x, 33.0f / y);
    glVertex2f(265.0f / x, 52.0f / y);
    glVertex2f(50.0f / x, 52.0f / y);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //3rd
    glVertex2f(47.0f / x, 52.0f / y);
    glVertex2f(267.0f / x, 52.0f / y);
    glVertex2f(267.0f / x, 85.0f / y);
    glVertex2f(47.0f / x, 85.0f / y);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //4th
    glVertex2f(23.0f / x, 85.0f / y);
    glVertex2f(291.0f / x, 85.0f / y);
    glVertex2f(291.0f / x, 105.0f / y);
    glVertex2f(23.0f / x, 105.0f / y);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //5th
    glVertex2f(18.0f / x, 105.0f / y);
    glVertex2f(296.0f / x, 105.0f / y);
    glVertex2f(296.0f / x, 134.0f / y);
    glVertex2f(18.0f / x, 134.0f / y);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //6th
    glVertex2f(19.0f / x, 142.0f / y);
    glVertex2f(110.0f / x, 142.0f / y);
    glVertex2f(110.0f / x, 395.0f / y);
    glVertex2f(19.0f / x, 395.0f / y);
    glEnd();

    /*
    glBegin(GL_LINE_STRIP);
    //7th
    glVertex2f(110.0f / x, 142.0f / y);
    glVertex2f(204.0f / x, 142.0f / y);
    glVertex2f(204.0f / x, 189.0f / y);
    glVertex2f(110.0f / x, 189.0f / y);
    glEnd();
    */
    glBegin(GL_LINE_LOOP);
    //8th
    glVertex2f(204.0f / x, 142.0f / y);
    glVertex2f(297.0f / x, 142.0f / y);
    glVertex2f(297.0f / x, 395.0f / y);
    glVertex2f(204.0f / x, 395.0f / y);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //9th
    glVertex2f(140.0f / x, 19.0f / y);
    glVertex2f(174.0f / x, 19.0f / y);
    glVertex2f(193.0f / x, 25.0f / y);
    glVertex2f(124.0f / x, 25.0f / y);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //10th
    glVertex2f(1.0f / x, 134.0f / y);
    glVertex2f(313.0f / x, 134.0f / y);
    glVertex2f(310.0f / x, 138.0f / y);
    glVertex2f(4.0f / x, 138.0f / y);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //11th
    glVertex2f(4.0f / x, 138.0f / y);
    glVertex2f(310.0f / x, 138.0f / y);
    glVertex2f(310.0f / x, 142.0f / y);
    glVertex2f(4.0f / x, 142.0f / y);
    glEnd();

    glColor3f(187.0f / 255.0f, 136.0f / 255.0f, 85.0f / 255.0f);
    glBegin(GL_QUADS);
    //12th
    glVertex2f(19.0f / x, 142.0f / y);
    glVertex2f(298.0f / x, 142.0f / y);
    glVertex2f(298.0f / x, 162.0f / y);
    glVertex2f(19.0f / x, 162.0f / y);

    //7th
    /*
    glVertex2f(105.0f / x, 142.0f / y);
    glVertex2f(204.0f / x, 142.0f / y);
    glVertex2f(204.0f / x, 213.0f / y);
    glVertex2f(105.0f / x, 213.0f / y);
    */
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    //12th
    glVertex2f(19.0f / x, 142.0f / y);
    glVertex2f(298.0f / x, 142.0f / y);
    glVertex2f(298.0f / x, 162.0f / y);
    glVertex2f(19.0f / x, 162.0f / y);
    glEnd();


    //Design in 12 th quads

    int n = 0;
    for (i = 0; i < 14; i++)
    {
        glBegin(GL_LINE_LOOP);
        glVertex2f((26.0f + n) / x, 142.0f / y);
        glVertex2f((35.0f + n) / x, 142.0f / y);
        glVertex2f((35.0f + n) / x, 144.0f / y);
        glVertex2f((26.0f + n) / x, 144.0f / y);
        glEnd();

        glBegin(GL_LINE_LOOP);

        glVertex2f((24.0f + n) / x, 144.0f / y);
        glVertex2f((37.0f + n) / x, 144.0f / y);
        glVertex2f((36.0f + n) / x, 148.0f / y);
        glVertex2f((25.0f + n) / x, 148.0f / y);
        glEnd();

        glBegin(GL_LINE_LOOP);

        glVertex2f((26.0f + n) / x, 148.0f / y);
        glVertex2f((35.0f + n) / x, 148.0f / y);
        glVertex2f((35.0f + n) / x, 156.0f / y);
        glVertex2f((26.0f + n) / x, 156.0f / y);
        glEnd();

        glBegin(GL_LINE_LOOP);

        glVertex2f((27.0f + n) / x, 156.0f / y);
        glVertex2f((34.0f + n) / x, 156.0f / y);
        glVertex2f((34.0f + n) / x, 160.0f / y);
        glVertex2f((27.0f + n) / x, 160.0f / y);
        glEnd();

        glBegin(GL_LINE_LOOP);
        glVertex2f((28.0f + n) / x, 160.0f / y);
        glVertex2f((28.0f + n) / x, 162.0f / y);
        glVertex2f((33.0f + n) / x, 162.0 / y);
        glVertex2f((33.0f + n) / x, 160.0f / y);


        glEnd();
        n = n + 20;
    }


    glBegin(GL_LINE_LOOP);
    //A
    glVertex2f(16.0f / x, 162.0f / y);
    glVertex2f(99.0f / x, 162.0f / y);
    glVertex2f(97.0f / x, 164.0f / y);
    glVertex2f(19.0f / x, 164.0f / y);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //B
    glVertex2f(19.0f / x, 164.0f / y);
    glVertex2f(97.0f / x, 164.0f / y);
    glVertex2f(97.0f / x, 168.0f / y);
    glVertex2f(19.0f / x, 168.0f / y);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //C
    glVertex2f(216.0f / x, 162.0f / y);
    glVertex2f(300.0f / x, 162.0f / y);
    glVertex2f(297.0f / x, 164.0f / y);
    glVertex2f(219.0f / x, 164.0f / y);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //D
    glVertex2f(219.0f / x, 164.0f / y);
    glVertex2f(297.0f / x, 164.0f / y);
    glVertex2f(297.0f / x, 168.0f / y);
    glVertex2f(219.0f / x, 168.0f / y);
    glEnd();


    glBegin(GL_LINE_LOOP);
    //E
    glVertex2f(19.0f / x, 168.0f / y);
    glVertex2f(97.0f / x, 168.0f / y);
    glVertex2f(96.0f / x, 232.0f / y);
    glVertex2f(19.0f / x, 232.0f / y);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //F
    glVertex2f(219.0f / x, 168.0f / y);
    glVertex2f(297.0f / x, 168.0f / y);
    glVertex2f(297.0f / x, 232.0f / y);
    glVertex2f(219.0f / x, 232.0f / y);
    glEnd();


    //Side Design on pillars
    glColor3f(187.0f / 255.0f, 136.0f / 255.0f, 85.0f / 255.0f);

    glBegin(GL_QUADS);

    //Right side 

    glVertex2f(98.0f / x, 232.0f / y);
    glVertex2f(117.0f / x, 232.0f / y);
    glVertex2f(114.0f / x, 237.0f / y);
    glVertex2f(98.0f / x, 237.0f / y);

    glVertex2f(98.0f / x, 237.0f / y);
    glVertex2f(114.0f / x, 237.0f / y);
    glVertex2f(114.0f / x, 239.0f / y);
    glVertex2f(98.0f / x, 239.0f / y);

    glVertex2f(98.0f / x, 239.0f / y);
    glVertex2f(112.0f / x, 239.0f / y);
    glVertex2f(111.0f / x, 244.0f / y);
    glVertex2f(98.0f / x, 244.0f / y);

    //Left side
    glVertex2f(197.0f / x, 233.0f / y);
    glVertex2f(217.0f / x, 233.0f / y);
    glVertex2f(217.0f / x, 236.0f / y);
    glVertex2f(200.0f / x, 237.0f / y);

    glVertex2f(201.0f / x, 237.0f / y);
    glVertex2f(215.0f / x, 237.0f / y);
    glVertex2f(216.0f / x, 239.0f / y);
    glVertex2f(201.0f / x, 239.0f / y);

    glVertex2f(202.0f / x, 239.0f / y);
    glVertex2f(217.0f / x, 239.0f / y);
    glVertex2f(217.0f / x, 243.0f / y);
    glVertex2f(203.0f / x, 243.0f / y);




    glEnd();

    glColor3f(0, 0, 0);

    //Lines around above quads
   /* glBegin(GL_LINE_STRIP);
    glVertex2f(85.0f  / x, 232.0f / y);
    glVertex2f(98.0f / x, 232.0f / y);
    glVertex2f(98.0f  / x, 237.0f / y);
    glVertex2f(85.0f / x, 237.0f / y);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2f(86.0f  / x, 237.0f / y);
    glVertex2f(99.0f  / x, 237.0f / y);
    glVertex2f(98.0f  / x, 242.0f / y);
    glVertex2f(85.0f  / x, 242.0f / y);
    glEnd();
    */
    glBegin(GL_LINE_STRIP);
    glVertex2f(98.0f / x, 232.0f / y);
    glVertex2f(117.0f / x, 232.0f / y);
    glVertex2f(114.0f / x, 237.0f / y);
    glVertex2f(98.0f / x, 237.0f / y);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2f(98.0f / x, 237.0f / y);
    glVertex2f(114.0f / x, 237.0f / y);
    glVertex2f(114.0f / x, 239.0f / y);
    glVertex2f(98.0f / x, 239.0f / y);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2f(98.0f / x, 239.0f / y);
    glVertex2f(112.0f / x, 239.0f / y);
    glVertex2f(111.0f / x, 244.0f / y);
    glVertex2f(97.0f / x, 244.0f / y);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex2f(197.0f / x, 233.0f / y);
    glVertex2f(217.0f / x, 233.0f / y);
    glVertex2f(217.0f / x, 236.0f / y);
    glVertex2f(200.0f / x, 237.0f / y);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex2f(201.0f / x, 237.0f / y);
    glVertex2f(215.0f / x, 237.0f / y);
    glVertex2f(216.0f / x, 239.0f / y);
    glVertex2f(201.0f / x, 239.0f / y);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex2f(202.0f / x, 239.0f / y);
    glVertex2f(217.0f / x, 239.0f / y);
    glVertex2f(217.0f / x, 243.0f / y);
    glVertex2f(203.0f / x, 243.0f / y);
    glEnd();
    /*  glBegin(GL_LINE_STRIP);

    glVertex2f(31.0f   / x, 232.0f / y);
    glVertex2f(19.0f / x, 232.0f / y);
    glVertex2f(19.0f  / x, 237.0f / y);
    glVertex2f(29.0f / x, 237.0f / y);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2f(29.0f / x, 237.0f / y);
    glVertex2f(15.0f   / x, 237.0f / y);
    glVertex2f(19.0f / x, 243.0f / y);
    glVertex2f(32.0f / x, 243.0f / y);
    glEnd();

    */

    //Design on the Two Pillars
    n = 0;
    int nx = 0;
    for (i = 0; i < 2; i++)
    {
        //GL_QUADS

        glColor3f(187.0f / 255.0f, 136.0f / 255.0f, 85.0f / 255.0f);
        glBegin(GL_QUADS);

        //upper
        glVertex2f((85.0f + nx) / x, 232.0f / y);
        glVertex2f((98.0f + nx) / x, 232.0f / y);
        glVertex2f((98.0f + nx) / x, 237.0f / y);
        glVertex2f((85.0f + nx) / x, 237.0f / y);

        glVertex2f((85.0f + nx) / x, 237.0f / y);
        glVertex2f((103.0f + nx) / x, 237.0f / y);
        glVertex2f((98.0f + nx) / x, 242.0f / y);
        glVertex2f((85.0f + nx) / x, 242.0f / y);

        glVertex2f((17.0f + nx) / x, 232.0f / y);
        glVertex2f((31.0f + nx) / x, 232.0f / y);
        glVertex2f((31.0f + nx) / x, 237.0f / y);
        glVertex2f((17.0f + nx) / x, 237.0f / y);

        glVertex2f((15.0f + nx) / x, 237.0f / y);
        glVertex2f((31.0f + nx) / x, 237.0f / y);
        glVertex2f((32.0f + nx) / x, 243.0f / y);
        glVertex2f((19.0f + nx) / x, 243.0f / y);

        //middle right
        glVertex2f((86.0f + nx) / x, 274.0f / y);
        glVertex2f((98.0f + nx) / x, 274.0f / y);
        glVertex2f((98.0f + nx) / x, 278.0f / y);
        glVertex2f((86.0f + nx) / x, 278.0f / y);

        glVertex2f((88.0f + nx) / x, 278.0f / y);
        glVertex2f((102.0f + nx) / x, 278.0f / y);
        glVertex2f((98.0f + nx) / x, 283.0f / y);
        glVertex2f((87.0f + nx) / x, 283.0f / y);

        glVertex2f((85.0f + nx) / x, 283.0f / y);
        glVertex2f((98.0f + nx) / x, 283.0f / y);
        glVertex2f((98.0f + nx) / x, 287.0f / y);
        glVertex2f((85.0f + nx) / x, 287.0f / y);

        glVertex2f((85.0f + nx) / x, 287.0f / y);
        glVertex2f((99.0f + nx) / x, 287.0f / y);
        glVertex2f((99.0f + nx) / x, 291.0f / y);
        glVertex2f((85.0f + nx) / x, 291.0f / y);

        //middle left
        glVertex2f((17.0f + nx) / x, 274.0f / y);
        glVertex2f((30.0f + nx) / x, 274.0f / y);
        glVertex2f((30.0f + nx) / x, 278.0f / y);
        glVertex2f((17.0f + nx) / x, 278.0f / y);

        glVertex2f((13.0f + nx) / x, 278.0f / y);
        glVertex2f((28.0f + nx) / x, 278.0f / y);
        glVertex2f((30.0f + nx) / x, 283.0f / y);
        glVertex2f((18.0f + nx) / x, 283.0f / y);

        glVertex2f((19.0f + nx) / x, 283.0f / y);
        glVertex2f((30.0f + nx) / x, 283.0f / y);
        glVertex2f((30.0f + nx) / x, 287.0f / y);
        glVertex2f((19.0f + nx) / x, 287.0f / y);

        glVertex2f((17.0f + nx) / x, 287.0f / y);
        glVertex2f((30.0f + nx) / x, 287.0f / y);
        glVertex2f((30.0f + nx) / x, 291.0f / y);
        glVertex2f((17.0f + nx) / x, 291.0f / y);

        //lower right
        glVertex2f((85.0f + nx) / x, 345.0f / y);
        glVertex2f((99.0f + nx) / x, 345.0f / y);
        glVertex2f((99.0f + nx) / x, 349.0f / y);
        glVertex2f((85.0f + nx) / x, 349.0f / y);

        glVertex2f((87.0f + nx) / x, 349.0f / y);
        glVertex2f((99.0f + nx) / x, 349.0f / y);
        glVertex2f((99.0f + nx) / x, 362.0f / y);
        glVertex2f((87.0f + nx) / x, 362.0f / y);

        glVertex2f((86.0f + nx) / x, 361.0f / y);
        glVertex2f((100.0f + nx) / x, 361.0f / y);
        glVertex2f((100.0f + nx) / x, 366.0f / y);
        glVertex2f((86.0f + nx) / x, 366.0f / y);

        glVertex2f((86.0f + nx) / x, 365.0f / y);
        glVertex2f((101.0f + nx) / x, 365.0f / y);
        glVertex2f((101.0f + nx) / x, 377.0f / y);
        glVertex2f((86.0f + nx) / x, 377.0f / y);

        glVertex2f((86.0f + nx) / x, 377.0f / y);
        glVertex2f((100.0f + nx) / x, 377.0f / y);
        glVertex2f((100.0f + nx) / x, 390.0f / y);
        glVertex2f((86.0f + nx) / x, 390.0f / y);

        //lower left
        glVertex2f((17.0f + nx) / x, 345.0f / y);
        glVertex2f((30.0f + nx) / x, 345.0f / y);
        glVertex2f((30.0f + nx) / x, 349.0f / y);
        glVertex2f((17.0f + nx) / x, 349.0f / y);

        glVertex2f((17.0f + nx) / x, 349.0f / y);
        glVertex2f((30.0f + nx) / x, 349.0f / y);
        glVertex2f((30.0f + nx) / x, 362.0f / y);
        glVertex2f((17.0f + nx) / x, 362.0f / y);

        glVertex2f((16.0f + nx) / x, 361.0f / y);
        glVertex2f((30.0f + nx) / x, 361.0f / y);
        glVertex2f((30.0f + nx) / x, 366.0f / y);
        glVertex2f((16.0f + nx) / x, 366.0f / y);

        glVertex2f((16.0f + nx) / x, 365.0f / y);
        glVertex2f((29.0f + nx) / x, 365.0f / y);
        glVertex2f((29.0f + nx) / x, 377.0f / y);
        glVertex2f((16.0f + nx) / x, 377.0f / y);

        glVertex2f((16.0f + nx) / x, 377.0f / y);
        glVertex2f((30.0f + nx) / x, 377.0f / y);
        glVertex2f((30.0f + nx) / x, 390.0f / y);
        glVertex2f((16.0f + nx) / x, 390.0f / y);

        glEnd();

        //Lines around above quads
        glColor3f(0, 0, 0);

        glBegin(GL_LINE_LOOP);

        for (int j = 0; j <= 100; j++)
        {
            float ang = 2 * M_PI * j / 100.0;

            glVertex2f(((58.0f + nx) / x) + 8.0 / x * cos(ang), (189.0f / y) + 8.0 / x * sin(ang));
        }
        glEnd();

        glBegin(GL_LINE_LOOP);

        for (int j = 0; j <= 100; j++)
        {
            float ang = 2 * M_PI * j / 100.0;

            glVertex2f(((58.0f + nx) / x) + 12.0 / x * cos(ang), (189.0f / y) + 12.0 / x * sin(ang));
        }
        glEnd();


        glBegin(GL_LINE_LOOP);
        glVertex2f((85.0f + nx) / x, 232.0f / y);
        glVertex2f((98.0f + nx) / x, 232.0f / y);
        glVertex2f((98.0f + nx) / x, 237.0f / y);
        glVertex2f((85.0f + nx) / x, 237.0f / y);
        glEnd();

        glBegin(GL_LINE_LOOP);
        glVertex2f((85.0f + nx) / x, 237.0f / y);
        glVertex2f((101.0f + nx) / x, 237.0f / y);
        glVertex2f((98.0f + nx) / x, 242.0f / y);
        glVertex2f((85.0f + nx) / x, 242.0f / y);
        glEnd();

        glBegin(GL_LINE_LOOP);
        glVertex2f((17.0f + nx) / x, 232.0f / y);
        glVertex2f((31.0f + nx) / x, 232.0f / y);
        glVertex2f((31.0f + nx) / x, 237.0f / y);
        glVertex2f((17.0f + nx) / x, 237.0f / y);
        glEnd();

        glBegin(GL_LINE_LOOP);
        glVertex2f((15.0f + nx) / x, 237.0f / y);
        glVertex2f((31.0f + nx) / x, 237.0f / y);
        glVertex2f((32.0f + nx) / x, 243.0f / y);
        glVertex2f((19.0f + nx) / x, 243.0f / y);
        glEnd();

        glBegin(GL_LINE_LOOP);
        glVertex2f((86.0f + nx) / x, 274.0f / y);
        glVertex2f((98.0f + nx) / x, 274.0f / y);
        glVertex2f((98.0f + nx) / x, 278.0f / y);
        glVertex2f((86.0f + nx) / x, 278.0f / y);
        glEnd();

        glBegin(GL_LINE_LOOP);
        glVertex2f((88.0f + nx) / x, 278.0f / y);
        glVertex2f((102.0f + nx) / x, 278.0f / y);
        glVertex2f((98.0f + nx) / x, 283.0f / y);
        glVertex2f((87.0f + nx) / x, 283.0f / y);
        glEnd();

        glBegin(GL_LINE_LOOP);
        glVertex2f((85.0f + nx) / x, 283.0f / y);
        glVertex2f((98.0f + nx) / x, 283.0f / y);
        glVertex2f((98.0f + nx) / x, 287.0f / y);
        glVertex2f((85.0f + nx) / x, 287.0f / y);
        glEnd();

        glBegin(GL_LINE_LOOP);
        glVertex2f((85.0f + nx) / x, 287.0f / y);
        glVertex2f((99.0f + nx) / x, 287.0f / y);
        glVertex2f((99.0f + nx) / x, 291.0f / y);
        glVertex2f((85.0f + nx) / x, 291.0f / y);
        glEnd();

        //
        glBegin(GL_LINE_LOOP);
        glVertex2f((17.0f + nx) / x, 274.0f / y);
        glVertex2f((30.0f + nx) / x, 274.0f / y);
        glVertex2f((30.0f + nx) / x, 278.0f / y);
        glVertex2f((17.0f + nx) / x, 278.0f / y);
        glEnd();

        glBegin(GL_LINE_LOOP);
        glVertex2f((13.0f + nx) / x, 278.0f / y);
        glVertex2f((28.0f + nx) / x, 278.0f / y);
        glVertex2f((30.0f + nx) / x, 283.0f / y);
        glVertex2f((18.0f + nx) / x, 283.0f / y);
        glEnd();

        glBegin(GL_LINE_LOOP);
        glVertex2f((19.0f + nx) / x, 283.0f / y);
        glVertex2f((30.0f + nx) / x, 283.0f / y);
        glVertex2f((30.0f + nx) / x, 287.0f / y);
        glVertex2f((19.0f + nx) / x, 287.0f / y);
        glEnd();

        glBegin(GL_LINE_LOOP);
        glVertex2f((17.0f + nx) / x, 287.0f / y);
        glVertex2f((30.0f + nx) / x, 287.0f / y);
        glVertex2f((30.0f + nx) / x, 291.0f / y);
        glVertex2f((17.0f + nx) / x, 291.0f / y);
        glEnd();

        //lower right
        glBegin(GL_LINE_LOOP);
        glVertex2f((86.0f + nx) / x, 345.0f / y);
        glVertex2f((99.0f + nx) / x, 345.0f / y);
        glVertex2f((99.0f + nx) / x, 349.0f / y);
        glVertex2f((86.0f + nx) / x, 349.0f / y);
        glEnd();

        glBegin(GL_LINE_LOOP);
        glVertex2f((86.0f + nx) / x, 349.0f / y);
        glVertex2f((99.0f + nx) / x, 349.0f / y);
        glVertex2f((99.0f + nx) / x, 362.0f / y);
        glVertex2f((86.0f + nx) / x, 362.0f / y);
        glEnd();

        glBegin(GL_LINE_LOOP);
        glVertex2f((87.0f + nx) / x, 362.0f / y);
        glVertex2f((100.0f + nx) / x, 362.0f / y);
        glVertex2f((100.0f + nx) / x, 366.0f / y);
        glVertex2f((87.0f + nx) / x, 366.0f / y);
        glEnd();

        glBegin(GL_LINE_LOOP);
        glVertex2f((88.0f + nx) / x, 366.0f / y);
        glVertex2f((101.0f + nx) / x, 366.0f / y);
        glVertex2f((101.0f + nx) / x, 377.0f / y);
        glVertex2f((88.0f + nx) / x, 377.0f / y);
        glEnd();

        glBegin(GL_LINE_LOOP);
        glVertex2f((89.0f + nx) / x, 377.0f / y);
        glVertex2f((100.0f + nx) / x, 377.0f / y);
        glVertex2f((100.0f + nx) / x, 390.0f / y);
        glVertex2f((89.0f + nx) / x, 390.0f / y);
        glEnd();

        //lower left
        glBegin(GL_LINE_LOOP);
        glVertex2f((17.0f + nx) / x, 345.0f / y);
        glVertex2f((30.0f + nx) / x, 345.0f / y);
        glVertex2f((30.0f + nx) / x, 349.0f / y);
        glVertex2f((17.0f + nx) / x, 349.0f / y);
        glEnd();

        glBegin(GL_LINE_LOOP);
        glVertex2f((17.0f + nx) / x, 349.0f / y);
        glVertex2f((30.0f + nx) / x, 349.0f / y);
        glVertex2f((30.0f + nx) / x, 362.0f / y);
        glVertex2f((17.0f + nx) / x, 362.0f / y);
        glEnd();

        glBegin(GL_LINE_LOOP);
        glVertex2f((16.0f + nx) / x, 362.0f / y);
        glVertex2f((28.0f + nx) / x, 362.0f / y);
        glVertex2f((28.0f + nx) / x, 366.0f / y);
        glVertex2f((16.0f + nx) / x, 366.0f / y);
        glEnd();

        glBegin(GL_LINE_LOOP);
        glVertex2f((16.0f + nx) / x, 366.0f / y);
        glVertex2f((28.0f + nx) / x, 366.0f / y);
        glVertex2f((28.0f + nx) / x, 377.0f / y);
        glVertex2f((16.0f + nx) / x, 377.0f / y);
        glEnd();

        glBegin(GL_LINE_LOOP);
        glVertex2f((16.0f + nx) / x, 377.0f / y);
        glVertex2f((27.0f + nx) / x, 377.0f / y);
        glVertex2f((27.0f + nx) / x, 390.0f / y);
        glVertex2f((16.0f + nx) / x, 390.0f / y);
        glEnd();
        //7
        glBegin(GL_LINE_LOOP);
        glVertex2f((33.0f + n) / x, 208.0f / y);
        glVertex2f((82.0f + n) / x, 208.0f / y);
        glVertex2f((82.0f + n) / x, 211.0f / y);
        glVertex2f((33.0f + n) / x, 211.0f / y);
        glEnd();

        //8
        glBegin(GL_LINE_LOOP);
        glVertex2f((30.0f + n) / x, 211.0f / y);
        glVertex2f((85.0f + n) / x, 211.0f / y);
        glVertex2f((85.0f + n) / x, 226.0f / y);
        glVertex2f((30.0f + n) / x, 226.0f / y);
        glEnd();

        //9
        glBegin(GL_LINE_LOOP);
        glVertex2f((32.0f + n) / x, 226.0f / y);
        glVertex2f((84.0f + n) / x, 226.0f / y);
        glVertex2f((84.0f + n) / x, 232.0f / y);
        glVertex2f((32.0f + n) / x, 232.0f / y);
        glEnd();

        //10
        glBegin(GL_LINE_LOOP);
        glVertex2f((30.0f + n) / x, 232.0f / y);
        glVertex2f((84.0f + n) / x, 232.0f / y);
        glVertex2f((84.0f + n) / x, 236.0f / y);
        glVertex2f((30.0f + n) / x, 236.0f / y);
        glEnd();

        glBegin(GL_LINE_LOOP);
        //11
        glVertex2f((28.0f + n) / x, 236.0f / y);
        glVertex2f((86.0f + n) / x, 236.0f / y);
        glVertex2f((86.0f + n) / x, 239.0f / y);
        glVertex2f((28.0f + n) / x, 239.0f / y);
        glEnd();

        //12
        glBegin(GL_LINE_LOOP);
        glVertex2f((31.0f + n) / x, 239.0f / y);
        glVertex2f((85.0f + n) / x, 239.0f / y);
        glVertex2f((85.0f + n) / x, 242.0f / y);
        glVertex2f((31.0f + n) / x, 242.0 / y);
        glEnd();

        //13
        glBegin(GL_LINE_LOOP);
        glVertex2f((32.0f + n) / x, 242.0f / y);
        glVertex2f((84.0f + n) / x, 242.0f / y);
        glVertex2f((84.0f + n) / x, 274.0f / y);
        glVertex2f((32.0f + n) / x, 274.0f / y);
        glEnd();

        //14
        glBegin(GL_LINE_LOOP);
        glVertex2f((36.0f + n) / x, 245.0f / y);
        glVertex2f((79.0f + n) / x, 245.0f / y);
        glVertex2f((79.0f + n) / x, 266.0f / y);
        glVertex2f((36.0f + n) / x, 266.0f / y);
        glEnd();

        //15
        glBegin(GL_LINE_LOOP);
        glVertex2f((30.0f + n) / x, 274.0f / y);
        glVertex2f((86.0f + n) / x, 274.0f / y);
        glVertex2f((86.0f + n) / x, 278.0f / y);
        glVertex2f((30.0f + n) / x, 278.0f / y);
        glEnd();

        //16
        glBegin(GL_LINE_LOOP);
        glVertex2f((28.0f + n) / x, 278.0f / y);
        glVertex2f((87.0f + n) / x, 278.0f / y);
        glVertex2f((87.0f + n) / x, 283.0f / y);
        glVertex2f((28.0f + n) / x, 283.0f / y);
        glEnd();

        //17
        glBegin(GL_LINE_LOOP);
        glVertex2f((30.0f + n) / x, 283.0f / y);
        glVertex2f((85.0f + n) / x, 283.0f / y);
        glVertex2f((85.0f + n) / x, 287.0f / y);
        glVertex2f((30.0f + n) / x, 287.0f / y);
        glEnd();

        //18
        glBegin(GL_LINE_LOOP);
        glVertex2f((29.0f + n) / x, 287.0f / y);
        glVertex2f((86.0f + n) / x, 287.0f / y);
        glVertex2f((86.0f + n) / x, 291.0f / y);
        glVertex2f((29.0f + n) / x, 291.0f / y);
        glEnd();

        //19
        glBegin(GL_LINE_LOOP);
        glVertex2f((31.0f + n) / x, 291.0f / y);
        glVertex2f((85.0f + n) / x, 291.0f / y);
        glVertex2f((85.0f + n) / x, 344.0f / y);
        glVertex2f((31.0f + n) / x, 344.0f / y);
        glEnd();

        //20
        glBegin(GL_LINE_LOOP);
        glVertex2f((30.0f + n) / x, 345.0f / y);
        glVertex2f((86.0f + n) / x, 345.0f / y);
        glVertex2f((86.0f + n) / x, 350.0f / y);
        glVertex2f((30.0f + n) / x, 350.0f / y);
        glEnd();

        //21
        glBegin(GL_LINE_LOOP);
        glVertex2f((30.0f + n) / x, 350.0f / y);
        glVertex2f((86.0f + n) / x, 350.0f / y);
        glVertex2f((86.0f + n) / x, 362.0f / y);
        glVertex2f((30.0f + n) / x, 362.0f / y);
        glEnd();

        //22
        glBegin(GL_LINE_LOOP);
        glVertex2f((29.0f + n) / x, 362.0f / y);
        glVertex2f((87.0f + n) / x, 362.0f / y);
        glVertex2f((87.0f + n) / x, 366.0f / y);
        glVertex2f((29.0f + n) / x, 366.0f / y);
        glEnd();

        //23
        glBegin(GL_LINE_LOOP);
        glVertex2f((28.0f + n) / x, 366.0f / y);
        glVertex2f((88.0f + n) / x, 366.0f / y);
        glVertex2f((88.0f + n) / x, 378.0f / y);
        glVertex2f((28.0f + n) / x, 378.0f / y);
        glEnd();

        //24
        glBegin(GL_LINE_LOOP);
        glVertex2f((27.0f + n) / x, 378.0f / y);
        glVertex2f((89.0f + n) / x, 378.0f / y);
        glVertex2f((89.0f + n) / x, 390.0f / y);
        glVertex2f((27.0f + n) / x, 390.0f / y);
        glEnd();

        glBegin(GL_LINES);
        //lines
        glVertex2f((97.0f) / x, 242.0f / y);
        glVertex2f((97.0f) / x, 274.0f / y);

        glVertex2f((99.0f) / x, 291.0f / y);
        glVertex2f((99.0f) / x, 345.0f / y);

        glVertex2f(219.0f / x, 242.0f / y);
        glVertex2f(219.0f / x, 274.0f / y);

        glVertex2f(217 / x, 292.0f / y);
        glVertex2f(217 / x, 345.0f / y);

        glEnd();
        
        n += 200;
        nx += 200;

    }

    //middle circular portion

    glColor3f(187.0f / 255.0f, 136.0f / 255.0f, 85.0f / 255.0f);
    glBegin(GL_TRIANGLE_STRIP);
    float centerx = 157.0f / x, centery = 232.0f / y, radius = 53.0f / x, radius2 = 45.5f / x;;
    float angle;

    float fx = 218.0f / x, fy = 162.5f / y;
    for (i = 0; i < 200; i++)
    {
        angle = M_PI * i / 200.0f;
        glVertex2f(fx, fy);
        glVertex2f(centerx + radius2 * cos(angle), centery + radius2 * sin(angle));
        fx = fx - (0.61) / x;

    }

    glEnd();

    glBegin(GL_QUADS);

    glVertex2f(112.0f / x, 231.0f / y);
    glVertex2f(112.0f / x, 225.0f / y);
    glVertex2f(104.0f / x, 225.0f / y);
    glVertex2f(104.0f / x, 231.0f / y);

    glVertex2f((112.0f + 98) / x, 231.0f / y);
    glVertex2f((112.0f + 98) / x, 225.0f / y);
    glVertex2f((104.0f + 98) / x, 225.0f / y);
    glVertex2f((104.0f + 98) / x, 231.0f / y);

    glEnd();

    glColor3f(0, 0, 0);


    glBegin(GL_LINES);
    glVertex2f(97.0f / x, 170.0f / y);
    glVertex2f(137.0f / x, 170.0f / y);

    glVertex2f(177.0f / x, 170.0f / y);

    glVertex2f(219.0f / x, 170.0f / y);
    glEnd();

    //Lines around circle
    glBegin(GL_LINE_LOOP);
    radius = 53.0f / x;

    for (i = 0; i < 200; i++)
    {
        angle = M_PI * i / 200.0f;
        glVertex2f(centerx + radius * cos(angle), centery + radius * sin(angle));

    }

    radius = 45.5f / x;

    for (i = 200; i > 0; i--)
    {
        angle = M_PI * i / 200.0f;
        glVertex2f(centerx + radius * cos(angle), centery + radius * sin(angle));


    }

    glEnd();

    glColor3f(187.0f / 255.0f, 136.0f / 255.0f, 85.0f / 255.0f);

    glBegin(GL_QUADS);

    glVertex2f(152.0f / x, 162.0f / y);
    glVertex2f(161.0f / x, 162.0f / y);
    glVertex2f(161.0f / x, 175.0f / y);
    glVertex2f(152.0f / x, 175.0f / y);

    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);

    glBegin(GL_LINE_LOOP);
    glVertex2f(152.0f / x, 162.0f / y);
    glVertex2f(161.0f / x, 162.0f / y);
    glVertex2f(161.0f / x, 175.0f / y);
    glVertex2f(152.0f / x, 175.0f / y);
    glEnd();

    //INDIA 
    glPushMatrix();
    glTranslatef(0.5f, -0.164f, 0);
    glScalef(0.07f, 0.05f, 0);
    india();

    glPopMatrix();
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
    glVertex2f(rocket_x + 0.007, rocket_y + 0.25); //upper left point
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
   // rocket_speed += rocket_acceleration;
    rocket_y += rocket_speed;
   
}


// Function to display (render) the scene
void displayFunc() {
    glClear(GL_COLOR_BUFFER_BIT);
   
    
    BackgroundSky();
    Ground();
    //xxxxxxx Clouds xxxxxxxx//
    glPushMatrix();
    glTranslatef(0.5f, 0.75f, 0.0f);
    cloud();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.7f, 0.35f, 0.0f);
    cloud();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.7f, 0.75f, 0.0f);
    cloud();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.7f, 0.20f, 0.0f);
    cloud();
    glPopMatrix();

    //xxxxxxx Clouds End xxxxxxx//
   
    glPushMatrix();
    glTranslatef(0.1, 0.0, 0.0);
    glScalef(1.2, 1.2, 0.0);
    drawRocket();  //Rocket
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-0.2, 0.60, 0);
    IndiaGate();  //India gate
    glPopMatrix();
   
        
    //xxxxxxxxxx Flag Positions xxxxxxxxxxxxxx//
    glPushMatrix();
    glTranslatef(-0.4, -0.4, 0.0);
    glScalef(0.4f, 0.4f, 0);
    Flag1();  
    glPopMatrix();

    
    //xxxxxxxxxxxxxxxxx Flag Display Ends xxxxxxxxxxxxx//
   // GridLines();
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

int main(int argc, char** argv) 
{

    void initialize(void);
    void resize(int, int);
    void display(void);
    void keyboardFunc(unsigned char, int, int);

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

void keyboardFunc(unsigned char key, int x, int y)
{
    // code
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
