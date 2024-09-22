#include <gl/GL.h>
#include <gl/GLU.h>

void Ground();
void Tree();
void Sky();
void Road();
void Lamp();
void Right_Houses();
void Left_Houses();
void Draw_Computer(GLfloat t);
void Code(GLfloat t);

void Tree()
{
    // tree
    glColor3f(0.6f, 0.3f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.70f, -1.0f);
    glVertex2f(-0.70f, -0.75f);
    glVertex2f(-0.80f, -0.75f);
    glVertex2f(-0.80f, -1.0f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.1f, 1.0f, 0.2f);
    glVertex2f(-0.75f, -0.35f);
    glColor3f(0.1f, 0.5f, 0.2f);
    glVertex2f(-0.55f, -0.75f);
    glVertex2f(-0.95f, -0.75f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.1f, 1.0f, 0.2f);
    glVertex2f(-0.75f, -0.30f);
    glColor3f(0.1f, 0.5f, 0.2f);
    glVertex2f(-0.57f, -0.65f);
    glVertex2f(-0.93f, -0.65f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.1f, 1.0f, 0.2f);
    glVertex2f(-0.75f, -0.30f);
    glColor3f(0.1f, 0.5f, 0.2f);
    glVertex2f(-0.59f, -0.55f);
    glVertex2f(-0.91f, -0.55f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.1f, 1.0f, 0.2f);
    glVertex2f(-0.75f, -0.30f);
    glColor3f(0.1f, 0.5f, 0.2f);
    glVertex2f(-0.61f, -0.45f);
    glVertex2f(-0.89f, -0.45f);
    glEnd();
}

void Road()
{
    // Road
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.02f, 0.0f);
    glVertex2f(0.02f, 0.0f);
    glVertex2f(0.55f, -1.0f);
    glVertex2f(-0.55f, -1.0f);
    glEnd();

    // White Strip
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.001f, 0.0f);
    glVertex2f(0.001f, 0.0f);
    glVertex2f(0.02f, -1.0f);
    glVertex2f(-0.02f, -1.0f);
    glEnd();

    // Grey Strip
    glColor3f(0.259f, 0.259f, 0.243f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.01f, 0.0f);
    glVertex2f(-0.02f, 0.0f);
    glVertex2f(-0.65f, -1.0f);
    glVertex2f(-0.55f, -1.0f);
    glEnd();

    glColor3f(0.259f, 0.259f, 0.243f);
    glBegin(GL_POLYGON);
    glVertex2f(0.01f, 0.0f);
    glVertex2f(0.02f, 0.0f);
    glVertex2f(0.65f, -1.0f);
    glVertex2f(0.55f, -1.0f);
    glEnd();
}

void Sky()
{
    // Background sky
    glBegin(GL_POLYGON);
    glColor3f(0.639, 0.549, 0.99);
    glVertex2f(-1.0f, 0.0f);
    glVertex2f(1.0f, 0.0f);
    glColor3f(0.78, 0.431, 0.91);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(-1.0f, 1.0f);
    glEnd();
}

