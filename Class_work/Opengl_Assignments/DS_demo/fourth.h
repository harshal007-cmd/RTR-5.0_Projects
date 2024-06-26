#pragma once
#include<GL\gl.h>
#include<GL\GLU.h>

GLuint texture_build2;

GLfloat build2_t = -1.0;
//GLfloat ot4 = 0.0;

void build2_tex()
{
	glBindTexture(GL_TEXTURE_2D, texture_build2);

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
	glVertex2f(2.3, 1.5);

	glTexCoord2f(0.0, 1.0);
	glVertex2f(-2.3, 1.5);

	glTexCoord2f(0.0, 0.0);
	glVertex2f(-2.3, -1.5);


	glTexCoord2f(1.0, 0.0);
	glVertex2f(2.3, -1.5);

	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);

}
