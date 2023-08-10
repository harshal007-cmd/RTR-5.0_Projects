void flag(void)
{

    float xCenter = 0.01f, yCenter = 0.5f;
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



}