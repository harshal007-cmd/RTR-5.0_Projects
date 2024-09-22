#pragma once
#include <gl/GL.h>
#include <gl/GLU.h>

#define _USE_MATH_DEFINES
#include <math.h>

void CircleAnimation(GLfloat t);
void Rushikesh(time_t delta_time, GLfloat t);
void GroupMembers(GLfloat t);
void Base(GLfloat t);
void Raster(void);

// GLfloat t = 1;
GLfloat p = 1;

GLfloat Scalex = 1, Scaley = 1;
GLfloat CircleAnimationRadius = 0.3;
int CircleAnimationFlag = 0;
GLdouble CircleRadiusAlpha = 0.00001;

void CircleAnimation(GLfloat t)
{
    GLfloat xCenter, yCenter, angle;

    glEnable(GL_POINT_SMOOTH);
    glBegin(GL_POINTS);
    xCenter = 0.0, yCenter = 0.35;
    GLfloat radius = 0.3;
    int i = 0;

    if (t >= 0.8)
    {
        while (radius >= CircleAnimationRadius)
        {
            glColor3f((GLfloat)rand() / (GLfloat)RAND_MAX * t, (GLfloat)rand() / (GLfloat)RAND_MAX * t, (GLfloat)rand() / (GLfloat)RAND_MAX * t);

            angle = 2 * M_PI * (i / 100.0);
            glVertex2f(xCenter + radius * cos(angle), yCenter + radius * sin(angle));
            radius = radius - 0.0001;
            i++;
        }
        glEnd();

        if (CircleAnimationRadius >= 0 && CircleAnimationFlag == 0)
        {
            CircleAnimationRadius = CircleAnimationRadius - CircleRadiusAlpha;
        }
        else if (CircleAnimationRadius < 0.4)
        {
            CircleAnimationFlag = 1;
            CircleAnimationRadius = CircleAnimationRadius + CircleRadiusAlpha;
            glLoadIdentity();
            glTranslatef(0.0, 0.35, 0);
            glScalef(CircleAnimationRadius, CircleAnimationRadius, 1);
            drawHappyBirthday();
            glLoadIdentity();
        }
        else
        {
            glLoadIdentity();
            glTranslatef(0.0, 0.35, 0);
            glScalef(CircleAnimationRadius, CircleAnimationRadius, 1);
            drawHappyBirthday();
            glLoadIdentity();
        }
    }
}

