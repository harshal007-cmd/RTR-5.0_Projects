#include<Windows.h>
#include"Theater.h"
#include<stdio.h>
#include<GL/GL.h>

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

