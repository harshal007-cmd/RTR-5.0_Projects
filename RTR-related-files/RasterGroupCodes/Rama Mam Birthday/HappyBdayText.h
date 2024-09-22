#include <gl/GL.h>
#include <gl/GLU.h>

void H(float LetterColor[]);
void A(float LetterColor[]);
void P(float LetterColor[]);
void PP(float LetterColor[]);
void Y(float LetterColor[]);
void B(float LetterColor[]);
void I(float LetterColor[]);
void R(float LetterColor[]);
void T(float LetterColor[]);
void HH(float LetterColor[]);
void D(float LetterColor[]);
void AA(float LetterColor[]);
void YY(float LetterColor[]);

void RR(float LetterColor[]);
void AAA(float LetterColor[]);
void M(float LetterColor[]);
void AAAA(float LetterColor[]);
void MM(float LetterColor[]);
void AAAAA(float LetterColor[]);
void Apostope(float LetterColor[]);
void AAAAAA(float LetterColor[]);
void MMM(float LetterColor[]);
void drawHappyBirthday(void);

void drawHappyBirthday(void)
{

    float LetColor[3] = {0.5, 0.8, 0.9};
    H(LetColor);
    A(LetColor);
    P(LetColor);
    PP(LetColor);
    Y(LetColor);

    B(LetColor);
    I(LetColor);
    R(LetColor);
    T(LetColor);
    HH(LetColor);
    D(LetColor);
    AA(LetColor);
    YY(LetColor);

    RR(LetColor);
    AAA(LetColor);
    M(LetColor);
    AAAA(LetColor);

    MM(LetColor);
    AAAAA(LetColor);
    Apostope(LetColor);
    AAAAAA(LetColor);
    MMM(LetColor);
}
void H(float LetterColor[])
{
    glColor3fv(LetterColor);
    glBegin(GL_QUADS);

    glVertex2f(-0.65, 0.6);
    glVertex2f(-0.63, 0.6);
    glVertex2f(-0.63, 0.4);
    glVertex2f(-0.65, 0.4);

    glVertex2f(-0.58, 0.49);
    glVertex2f(-0.58, 0.51);
    glVertex2f(-0.63, 0.51);
    glVertex2f(-0.63, 0.49);

    glVertex2f(-0.58, 0.6);
    glVertex2f(-0.56, 0.6);
    glVertex2f(-0.56, 0.4);
    glVertex2f(-0.58, 0.4);

    glEnd();
}

void A(float LetterColor[])
{
    glColor3fv(LetterColor);
    glBegin(GL_QUADS);

    glVertex2f(-0.50, 0.6);
    glVertex2f(-0.48, 0.6);
    glVertex2f(-0.48, 0.4);
    glVertex2f(-0.50, 0.4);

    glVertex2f(-0.43, 0.49);
    glVertex2f(-0.43, 0.51);
    glVertex2f(-0.48, 0.51);
    glVertex2f(-0.48, 0.49);

    glVertex2f(-0.43, 0.6);
    glVertex2f(-0.41, 0.6);
    glVertex2f(-0.41, 0.4);
    glVertex2f(-0.43, 0.4);

    glVertex2f(-0.41, 0.58);
    glVertex2f(-0.41, 0.6);
    glVertex2f(-0.50, 0.6);
    glVertex2f(-0.50, 0.58);

    glEnd();
}

void P(float LetterColor[])
{
    glColor3fv(LetterColor);
    glBegin(GL_QUADS);

    glVertex2f(-0.36, 0.6);
    glVertex2f(-0.34, 0.6);
    glVertex2f(-0.34, 0.4);
    glVertex2f(-0.36, 0.4);

    glVertex2f(-0.29, 0.58);
    glVertex2f(-0.29, 0.60);
    glVertex2f(-0.34, 0.60);
    glVertex2f(-0.34, 0.58);

    glVertex2f(-0.29, 0.49);
    glVertex2f(-0.29, 0.51);
    glVertex2f(-0.34, 0.51);
    glVertex2f(-0.34, 0.49);

    glVertex2f(-0.29, 0.60);
    glVertex2f(-0.27, 0.60);
    glVertex2f(-0.27, 0.49);
    glVertex2f(-0.29, 0.49);

    glEnd();
}