void Rushikesh(time_t delta_time, GLfloat t)
{
    GLfloat xCenter, yCenter, radius, angle;
    int i;
    GLfloat TshirtColor[3] = {0};
    GLfloat SkinColor[3] = {(GLfloat)0.98 * t, (GLfloat)0.839 * t, (GLfloat)0.557 * t};
    GLfloat PantsColor[3] = {(GLfloat)0.243 * t, (GLfloat)0.29 * t, (GLfloat)0.502 * t};
    // Head
    // glColor3f(0.98, 0.839, 0.557);
    glColor3fv(SkinColor);
    glBegin(GL_POLYGON);
    xCenter = -0.7, yCenter = 0.2, radius = 0.08;
    for (i = 0; i < 100; i++)
    {
        angle = 2 * M_PI * (i / 100.0);
        glVertex2f(xCenter + radius * cos(angle), yCenter + radius * sin(angle));
    }
    glEnd();

    // Hairs
    glRotatef(45, 0, 0, 1);
    glTranslatef(0.46, 0.35, 0);
    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    GLfloat r2 = 0.07;
    xCenter = -0.8, yCenter = 0.36, radius = 0.021;
    for (i = 0; i < 100; i++)
    {
        angle = 2 * M_PI * (i / 100.0);
        glVertex2f(xCenter + r2 * cos(angle), yCenter + radius * sin(angle));
    }
    glEnd();

    glLoadIdentity();

    glRotatef(-45, 0, 0, 1);
    glTranslatef(0.15, -0.64, 0);
    glBegin(GL_POLYGON);
    r2 = 0.07;
    xCenter = -0.8, yCenter = 0.36, radius = 0.021;
    for (i = 0; i < 100; i++)
    {
        angle = 2 * M_PI * (i / 100.0);
        glVertex2f(xCenter + r2 * cos(angle), yCenter + radius * sin(angle));
    }
    glEnd();
    glLoadIdentity();

    // Eyes
    glPointSize(4);
    glEnable(GL_POINT_SMOOTH);

    glColor3f(0, 0, 0);
    glBegin(GL_POINTS);
    glVertex2f(-0.66, 0.21);
    glVertex2f(-0.74, 0.21);
    glEnd();
    glPointSize(1);

    // Ears
    glColor3fv(SkinColor);
    glBegin(GL_POLYGON);
    xCenter = -0.78, yCenter = 0.2, radius = 0.01;

    for (i = 0; i < 100; i++)
    {
        angle = 2 * M_PI * (i / 100.0);
        glVertex2f(xCenter + radius * cos(angle), yCenter + 0.02 * sin(angle));
    }
    glEnd();

    glBegin(GL_POLYGON);
    xCenter = -0.62, yCenter = 0.2, radius = 0.01;

    for (i = 0; i < 100; i++)
    {
        angle = 2 * M_PI * (i / 100.0);
        glVertex2f(xCenter + radius * cos(angle), yCenter + 0.02 * sin(angle));
    }
    glEnd();

    // Smile
    /*
    glLineWidth(2);
    glBegin(GL_LINE_STRIP);
    xCenter = -0.7, yCenter = 0.2, radius = 0.06;
    for (i = 0; i < 100; i++)
    {
        angle = -(M_PI - 1.0) * (i / 100.0) - 0.50;
        glVertex2f(xCenter + radius * cos(angle), yCenter + radius * sin(angle));
    }
    glEnd();
    */
    glColor3f(0, 00, 0);
    glLineWidth(1);
    glBegin(GL_POLYGON);
    xCenter = -0.7, yCenter = 0.15, radius = delta_time % 2 * 0.005 + 0.002;

    for (i = 0; i < 100; i++)
    {
        angle = 2 * M_PI * (i / 100.0);
        glVertex2f(xCenter + 0.008 * cos(angle), yCenter + radius * sin(angle));
    }
    glEnd();

    glLineWidth(1);

    glBegin(GL_QUADS);
    glColor3fv(SkinColor);
    // Neck
    glVertex2f(-0.72, 0.12);
    glVertex2f(-0.68, 0.12);
    glVertex2f(-0.68, 0.08);
    glVertex2f(-0.72, 0.08);

    // Hands
    // glColor3fv(SkinColor);
    glVertex2f(-0.82, 0.08);
    glVertex2f(-0.86, -0.1);
    glVertex2f(-0.84, -0.1);
    glVertex2f(-0.78, 0.08);

    glVertex2f(-0.58, 0.08);
    glVertex2f(-0.54, -0.1);
    glVertex2f(-0.56, -0.1);
    glVertex2f(-0.62, 0.08);

    glColor3fv(TshirtColor);
    glVertex2f(-0.82, 0.08);
    glVertex2f(-0.86, -0.05);
    glVertex2f(-0.82, -0.05);
    glVertex2f(-0.78, 0.08);

    glVertex2f(-0.58, 0.08);
    glVertex2f(-0.54, -0.05);
    glVertex2f(-0.58, -0.05);
    glVertex2f(-0.62, 0.08);

    // Main Body
    // glColor3fv(TshirtColor);
    glVertex2f(-0.82, 0.08);
    glVertex2f(-0.58, 0.08);
    glVertex2f(-0.62, -0.22);
    glVertex2f(-0.78, -0.22);

    // Fore Arms
    glColor3fv(SkinColor);
    glVertex2f(-0.86, -0.1);
    glVertex2f(-0.84, -0.1);
    glVertex2f(-0.68, -0.02);
    glVertex2f(-0.70, -0.02);

    glVertex2f(-0.54, -0.1);
    glVertex2f(-0.56, -0.1);
    glVertex2f(-0.70, -0.02);
    glVertex2f(-0.68, -0.02);

    // Palms
    glVertex2f(-0.68, -0.02);
    glVertex2f(-0.70, -0.02);
    glVertex2f(-0.70, -0.02);
    glVertex2f(-0.69, 0.06);

    // Legs
    glColor3fv(PantsColor);
    glVertex2f(-0.78, -0.22);
    glVertex2f(-0.69, -0.22);
    glVertex2f(-0.74, -0.66);
    glVertex2f(-0.78, -0.66);

    glVertex2f(-0.62, -0.22);
    glVertex2f(-0.71, -0.22);
    glVertex2f(-0.66, -0.66);
    glVertex2f(-0.62, -0.66);

    glEnd();

    // Leg Palm
    glColor3fv(SkinColor);
    glBegin(GL_POLYGON);
    xCenter = -0.76, yCenter = -0.67, radius = 0.03;
    for (i = 0; i < 100; i++)
    {
        angle = M_PI * (i / 100.0);
        glVertex2f(xCenter + radius * cos(angle), yCenter + radius * sin(angle));
    }

    glEnd();

    glBegin(GL_POLYGON);
    xCenter = -0.64, yCenter = -0.67, radius = 0.03;
    for (i = 0; i < 100; i++)
    {
        angle = M_PI * (i / 100.0);
        glVertex2f(xCenter + radius * cos(angle), yCenter + radius * sin(angle));
    }

    glEnd();

    // Raster Logo

    glBegin(GL_TRIANGLES);
    glColor3f(1 * t, 0, 0);
    glVertex2f(-0.64, 0.05);
    glColor3f(0, 1 * t, 0);
    glVertex2f(-0.62, 0.02);
    glColor3f(0, 0, 1 * t);
    glVertex2f(-0.66, 0.02);
    glEnd();

    // GL
    glColor3f(1 * t, 1 * t, 1 * t);
    glBegin(GL_LINE_STRIP);
    xCenter = -0.64, yCenter = -0.01, radius = 0.012;
    for (i = 0; i < 100; i++)
    {
        angle = ((M_PI + 0.3) * (i / 100.0)) + (M_PI / 2.0);
        glVertex2f(xCenter + radius * cos(angle), yCenter + radius * sin(angle));
    }
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-0.639, -0.01);
    glVertex2f(-0.639, -0.02);

    glVertex2f(-0.63, 0.002);
    glVertex2f(-0.63, -0.02);

    glVertex2f(-0.63, -0.02);
    glVertex2f(-0.62, -0.02);

    glEnd();
}

