#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

#include <gl/GL.h>

void stars(GLfloat t1);
void windowGrid(GLfloat t1);
void window(GLfloat t1);
void watch_border(float cx, float cy, float r, int num_segments, GLfloat t1);
void watch_on_Wall(float cx, float cy, float r, int num_segments, GLfloat t1);

static GLfloat t = 0.0f;
GLfloat ClockMinuteHandAngle = -4 * M_PI - (M_PI / 2.0);
GLfloat PrevClockMinuteHandAngle = -4 * M_PI - (M_PI / 2.0);

float lerp(float start, float end, float t)
{
	return start + t * (end - start);
}

void stars(GLfloat t1)
{
	// glEnable(GL_POINT_SMOOTH);
	glPointSize(0.5);
	glBegin(GL_POINTS);
	// glColor3f(lerp(0.0,1.0,t2), lerp(0.0, 1.0, t2), lerp(0.0, 1.0, t2));
	glColor3f(1.0 * t1, 1.0 * t1, 1.0 * t1);
	glVertex2f(-0.50, 0.40);
	glVertex2f(-0.15, 0.20);
	glVertex2f(-0.45, 0.20);
	glVertex2f(-0.50, 0.13);
	glVertex2f(-0.11, 0.37);
	glVertex2f(-0.30, 0.12);
	glEnd();
}

void windowGrid(GLfloat t1)
{
	// Window gril Lines
	glEnable(GL_LINE_SMOOTH);
	glLineWidth(1.0);
	glBegin(GL_LINES);
	// glColor3f(0.0 * t1, 0.0 * t1, 0.0 * t1);
	glColor3f(1, 1, 1);
	glVertex2f(-0.275, 0.0);
	glVertex2f(-0.275, 0.55);
	glEnd();

	glLineWidth(1.0);
	glBegin(GL_LINES);
	// glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.55, 0.275);
	glVertex2f(0.0, 0.275);
	glEnd();
	glDisable(GL_LINE_SMOOTH);
}

void window(GLfloat t1)
{

	// --------- Window ---------
	// outer window
	glPolygonMode(GL_BACK, GL_FILL);
	glBegin(GL_POLYGON);
	glColor3f(0.5 * t1, 0.5 * t1, 0.5 * t1); /// window color
	glVertex3f(-0.7, 0.0, 0.0);				 // Bottom Left point
	glVertex3f(-0.7, 0.5, 0.0);
	glVertex3f(0.0, 0.5, 0.0);
	glVertex3f(0.0, 0.0, 0.0); // Bottom right point
	glEnd();

	// Borders for outer window
	glLineWidth(2.0);
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.7, -0.0); // Bottom Left point
	glVertex2f(-0.7, 0.5);
	glVertex2f(0.0, 0.5);
	glVertex2f(0.0, 0.0); // Bottom right point
	glEnd();
	// Borders for outer window Ends
	//--------------------- Outer Window Ends ---------------------------//

	// Inner window
	glBegin(GL_POLYGON);
	glColor3f(lerp(0.0, 0.5294, t) * t1, lerp(0.0, 0.8078, t) * t1, lerp(0.0, 0.9215, t) * t1); // 135, 206, 235
	glVertex3f(-0.65, 0.0, 0.0);																// BL point
	glVertex3f(-0.65, 0.45, 0.0);
	glVertex3f(0.0, 0.45, 0.0);
	glVertex3f(0.0, 0.0, 0.0); // BR point
	glEnd();

	// Borders Lines for inner window ----------
	// glLineWidth(1.0);
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.65, 0.0);	 // BL
	glVertex2f(-0.65, 0.45); // TL
	glVertex2f(0.0, 0.45);	 // TR
	glVertex2f(0.0, 0.0);	 // BR
	glEnd();

	//------------------ Inner Window Ends ------------------------//

	// Upper left corner line
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	// glColor3f(1, 1, 1);
	glVertex2f(-0.7, 0.5);
	glVertex2f(-0.65, 0.45);
	glEnd();
	//---------

	// Window gril Lines
	glEnable(GL_LINE_SMOOTH);
	glLineWidth(1.0);
	glBegin(GL_LINES); // vertical
	// glColor3f(0.0, 0.0, 0.0);
	glColor3f(1, 1, 1);
	glVertex2f(-0.325, 0.0);
	glVertex2f(-0.325, 0.45);
	glEnd();

	glLineWidth(1.0);
	glBegin(GL_LINES);
	// glColor3f(0.0, 0.0, 0.0);
	glColor3f(1, 1, 1);
	glVertex2f(-0.65, 0.225);
	glVertex2f(0.0, 0.225);
	glEnd();
	glDisable(GL_LINE_SMOOTH);

	// Windwo grill Lines ends ----------
}

void watch_border(float cx, float cy, float r, int num_segments, GLfloat t1)
{
	// watch border

	glEnable(GL_LINE_SMOOTH);
	glLineWidth(4.0);
	glColor3f(1.0f * t1, 0.0f * t1, 0.0f * t1);
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
void watch_on_Wall(float cx, float cy, float r, int num_segments, GLfloat t1)
{
	// Watch background
	glColor3f(0.8f * t1, 0.8f * t1, 0.8f * t1);
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

	// time showing dots
	glEnable(GL_POINT_SIZE);
	glPointSize(2.0);
	glBegin(GL_POINTS);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(cx, cy);	   // center
	glVertex2f(0.4, 0.68); // 12
	glVertex2f(0.48, 0.6); // 3
	glVertex2f(0.4, 0.52); // 6
	glVertex2f(0.32, 0.6); // 9
	glEnd();
	glDisable(GL_POINT_SIZE);

	// Moving clock hands --------------
	//  Moving clock hands --------------
	glPointSize(1.0);
	glLineWidth(1.5);
	glBegin(GL_LINES);

	glVertex2f(cx, cy);
	glVertex2f(cx + 0.08 * cos(-ClockMinuteHandAngle), cy + 0.08 * sin(-ClockMinuteHandAngle));

	glEnd();

	if (ClockMinuteHandAngle >= (PrevClockMinuteHandAngle + M_PI / 6.0))
	{

		PrevClockMinuteHandAngle = ClockMinuteHandAngle;
	}
	GLfloat HourHandAngle = ((-PrevClockMinuteHandAngle) * (30.0 * M_PI / 180.0)) / (2 * M_PI);
	glPointSize(1.0);
	glLineWidth(1.5);
	glBegin(GL_LINES);

	glVertex2f(cx, cy);
	glVertex2f(cx + 0.05 * cos(HourHandAngle), cy + 0.05 * sin(HourHandAngle));

	glEnd();
}