void PP(float LetterColor[])
{
    glColor3fv(LetterColor);
    glBegin(GL_QUADS);

    glVertex2f(-0.23, 0.6);
    glVertex2f(-0.21, 0.6);
    glVertex2f(-0.21, 0.4);
    glVertex2f(-0.23, 0.4);

    glVertex2f(-0.16, 0.58);
    glVertex2f(-0.16, 0.60);
    glVertex2f(-0.21, 0.60);
    glVertex2f(-0.21, 0.58);

    glVertex2f(-0.16, 0.49);
    glVertex2f(-0.16, 0.51);
    glVertex2f(-0.21, 0.51);
    glVertex2f(-0.21, 0.49);

    glVertex2f(-0.16, 0.60);
    glVertex2f(-0.14, 0.60);
    glVertex2f(-0.14, 0.49);
    glVertex2f(-0.16, 0.49);

    glEnd();
}

void Y(float LetterColor[])
{
    glColor3fv(LetterColor);
    glBegin(GL_QUADS);

    glVertex2f(-0.08, 0.6);
    glVertex2f(-0.06, 0.6);
    glVertex2f(-0.06, 0.5);
    glVertex2f(-0.08, 0.5);

    glVertex2f(-0.01, 0.6);
    glVertex2f(0.01, 0.6);
    glVertex2f(0.01, 0.5);
    glVertex2f(-0.01, 0.5);

    glVertex2f(0.01, 0.49);
    glVertex2f(0.01, 0.51);
    glVertex2f(-0.08, 0.51);
    glVertex2f(-0.08, 0.49);

    glVertex2f(-0.04, 0.5);
    glVertex2f(-0.02, 0.5);
    glVertex2f(-0.02, 0.4);
    glVertex2f(-0.04, 0.4);

    glEnd();
}

void B(float LetterColor[])
{
    glColor3fv(LetterColor);
    glBegin(GL_QUADS);

    glVertex2f(-0.36, 0.3);
    glVertex2f(-0.34, 0.3);
    glVertex2f(-0.34, 0.1);
    glVertex2f(-0.36, 0.1);

    glVertex2f(-0.29, 0.28);
    glVertex2f(-0.29, 0.30);
    glVertex2f(-0.34, 0.30);
    glVertex2f(-0.34, 0.28);

    glVertex2f(-0.29, 0.19);
    glVertex2f(-0.29, 0.21);
    glVertex2f(-0.34, 0.21);
    glVertex2f(-0.34, 0.19);

    glVertex2f(-0.29, 0.3);
    glVertex2f(-0.27, 0.3);
    glVertex2f(-0.27, 0.1);
    glVertex2f(-0.29, 0.1);

    glVertex2f(-0.29, 0.19);
    glVertex2f(-0.29, 0.21);
    glVertex2f(-0.34, 0.21);
    glVertex2f(-0.34, 0.19);

    glVertex2f(-0.27, 0.1);
    glVertex2f(-0.27, 0.08);
    glVertex2f(-0.36, 0.08);
    glVertex2f(-0.36, 0.1);

    glEnd();
}

void I(float LetterColor[])
{
    glColor3fv(LetterColor);
    glBegin(GL_QUADS);

    glVertex2f(-0.14, 0.28);
    glVertex2f(-0.14, 0.30);
    glVertex2f(-0.22, 0.30);
    glVertex2f(-0.22, 0.28);

    glVertex2f(-0.19, 0.3);
    glVertex2f(-0.17, 0.3);
    glVertex2f(-0.17, 0.1);
    glVertex2f(-0.19, 0.1);

    glVertex2f(-0.14, 0.08);
    glVertex2f(-0.14, 0.1);
    glVertex2f(-0.22, 0.1);
    glVertex2f(-0.22, 0.08);

    glEnd();
}