void Ground()
{
    // Green Ground
    glColor3f(0.0f, 0.39f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-1.0f, 0.0f);
    glVertex2f(1.0f, 0.0f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(-1.0f, -1.0f);
    glEnd();
}

void Lamp()
{
    // lamp
    // right 1st
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(0.05f, 0.0f);
    glVertex2f(0.06f, 0.0f);
    glVertex2f(0.06f, 0.08f);
    glVertex2f(0.05f, 0.08f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(0.07f, 0.08f);
    glVertex2f(0.07f, 0.09f);
    glVertex2f(0.04f, 0.09f);
    glVertex2f(0.04f, 0.08f);
    glEnd();

    // right 2
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(0.35f, 0.0f);
    glVertex2f(0.36f, 0.0f);
    glVertex2f(0.36f, 0.08f);
    glVertex2f(0.35f, 0.08f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(0.34f, 0.08f);
    glVertex2f(0.34f, 0.09f);
    glVertex2f(0.37f, 0.09f);
    glVertex2f(0.37f, 0.08f);
    glEnd();

    // right 3
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(0.45f, 0.0f);
    glVertex2f(0.46f, 0.0f);
    glVertex2f(0.46f, 0.08f);
    glVertex2f(0.45f, 0.08f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(0.44f, 0.08f);
    glVertex2f(0.44f, 0.09f);
    glVertex2f(0.47f, 0.09f);
    glVertex2f(0.47f, 0.08f);
    glEnd();

    // left 3rd
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.06f, 0.0f);
    glVertex2f(-0.07f, 0.0f);
    glVertex2f(-0.07f, 0.08f);
    glVertex2f(-0.06f, 0.08f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.08f, 0.08f);
    glVertex2f(-0.08f, 0.09f);
    glVertex2f(-0.05f, 0.09f);
    glVertex2f(-0.05f, 0.08f);
    glEnd();

    // left 2nd
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.35f, 0.0f);
    glVertex2f(-0.36f, 0.0f);
    glVertex2f(-0.36f, 0.08f);
    glVertex2f(-0.35f, 0.08f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.37f, 0.09f);
    glVertex2f(-0.37f, 0.08f);
    glVertex2f(-0.34f, 0.08f);
    glVertex2f(-0.34f, 0.09f);
    glEnd();

    // left 1st
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.65f, 0.0f);
    glVertex2f(-0.66f, 0.0f);
    glVertex2f(-0.66f, 0.08f);
    glVertex2f(-0.65f, 0.08f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.64f, 0.09f);
    glVertex2f(-0.64f, 0.08f);
    glVertex2f(-0.67f, 0.08f);
    glVertex2f(-0.67f, 0.09f);
    glEnd();
}

void Right_Houses()
{
    // buldings right 1st
    glColor3f(0.6f, 0.6f, 0.5f);
    glBegin(GL_POLYGON);
    glVertex2f(0.1f, 0.0f);
    glVertex2f(0.3f, 0.0f);
    glVertex2f(0.3f, 0.3f);
    glVertex2f(0.1f, 0.3f);
    glEnd();

    glColor3f(0.878f, 0.871f, 0.282f);
    glBegin(GL_POLYGON);
    glVertex2f(0.2f, 0.2f);
    glVertex2f(0.2f, 0.1f);
    glVertex2f(0.3f, 0.1f);
    glVertex2f(0.3f, 0.2f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(0.2f, 0.2f);
    glVertex2f(0.2f, 0.1f);
    glVertex2f(0.3f, 0.1f);
    glVertex2f(0.3f, 0.2f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex2f(0.20f, 0.15f);
    glVertex2f(0.30f, 0.15f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex2f(0.25f, 0.2f);
    glVertex2f(0.25f, 0.1f);
    glEnd();

    glColor3f(0.514f, 0.502f, 0.502f);
    glBegin(GL_POLYGON);
    glVertex2f(0.09f, 0.0f);
    glVertex2f(0.25f, 0.0f);
    glVertex2f(0.15f, 0.2f);
    glVertex2f(0.09f, 0.2f);
    glEnd();

    // buldings right 2nd
    glColor3f(0.231f, 0.231f, 0.22f);
    glBegin(GL_POLYGON);
    glVertex2f(0.6f, 0.0f);
    glVertex2f(0.6f, 0.2f);
    glVertex2f(0.9f, 0.2f);
    glVertex2f(0.9f, 0.0f);
    glEnd();
}

void Left_Houses()
{
    // buldings left 1st
    glColor3f(0.514f, 0.502f, 0.502f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.7f, 0.0f);
    glVertex2f(-0.7f, 0.3f);
    glVertex2f(-0.9f, 0.3f);
    glVertex2f(-0.9f, 0.0f);
    glEnd();
    glBegin(GL_TRIANGLES);
    glColor3f(0.5f, 0.3f, 0.2f);
    glVertex2f(-0.7f, 0.3f);
    glVertex2f(-0.8f, 0.5f);
    glVertex2f(-0.9f, 0.3f);
    glEnd();

    // buldings left 2nd
    glColor3f(0.4f, 0.4f, 0.6f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.4f, 0.0f);
    glVertex2f(-0.4f, 0.2f);
    glVertex2f(-0.6f, 0.2f);
    glVertex2f(-0.6f, 0.0f);
    glEnd();

    // buldings left 3rd
    glColor3f(0.231f, 0.231f, 0.22f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.1f, 0.0f);
    glVertex2f(-0.3f, 0.0f);
    glVertex2f(-0.3f, 0.4f);
    glVertex2f(-0.1f, 0.4f);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-0.08f, 0.3f);
    glVertex2f(-0.32f, 0.3f);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(-0.08f, 0.25f);
    glVertex2f(-0.32f, 0.25f);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-0.08f, 0.2f);
    glVertex2f(-0.32f, 0.2f);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(-0.08f, 0.15f);
    glVertex2f(-0.32f, 0.15f);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(-0.08f, 0.1f);
    glVertex2f(-0.32f, 0.1f);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(-0.08f, 0.05f);
    glVertex2f(-0.32f, 0.05f);
    glEnd();
}

void Draw_Computer(GLfloat t)
{
    // monitor outer rectangle
    glBegin(GL_POLYGON);
    glColor3f(0.5f * t, 0.5f * t, 0.5f * t);
    glVertex3f(-0.25f, 0.25f, 0.0f);
    glVertex3f(-0.25f, -0.25f, 0.0f);
    glVertex3f(0.25f, -0.25f, 0.0f);
    glVertex3f(0.25f, 0.25f, 0.0f);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0.0f * t, 0.0f * t, 0.0f * t);
    glVertex3f(-0.25f, 0.25f, 0.0f);
    glVertex3f(-0.25f, -0.25f, 0.0f);
    glVertex3f(0.25f, -0.25f, 0.0f);
    glVertex3f(0.25f, 0.25f, 0.0f);
    glEnd();

    // monitor inner rectangle
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.0f, 0.5f * t);
    glVertex3f(-0.23f, 0.22f, 0.0f);
    glVertex3f(-0.23f, -0.22f, 0.0f);
    glVertex3f(0.23f, -0.22f, 0.0f);
    glVertex3f(0.23f, 0.22f, 0.0f);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(-0.23f, 0.22f, 0.0f);
    glVertex3f(-0.23f, -0.22f, 0.0f);
    glVertex3f(0.23f, -0.22f, 0.0f);
    glVertex3f(0.23f, 0.22f, 0.0f);
    glEnd();

    // monitor vertical support
    glBegin(GL_POLYGON);
    glColor3f(0.5f * t, 0.5f * t, 0.5f * t);
    glVertex3f(-0.025f, -0.25f, 0.0f);
    glVertex3f(-0.025f, -0.30f, 0.0f);
    glVertex3f(0.025f, -0.30f, 0.0f);
    glVertex3f(0.025f, -0.25f, 0.0f);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(-0.025f, -0.25f, 0.0f);
    glVertex3f(-0.025f, -0.30f, 0.0f);
    glVertex3f(0.025f, -0.30f, 0.0f);
    glVertex3f(0.025f, -0.25f, 0.0f);
    glEnd();

    // monitor horizontal support
    glBegin(GL_POLYGON);
    glColor3f(0.5f * t, 0.5f * t, 0.5f * t);
    glVertex3f(-0.1f, -0.270f, 0.0f);
    glVertex3f(-0.15f, -0.30f, 0.0f);
    glVertex3f(0.15f, -0.30f, 0.0f);
    glVertex3f(0.1f, -0.270f, 0.0f);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(-0.1f, -0.270f, 0.0f);
    glVertex3f(-0.15f, -0.30f, 0.0f);
    glVertex3f(0.15f, -0.30f, 0.0f);
    glVertex3f(0.1f, -0.270f, 0.0f);
    glEnd();

    // keyboard
    glBegin(GL_POLYGON);
    glColor3f(0.5f * t, 0.5f * t, 0.5f * t);
    glVertex3f(-0.25f, -0.35f, 0.0f);
    glVertex3f(-0.30f, -0.50f, 0.0f);
    glVertex3f(0.30f, -0.50f, 0.0f);
    glVertex3f(0.25f, -0.35f, 0.0f);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(-0.25f, -0.35f, 0.0f);
    glVertex3f(-0.30f, -0.50f, 0.0f);
    glVertex3f(0.30f, -0.50f, 0.0f);
    glVertex3f(0.25f, -0.35f, 0.0f);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(-0.23f, -0.37f, 0.0f);
    glVertex3f(-0.28f, -0.48f, 0.0f);
    glVertex3f(0.20f, -0.48f, 0.0f);
    glVertex3f(0.15f, -0.37f, 0.0f);
    glEnd();

    glBegin(GL_LINE_LOOP);

    glVertex3f(0.28f, -0.48f, 0.0f);
    glVertex3f(0.23f, -0.37f, 0.0f);
    glVertex3f(0.15f, -0.37f, 0.0f);
    glVertex3f(0.20f, -0.48f, 0.0f);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(-0.23f, -0.39f, 0.0f);
    glVertex3f(0.15f, -0.39f, 0.0f);

    glVertex3f(-0.23f, -0.41f, 0.0f);
    glVertex3f(0.15f, -0.41f, 0.0f);

    glVertex3f(-0.24f, -0.43f, 0.0f);
    glVertex3f(0.16f, -0.43f, 0.0f);

    glVertex3f(-0.24f, -0.45f, 0.0f);
    glVertex3f(0.16f, -0.45f, 0.0f);

    glVertex3f(0.23f, -0.39f, 0.0f);
    glVertex3f(0.14f, -0.39f, 0.0f);

    glVertex3f(0.24f, -0.41f, 0.0f);
    glVertex3f(0.14f, -0.41f, 0.0f);

    glVertex3f(0.24f, -0.43f, 0.0f);
    glVertex3f(0.15f, -0.43f, 0.0f);
    // glVertex3f(-0.28f, -0.48f, 0.0f);
    // glVertex3f(0.20f, -0.48f, 0.0f);

    glEnd();

    // keyboard height
    glBegin(GL_POLYGON);
    glColor3f(0.6f * t, 0.6f * t, 0.6f * t);
    glVertex3f(-0.30f, -0.50f, 0.0f);
    glVertex3f(-0.30f, -0.53f, 0.0f);
    glVertex3f(0.30f, -0.53f, 0.0f);
    glVertex3f(0.30f, -0.50f, 0.0f);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(-0.30f, -0.50f, 0.0f);
    glVertex3f(-0.30f, -0.53f, 0.0f);
    glVertex3f(0.30f, -0.53f, 0.0f);
    glVertex3f(0.30f, -0.50f, 0.0f);
    glEnd();

    /*
    // CPU
    glBegin(GL_POLYGON);
    glColor3f(0.5f * t, 0.5f * t, 0.5f * t);
    glVertex3f(0.35f, 0.25f, 0.0f);
    glVertex3f(0.35f, -0.25f, 0.0f);
    glVertex3f(0.5f, -0.25f, 0.0f);
    glVertex3f(0.5f, 0.25f, 0.0f);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.35f, 0.25f, 0.0f);
    glVertex3f(0.35f, -0.25f, 0.0f);
    glVertex3f(0.5f, -0.25f, 0.0f);
    glVertex3f(0.5f, 0.25f, 0.0f);
    glEnd();

    // CPU depth
    glBegin(GL_POLYGON);
    glColor3f(0.6f * t, 0.6f * t, 0.6f * t);
    glVertex3f(0.30f, 0.20f, 0.0f);
    glVertex3f(0.30f, -0.20f, 0.0f);
    glVertex3f(0.35f, -0.25f, 0.0f);
    glVertex3f(0.35f, 0.25f, 0.0f);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.30f, 0.20f, 0.0f);
    glVertex3f(0.30f, -0.20f, 0.0f);
    glVertex3f(0.35f, -0.25f, 0.0f);
    glVertex3f(0.35f, 0.25f, 0.0f);
    glEnd();

    // CPU CD drive opening
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.36f, 0.10f, 0.0f);
    glVertex3f(0.36f, 0.13f, 0.0f);
    glVertex3f(0.49f, 0.13f, 0.0f);
    glVertex3f(0.49f, 0.10f, 0.0f);
    glEnd();
    */

    // mouse
    /*
    glBegin(GL_POLYGON);
    glColor3f(0.5f * t, 0.5f * t, 0.5f * t);
    glVertex3f(0.40f, -0.35f, 0.0f);
    glVertex3f(0.40f, -0.45f, 0.0f);
    glVertex3f(0.45f, -0.45f, 0.0f);
    glVertex3f(0.45f, -0.35f, 0.0f);
    glEnd();
*/

    glBegin(GL_POLYGON);
    glColor3f(0.5f * t, 0.5f * t, 0.5f * t);
    glVertex3f(0.30f, -0.38f, 0.0f);
    glVertex3f(0.33f, -0.45f, 0.0f);
    glVertex3f(0.38f, -0.45f, 0.0f);
    glVertex3f(0.35f, -0.38f, 0.0f);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.30f, -0.38f, 0.0f);
    glVertex3f(0.33f, -0.45f, 0.0f);
    glVertex3f(0.38f, -0.45f, 0.0f);
    glVertex3f(0.35f, -0.38f, 0.0f);
    glEnd();

    /*  // mouse wire
     glBegin(GL_LINE_STRIP);
     glColor3f(0.0f, 0.0f, 0.0f);
     glVertex3f(0.025f, -0.25f, 0.0f);
     glVertex3f(0.37f, -0.30f, 0.0f);
     glVertex3f(0.42f, -0.35f, 0.0f);
     glEnd();

     // monitor to cpu wire
     glBegin(GL_LINE_STRIP);
     glColor3f(0.0f, 0.0f, 0.0f);
     glVertex3f(0.25f, -0.15f, 0.0f);
     glVertex3f(0.30f, -0.10f, 0.0f);
     glEnd();

     // keyboard to cpu wire
     glBegin(GL_LINE_STRIP);
     glColor3f(0.0f, 0.0f, 0.0f);
     glVertex3f(0.0f, -0.35f, 0.0f);
     glVertex3f(0.27f, -0.25f, 0.0f);
     glVertex3f(0.30f, -0.15f, 0.0f);
     glEnd();
     */
}

