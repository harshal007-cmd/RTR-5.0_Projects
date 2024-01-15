#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

#include <gl/GL.h>

void scene1();
void scene2(GLfloat t);
void Plant(GLfloat t);
void Table(GLfloat t);
void Chair(GLfloat t);
void Calender(GLfloat t);
void mam(GLfloat t);

void scene1()
{
	// glScalef(0.5f, 0.5f, 0.0f);

	// Wall

	glBegin(GL_QUADS);

	glColor3f(0, 0, 0);
	glVertex3f(-1.0f, -0.7f, 0.0f);

	glColor3f(0.439, 0.439, 0.439);
	glVertex3f(-1.0f, 1.0f, 0.0f);

	glColor3f(0.439, 0.439, 0.439);
	glVertex3f(1.0f, 1.0f, 0.0f);

	glColor3f(0, 0, 0);
	glVertex3f(1.0f, -0.7f, 0.0f);

	glEnd();

	// Floor

	glBegin(GL_QUADS);

	glColor3f(0, 0, 0);
	glVertex3f(-1.0f, -0.7f, 0.0f);

	glColor3f(0.161, 0.161, 0.157);
	glVertex3f(-1.0f, -1.0f, 0.0f);

	glColor3f(0.161, 0.161, 0.157);
	glVertex3f(1.0f, -1.0f, 0.0f);

	glColor3f(0, 0, 0);
	glVertex3f(1.0f, -0.7f, 0.0f);

	glEnd();

	// Partition

	glColor3f(0.251, 0.243, 0.239);
	glLineWidth(1.50f);
	glBegin(GL_LINES);

	glVertex3f(-1.0f, -0.7f, 0.0f);
	glVertex3f(1.0f, -0.7f, 0.0f);

	glEnd();

	// In - Doors

	glLineWidth(2.0f);
	glBegin(GL_QUADS);

	glColor3f(1, 0.8, 0);
	glVertex3f(0.1f, -0.7f, 0.0f);

	glColor3f(0.957, 0.961, 0.573);
	glVertex3f(0.1f, 0.3f, 0.0f);

	glColor3f(1, 0.8, 0);
	glVertex3f(0.6f, 0.3f, 0.0f);

	glColor3f(1, 0.8, 0);
	glVertex3f(0.6f, -0.7f, 0.0f);

	glEnd();

	// Door Frame in

	glLineWidth(2.0f);
	glColor3f(0.51, 0.243, 0.043);
	glBegin(GL_LINE_STRIP);

	glVertex3f(0.1f, -0.7f, 0.0f);
	glVertex3f(0.1f, 0.3f, 0.0f);
	glVertex3f(0.6f, 0.3f, 0.0f);
	glVertex3f(0.6f, -0.7f, 0.0f);

	glEnd();

	// Door

	glBegin(GL_QUADS);

	glColor3f(0.761, 0.396, 0.122);
	glVertex3f(0.150f, -0.650f, 0.0f);

	glColor3f(0.761, 0.396, 0.122);
	glVertex3f(0.150f, 0.250f, 0.0f);

	glColor3f(0.569, 0.275, 0.047);
	glVertex3f(0.6f, 0.3f, 0.0f);

	glColor3f(0.569, 0.275, 0.047);
	glVertex3f(0.6f, -0.7f, 0.0f);

	glEnd();

	// Door Knob

	glBegin(GL_POLYGON);

	float radius = 0.020f;
	float x_centre = 0.190f;  // distance from X-Axis
	float y_centre = -0.165f; // distance from Y-Axis
	for (int i = 0; i < 1000; i++)
	{
		float angle = 2.0f * M_PI * i / 1000;
		glVertex2f(x_centre + radius * cos(angle), y_centre + radius * sin(angle));
		glColor3f(0.38, 0.188, 0.016);
	}
	glEnd();

	/*
	// Window

	glBegin(GL_QUADS);
	glColor3f(0.949, 0.757, 0.208);
	glVertex3f(-0.4f, 0.3f, 0.0f);

	glColor3f(0.988, 0.616, 0);
	glVertex3f(-0.1f, 0.3f, 0.0f);

	glColor3f(0.949, 0.757, 0.208);
	glVertex3f(-0.1f, 0.0f, 0.0f);

	glColor3f(0.988, 0.616, 0);
	glVertex3f(-0.4f, 0.0f, 0.0f);

	glEnd();

	// Window grid (V)

	glColor3f(0.659, 0.314, 0.098);
	glBegin(GL_LINES);

	glVertex3f(-0.25f, 0.0f, 0.0f);
	glVertex3f(-0.25f, 0.3f, 0.0f);

	glEnd();

	// Window grid (H)

	glColor3f(0.659, 0.314, 0.098);
	glBegin(GL_LINES);

	glVertex3f(-0.4f, 0.15f, 0.0f);
	glVertex3f(-0.1f, 0.15f, 0.0f);

	glEnd();
	*/

	// Door Shadow

	glBegin(GL_QUADS);

	glColor4f(1, 0.8, 0, 0.7);
	glVertex3f(0.1f, -0.7f, 0.0f);

	glColor4f(0.212, 0.208, 0.208, 0.7);
	glVertex3f(-0.5f, -1.0, 0.0f);

	glColor4f(0.212, 0.208, 0.208, 0.7);
	glVertex3f(0.5f, -1.0f, 0.0f);

	glColor4f(1, 0.8, 0, 0.7);
	glVertex3f(0.6f, -0.7f, 0.0f);

	glEnd();
}