void R(float LetterColor[])
{
    glColor3fv(LetterColor);
    glBegin(GL_QUADS);

    glVertex2f(-0.08, 0.3);
    glVertex2f(-0.06, 0.3);
    glVertex2f(-0.06, 0.08);
    glVertex2f(-0.08, 0.08);

    glVertex2f(-0.01, 0.28);
    glVertex2f(-0.01, 0.3);
    glVertex2f(-0.06, 0.3);
    glVertex2f(-0.06, 0.28);

    glVertex2f(-0.01, 0.19);
    glVertex2f(-0.01, 0.21);
    glVertex2f(-0.06, 0.21);
    glVertex2f(-0.06, 0.19);

    glVertex2f(0.01, 0.3);
    glVertex2f(-0.01, 0.3);
    glVertex2f(-0.01, 0.19);
    glVertex2f(0.01, 0.19);

    glVertex2f(-0.03, 0.08);
    glVertex2f(-0.01, 0.08);
    glVertex2f(-0.01, 0.19);
    glVertex2f(-0.03, 0.19);

    glEnd();
}

void T(float LetterColor[])
{
    glColor3fv(LetterColor);
    glBegin(GL_QUADS);

    glVertex2f(0.06, 0.28);
    glVertex2f(0.06, 0.30);
    glVertex2f(0.18, 0.30);
    glVertex2f(0.18, 0.28);

    glVertex2f(0.11, 0.3);
    glVertex2f(0.13, 0.3);
    glVertex2f(0.13, 0.08);
    glVertex2f(0.11, 0.08);

    glEnd();
}

void HH(float LetterColor[])
{
    glColor3fv(LetterColor);
    glBegin(GL_QUADS);

    glVertex2f(0.24, 0.3);
    glVertex2f(0.26, 0.3);
    glVertex2f(0.26, 0.08);
    glVertex2f(0.24, 0.08);

    glVertex2f(0.26, 0.19);
    glVertex2f(0.26, 0.21);
    glVertex2f(0.31, 0.21);
    glVertex2f(0.31, 0.19);

    glVertex2f(0.31, 0.3);
    glVertex2f(0.33, 0.3);
    glVertex2f(0.33, 0.08);
    glVertex2f(0.31, 0.08);

    glEnd();
}

void D(float LetterColor[])
{
    glColor3fv(LetterColor);
    glBegin(GL_QUADS);

    glVertex2f(0.39, 0.3);
    glVertex2f(0.41, 0.3);
    glVertex2f(0.41, 0.08);
    glVertex2f(0.39, 0.08);

    glVertex2f(0.39, 0.28);
    glVertex2f(0.39, 0.30);
    glVertex2f(0.47, 0.30);
    glVertex2f(0.47, 0.28);

    glVertex2f(0.39, 0.08);
    glVertex2f(0.39, 0.1);
    glVertex2f(0.47, 0.1);
    glVertex2f(0.47, 0.08);

    glVertex2f(0.47, 0.28);
    glVertex2f(0.49, 0.28);
    glVertex2f(0.49, 0.1);
    glVertex2f(0.47, 0.1);

    glVertex2f(0.26, 0.19);
    glVertex2f(0.26, 0.21);
    glVertex2f(0.31, 0.21);
    glVertex2f(0.31, 0.19);

    glVertex2f(0.31, 0.3);
    glVertex2f(0.33, 0.3);
    glVertex2f(0.33, 0.08);
    glVertex2f(0.31, 0.08);

    glEnd();
}

void AA(float LetterColor[])
{
    glColor3fv(LetterColor);
    glBegin(GL_QUADS);

    glVertex2f(0.55, 0.3);
    glVertex2f(0.57, 0.3);
    glVertex2f(0.57, 0.08);
    glVertex2f(0.55, 0.08);

    glVertex2f(0.57, 0.28);
    glVertex2f(0.57, 0.30);
    glVertex2f(0.62, 0.30);
    glVertex2f(0.62, 0.28);

    glVertex2f(0.62, 0.3);
    glVertex2f(0.64, 0.3);
    glVertex2f(0.64, 0.08);
    glVertex2f(0.62, 0.08);

    glVertex2f(0.57, 0.19);
    glVertex2f(0.57, 0.21);
    glVertex2f(0.62, 0.21);
    glVertex2f(0.62, 0.19);

    glEnd();
}

void YY(float LetterColor[])
{
    glColor3fv(LetterColor);
    glBegin(GL_QUADS);

    glVertex2f(0.70, 0.3);
    glVertex2f(0.72, 0.3);
    glVertex2f(0.72, 0.19);
    glVertex2f(0.70, 0.19);

    glVertex2f(0.77, 0.3);
    glVertex2f(0.79, 0.3);
    glVertex2f(0.79, 0.19);
    glVertex2f(0.77, 0.19);

    glVertex2f(0.70, 0.19);
    glVertex2f(0.79, 0.19);
    glVertex2f(0.79, 0.21);
    glVertex2f(0.70, 0.21);

    glVertex2f(0.74, 0.19);
    glVertex2f(0.76, 0.19);
    glVertex2f(0.76, 0.08);
    glVertex2f(0.74, 0.08);

    glEnd();
}

