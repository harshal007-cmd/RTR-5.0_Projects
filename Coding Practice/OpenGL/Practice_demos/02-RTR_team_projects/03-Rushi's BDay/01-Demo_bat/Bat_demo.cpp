#include<GL\freeglut.h>

int bIsScreenFull = false;
/*
63, 169
63, 132
118, 112
121, 84
124, 54
127, 75
141, 75
144, 54
148, 84
150, 114
205, 133
208, 166
135, 124
*/
GLfloat tx1 = 0.0;
GLfloat tx2 = 0.0;
GLfloat ty1 = 0.0;
GLfloat ty2 = 0.0;

void change(float x, float y)
{
	tx1 += x;
	ty1 += y;
}

GLfloat batman_vertex[] = { 1.35, 1.24,
				   2.08, 1.66,
				   2.05, 1.33,
				   1.50, 1.14,
				   1.48, 0.84,
				   1.44, 0.54,
				   1.41, 0.75,
				   1.27, 0.75,
				   1.24, 0.54,
				   1.21, 0.84,
				   1.18, 1.12,
				   0.63, 1.32,
				   0.63, 1.69
};

void batman_cape()
{
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 0.0);
		glVertex2f(0.135, 0.124);
		glVertex2f(0.208, 0.166);
		glVertex2f(0.205, 0.133);
		glVertex2f(0.150, 0.114);
		glVertex2f(0.148, 0.084);
		glVertex2f(0.144, 0.054);
		glVertex2f(0.141, 0.075);
		glVertex2f(0.127, 0.075);
		glVertex2f(0.124, 0.054);
		glVertex2f(0.121, 0.084);
		glVertex2f(0.118, 0.112);
		glVertex2f(0.063, 0.132);
		glVertex2f(0.063, 0.169);	
	glEnd();

	/*		glVertex2f(1.35, 1.24);
		glVertex2f(2.08, 1.66);
		glVertex2f(2.05, 1.33);
		glVertex2f(1.50, 1.14);
		glVertex2f(1.48, 0.84);
		glVertex2f(1.44, 0.54);
		glVertex2f(1.41, 0.75);
		glVertex2f(1.27, 0.75);
		glVertex2f(1.24, 0.54);
		glVertex2f(1.21, 0.84);
		glVertex2f(1.18, 1.12);
		glVertex2f(0.63, 1.32);
		glVertex2f(0.63, 1.69);	
*/

}

void batman_body()
{
	//body
	glBegin(GL_POLYGON);
	glColor3f(0.5, 0.5, 0.5);
	glVertex2f(0.58, 1.16);
	glVertex2f(0.73, 1.30);
	glVertex2f(0.72, 1.46);
	glVertex2f(1.09, 1.45);
	glVertex2f(1.22, 1.15);
	glVertex2f(1.23, 1.01);
	glVertex2f(0.90, 0.84);
	glVertex2f(0.59, 0.99);
	glEnd();

}

int main(int argc, char* argv[])
{
	void initialize(void);
	void display(void);
	void resize(int, int);
	void keyboard(unsigned char, int, int);
	void mouse(int, int, int, int);
	void uninitialize(void);

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(800,700);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Batman suit demo");

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
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

}

void resize(int width, int height) {

	if (height <= 0)
	{
		height = 1;

	}

	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);//use GL_Projection from Matrix maths from OpenGL math lib
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
/*
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
*/
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(-0.3, 0.3, -1.0);
	glScalef(1.5, -1.5, 1.0);
	batman_cape();

	glLoadIdentity();
	glTranslatef(tx1, ty1, -6.0);
	glScalef(1.0, -1.0, 1.0);
	//batman_body();
	
	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{	
	case 27:
		glutLeaveMainLoop();
			break;
	case 'F':
	case 'f':
		if (bIsScreenFull == false)
		{
			glutFullScreen();
			bIsScreenFull = true;
		}
		else
		{
			glutLeaveFullScreen();
			bIsScreenFull = false;
		}
		break;
	default:
		break;
	}
}

void mouse(int button, int state, int x, int y)
{
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

}