void GroupMembers(GLfloat t)
{
    void Raster(void);

    GLfloat xCenter, yCenter, radius, angle;
    int i, j;
    GLfloat TshirtColor[3] = {(GLfloat)0.373 * t, (GLfloat)0.384 * t, (GLfloat)0.6 * t};
    GLfloat SkinColor[3] = {(GLfloat)0.98 * t, (GLfloat)0.839 * t, (GLfloat)0.557 * t};
    GLfloat PantsColor[3] = {0}; //{0.243, 0.29, 0.502};

    for (j = 0; j < 4; j++)
    {
        glLoadIdentity();
        // glTranslatef(-0.4, 0, 0);
        glTranslatef(0.4 * j - 0.05, -0.6, 0);
        glScalef(0.8, 0.8, 1);

        // Ears
        glColor3fv(SkinColor);
        glBegin(GL_POLYGON);
        xCenter = -0.78, yCenter = 0.2, radius = 0.02;

        for (i = 0; i < 100; i++)
        {
            angle = 2 * M_PI * (i / 100.0);
            glVertex2f(xCenter + radius * cos(angle), yCenter + 0.02 * sin(angle));
        }
        glEnd();

        glBegin(GL_POLYGON);
        xCenter = -0.62, yCenter = 0.2, radius = 0.02;

        for (i = 0; i < 100; i++)
        {
            angle = 2 * M_PI * (i / 100.0);
            glVertex2f(xCenter + radius * cos(angle), yCenter + 0.02 * sin(angle));
        }
        glEnd();

        //  Head
        glColor3fv(SkinColor);
        glBegin(GL_POLYGON);
        xCenter = -0.7, yCenter = 0.2, radius = 0.08;
        for (i = 0; i < 100; i++)
        {
            angle = 2 * M_PI * (i / 100.0);
            glVertex2f(xCenter + radius * cos(angle), yCenter + radius * sin(angle));
        }
        glEnd();

        glColor3f(0, 0, 0);
        glBegin(GL_POLYGON);
        xCenter = -0.7, yCenter = 0.22, radius = 0.09;
        for (i = 0; i < 100; i++)
        {
            angle = 2 * M_PI * (i / 100.0);
            glVertex2f(xCenter + radius * cos(angle), yCenter + radius * sin(angle));
        }
        glEnd();

        glBegin(GL_QUADS);
        glColor3fv(SkinColor);
        // Neck
        glVertex2f(-0.72, 0.13);
        glVertex2f(-0.68, 0.13);
        glVertex2f(-0.68, 0.08);
        glVertex2f(-0.72, 0.08);

        // Hands
        // glColor3f(0.98, 0.839, 0.557);
        glVertex2f(-0.82, 0.08);
        glVertex2f(-0.86, -0.1);
        glVertex2f(-0.84, -0.1);
        glVertex2f(-0.78, 0.08);

        glVertex2f(-0.58, 0.08);
        glVertex2f(-0.54, -0.1);
        glVertex2f(-0.56, -0.1);
        glVertex2f(-0.62, 0.08);

        glColor3fv(TshirtColor);
        glVertex2f(-0.82, 0.08);
        glVertex2f(-0.86, -0.05);
        glVertex2f(-0.82, -0.05);
        glVertex2f(-0.78, 0.08);

        glVertex2f(-0.58, 0.08);
        glVertex2f(-0.54, -0.05);
        glVertex2f(-0.58, -0.05);
        glVertex2f(-0.62, 0.08);

        // Fore Arms
        glColor3fv(SkinColor);
        glVertex2f(-0.86, -0.1);
        glVertex2f(-0.84, -0.1);
        glVertex2f(-0.68, -0.02);
        glVertex2f(-0.70, -0.02);

        glVertex2f(-0.54, -0.1);
        glVertex2f(-0.56, -0.1);
        glVertex2f(-0.70, -0.02);
        glVertex2f(-0.68, -0.02);

        // Palms
        glVertex2f(-0.68, -0.02);
        glVertex2f(-0.70, -0.02);
        glVertex2f(-0.70, -0.02);
        glVertex2f(-0.69, 0.06);
        // Main Body
        glColor3fv(TshirtColor);
        glVertex2f(-0.82, 0.08);
        glVertex2f(-0.58, 0.08);
        glVertex2f(-0.62, -0.22);
        glVertex2f(-0.78, -0.22);

        // Sitting position
        glColor3fv(PantsColor);

        glVertex2f(-0.62, -0.22);
        glVertex2f(-0.78, -0.22);
        glVertex2f(-0.82, -0.28);
        glVertex2f(-0.58, -0.28);

        glVertex2f(-0.82, -0.28);
        glVertex2f(-0.85, -0.20);
        glVertex2f(-0.78, -0.20);
        glVertex2f(-0.76, -0.28);

        glVertex2f(-0.58, -0.28);
        glVertex2f(-0.55, -0.20);
        glVertex2f(-0.62, -0.20);
        glVertex2f(-0.64, -0.28);

        glEnd();

        glBegin(GL_POLYGON);
        xCenter = -0.815, yCenter = -0.20, radius = 0.035;
        for (i = 0; i < 100; i++)
        {
            angle = (M_PI * 2) * (i / 100.0);
            glVertex2f(xCenter + radius * cos(angle), yCenter + radius * sin(angle));
        }
        glEnd();

        glBegin(GL_POLYGON);
        xCenter = -0.584, yCenter = -0.20, radius = 0.035;
        for (i = 0; i < 100; i++)
        {
            angle = (M_PI * 2) * (i / 100.0);
            glVertex2f(xCenter + radius * cos(angle), yCenter + radius * sin(angle));
        }
        glEnd();
        // hairs
        if (j == 3)
        {
            glColor3f(0, 0, 0);
            GLfloat x, y, x1, y1;
            xCenter = -0.8, yCenter = -0.1, radius = 0.02;
            x = xCenter;
            y = yCenter;
            x1 = -0.78, y1 = 0.22;

            glBegin(GL_TRIANGLE_STRIP);

            for (i = 0; i < 200; i++)
            {
                x = x + 0.001;
                angle = 2 * M_PI * (i / 100.0);
                y = yCenter + radius * sin(angle);
                glVertex2f(x, y);
                glVertex2f(x1, y1);
                x1 = x1 + 0.0008;
            }

            glEnd();
        }
        Raster();
    }

    for (j = 0; j < 5; j++)
    {
        glLoadIdentity();
        // glTranslatef(-0.4, 0, 0);
        glTranslatef(0.4 * j - 0.1, -0.9, 0);
        // glScalef(0.7, 0.7, 1);

        // Ears
        glColor3fv(SkinColor);
        glBegin(GL_POLYGON);
        xCenter = -0.78, yCenter = 0.2, radius = 0.02;

        for (i = 0; i < 100; i++)
        {
            angle = 2 * M_PI * (i / 100.0);
            glVertex2f(xCenter + radius * cos(angle), yCenter + 0.02 * sin(angle));
        }
        glEnd();

        glBegin(GL_POLYGON);
        xCenter = -0.62, yCenter = 0.2, radius = 0.02;

        for (i = 0; i < 100; i++)
        {
            angle = 2 * M_PI * (i / 100.0);
            glVertex2f(xCenter + radius * cos(angle), yCenter + 0.02 * sin(angle));
        }
        glEnd();

        //  Head
        glColor3fv(SkinColor);
        glBegin(GL_POLYGON);
        xCenter = -0.7, yCenter = 0.2, radius = 0.08;
        for (i = 0; i < 100; i++)
        {
            angle = 2 * M_PI * (i / 100.0);
            glVertex2f(xCenter + radius * cos(angle), yCenter + radius * sin(angle));
        }
        glEnd();
        glColor3f(0, 0, 0);
        glBegin(GL_POLYGON);
        xCenter = -0.7, yCenter = 0.22, radius = 0.09;
        for (i = 0; i < 100; i++)
        {
            angle = 2 * M_PI * (i / 100.0);
            glVertex2f(xCenter + radius * cos(angle), yCenter + radius * sin(angle));
        }
        glEnd();
        glBegin(GL_QUADS);
        glColor3fv(SkinColor);
        // Neck
        glVertex2f(-0.72, 0.13);
        glVertex2f(-0.68, 0.13);
        glVertex2f(-0.68, 0.08);
        glVertex2f(-0.72, 0.08);

        // Hands
        // glColor3f(0.98, 0.839, 0.557);
        glVertex2f(-0.82, 0.08);
        glVertex2f(-0.86, -0.1);
        glVertex2f(-0.84, -0.1);
        glVertex2f(-0.78, 0.08);

        glVertex2f(-0.58, 0.08);
        glVertex2f(-0.54, -0.1);
        glVertex2f(-0.56, -0.1);
        glVertex2f(-0.62, 0.08);

        glColor3fv(TshirtColor);
        glVertex2f(-0.82, 0.08);
        glVertex2f(-0.86, -0.05);
        glVertex2f(-0.82, -0.05);
        glVertex2f(-0.78, 0.08);

        glVertex2f(-0.58, 0.08);
        glVertex2f(-0.54, -0.05);
        glVertex2f(-0.58, -0.05);
        glVertex2f(-0.62, 0.08);

        // Fore Arms
        glColor3fv(SkinColor);
        glVertex2f(-0.86, -0.1);
        glVertex2f(-0.84, -0.1);
        glVertex2f(-0.68, -0.02);
        glVertex2f(-0.70, -0.02);

        glVertex2f(-0.54, -0.1);
        glVertex2f(-0.56, -0.1);
        glVertex2f(-0.70, -0.02);
        glVertex2f(-0.68, -0.02);

        // Palms
        glVertex2f(-0.68, -0.02);
        glVertex2f(-0.70, -0.02);
        glVertex2f(-0.70, -0.02);
        glVertex2f(-0.69, 0.06);
        // Main Body
        glColor3fv(TshirtColor);
        glVertex2f(-0.82, 0.08);
        glVertex2f(-0.58, 0.08);
        glVertex2f(-0.62, -0.22);
        glVertex2f(-0.78, -0.22);

        // Sitting position
        glColor3fv(PantsColor);

        glVertex2f(-0.62, -0.22);
        glVertex2f(-0.78, -0.22);
        glVertex2f(-0.82, -0.28);
        glVertex2f(-0.58, -0.28);

        glVertex2f(-0.82, -0.28);
        glVertex2f(-0.85, -0.20);
        glVertex2f(-0.78, -0.20);
        glVertex2f(-0.76, -0.28);

        glVertex2f(-0.58, -0.28);
        glVertex2f(-0.55, -0.20);
        glVertex2f(-0.62, -0.20);
        glVertex2f(-0.64, -0.28);
        glEnd();

        glBegin(GL_POLYGON);
        xCenter = -0.815, yCenter = -0.20, radius = 0.035;
        for (i = 0; i < 100; i++)
        {
            angle = (M_PI * 2) * (i / 100.0);
            glVertex2f(xCenter + radius * cos(angle), yCenter + radius * sin(angle));
        }
        glEnd();

        glBegin(GL_POLYGON);
        xCenter = -0.584, yCenter = -0.20, radius = 0.035;
        for (i = 0; i < 100; i++)
        {
            angle = (M_PI * 2) * (i / 100.0);
            glVertex2f(xCenter + radius * cos(angle), yCenter + radius * sin(angle));
        }
        glEnd();

        // hairs
        if (j == 3)
        {
            glColor3f(0, 0, 0);
            GLfloat x, y, x1, y1;
            xCenter = -0.8, yCenter = -0.1, radius = 0.02;
            x = xCenter;
            y = yCenter;
            x1 = -0.78, y1 = 0.22;

            glBegin(GL_TRIANGLE_STRIP);

            for (i = 0; i < 200; i++)
            {
                x = x + 0.001;
                angle = 2 * M_PI * (i / 100.0);
                y = yCenter + radius * sin(angle);
                glVertex2f(x, y);
                glVertex2f(x1, y1);
                x1 = x1 + 0.0008;
            }

            glEnd();
        }

        Raster();
    }
    glLoadIdentity();
}