void RR(float LetterColor[])
{
    glColor3fv(LetterColor);
    glBegin(GL_QUADS);

    glVertex2f(-0.65, -0.1);
    glVertex2f(-0.63, -0.1);
    glVertex2f(-0.63, -0.3);
    glVertex2f(-0.65, -0.3);

    glVertex2f(-0.58, -0.1);
    glVertex2f(-0.58, -0.12);
    glVertex2f(-0.63, -0.12);
    glVertex2f(-0.63, -0.1);

    glVertex2f(-0.63, -0.2);
    glVertex2f(-0.63, -0.22);
    glVertex2f(-0.58, -0.22);
    glVertex2f(-0.58, -0.20);

    glVertex2f(-0.58, -0.1);
    glVertex2f(-0.56, -0.1);
    glVertex2f(-0.56, -0.22);
    glVertex2f(-0.58, -0.22);

    glVertex2f(-0.60, -0.22);
    glVertex2f(-0.58, -0.22);
    glVertex2f(-0.58, -0.3);
    glVertex2f(-0.60, -0.3);

    glEnd();
}

void AAA(float LetterColor[])
{
    glColor3fv(LetterColor);
    glBegin(GL_QUADS);

    glVertex2f(-0.50, -0.1);
    glVertex2f(-0.48, -0.1);
    glVertex2f(-0.48, -0.3);
    glVertex2f(-0.50, -0.3);

    glVertex2f(-0.43, -0.19);
    glVertex2f(-0.43, -0.21);
    glVertex2f(-0.48, -0.21);
    glVertex2f(-0.48, -0.19);

    glVertex2f(-0.43, -0.1);
    glVertex2f(-0.41, -0.1);
    glVertex2f(-0.41, -0.3);
    glVertex2f(-0.43, -0.3);

    glVertex2f(-0.41, -0.1);
    glVertex2f(-0.41, -0.12);
    glVertex2f(-0.50, -0.12);
    glVertex2f(-0.50, -0.1);

    glEnd();
}

void M(float LetterColor[])
{
    glColor3fv(LetterColor);
    glBegin(GL_QUADS);

    glVertex2f(-0.36, -0.1);
    glVertex2f(-0.34, -0.1);
    glVertex2f(-0.34, -0.3);
    glVertex2f(-0.36, -0.3);

    glVertex2f(-0.36, -0.1);
    glVertex2f(-0.36, -0.12);
    glVertex2f(-0.31, -0.12);
    glVertex2f(-0.31, -0.1);

    glVertex2f(-0.31, -0.12);
    glVertex2f(-0.29, -0.12);
    glVertex2f(-0.29, -0.25);
    glVertex2f(-0.31, -0.25);

    glVertex2f(-0.29, -0.1);
    glVertex2f(-0.29, -0.12);
    glVertex2f(-0.24, -0.12);
    glVertex2f(-0.24, -0.1);

    glVertex2f(-0.26, -0.1);
    glVertex2f(-0.24, -0.1);
    glVertex2f(-0.24, -0.3);
    glVertex2f(-0.26, -0.3);

    glEnd();
}

void AAAA(float LetterColor[])
{
    glColor3fv(LetterColor);
    glBegin(GL_QUADS);

    glVertex2f(-0.18, -0.1);
    glVertex2f(-0.16, -0.1);
    glVertex2f(-0.16, -0.3);
    glVertex2f(-0.18, -0.3);

    glVertex2f(-0.11, -0.19);
    glVertex2f(-0.11, -0.21);
    glVertex2f(-0.16, -0.21);
    glVertex2f(-0.16, -0.19);

    glVertex2f(-0.11, -0.1);
    glVertex2f(-0.09, -0.1);
    glVertex2f(-0.09, -0.3);
    glVertex2f(-0.11, -0.3);

    glVertex2f(-0.09, -0.1);
    glVertex2f(-0.09, -0.12);
    glVertex2f(-0.18, -0.12);
    glVertex2f(-0.18, -0.1);

    glEnd();
}