void mam(GLfloat t)
{
	GLfloat xCenter, yCenter, xradius, yradius, angle;
	int i;
	GLfloat TshirtColor[3] = {(GLfloat)0 * t};
	GLfloat SkinColor[3] = {(GLfloat)0.812 * t, (GLfloat)0.706 * t, (GLfloat)0.388 * t};
	GLfloat PantsColor[3] = {(GLfloat)0.243 * t, (GLfloat)0.29 * t, (GLfloat)0.502 * t};

	glColor3fv(SkinColor);
	glColor3f(0.3 * t, 0.3 * t, 0.3 * t);
	glBegin(GL_POLYGON);
	xCenter = 0.7, yCenter = 0.2, xradius = 0.12, yradius = 0.18;
	for (i = 0; i < 100; i++)
	{
		angle = 2 * M_PI * (i / 100.0);
		glVertex2f(xCenter + xradius * cos(angle), yCenter + yradius * sin(angle));
	}
	glEnd();

	// Neck Area
	glColor3fv(SkinColor);

	glBegin(GL_QUADS);
	glVertex2f(0.74, -0.01);
	glVertex2f(0.66, -0.01);
	glVertex2f(0.66, -0.09);
	glVertex2f(0.74, -0.09);

	glEnd();

	// Fore hands going towards keyboard
	glColor3f(0.71 * t, 0.627 * t, 0.373 * t);
	/*
	glBegin(GL_TRIANGLES);
	glVertex2f(0.37, -0.4);
	glVertex2f(0.44, -0.41);
	glVertex2f(0.7, -0.2);
	// glVertex2f(0.4, -0.3);

	glVertex2f(1.03, -0.4);
	glVertex2f(0.96, -0.41);
	glVertex2f(0.7, -0.2);
	glEnd();
*/
	glBegin(GL_QUADS);
	glVertex2f(0.4, -0.3);
	glVertex2f(0.48, -0.35);
	glVertex2f(0.52, 0.0);
	glVertex2f(0.48, 0.0);

	glVertex2f(1.0, -0.3);
	glVertex2f(0.92, -0.35);
	glVertex2f(0.88, 0);
	glVertex2f(0.92, 0);

	glEnd();

	glBegin(GL_POLYGON);
	glVertex2f(0.52, 0.0);
	glVertex2f(0.54, 0.02);
	glVertex2f(0.52, 0.05);
	glVertex2f(0.48, 0.05);
	glVertex2f(0.46, 0.02);
	glVertex2f(0.48, 0.0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2f(0.88, 0);
	glVertex2f(0.86, 0.02);
	glVertex2f(0.88, 0.05);
	glVertex2f(0.92, 0.05);
	glVertex2f(0.94, 0.02);
	glVertex2f(0.92, 0);
	glEnd();
	// Body
	glColor3fv(TshirtColor);
	glBegin(GL_QUADS);
	glVertex2f(0.5, -0.09);
	glVertex2f(0.9, -0.09);
	glVertex2f(0.9, -0.6);
	glVertex2f(0.5, -0.6);

	glEnd();

	// Hands
	glBegin(GL_QUADS);
	glVertex2f(0.5, -0.09);
	glVertex2f(0.58, -0.09);
	glVertex2f(0.48, -0.35);
	glVertex2f(0.4, -0.3);

	glVertex2f(0.9, -0.09);
	glVertex2f(0.82, -0.09);
	glVertex2f(0.92, -0.35);
	glVertex2f(1.0, -0.3);

	glEnd();

	//
	// Fore Hands

	/*
		glColor3fv(SkinColor);
		glBegin(GL_QUADS);
		glVertex2f(0.48, -0.35);
		glVertex2f(0.4, -0.3);
		glVertex2f(0.37, -0.4);
		glVertex2f(0.44, -0.4);

		glVertex2f(0.92, -0.35);
		glVertex2f(1.0, -0.3);
		glVertex2f(1.03, -0.4);
		glVertex2f(0.96, -0.4);

		glEnd();
	*/
	// Elbow
	glBegin(GL_POLYGON);
	glColor3fv(SkinColor);
	xCenter = 0.44, yCenter = -0.32, xradius = 0.035, yradius = 0.04;
	for (i = 0; i < 100; i++)
	{
		angle = -M_PI * (i / 100.0) - 0.5;
		glVertex2f(xCenter + xradius * cos(angle), yCenter + xradius * sin(angle));
	}
	glEnd();

	glBegin(GL_POLYGON);
	glColor3fv(SkinColor);
	xCenter = 0.96, yCenter = -0.32, xradius = 0.035, yradius = 0.04;
	for (i = 0; i < 100; i++)
	{
		angle = -M_PI * (i / 100.0) + 0.5;
		glVertex2f(xCenter + xradius * cos(angle), yCenter + xradius * sin(angle));
	}
	glEnd();

	//  Neck Roll
	glBegin(GL_POLYGON);
	glColor3fv(SkinColor);
	xCenter = 0.70, yCenter = -0.09, xradius = 0.07, yradius = 0.04;
	for (i = 0; i < 100; i++)
	{
		angle = -M_PI * (i / 100.0);
		glVertex2f(xCenter + xradius * cos(angle), yCenter + yradius * sin(angle));
	}
	glEnd();

	// Hairs
	glColor3f(0.3 * t, 0.3 * t, 0.3 * t);
	glBegin(GL_QUADS);
	glVertex2f(0.58, 0.17);
	glVertex2f(0.82, 0.17);
	glVertex2f(0.72, -0.05);
	glVertex2f(0.68, -0.05);
	glEnd();

	// Bow
	glColor3f(0 * t, 0 * t, 0 * t);
	glBegin(GL_QUADS);
	glVertex2f(0.73, -0.03);
	glVertex2f(0.67, -0.03);
	glVertex2f(0.67, -0.07);
	glVertex2f(0.73, -0.07);
	glEnd();

	// Low hairs
	glColor3f(0.3 * t, 0.3 * t, 0.3 * t);
	GLfloat x, y, x1, y1;
	xCenter = 0.55, yCenter = -0.35, yradius = 0.01;
	x = xCenter;
	y = yCenter;
	x1 = 0.68, y1 = -0.05;

	glBegin(GL_TRIANGLE_STRIP);
	int j = 0;
	for (i = 0; i < 350; i++)
	{
		x = x + 0.001;
		angle = 2 * M_PI * (i / 100.0);
		y = yCenter + yradius * sin(angle);
		glVertex2f(x, y);
		glVertex2f(x1, y1);
		x1 = x1 + 0.0001;

		// glColor3f(lerp(0.0, 1.0, i / 600.0), lerp(0.0, 1.0, 6 / 600.0), lerp(0.0, 1.0, i / 600.0));
	}

	glEnd();
}

void scene2(GLfloat t)
{
	// Wall

	glBegin(GL_QUADS);

	glColor3f(0.812 * t, 0.365 * t, 0.071 * t);
	//	glColor3f(0.035, 0.467, 0.529);
	glVertex3f(-1.0f, -0.7f, 0.0f);

	glColor3f(0.98 * t, 0.643 * t, 0.42 * t);
	// glColor3f(0.122, 0.357, 0.388);
	glVertex3f(-1.0f, 1.0f, 0.0f);

	glColor3f(0.98 * t, 0.643 * t, 0.42 * t);
	// glColor3f(0.122, 0.357, 0.388);
	glVertex3f(1.0f, 1.0f, 0.0f);

	glColor3f(0.812 * t, 0.365 * t, 0.071 * t);
	// glColor3f(0.035, 0.467, 0.529);
	glVertex3f(1.0f, -0.7f, 0.0f);

	glEnd();

	//	// 0.337, 0.827, 0.902 0.243, 0.588, 0.639

	// Floor

	glColor3f(0.161 * t, 0.161 * t, 0.157 * t);
	glBegin(GL_QUADS);

	glVertex3f(-1.0f, -0.7f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glVertex3f(1.0f, -0.7f, 0.0f);

	glEnd();

	// Floor Tiles

	glColor3f(0.122 * t, 0.122 * t, 0.122 * t);
	glLineWidth(1.50f);
	glBegin(GL_LINES);

	glVertex3f(-0.67f, -0.7f, 0.0f);
	glVertex3f(-1.0f, -0.90f, 0.0f);

	glVertex3f(-0.4f, -0.7f, 0.0f);
	glVertex3f(-0.7f, -1.0f, 0.0f);

	glVertex3f(-0.15f, -0.7f, 0.0f);
	glVertex3f(-0.35f, -1.0f, 0.0f);

	glVertex3f(0.10f, -0.7f, 0.0f);
	glVertex3f(0.0f, -1.0f, 0.0f);

	glVertex3f(0.30f, -0.7f, 0.0f);
	glVertex3f(0.40f, -1.0f, 0.0f);

	glVertex3f(0.50f, -0.7f, 0.0f);
	glVertex3f(0.75f, -1.0f, 0.0f);

	glVertex3f(0.75f, -0.7f, 0.0f);
	glVertex3f(1.0f, -0.90f, 0.0f);

	glVertex3f(-1.0f, -0.8f, 0.0f);
	glVertex3f(1.0f, -0.8f, 0.0f);

	glEnd();

	// Partition

	glColor3f(0.122 * t, 0.122 * t, 0.122 * t);
	glLineWidth(1.50f);
	glBegin(GL_LINES);

	glVertex3f(-1.0f, -0.7f, 0.0f);
	glVertex3f(1.0f, -0.7f, 0.0f);

	glEnd();

	// Shelf

	glColor3f(0.439 * t, 0.184 * t, 0.016 * t);
	glBegin(GL_QUADS);

	glVertex3f(1.0f, 0.28f, 0.0f);
	glVertex3f(0.55f, 0.28f, 0.0f);
	glVertex3f(0.55f, 0.23f, 0.0f);
	glVertex3f(1.0f, 0.23f, 0.0f);

	glEnd();

	// Radio

	glColor3f(0 * t, 0 * t, 0 * t);
	glBegin(GL_QUADS);

	glVertex3f(0.60f, 0.28f, 0.0f);
	glVertex3f(0.60f, 0.40f, 0.0f);
	glVertex3f(0.90f, 0.40f, 0.0f);
	glVertex3f(0.90f, 0.28f, 0.0f);

	glEnd();

	// Radio Antennae

	glColor3f(0 * t, 0 * t, 0 * t);
	glLineWidth(1.50f);
	glBegin(GL_LINES);

	glVertex3f(0.90f, 0.40f, 0.0f);
	glVertex3f(0.70f, 0.55f, 0.0f);

	glEnd();

	// Radio Buttons

	glBegin(GL_POLYGON); // Left Button

	float radius_2 = 0.02f;
	float x_centre_2 = 0.65f; // distance from X-Axis
	float y_centre_2 = 0.34f; // distance from Y-Axis
	for (int i = 0; i < 1000; i++)
	{
		float angle = 2.0f * M_PI * i / 1000;
		glVertex2f(x_centre_2 + radius_2 * cos(angle), y_centre_2 + radius_2 * sin(angle));
		glColor3f(1 * t, 1 * t, 1 * t);
	}
	glEnd();

	glBegin(GL_POLYGON); // Right Button

	float radius_3 = 0.02f;
	float x_centre_3 = 0.72f; // distance from X-Axis
	float y_centre_3 = 0.34f; // distance from Y-Axis
	for (int i = 0; i < 1000; i++)
	{
		float angle = 2.0f * M_PI * i / 1000;
		glVertex2f(x_centre_3 + radius_3 * cos(angle), y_centre_3 + radius_3 * sin(angle));
		glColor3f(1 * t, 1 * t, 1 * t);
	}
	glEnd();

	glColor3f(1 * t, 1 * t, 1 * t); // Bottom Right Button
	glBegin(GL_QUADS);

	glVertex3f(0.86f, 0.31f, 0.0f);
	glVertex3f(0.84f, 0.31f, 0.0f);
	glVertex3f(0.84f, 0.33f, 0.0f);
	glVertex3f(0.86f, 0.33f, 0.0f);

	glEnd();

	glColor3f(1 * t, 1 * t, 1 * t); // Bottom Left Button
	glBegin(GL_QUADS);

	glVertex3f(0.82f, 0.31f, 0.0f);
	glVertex3f(0.80f, 0.31f, 0.0f);
	glVertex3f(0.80f, 0.33f, 0.0f);
	glVertex3f(0.82f, 0.33f, 0.0f);

	glEnd();

	// Calendar
	/*
		glColor3f(1 * t, 1 * t, 1 * t);
		glBegin(GL_QUADS); // Calendar

		glVertex3f(-0.050f, 0.15f, 0.0f);
		glVertex3f(-0.050f, 0.40f, 0.0f);
		glVertex3f(0.45f, 0.40f, 0.0f);
		glVertex3f(0.45f, 0.15f, 0.0f);

		glEnd();

		glColor3f(0.357 * t, 0.357 * t, 0.988 * t); // Date
		glBegin(GL_QUADS);

		glVertex3f(-0.050f, 0.32f, 0.0f);
		glVertex3f(-0.050f, 0.40f, 0.0f);
		glVertex3f(0.45f, 0.40f, 0.0f);
		glVertex3f(0.45f, 0.32f, 0.0f);

		glEnd();

		glColor3f(0 * t, 0 * t, 0 * t); // Date Border
		glBegin(GL_LINES);

		glVertex3f(-0.050f, 0.32f, 0.0f);
		glVertex3f(0.45f, 0.32f, 0.0f);

		glEnd();

		glColor3f(0 * t, 0 * t, 0 * t); // 1
		glBegin(GL_LINES);

		glVertex3f(0.065f, 0.39f, 0.0f);
		glVertex3f(0.065f, 0.34f, 0.0f);

		glEnd();

		glColor3f(0 * t, 0 * t, 0 * t); // 8
		glBegin(GL_LINE_STRIP);

		float radius_4 = 0.0125f;
		float x_centre_4 = 0.090f; // distance from X-Axis
		float y_centre_4 = 0.375f; // distance from Y-Axis
		for (int i = 0; i < 100000; i++)
		{
			float angle = 2.0f * M_PI * i / 1000;
			glVertex2f(x_centre_4 + radius_4 * cos(angle), y_centre_4 + radius_4 * sin(angle));
		}
		glEnd();
		glBegin(GL_LINE_STRIP);

		float radius_5 = 0.0125f;
		float x_centre_5 = 0.090f; // distance from X-Axis
		float y_centre_5 = 0.349f; // distance from Y-Axis
		for (int i = 0; i < 100000; i++)
		{
			float angle = 2.0f * M_PI * i / 1000;
			glVertex2f(x_centre_5 + radius_5 * cos(angle), y_centre_5 + radius_5 * sin(angle));
		}
		glEnd();

		glColor3f(0 * t, 0 * t, 0 * t); // A
		glBegin(GL_LINE_STRIP);

		glVertex3f(0.15f, 0.365f, 0.0f);
		glVertex3f(0.12f, 0.34f, 0.0f);
		glVertex3f(0.13f, 0.39f, 0.0f);
		glVertex3f(0.14f, 0.34f, 0.0f);

		glEnd();

		glColor3f(0 * t, 0 * t, 0 * t); // U
		glBegin(GL_LINE_STRIP);

		glVertex3f(0.16f, 0.39f, 0.0f);
		glVertex3f(0.16f, 0.34f, 0.0f);
		glVertex3f(0.18f, 0.34f, 0.0f);
		glVertex3f(0.18f, 0.39f, 0.0f);

		glEnd();

		glColor3f(0 * t, 0 * t, 0 * t); // G
		glBegin(GL_LINE_STRIP);

		glVertex3f(0.22f, 0.39f, 0.0f);
		glVertex3f(0.20f, 0.39f, 0.0f);
		glVertex3f(0.20f, 0.34f, 0.0f);
		glVertex3f(0.22f, 0.34f, 0.0f);
		glVertex3f(0.22f, 0.36f, 0.0f);
		glVertex3f(0.21f, 0.36f, 0.0f);

		glEnd();

		glColor3f(0 * t, 0 * t, 0 * t); // 2
		glBegin(GL_LINE_STRIP);

		glVertex3f(0.24f, 0.39f, 0.0f);
		glVertex3f(0.26f, 0.39f, 0.0f);
		glVertex3f(0.26f, 0.37f, 0.0f);
		glVertex3f(0.24f, 0.37f, 0.0f);
		glVertex3f(0.24f, 0.34f, 0.0f);
		glVertex3f(0.26f, 0.34f, 0.0f);

		glEnd();

		glColor3f(0 * t, 0 * t, 0 * t); // 0
		glBegin(GL_LINE_STRIP);

		glVertex3f(0.28f, 0.39f, 0.0f);
		glVertex3f(0.28f, 0.34f, 0.0f);
		glVertex3f(0.30f, 0.34f, 0.0f);
		glVertex3f(0.30f, 0.39f, 0.0f);
		glVertex3f(0.28f, 0.39f, 0.0f);

		glEnd();

		glColor3f(0 * t, 0 * t, 0 * t); // 1
		glBegin(GL_LINES);

		glVertex3f(0.32f, 0.39f, 0.0f);
		glVertex3f(0.32f, 0.34f, 0.0f);

		glEnd();

		glColor3f(0 * t, 0 * t, 0 * t); // 7
		glBegin(GL_LINE_STRIP);

		glVertex3f(0.34f, 0.39f, 0.0f);
		glVertex3f(0.36f, 0.39f, 0.0f);
		glVertex3f(0.35f, 0.34f, 0.0f);

		glEnd();

		// Calendar Grid

		glColor3f(0 * t, 0 * t, 0 * t); // V
		glBegin(GL_LINES);

		glVertex3f(0.075f, 0.32f, 0.0f);
		glVertex3f(0.075f, 0.15f, 0.0f);

		glEnd();

		glColor3f(0 * t, 0 * t, 0 * t); // V
		glBegin(GL_LINES);

		glVertex3f(0.2f, 0.32f, 0.0f);
		glVertex3f(0.2f, 0.15f, 0.0f);

		glEnd();

		glColor3f(0, 0, 0); // V
		glBegin(GL_LINES);

		glVertex3f(0.325f, 0.32f, 0.0f);
		glVertex3f(0.325f, 0.15f, 0.0f);

		glEnd();

		glColor3f(0, 0, 0); // H
		glBegin(GL_LINES);

		glVertex3f(-0.050f, 0.263f, 0.0f);
		glVertex3f(0.45f, 0.263f, 0.0f);

		glEnd();

		glColor3f(0, 0, 0); // H
		glBegin(GL_LINES);

		glVertex3f(-0.050f, 0.206f, 0.0f);
		glVertex3f(0.45f, 0.206f, 0.0f);

		glEnd();

		glColor3f(0, 0, 0); // Border
		glLineWidth(2.00f);
		glBegin(GL_LINE_STRIP);

		glVertex3f(-0.050f, 0.15f, 0.0f);
		glVertex3f(-0.050f, 0.40f, 0.0f);
		glVertex3f(0.45f, 0.40f, 0.0f);
		glVertex3f(0.45f, 0.15f, 0.0f);
		glVertex3f(-0.050f, 0.15f, 0.0f);

		glEnd();
		*/
}

void Calender(GLfloat t)
{
	// Calendar

	glColor3f(1 * t, 1 * t, 1 * t);
	glBegin(GL_QUADS); // Calendar

	glVertex3f(-0.050f, 0.15f, 0.0f);
	glVertex3f(-0.050f, 0.40f, 0.0f);
	glVertex3f(0.45f, 0.40f, 0.0f);
	glVertex3f(0.45f, 0.15f, 0.0f);

	glEnd();

	glColor3f(0.357 * t, 0.357 * t, 0.988 * t); // Date
	glBegin(GL_QUADS);

	glVertex3f(-0.050f, 0.32f, 0.0f);
	glVertex3f(-0.050f, 0.40f, 0.0f);
	glVertex3f(0.45f, 0.40f, 0.0f);
	glVertex3f(0.45f, 0.32f, 0.0f);

	glEnd();

	glColor3f(0 * t, 0 * t, 0 * t); // Date Border
	glBegin(GL_LINES);

	glVertex3f(-0.050f, 0.32f, 0.0f);
	glVertex3f(0.45f, 0.32f, 0.0f);

	glEnd();

	glColor3f(0 * t, 0 * t, 0 * t); // 1
	glBegin(GL_LINES);

	glVertex3f(0.065f, 0.39f, 0.0f);
	glVertex3f(0.065f, 0.34f, 0.0f);

	glEnd();

	glColor3f(0 * t, 0 * t, 0 * t); // 8
	glBegin(GL_LINE_STRIP);

	float radius_4 = 0.0125f;
	float x_centre_4 = 0.090f; // distance from X-Axis
	float y_centre_4 = 0.375f; // distance from Y-Axis
	for (int i = 0; i < 100000; i++)
	{
		float angle = 2.0f * M_PI * i / 1000;
		glVertex2f(x_centre_4 + radius_4 * cos(angle), y_centre_4 + radius_4 * sin(angle));
	}
	glEnd();
	glBegin(GL_LINE_STRIP);

	float radius_5 = 0.0125f;
	float x_centre_5 = 0.090f; // distance from X-Axis
	float y_centre_5 = 0.349f; // distance from Y-Axis
	for (int i = 0; i < 100000; i++)
	{
		float angle = 2.0f * M_PI * i / 1000;
		glVertex2f(x_centre_5 + radius_5 * cos(angle), y_centre_5 + radius_5 * sin(angle));
	}
	glEnd();

	glColor3f(0 * t, 0 * t, 0 * t); // A
	glBegin(GL_LINE_STRIP);

	glVertex3f(0.15f, 0.365f, 0.0f);
	glVertex3f(0.12f, 0.34f, 0.0f);
	glVertex3f(0.13f, 0.39f, 0.0f);
	glVertex3f(0.14f, 0.34f, 0.0f);

	glEnd();

	glColor3f(0 * t, 0 * t, 0 * t); // U
	glBegin(GL_LINE_STRIP);

	glVertex3f(0.16f, 0.39f, 0.0f);
	glVertex3f(0.16f, 0.34f, 0.0f);
	glVertex3f(0.18f, 0.34f, 0.0f);
	glVertex3f(0.18f, 0.39f, 0.0f);

	glEnd();

	glColor3f(0 * t, 0 * t, 0 * t); // G
	glBegin(GL_LINE_STRIP);

	glVertex3f(0.22f, 0.39f, 0.0f);
	glVertex3f(0.20f, 0.39f, 0.0f);
	glVertex3f(0.20f, 0.34f, 0.0f);
	glVertex3f(0.22f, 0.34f, 0.0f);
	glVertex3f(0.22f, 0.36f, 0.0f);
	glVertex3f(0.21f, 0.36f, 0.0f);

	glEnd();

	glColor3f(0 * t, 0 * t, 0 * t); // 2
	glBegin(GL_LINE_STRIP);

	glVertex3f(0.24f, 0.39f, 0.0f);
	glVertex3f(0.26f, 0.39f, 0.0f);
	glVertex3f(0.26f, 0.37f, 0.0f);
	glVertex3f(0.24f, 0.37f, 0.0f);
	glVertex3f(0.24f, 0.34f, 0.0f);
	glVertex3f(0.26f, 0.34f, 0.0f);

	glEnd();

	glColor3f(0 * t, 0 * t, 0 * t); // 0
	glBegin(GL_LINE_STRIP);

	glVertex3f(0.28f, 0.39f, 0.0f);
	glVertex3f(0.28f, 0.34f, 0.0f);
	glVertex3f(0.30f, 0.34f, 0.0f);
	glVertex3f(0.30f, 0.39f, 0.0f);
	glVertex3f(0.28f, 0.39f, 0.0f);

	glEnd();

	glColor3f(0 * t, 0 * t, 0 * t); // 1
	glBegin(GL_LINES);

	glVertex3f(0.32f, 0.39f, 0.0f);
	glVertex3f(0.32f, 0.34f, 0.0f);

	glEnd();

	glColor3f(0 * t, 0 * t, 0 * t); // 7
	glBegin(GL_LINE_STRIP);

	glVertex3f(0.34f, 0.39f, 0.0f);
	glVertex3f(0.36f, 0.39f, 0.0f);
	glVertex3f(0.35f, 0.34f, 0.0f);

	glEnd();

	// Calendar Grid

	glColor3f(0 * t, 0 * t, 0 * t); // V
	glBegin(GL_LINES);

	glVertex3f(0.075f, 0.32f, 0.0f);
	glVertex3f(0.075f, 0.15f, 0.0f);

	glEnd();

	glColor3f(0 * t, 0 * t, 0 * t); // V
	glBegin(GL_LINES);

	glVertex3f(0.2f, 0.32f, 0.0f);
	glVertex3f(0.2f, 0.15f, 0.0f);

	glEnd();

	glColor3f(0, 0, 0); // V
	glBegin(GL_LINES);

	glVertex3f(0.325f, 0.32f, 0.0f);
	glVertex3f(0.325f, 0.15f, 0.0f);

	glEnd();

	glColor3f(0, 0, 0); // H
	glBegin(GL_LINES);

	glVertex3f(-0.050f, 0.263f, 0.0f);
	glVertex3f(0.45f, 0.263f, 0.0f);

	glEnd();

	glColor3f(0, 0, 0); // H
	glBegin(GL_LINES);

	glVertex3f(-0.050f, 0.206f, 0.0f);
	glVertex3f(0.45f, 0.206f, 0.0f);

	glEnd();

	glColor3f(0, 0, 0); // Border
	glLineWidth(2.00f);
	glBegin(GL_LINE_STRIP);

	glVertex3f(-0.050f, 0.15f, 0.0f);
	glVertex3f(-0.050f, 0.40f, 0.0f);
	glVertex3f(0.45f, 0.40f, 0.0f);
	glVertex3f(0.45f, 0.15f, 0.0f);
	glVertex3f(-0.050f, 0.15f, 0.0f);

	glEnd();
}

void Plant(GLfloat t)
{
	glColor3f(0.612f * t, 0.227f * t, 0.047f * t);
	glBegin(GL_POLYGON);
	glVertex2f(-0.4f, -0.5f);
	glVertex2f(-0.7f, -0.5f);
	glVertex2f(-0.6f, -0.8f);
	glVertex2f(-0.5f, -0.8f);
	glEnd();

	glLineWidth(4);
	glColor3f(0.0f * t, 1.0f * t, 0.0f * t);
	glBegin(GL_LINES);
	glVertex2f(-0.55f, -0.5f);
	glVertex2f(-0.42f, -0.3f);
	glVertex2f(-0.55f, -0.5f);
	glVertex2f(-0.46f, -0.2f);
	glVertex2f(-0.55f, -0.5f);
	glVertex2f(-0.47f, -0.1f);
	glVertex2f(-0.55f, -0.5f);
	glVertex2f(-0.75f, -0.30f);
	glVertex2f(-0.55f, -0.5f);
	glVertex2f(-0.70f, -0.2f);
	glVertex2f(-0.55f, -0.5f);
	glVertex2f(-0.67f, -0.2f);
	glVertex2f(-0.55f, -0.5f);
	glVertex2f(-0.55f, -0.2f);
	glEnd();

	glColor3f(0, 0, 0);
	// glColor3f(100.0f * t, 84.3f * t, 0.0f * t);
	glBegin(GL_LINES);
	glVertex2f(-0.75f, -0.80f);
	glVertex2f(-0.75f, -0.99f);
	glVertex2f(-0.75f, -0.80f);
	glVertex2f(-0.35f, -0.80f);
	glVertex2f(-0.35f, -0.80f);
	glVertex2f(-0.35f, -0.99f);
	glVertex2f(-0.35f, -0.90f);
	glVertex2f(-0.10f, -0.90f);
	glVertex2f(-0.10f, -0.90f);
	glVertex2f(-0.10f, -0.99f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0f * t, 0.0f * t, 0.0f * t);
	glVertex2f(-0.25f, -0.50f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(-0.20f, -0.89f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2f(-0.30f, -0.89f);

	glEnd();
}

void Table(GLfloat t)
{

	glBegin(GL_POLYGON);

	// Table Top
	glColor3f(0.8f * t, 0.5f * t, 0.1f * t);
	glVertex3f(-0.7f, 0.5f, 0.0f);
	glVertex3f(0.7f, 0.5f, 0.0f);
	glVertex3f(0.8f, 0.2f, 0.0f);
	glVertex3f(-0.8f, 0.2f, 0.0f);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-0.7f, 0.5f, 0.0f);
	glVertex3f(0.7f, 0.5f, 0.0f);
	glVertex3f(0.8f, 0.2f, 0.0f);
	glVertex3f(-0.8f, 0.2f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);

	// Table Front Side Perspective
	glColor3f(0.8f * t, 0.5f * t, 0.1f * t); // colors (RGB)
	glVertex3f(-0.8f, 0.2f, 0.0f);
	glVertex3f(0.8f, 0.2f, 0.0f);
	glVertex3f(0.8f, 0.1f, 0.0f);
	glVertex3f(-0.8f, 0.1f, 0.0f);
	glEnd();

	glBegin(GL_LINE_LOOP);

	// Table Front Side Perspective
	glColor3f(0.0f, 0.0f, 0.0f); // colors (RGB)
	glVertex3f(-0.8f, 0.2f, 0.0f);
	glVertex3f(0.8f, 0.2f, 0.0f);
	glVertex3f(0.8f, 0.1f, 0.0f);
	glVertex3f(-0.8f, 0.1f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);

	// Front Left Leg
	glColor3f(0.8f * t, 0.5f * t, 0.1f * t);
	glVertex3f(-0.75f, 0.1f, 0.0f);
	glVertex3f(-0.70f, 0.1f, 0.0f);
	glVertex3f(-0.70f, -0.8f, 0.0f);
	glVertex3f(-0.75f, -0.8f, 0.0f);
	glEnd();

	glBegin(GL_LINE_LOOP);

	// Front Left Leg
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-0.75f, 0.1f, 0.0f);
	glVertex3f(-0.70f, 0.1f, 0.0f);
	glVertex3f(-0.70f, -0.8f, 0.0f);
	glVertex3f(-0.75f, -0.8f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);

	// Front Right Leg
	glColor3f(0.8f * t, 0.5f * t, 0.1f * t);
	glVertex3f(0.75f, 0.1f, 0.0f);
	glVertex3f(0.70f, 0.1f, 0.0f);
	glVertex3f(0.70f, -0.8f, 0.0f);
	glVertex3f(0.75f, -0.8f, 0.0f);
	glEnd();

	glBegin(GL_LINE_LOOP);

	// Front Right Leg
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.75f, 0.1f, 0.0f);
	glVertex3f(0.70f, 0.1f, 0.0f);
	glVertex3f(0.70f, -0.8f, 0.0f);
	glVertex3f(0.75f, -0.8f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);

	// Drawers
	glColor3f(0.8f * t, 0.5f * t, 0.1f * t); // colors (RGB)
	glVertex3f(-0.70f, 0.1f, 0.0f);
	glVertex3f(0.70f, 0.1f, 0.0f);
	glVertex3f(0.70f, -0.15f, 0.0f);
	glVertex3f(-0.70f, -0.15f, 0.0f);
	glEnd();

	glBegin(GL_LINE_LOOP);
	// Drawers
	glColor3f(0.0f, 0.0f, 0.0f); // colors (RGB)
	glVertex3f(-0.70f, 0.1f, 0.0f);
	glVertex3f(0.70f, 0.1f, 0.0f);
	glVertex3f(0.70f, -0.15f, 0.0f);
	glVertex3f(-0.70f, -0.15f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);

	// Back Left Leg
	glColor3f(0.7f * t, 0.4f * t, 0.0f * t); // colors (RGB)
	glVertex3f(-0.65f, -0.15f, 0.0f);
	glVertex3f(-0.60f, -0.15f, 0.0f);
	glVertex3f(-0.60f, -0.6f, 0.0f);
	glVertex3f(-0.65f, -0.6f, 0.0f);
	glEnd();

	glBegin(GL_LINE_LOOP);

	// Back Left Leg
	glColor3f(0.0f, 0.0f, 0.0f); // colors (RGB)
	glVertex3f(-0.65f, -0.15f, 0.0f);
	glVertex3f(-0.60f, -0.15f, 0.0f);
	glVertex3f(-0.60f, -0.6f, 0.0f);
	glVertex3f(-0.65f, -0.6f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);

	// Back Right Leg
	glColor3f(0.7f * t, 0.4f * t, 0.0f * t); // colors (RGB)
	glVertex3f(0.65f, -0.15f, 0.0f);
	glVertex3f(0.60f, -0.15f, 0.0f);
	glVertex3f(0.60f, -0.6f, 0.0f);
	glVertex3f(0.65f, -0.6f, 0.0f);
	glEnd();

	glBegin(GL_LINE_LOOP);

	// Back Right Leg
	glColor3f(0.0f, 0.0f, 0.0f); // colors (RGB)
	glVertex3f(0.65f, -0.15f, 0.0f);
	glVertex3f(0.60f, -0.15f, 0.0f);
	glVertex3f(0.60f, -0.6f, 0.0f);
	glVertex3f(0.65f, -0.6f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);

	// Left Inside Drawer
	glColor3f(0.8f * t, 0.5f * t, 0.1f * t); // colors (RGB)
	glVertex3f(-0.60f, 0.060f, 0.0f);
	glVertex3f(-0.005f, 0.060f, 0.0f);
	glVertex3f(-0.005f, -0.12f, 0.0f);
	glVertex3f(-0.60f, -0.12f, 0.0f);
	glEnd();

	glBegin(GL_LINE_LOOP);

	// Left Inside Drawer
	glColor3f(0.0f, 0.0f, 0.0f); // colors (RGB)
	glVertex3f(-0.60f, 0.060f, 0.0f);
	glVertex3f(-0.005f, 0.060f, 0.0f);
	glVertex3f(-0.005f, -0.12f, 0.0f);
	glVertex3f(-0.60f, -0.12f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);

	// Right Inside Drawer
	glColor3f(0.8f * t, 0.5f * t, 0.1f * t); // colors (RGB)
	glVertex3f(0.10f, 0.060f, 0.0f);
	glVertex3f(0.60f, 0.060f, 0.0f);
	glVertex3f(0.60f, -0.12f, 0.0f);
	glVertex3f(0.10f, -0.12f, 0.0f);
	glEnd();

	glBegin(GL_LINE_LOOP);

	// Right Inside Drawer
	glColor3f(0.0f, 0.0f, 0.0f); // colors (RGB)
	glVertex3f(0.10f, 0.060f, 0.0f);
	glVertex3f(0.60f, 0.060f, 0.0f);
	glVertex3f(0.60f, -0.12f, 0.0f);
	glVertex3f(0.10f, -0.12f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);

	// Left Inside Drawer Handle
	glColor3f(0.0f, 0.0f, 0.0f); // colors (RGB)
	glVertex3f(-0.40f, -0.03f, 0.0f);
	glVertex3f(-0.20f, -0.03f, 0.0f);
	glVertex3f(-0.20f, -0.06f, 0.0f);
	glVertex3f(-0.40f, -0.06f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);

	// Right Inside Drawer Handle
	glColor3f(0.0f, 0.0f, 0.0f); // colors (RGB)
	glVertex3f(0.45f, -0.03f, 0.0f);
	glVertex3f(0.25f, -0.03f, 0.0f);
	glVertex3f(0.25f, -0.06f, 0.0f);
	glVertex3f(0.45f, -0.06f, 0.0f);
	glEnd();
}

void Chair(GLfloat t)
{

	// Chair
	glBegin(GL_POLYGON);

	glColor3f(0.5f * t, 0.2f * t, 0.0f * t);
	glVertex3f(-0.20f, 0.25f, 0.0f);
	glVertex3f(0.20f, 0.25f, 0.0f);
	glVertex3f(0.20f, -0.45f, 0.0f);
	glVertex3f(-0.20f, -0.45f, 0.0f);
	glEnd();

	glBegin(GL_LINE_LOOP);

	glColor3f(0.0f * t, 0.0f * t, 0.0f * t);
	glVertex3f(-0.20f, 0.25f, 0.0f);
	glVertex3f(0.20f, 0.25f, 0.0f);
	glVertex3f(0.20f, -0.45f, 0.0f);
	glVertex3f(-0.20f, -0.45f, 0.0f);
	glEnd();

	// Base
	glBegin(GL_POLYGON);

	glColor3f(0.5f * t, 0.2f * t, 0.0f * t);
	glVertex3f(-0.20f, -0.43f, 0.0f);
	glVertex3f(0.20f, -0.43f, 0.0f);
	glVertex3f(0.20f, -0.45f, 0.0f);
	glVertex3f(-0.20f, -0.45f, 0.0f);
	glEnd();

	glBegin(GL_LINE_LOOP);

	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-0.20f, -0.40f, 0.0f);
	glVertex3f(0.20f, -0.40f, 0.0f);
	glVertex3f(0.20f, -0.45f, 0.0f);
	glVertex3f(-0.20f, -0.45f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);

	// Left Leg
	glColor3f(0.5f * t, 0.2f * t, 0.0f * t);
	glVertex3f(-0.18f, -0.45f, 0.0f);
	glVertex3f(-0.14f, -0.45f, 0.0f);
	glVertex3f(-0.14f, -0.8f, 0.0f);
	glVertex3f(-0.18f, -0.8f, 0.0f);
	glEnd();

	glBegin(GL_LINE_LOOP);

	// Left Leg
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-0.18f, -0.45f, 0.0f);
	glVertex3f(-0.14f, -0.45f, 0.0f);
	glVertex3f(-0.14f, -0.8f, 0.0f);
	glVertex3f(-0.18f, -0.8f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);

	// Right Leg
	glColor3f(0.5f * t, 0.2f * t, 0.0f * t);
	glVertex3f(0.18f, -0.45f, 0.0f);
	glVertex3f(0.14f, -0.45f, 0.0f);
	glVertex3f(0.14f, -0.8f, 0.0f);
	glVertex3f(0.18f, -0.8f, 0.0f);
	glEnd();

	glBegin(GL_LINE_LOOP);

	// Right Leg
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.18f, -0.45f, 0.0f);
	glVertex3f(0.14f, -0.45f, 0.0f);
	glVertex3f(0.14f, -0.8f, 0.0f);
	glVertex3f(0.18f, -0.8f, 0.0f);
	glEnd();

	// Base 2
	glBegin(GL_POLYGON);

	glColor3f(0.5f * t, 0.2f * t, 0.0f * t);
	glVertex3f(-0.14f, -0.45f, 0.0f);
	glVertex3f(0.14f, -0.45f, 0.0f);
	glVertex3f(0.14f, -0.56f, 0.0f);
	glVertex3f(-0.14f, -0.56f, 0.0f);
	glEnd();

	glBegin(GL_LINE_LOOP);

	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-0.14f, -0.45f, 0.0f);
	glVertex3f(0.14f, -0.45f, 0.0f);
	glVertex3f(0.14f, -0.56f, 0.0f);
	glVertex3f(-0.14f, -0.56f, 0.0f);
	glEnd();

	// Left Leg
	glBegin(GL_POLYGON);

	glColor3f(0.5f * t, 0.2f * t, 0.0f * t);
	glVertex3f(-0.14f, -0.56f, 0.0f);
	glVertex3f(-0.10f, -0.56f, 0.0f);
	glVertex3f(-0.10f, -0.73f, 0.0f);
	glVertex3f(-0.14f, -0.73f, 0.0f);
	glEnd();

	glBegin(GL_LINE_LOOP);

	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-0.14f, -0.56f, 0.0f);
	glVertex3f(-0.10f, -0.56f, 0.0f);
	glVertex3f(-0.10f, -0.73f, 0.0f);
	glVertex3f(-0.14f, -0.73f, 0.0f);
	glEnd();

	// Right Leg
	glBegin(GL_POLYGON);

	glColor3f(0.5f * t, 0.2f * t, 0.0f);
	glVertex3f(0.14f, -0.56f, 0.0f);
	glVertex3f(0.10f, -0.56f, 0.0f);
	glVertex3f(0.10f, -0.73f, 0.0f);
	glVertex3f(0.14f, -0.73f, 0.0f);
	glEnd();

	glBegin(GL_LINE_LOOP);

	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.14f, -0.56f, 0.0f);
	glVertex3f(0.10f, -0.56f, 0.0f);
	glVertex3f(0.10f, -0.73f, 0.0f);
	glVertex3f(0.14f, -0.73f, 0.0f);
	glEnd();
}