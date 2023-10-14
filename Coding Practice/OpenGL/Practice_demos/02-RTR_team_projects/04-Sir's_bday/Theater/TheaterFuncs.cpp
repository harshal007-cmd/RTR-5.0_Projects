#include<Windows.h>
#include"Theater.h"
#include<stdio.h>
#include<GL/GL.h>



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

void Hall()
{
	//Ground
	glColor3f(0.1, 0.1, 0.1);
	glBegin(GL_POLYGON);
		glVertex2f(1.0, 0.0);
		glVertex2f(-1.0, 0.0);
		glVertex2f(-1.0, -0.7);
		glVertex2f(1.0, -0.7);
	glEnd();

	//Base
	glColor3f(0.3, 0.3, 0.3);
	glBegin(GL_POLYGON);
		glVertex2f(0.75, -0.450);
		glVertex2f(-0.75, -0.450);
		glVertex2f(-0.75, -0.53);
		glVertex2f(0.75, -0.53);
	glEnd();
	glColor3f(0.2, 0.2, 0.2);
	glLineWidth(2.0);
	glBegin(GL_LINES);
		glVertex2f(0.75, -0.490);
		glVertex2f(-0.75, -0.490);
	glEnd();

	
	//Celing
	glColor3f(0.2, 0.2, 0.2);
	glBegin(GL_POLYGON);
		glVertex2f(0.72, 0.5);
		glVertex2f(1.0, 0.65);
		glVertex2f(1.0, 1.0);
		glVertex2f(-1.0, 1.0);
		glVertex2f(-1.0, 0.65);
		glVertex2f(-0.72, 0.465);
	glEnd();
	glLineWidth(2.0);
	glColor3f(0.8, 0.4, 0.0);
	glBegin(GL_LINES);
		glVertex2f(0.125, 0.5);
		glVertex2f(0.5, 1.0);

		glVertex2f(0.5, 0.5);
		//glVertex2f(0.875, 1.0);
		glVertex2f(1.0, 1.0);

		glVertex2f(-0.125, 0.5);
		glVertex2f(-0.5, 1.0);

		glVertex2f(-0.5, 0.5);
		glVertex2f(-1.0, 1.0);

	glEnd();

	
	//Left wall
	glColor3f(0.4, 0.4, 0.4);
	glBegin(GL_POLYGON);
		glVertex2f(-0.72, 0.500);
		glVertex2f(-1.0, 0.650);
		glVertex2f(-1.0, -0.650);
		glVertex2f(-0.72, -0.465);
	glEnd();
	glColor3f(1.0, 0.0, 0.0);///lines
	glLineWidth(5.0);
	glBegin(GL_LINES);
		glVertex2f(-0.625, 0.375);
		glVertex2f(-1.0, 0.5);
		
		glVertex2f(-0.625, 0.25);
		glVertex2f(-1.0, 0.375);

		glVertex2f(-0.625, 0.0);
		glVertex2f(-1.0, -0.125);

		glVertex2f(-0.625, -0.125);
		glVertex2f(-1.0, -0.250);

	glEnd();


	//Right wall
	glColor3f(0.4, 0.4, 0.4);
	glBegin(GL_POLYGON);
		glVertex2f(0.72, 0.5);
		glVertex2f(1.0, 0.650);
		glVertex2f(1.0, -0.650);
		glVertex2f(0.72, -0.465);
	glEnd();
	glColor3f(1.0, 0.0, 0.0);///lines
	glLineWidth(5.0);
	glBegin(GL_LINES);
		glVertex2f(0.625, 0.375);
		glVertex2f(1.0, 0.5);
		
		glVertex2f(0.625, 0.25);
		glVertex2f(1.0, 0.375);

		glVertex2f(0.625, 0.0);
		glVertex2f(1.0, -0.125);

		glVertex2f(0.625, -0.125);
		glVertex2f(1.0, -0.250);

	glEnd();


	//Back wall
	glColor3f(0.1, 0.1, 0.1);
	glBegin(GL_POLYGON);
		glVertex2f(0.72, 0.5);
		glVertex2f(-0.72, 0.5);
		glVertex2f(-0.72, -0.465);
		glVertex2f(0.72, -0.465);
	glEnd();

	//White Screen
	glColor3f(0.7, 0.7, 0.7);
	glBegin(GL_POLYGON);
		glVertex2f(0.7, 0.475);
		glVertex2f(-0.7, 0.475);
		glVertex2f(-0.7, -0.435);
		glVertex2f(0.7, -0.435);
		glEnd();

}
void mainScreen()
{
	//back wall
	glColor3f(0.4, 0.4, 0.4);
	glBegin(GL_POLYGON);
		glVertex2f(0.9, 0.8);
		glVertex2f(-0.9, 0.8);
		glVertex2f(-0.9, -0.8);
		glVertex2f(0.9, -0.8);
	glEnd();


	//Celing
	glColor3f(0.7, 0.0, 0.0);
	glBegin(GL_QUADS);
		glVertex2f(1.0,1.0);
		glVertex2f(-1.0,1.0);
		glVertex2f(-0.82,0.45);
		glVertex2f(0.82,0.45);
	glEnd();
	
	//side wall left

	/*
	//mainscreen background
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -2.0);
	glScalef(0.62, 0.62, 0.62);
	*/
	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_POLYGON);
		glVertex2f(0.82, 0.45);
		glVertex2f(-0.82, 0.45);
		glVertex2f(-0.82, -0.45);
		glVertex2f(0.82, -0.45);
	glEnd();

	//mainscreen
	glColor3f(0.8, 0.8, 0.8);
	glBegin(GL_POLYGON);
		glVertex2f(0.72, 0.4);
		glVertex2f(-0.72, 0.4);
		glVertex2f(-0.72, -0.4);
		glVertex2f(0.72, -0.4);
	glEnd();
		
}