void MM(float LetterColor[])
{
    glColor3fv(LetterColor);
    glBegin(GL_QUADS);

    glVertex2f(0.24, -0.1);
    glVertex2f(0.26, -0.1);
    glVertex2f(0.26, -0.3);
    glVertex2f(0.24, -0.3);

    glVertex2f(0.24, -0.1);
    glVertex2f(0.24, -0.12);
    glVertex2f(0.29, -0.12);
    glVertex2f(0.29, -0.1);

    glVertex2f(0.29, -0.12);
    glVertex2f(0.31, -0.12);
    glVertex2f(0.31, -0.25);
    glVertex2f(0.29, -0.25);

    glVertex2f(0.31, -0.1);
    glVertex2f(0.31, -0.12);
    glVertex2f(0.36, -0.12);
    glVertex2f(0.36, -0.1);

    glVertex2f(0.36, -0.1);
    glVertex2f(0.34, -0.1);
    glVertex2f(0.34, -0.3);
    glVertex2f(0.36, -0.3);

    glEnd();
}

void AAAAA(float LetterColor[])
{
    glColor3fv(LetterColor);
    glBegin(GL_QUADS);

    glVertex2f(0.39, -0.1);
    glVertex2f(0.41, -0.1);
    glVertex2f(0.41, -0.3);
    glVertex2f(0.39, -0.3);

    glVertex2f(0.41, -0.1);
    glVertex2f(0.41, -0.12);
    glVertex2f(0.46, -0.12);
    glVertex2f(0.46, -0.1);

    glVertex2f(0.41, -0.19);
    glVertex2f(0.41, -0.21);
    glVertex2f(0.46, -0.21);
    glVertex2f(0.46, -0.19);

    glVertex2f(0.46, -0.1);
    glVertex2f(0.48, -0.1);
    glVertex2f(0.48, -0.3);
    glVertex2f(0.46, -0.3);

    glEnd();
}

void Apostope(float LetterColor[])
{
    glColor3fv(LetterColor);
    glBegin(GL_QUADS);

    glVertex2f(0.49, -0.1);
    glVertex2f(0.50, -0.1);
    glVertex2f(0.50, -0.15);
    glVertex2f(0.49, -0.15);

    glEnd();
}
void AAAAAA(float LetterColor[])
{
    glColor3fv(LetterColor);
    glBegin(GL_QUADS);

    glVertex2f(0.52, -0.1);
    glVertex2f(0.54, -0.1);
    glVertex2f(0.54, -0.3);
    glVertex2f(0.52, -0.3);

    glVertex2f(0.54, -0.1);
    glVertex2f(0.54, -0.12);
    glVertex2f(0.59, -0.12);
    glVertex2f(0.59, -0.1);

    glVertex2f(0.54, -0.19);
    glVertex2f(0.54, -0.21);
    glVertex2f(0.59, -0.21);
    glVertex2f(0.59, -0.19);

    glVertex2f(0.59, -0.1);
    glVertex2f(0.61, -0.1);
    glVertex2f(0.61, -0.3);
    glVertex2f(0.59, -0.3);

    glEnd();
}

void MMM(float LetterColor[])
{
    glColor3fv(LetterColor);
    glBegin(GL_QUADS);

    glVertex2f(0.64, -0.1);
    glVertex2f(0.66, -0.1);
    glVertex2f(0.66, -0.3);
    glVertex2f(0.64, -0.3);

    glVertex2f(0.64, -0.1);
    glVertex2f(0.64, -0.12);
    glVertex2f(0.69, -0.12);
    glVertex2f(0.69, -0.1);

    glVertex2f(0.69, -0.12);
    glVertex2f(0.71, -0.12);
    glVertex2f(0.71, -0.25);
    glVertex2f(0.69, -0.25);

    glVertex2f(0.71, -0.1);
    glVertex2f(0.71, -0.12);
    glVertex2f(0.76, -0.12);
    glVertex2f(0.76, -0.1);

    glVertex2f(0.76, -0.1);
    glVertex2f(0.74, -0.1);
    glVertex2f(0.74, -0.3);
    glVertex2f(0.76, -0.3);

    glEnd();
}
