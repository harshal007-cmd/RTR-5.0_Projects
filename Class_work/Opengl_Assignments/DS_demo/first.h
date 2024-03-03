#pragma once
#include<GL\gl.h>
#include<GL/GLU.h>

//textre vars
GLuint texture_clouds = 0;

//update variables
GLfloat oUpperY = 0.0;
GLfloat oLowerY = 0.0;
GLfloat ot1 = 0.0;
GLfloat ot2 = 0.0;
GLfloat ot3 = 0.0;
GLfloat ot4 = 0.0;
GLfloat ot5 = 0.0;

void clouds_tex()
{
	glBindTexture(GL_TEXTURE_2D, texture_clouds);

	/*
	glBegin(GL_POLYGON);
	glVertex2f(1.0, 1.0);
	glVertex2f(-1.0, 1.0);
	glVertex2f(-1.0, -1.0);
	glVertex2f(1.0, -1.0);
	glEnd();
	*/
	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 1.0);//TRight
	glVertex2f(1.0, 1.0);

	glTexCoord2f(0.0, 1.0);
	glVertex2f(-1.0, 1.0);

	glTexCoord2f(0.0, 0.0);
	glVertex2f(-1.0, -1.0);

	glTexCoord2f(1.0, 0.0);
	glVertex2f(1.0, -1.0);

	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);

}

void opening()
{
	//opening, upper and lower
	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(0.0, oUpperY, 0.0);
	glBegin(GL_QUADS);
	glVertex2f(2.0, 2.0);
	glVertex2f(-2.0, 2.0);
	glVertex2f(-2.0, 0.0);
	glVertex2f(2.0, 0.0);
	glEnd();

	glPopMatrix();

	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(0.0, (-1) * oUpperY, 0.0);
	glBegin(GL_QUADS);
	glVertex2f(2.0, 0.0);
	glVertex2f(-2.0, 0.0);
	glVertex2f(-2.0, -2.0);
	glVertex2f(2.0, -2.0);
	glEnd();

}

void room()
{
	//floor
	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_QUADS);
	glVertex2f(2.0, -0.5);
	glVertex2f(-2.0, -0.5);
	glVertex2f(-2.0, -1.875);
	glVertex2f(2.0, -1.875);
	glEnd();

	//right wall
	glColor3f(0.3, 0.3, 0.3);
	glBegin(GL_QUADS);
	glVertex2f(2.0, 2.0);//upper right
	glVertex2f(0.625, 2.0);
	glVertex2f(0.625, -0.5);
	glVertex2f(2.0, -0.5);
	glEnd();

	//left wall
	glColor3f(0.3, 0.3, 0.3);
	glBegin(GL_QUADS);
	glVertex2f(-0.625, 2.0);//upper right
	glVertex2f(-2.0, 2.0);
	glVertex2f(-2.0, -0.5);
	glVertex2f(-0.625, -0.5);
	glEnd();


	//Gallary glass
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glColor4f(0.5, 0.5, 0.5, 0.4);
	glBegin(GL_QUADS);
	glVertex2f(0.625, -0.125);//upper right
	glVertex2f(-0.625, -0.125);
	glVertex2f(-0.625, -0.5);
	glVertex2f(0.625, -0.5);
	glEnd();
	glEnable(GL_BLEND);

	//glass border
	glEnable(GL_LINE_SMOOTH);
	glLineWidth(3.0);
	glColor3f(0.2, 0.2, 0.2);
	glBegin(GL_LINES);
	glVertex2f(0.625, -0.125);
	glVertex2f(-0.625, -0.125);
	glEnd();
	glDisable(GL_LINE_SMOOTH);


}

void manStanding()
{
	float cx = 0.0;
	float cy = 0.02;
	float r = 0.06;
	int num_segments = 100;

	//head
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(cx, cy);
	float angle;

	for (int i = 0; i <= num_segments; ++i)
	{
		angle = 2.0 * M_PI * (float)i / (float)num_segments;
		float x = r * cos(angle);
		float y = r * sin(angle);
		glVertex2f(cx + x, cy + y);
	}
	glEnd();

	//neck
	glLineWidth(20.0);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2f(cx, cy);
	glVertex2f(cx, cy + (-0.2));
	glEnd();

	//upper body
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(0.07, -0.07);
	glVertex2f(-0.07, -0.07);
	glVertex2f(-0.077, -0.077);
	glVertex2f(-0.077, -0.27);
	glVertex2f(0.077, -0.27);
	glVertex2f(0.077, -0.077);
	glEnd();

	//legs
		//left
	glBegin(GL_QUADS);
	glVertex2f(-0.0, -0.27);
	glVertex2f(-0.077, -0.27);
	glVertex2f(-0.080, -0.5);
	glVertex2f(-0.025, -0.5);
	glEnd();

	//right
	glBegin(GL_QUADS);
	glVertex2f(0.0, -0.27);
	glVertex2f(0.077, -0.27);
	glVertex2f(0.080, -0.5);
	glVertex2f(0.025, -0.5);
	glEnd();

	//Hands
		//right
	glEnable(GL_LINE_SMOOTH);
	glLineWidth(10.0);
	glBegin(GL_LINES);
	glVertex2f(0.07, -0.07);
	glVertex2f(0.11, -0.27);

	glVertex2f(-0.07, -0.07);
	glVertex2f(-0.11, -0.27);
	glDisable(GL_LINE_SMOOTH);
	glEnd();

	glEnable(GL_POINT_SMOOTH);
	glPointSize(15.0);
	glBegin(GL_POINTS);
	glVertex2f(0.11, -0.265);
	glVertex2f(-0.11, -0.265);
	glDisable(GL_POINT_SMOOTH);

	glEnd();


}

void watch_border()
{

	float cx = 1.0;
	float cy = 0.5;
	float r = 0.1;
	int num_segments = 100;
	// watch border

	glEnable(GL_LINE_SMOOTH);
	glLineWidth(4.0);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2f(cx, cy);
	for (int i = 0; i <= num_segments; ++i)
	{
		float theta = 2.0f * 3.1415926f * (float)i / (float)num_segments;
		float x = r * cosf(theta);
		float y = r * sinf(theta);
		glVertex2f(cx + x, cy + y);
	}
	glEnd();
	glDisable(GL_LINE_SMOOTH);
}

void watch_on_Wall()
{
	float cx = 1.0;
	float cy = 0.5;
	float r = 0.1;
	int num_segments = 100;

	// Watch background
	glColor3f(0.8f, 0.8f, 0.8f);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(cx, cy);
	float theta;
	for (int i = 0; i <= num_segments; ++i)
	{
		theta = 2.0f * 3.1415926f * (float)i / (float)num_segments;
		float x = r * cosf(theta);
		float y = r * sinf(theta);
		glVertex2f(cx + x, cy + y);
	}
	glEnd();


	// Moving clock hands --------------
	//  Moving clock hands --------------
	glColor3f(0.0, 0.0, 0.0);
	glPointSize(1.0);
	glLineWidth(1.5);
	glBegin(GL_LINES);

	glVertex2f(cx, cy);
	glVertex2f(cx + 0.06, cy + 0.02);

	glEnd();
	glColor3f(0.0, 0.0, 0.0);
	glPointSize(1.0);
	glLineWidth(1.5);
	glBegin(GL_LINES);

	glVertex2f(cx, cy);
	glVertex2f(cx + 0.05, cy + 0.05);

	glEnd();

}

void scene1()
{
	clouds_tex();
	room();
	watch_border();
	watch_on_Wall();
	manStanding();
	opening();
}