void Base(GLfloat t)
{
    GLfloat xCenter, yCenter, radius, angle;
    int i;

    glBegin(GL_QUADS);
    // Front Wall
    glColor3f(0.318 * t, 0.38 * t, 0.459 * t);
    glVertex2f(-1, 1);
    glVertex2f(1, 1);
    //	glColor3f(0.218, 0.28, 0.359);
    glColor3f(0.118 * t, 0.18 * t, 0.2 * t);
    glVertex2f(1, -0.5);
    glVertex2f(-1, -0.5);

    // Floor
    glColor3f(0.6 * t, 0.6 * t, 0.6 * t);
    glVertex2f(-1, -0.5);
    glVertex2f(1, -0.5);
    glColor3f(0.737 * t, 0.753 * t, 0.769 * t);
    glVertex2f(1, -1);
    glVertex2f(-1, -1);

    // TV
    // Outer Rect
    // glColor3f(0.6, 0.6, 0.6);
    glColor3f(0.2 * t, 0.2 * t, 0.2 * t);
    glVertex2f(-0.4, 0.7);
    glVertex2f(0.4, 0.7);
    glVertex2f(0.4, 0.0);
    glVertex2f(-0.4, 00.0);

    // Inner Rect
    glColor3f(0.3 * t, 0.3 * t, 0.3 * t);
    glVertex2f(-0.39, 0.69);
    glVertex2f(0.39, 0.69);
    glColor3f(0.1 * t, 0.1 * t, 0.1 * t);
    glVertex2f(0.39, 0.01);
    glVertex2f(-0.39, 00.01);

    glColor3f(0 * t, 0 * t, 0 * t);
    glVertex2f(0.4, 0.0);
    glVertex2f(-0.4, 0.0);
    glColor3f(0.218 * t, 0.28 * t, 0.3 * t);
    glVertex2f(-0.395, -0.02);
    glVertex2f(0.395, -0.02);

    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0.1 * t, 0.1 * t, 0.1 * t);
    glVertex2f(-0.4, 0.7);
    glVertex2f(0.4, 0.7);
    glVertex2f(0.4, 0.0);
    glVertex2f(-0.4, 00.0);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.39, 0.69);
    glVertex2f(0.39, 0.69);
    glVertex2f(0.39, 0.01);
    glVertex2f(-0.39, 00.01);
    glEnd();
    /*
        glBegin(GL_QUADS);

        // Outer Rect
        glColor3f(0.6, 0.6, 0.6);
        glVertex2f(-0.4, -0.7);
        glVertex2f(0.4, -0.7);
        glVertex2f(0.42, -1.0);
        glVertex2f(-0.42, -1.0);

        // Inner REct
        glColor3f(0.6, 0.6, 0.6);
        glVertex2f(-0.4, -0.7);
        glVertex2f(0.4, -0.7);
        glVertex2f(0.42, -1.0);
        glVertex2f(-0.42, -1.0);
        glEnd();
    */

    // Tiles
    glBegin(GL_LINES);
    glColor3f(0, 0, 0);

    glVertex2f(1, -0.5);
    glVertex2f(-1, -0.5);

    // Horisontal Lines
    glColor3f(0.1 * t, 0.1 * t, 0.1 * t);

    glVertex2f(0.15, -0.5);
    glVertex2f(0.25, -1.0);

    glVertex2f(-0.15, -0.5);
    glVertex2f(-0.25, -1.0);

    glColor3f(0.2 * t, 0.2 * t, 0.2 * t);

    glVertex2f(0.45, -0.5);
    glVertex2f(0.65, -1.0);

    glVertex2f(-0.45, -0.5);
    glVertex2f(-0.65, -1.0);

    glColor3f(0.5 * t, 0.5 * t, 0.5 * t);
    glVertex2f(0.75, -0.5);
    glVertex2f(1.05, -1.0);

    glVertex2f(-0.75, -0.5);
    glVertex2f(-1.05, -1.0);

    // Horisontal  Lines
    glColor3f(0.5 * t, 0.5 * t, 0.5 * t);

    glVertex2f(1, -0.55);
    glVertex2f(-1, -0.55);

    glColor3f(0.4 * t, 0.4 * t, 0.4 * t);

    glVertex2f(1, -0.65);
    glVertex2f(-1, -0.65);
    glColor3f(0.3 * t, 0.3 * t, 0.3 * t);

    glVertex2f(1, -0.8);
    glVertex2f(-1, -0.8);
    glColor3f(0.3 * t, 0.3 * t, 0.3 * t);

    glVertex2f(1, -0.99);
    glVertex2f(-1, -0.99);
    glEnd();

    // Dressing Table
    glBegin(GL_QUADS);
    glColor3f(0.953 * t, 0.973 * t, 0.98 * t);

    glVertex2f(-0.7, -0.24);
    glVertex2f(0.7, -0.24);
    glVertex2f(0.7, -0.51);
    glVertex2f(-0.7, -0.51);

    glColor3f(0.9 * t, 0.9 * t, 0.9 * t);
    glVertex2f(0.67, -0.51);
    glVertex2f(-0.67, -0.51);
    glVertex2f(-0.67, -0.55);
    glVertex2f(0.67, -0.55);

    glColor3f(0.929 * t, 0.882 * t, 0.604 * t);
    glVertex2f(-0.7, -0.24);
    glVertex2f(0.7, -0.24);
    glVertex2f(0.7, -0.18);
    glVertex2f(-0.7, -0.18);

    glColor3f(0.8 * t, 0.757 * t, 0.506 * t);
    glVertex2f(0.7, -0.18);
    glVertex2f(-0.7, -0.18);
    glVertex2f(-0.65, -0.16);
    glVertex2f(0.65, -0.16);
    glEnd();

    glColor3f(0, 0, 0);

    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.7, -0.24);
    glVertex2f(0.7, -0.24);
    glVertex2f(0.7, -0.51);
    glVertex2f(-0.7, -0.51);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex2f(0.67, -0.51);
    glVertex2f(-0.67, -0.51);
    glVertex2f(-0.67, -0.55);
    glVertex2f(0.67, -0.55);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.7, -0.24);
    glVertex2f(0.7, -0.24);
    glVertex2f(0.7, -0.18);
    glVertex2f(-0.7, -0.18);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex2f(0.7, -0.18);
    glVertex2f(-0.7, -0.18);
    glVertex2f(-0.65, -0.16);
    glVertex2f(0.65, -0.16);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0, 0, 0);
    glVertex2f(-0.4, -0.20);
    glVertex2f(-0.4, -0.30);
    glVertex2f(0.4, -0.30);
    glVertex2f(0.4, -0.20);

    glColor3f(0.8 * t, 0.757 * t, 0.506 * t);
    glVertex2f(-0.4, -0.29);
    glVertex2f(-0.4, -0.30);
    glVertex2f(0.4, -0.30);
    glVertex2f(0.4, -0.29);

    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex2f(-0.4, -0.20);
    glVertex2f(-0.4, -0.30);
    glVertex2f(-0.39, -0.29);

    glVertex2f(0.4, -0.20);
    glVertex2f(0.4, -0.30);
    glVertex2f(0.39, -0.29);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex2f(-0.4, -0.20);
    glVertex2f(-0.4, -0.30);
    glVertex2f(0.4, -0.30);
    glVertex2f(0.4, -0.20);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.4, -0.20);
    glVertex2f(-0.4, -0.30);
    glVertex2f(-0.39, -0.29);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex2f(0.4, -0.20);
    glVertex2f(0.4, -0.30);
    glVertex2f(0.39, -0.29);
    glEnd();

    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3f(0.4 * t, 0.4 * t, 0.4 * t);
    glVertex2f(-0.35, -0.30);
    glVertex2f(-0.35, -0.51);

    glVertex2f(0.35, -0.30);
    glVertex2f(0.35, -0.51);
    glEnd();
    glLineWidth(1);

    // Room Decoration
    // Stool

    glColor3f(0, 0, 0);
    glBegin(GL_LINES);

    glVertex2f(0.75, -0.53);
    glVertex2f(0.77, -0.23);

    glVertex2f(0.75, -0.53);
    glVertex2f(0.81, -0.25);

    glVertex2f(0.81, -0.25);
    glVertex2f(0.85, -0.55);

    glVertex2f(0.85, -0.55);
    glVertex2f(0.90, -0.25);

    glVertex2f(0.90, -0.25);
    glVertex2f(0.96, -0.53);

    glVertex2f(0.96, -0.53);
    glVertex2f(0.94, -0.23);

    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    GLfloat r2 = 0.1;
    xCenter = 0.855, yCenter = -0.23, radius = 0.02;
    for (i = 0; i < 100; i++)
    {
        angle = 2 * M_PI * (i / 100.0);
        glVertex2f(xCenter + r2 * cos(angle), yCenter + radius * sin(angle));
    }
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.8 * t, 0.757 * t, 0.506 * t);

    xCenter = 0.83, yCenter = -0.17, radius = 0.06;
    for (i = 0; i < 100; i++)
    {
        angle = 2 * M_PI * (i / 100.0);
        glVertex2f(xCenter + radius * cos(angle), yCenter + radius * sin(angle));
    }
    glEnd();

    glColor3f(0.953 * t, 0.973 * t, 0.98 * t);
    glBegin(GL_QUADS);
    glVertex2f(0.77, 0.02);
    glVertex2f(0.89, 0.02);
    glVertex2f(0.91, -0.12);
    glVertex2f(0.75, -0.12);
    glEnd();

    // Remote
}

