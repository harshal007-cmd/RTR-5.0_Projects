#include<Windows.h>
#include<GL/GL.h>
#include<stdio.h>
#include"Poster.h"

void movie_name()
{

	glBegin(GL_POLYGON);
	for (int i = 0; i < ARRAY_LENGTH(Harry); i = i + 2)
	{
		glVertex2f(Harry[i], Harry[i + 1]);
	}
	glEnd();
}


