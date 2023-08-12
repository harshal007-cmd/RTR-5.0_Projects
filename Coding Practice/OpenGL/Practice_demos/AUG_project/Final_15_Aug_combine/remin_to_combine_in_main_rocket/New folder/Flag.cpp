// Header Files
#include <GL/freeglut.h>

#define _USE_MATH_DEFINES
#include <math.h>

// Global variable declarations
bool bIsFullScreen = false;

// Entry-point function
int main(int argc, char* argv[])
{
	// Function declarations
	void initialize(void);
	void resize(int, int);
	void display(void);
	void keyboard(unsigned char, int, int);
	void mouse(int, int, int, int);
	void uninitialize(void);

	// code
	glutInit(&argc, argv);  //Init(initialization)
  
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);


	glutInitWindowSize(800, 600); //(800x600), 800-width, 600-height
	glutInitWindowPosition(100, 100); //
	glutCreateWindow("Flag");

	initialize();

	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutCloseFunc(uninitialize);

	glutMainLoop();

	return 0;
}

void initialize(void)
{
	//code
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void resize(int width, int height)
{
	//code
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
}

void display(void)
{
	// code 
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
		
	float xCenter = 0.01f, yCenter = 0.4f;
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

	// Orange
	/*glBegin(GL_QUADS);

	glColor3f(1.0f, 0.5f, 0.0f); // color (orange) 
	glVertex2f(0.01f, 0.5f); 
	glVertex2f(0.3f, 0.5f);    
	glVertex2f(0.3f, 0.4f);     
	glVertex2f(0.01f, 0.4f);   
	glEnd();

	// White
	glBegin(GL_QUADS);

	glColor3f(1.0f, 1.0f, 1.0f); // color (white) 
	glVertex2f(0.01f, 0.4f); 
	glVertex2f(0.3f, 0.4f); 
	glVertex2f(0.3f, 0.3f); 
	glVertex2f(0.01f, 0.3f); 
	glEnd(); */

	// Ashoka Chakra
	float x_center = 0.15f;
	float y_center = 0.35f;
	glColor3f(0.0f, 0.0f, 1.0f); // color(Dark Blue)
	glBegin(GL_LINE_LOOP);

	for (int i = 0; i < 100; i++)
	{
		float angle = 2.0f * M_PI * i / 100;
		glVertex2f(x_center + 0.05 * cos(angle), y_center + 0.05 * sin(angle));
	}
	glEnd();

	glBegin(GL_LINES);

	for (int i = 0; i < 24; i++)
	{
		float angle = 2.0f * M_PI * i / 24;
		glVertex2f(x_center, y_center);
		glVertex2f(x_center + 0.05 * cos(angle), y_center + 0.05 * sin(angle));
	}
	glEnd();

	// Green
	/*glBegin(GL_QUADS);

	glColor3f(0.0f, 0.39f, 0.0f); // color (Green) 
	glVertex2f(0.01f, 0.3f);
	glVertex2f(0.3f, 0.3f); 
	glVertex2f(0.3f, 0.2f); 
	glVertex2f(0.01f, 0.2f); 
	glEnd(); */

	// Flag Pole
	glBegin(GL_POLYGON);

	glColor3f(0.67f, 0.67f, 0.67f); // color (grey) 
	glVertex2f(-0.01f, 0.5f);
	glVertex2f(0.01f, 0.5f);
	glVertex2f(0.01f, -0.5f);
	glVertex2f(-0.01f, -0.5f);
	glEnd();

	//Base
	glBegin(GL_QUADS);

	glColor3f(0.50f, 0.50f, 0.50f);
	glVertex2f(-0.09f, -0.5f);
	glVertex2f(0.09f, -0.5f);
	glVertex2f(0.09f, -0.55f);
	glVertex2f(-0.09f, -0.55f);
	glEnd();

	//Base 02
	glBegin(GL_QUADS);

	glColor3f(0.41f, 0.41, 0.41f);
	glVertex2f(-0.11f, -0.55f);
	glVertex2f(0.11f, -0.55f);
	glVertex2f(0.11f, -0.6f);
	glVertex2f(-0.11f, -0.6f);
	glEnd();
	
	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
	//code
	switch (key)
	{
	case 27:
		glutLeaveMainLoop();
		break;
	case 'F':
	case 'f':

		if (bIsFullScreen == false)
		{
			glutFullScreen();
			bIsFullScreen = true;
		}
		else
		{
			glutLeaveFullScreen();
			bIsFullScreen = false;
		}
		break;
		
	default:
		break;
	}

}

void mouse(int button, int state, int x, int y)
{
	//code
	switch (button)
	{

	case GLUT_RIGHT_BUTTON:

	 glutLeaveMainLoop();

	break;

	default:
		break;
	}
}


void uninitialize(void)
{
	//code

}