void Code(GLfloat t)
{
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-1.0f, 1.0f);
    glVertex2f(-0.6f, 1.0f);
    glVertex2f(-0.6f, -1.0f);
    glVertex2f(-1.0f, -1.0f);
    glEnd();

    glColor3f(1.0f * t, 0.0f, 0.0f);
    glLineWidth(1);
    glBegin(GL_LINE_STRIP);
    glVertex2f(-1.0f, 0.9f);
    glVertex2f(-0.6f, 0.9f);
    glVertex2f(-0.6f, -0.9f);
    glVertex2f(-1.0f, -0.9f);
    glEnd();

    glColor3f(0.322f * t, 0.318f * t, 0.318f * t);
    glBegin(GL_POLYGON);
    glVertex2f(-0.6f, 1.0f);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(-0.6f, -1.0f);
    glEnd();

    glColor3f(1.0f * t, 1.0f * t, 1.0f * t);
    glBegin(GL_POLYGON);
    glVertex2f(-1.0f, 1.0f);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(1.0f, 0.88f);
    glVertex2f(-1.0f, 0.88f);
    glEnd();

    glLineWidth(4);
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex2f(-0.5f, 0.95f);
    glVertex2f(0.5f, 0.95f);

    glLineWidth(4);
    glColor3f(1.0f * t, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex2f(0.8f, 0.95f);
    glVertex2f(0.9f, 0.95f);

    glLineWidth(2);
    glColor3f(0.42f * t, 0.267f * t, 0.62f * t);
    glBegin(GL_LINES);
    glVertex2f(-0.5f, 0.6f);
    glVertex2f(0.5f, 0.6f);
    glVertex2f(-0.5f, 0.3f);
    glVertex2f(0.5f, 0.3f);
    glVertex2f(-0.9f, -0.1f);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(-0.4f, 0.8f);
    glVertex2f(0.4f, 0.8f);
    glVertex2f(-0.4f, 0.5f);
    glVertex2f(0.4f, 0.5f);
    glVertex2f(-0.4f, 0.3f);
    glVertex2f(0.4f, 0.3f);
    glVertex2f(-0.4f, 0.4f);
    glVertex2f(0.4f, 0.4f);
    glVertex2f(-0.4f, 0.2f);
    glVertex2f(0.4f, 0.2f);
    glVertex2f(-0.4f, 0.1f);
    glVertex2f(0.4f, 0.1f);
    glVertex2f(-0.4f, 0.0f);
    glVertex2f(0.4f, 0.0f);
    glVertex2f(-0.4f, -0.1f);
    glVertex2f(0.4f, -0.1f);
    glVertex2f(-0.4f, -0.2f);
    glVertex2f(0.4f, -0.2f);
    glVertex2f(-0.4f, -0.3f);
    glVertex2f(0.4f, -0.3f);
    glEnd();

    glColor3f(1.0f * t, 1.0f * t, 1.0f * t);
    glBegin(GL_LINES);
    glLineWidth(4);
    glVertex2f(-0.9f, 0.9f);
    glVertex2f(-0.7f, 0.9f);
    glVertex2f(-0.9f, 0.7f);
    glVertex2f(-0.7f, 0.7f);
    glVertex2f(-0.9f, 0.5f);
    glVertex2f(-0.7f, 0.5f);
    glVertex2f(-0.9f, 0.3f);
    glVertex2f(-0.7f, 0.3f);
    glVertex2f(-0.9f, 0.1f);
    glVertex2f(-0.7f, 0.1f);
    glEnd();

    glLineWidth(1);
}
