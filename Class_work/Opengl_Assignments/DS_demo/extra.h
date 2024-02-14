#pragma once
#include<GL\gl.h>

void VerticalLines()
{
	float xPt1 = 0.025f;
	float xPt2 = -0.025f;

	glLineWidth(3.2);
	glBegin(GL_LINES);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, -1.0, 0.0);
	glEnd();

	glColor3f(0.0, 0.0, 1.0);
	for (int i = 1; i <= 40; i++)
	{
		if (i % 5 == 0)
		{
			glLineWidth(2.2f);
		}
		else
		{
			glLineWidth(1.0f);
		}

		glBegin(GL_LINES);

		glVertex2f(xPt1, 1.0);
		glVertex2f(xPt1, -1.0);

		xPt1 += 0.025;
		glEnd();
	}

	glColor3f(0.0, 0.0, 1.0);
	for (int j = 1; j <= 40; j++)
	{
		if (j % 5 == 0)
		{
			glLineWidth(2.2);
		}
		else
		{
			glLineWidth(1.0);
		}

		glBegin(GL_LINES);
		glVertex2f(xPt2, 1.0);
		glVertex2f(xPt2, -1.0);

		xPt2 -= 0.025f;
		glEnd();
	}
}

void HorizontalLines()
{
	float yPt1 = 0.025f;
	float yPt2 = -0.025f;

	glLineWidth(3.2);
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(-1.0, 0.0, 0.0);
	glVertex3f(1.0, 0.0, 0.0);
	glColor3f(0.0, 0.0, 1.0);
	glEnd();

	glColor3f(0.0, 0.0, 1.0);
	for (int i = 1; i <= 40; i++)
	{
		if (i % 5 == 0)
			glLineWidth(2.2);
		else
			glLineWidth(1.0);

		glBegin(GL_LINES);
		glVertex2f(-1.0f, yPt1);
		glVertex2f(1.0f, yPt1);

		yPt1 += 0.025;
		glEnd();
	}


	glColor3f(0.0, 0.0, 1.0);
	for (int j = 1; j <= 40; j++)
	{
		if (j % 5 == 0)
			glLineWidth(2.2);
		else
			glLineWidth(1.0);
		glBegin(GL_LINES);
		glVertex2f(-1.0f, yPt2);
		glVertex2f(1.0f, yPt2);

		yPt2 -= 0.025f;
		glEnd();
	}
}