void Raster(void)
{
    GLfloat xCenter, yCenter, radius, angle;
    int i, j;

    glTranslatef(-0.78, -0.1, 0);
    glScalef(0.6, 0.6, 1);
    glEnable(GL_LINE_SMOOTH);

    glBegin(GL_LINES);
    // R
    glVertex2f(0, 0.1);
    glVertex2f(0, 0);

    glVertex2f(0, 0.05);
    glVertex2f(0.03, 0);
    glEnd();

    glBegin(GL_LINE_STRIP);

    xCenter = 0, yCenter = 0.075, radius = 0.025;
    for (i = 0; i < 100; i++)
    {
        angle = -(M_PI * (i / 100.0)) + (M_PI / 2.0);
        glVertex2f(xCenter + radius * cos(angle), yCenter + radius * sin(angle));
    }
    glEnd();

    // A
    glTranslatef(0.065, 0, 0);
    glBegin(GL_LINES);
    glVertex2f(0, 0.1);
    glVertex2f(-0.025, 0);

    glVertex2f(0, 0.1);
    glVertex2f(0.025, 0);

    glVertex2f(-0.01, 0.05);
    glVertex2f(0.01, 0.05);

    glEnd();

    // S
    glTranslatef(0.05, 0, 0);

    glBegin(GL_LINE_STRIP);
    xCenter = 0, yCenter = 0.075, radius = 0.025;
    for (i = 0; i < 100; i++)
    {
        angle = ((M_PI + 0.3) * (i / 100.0)) + (M_PI / 2.0);
        glVertex2f(xCenter + radius * cos(angle), yCenter + radius * sin(angle));
    }
    glEnd();

    glBegin(GL_LINE_STRIP);
    xCenter = 0, yCenter = 0.025, radius = 0.025;
    for (i = 0; i < 100; i++)
    {
        angle = -((M_PI + 0.3) * (i / 100.0)) + (M_PI / 2.0) + 0.2;
        glVertex2f(xCenter + radius * cos(angle), yCenter + radius * sin(angle));
    }
    glEnd();

    // T
    glTranslatef(0.05, 0, 0);

    glBegin(GL_LINES);

    glVertex2f(-0.025, 0.1);
    glVertex2f(0.025, 0.1);

    glVertex2f(0, 0.1);
    glVertex2f(0, 0);
    glEnd();

    // E

    glTranslatef(0.06, 0, 0);

    glBegin(GL_LINES);

    glVertex2f(-0.025, 0.1);
    glVertex2f(-0.025, 0);

    glVertex2f(-0.025, 0.1);
    glVertex2f(0.01, 0.1);

    glVertex2f(-0.025, 0.05);
    glVertex2f(0.01, 0.05);

    glVertex2f(-0.025, 0.0);
    glVertex2f(0.01, 0.0);

    glEnd();

    glTranslatef(0.03, 0, 0);
    glBegin(GL_LINES);
    // R
    glVertex2f(0, 0.1);
    glVertex2f(0, 0);

    glVertex2f(0, 0.05);
    glVertex2f(0.03, 0);
    glEnd();

    glBegin(GL_LINE_STRIP);

    xCenter = 0, yCenter = 0.075, radius = 0.025;
    for (i = 0; i < 100; i++)
    {
        angle = -(M_PI * (i / 100.0)) + (M_PI / 2.0);
        glVertex2f(xCenter + radius * cos(angle), yCenter + radius * sin(angle));
    }
    glEnd();
}
