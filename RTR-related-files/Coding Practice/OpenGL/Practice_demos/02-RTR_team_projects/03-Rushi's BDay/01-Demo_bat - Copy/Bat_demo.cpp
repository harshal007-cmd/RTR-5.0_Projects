#include<GL\freeglut.h>

int bIsScreenFull = false;

GLfloat batman_vertex[] = { 0.399,0.310,
0.393,0.243,
0.303,0.215,
0.295,0.166,
0.286,0.114,
0.281,0.149,
0.261,0.152,
0.251,0.119,
0.247,0.174,
0.246,0.216,
0.157,0.248,
0.151,0.318,
0.275,0.237,
0.399,0.310

};

/*
GLfloat bat_cape[] = { 0.136,0.088,
0.100,0.075,
0.098,0.058,
0.097,0.038,
0.095,0.050,
0.085,0.050,
0.083,0.039,
0.081,0.057,
0.079,0.077,
0.042,0.087,
0.041,0.113,
0.090,0.083,
0.138,0.113 };
*/


GLfloat bat_cape[] = { 0.041,0.115,
0.043,0.089,
0.078,0.077,
0.083,0.039
};

GLfloat bat_body_vertex[] = { 0.122, 0.100,
		0.091, 0.083,
		0.059, 0.099,
		0.059, 0.114,
		0.073, 0.128,
		0.072, 0.146,
		0.109, 0.145,
		0.109, 0.129,
		0.122, 0.115
		
};


void batman()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	
	glVertexPointer(2, GL_FLOAT, 0, &batman_vertex[0]);

	glScalef(1.0, -1.0, 0.0);
	glColor3f(1.0, 1.0, 0.0);
	glDrawArrays(GL_POLYGON, 0, 14);
	/*
	glArrayElement(0);
	glArrayElement(1);
	glArrayElement(2);
	glArrayElement(3);
	glArrayElement(4);
	glArrayElement(5);
	glArrayElement(6);
	glArrayElement(7);
	glArrayElement(8);
	glArrayElement(9);
	glArrayElement(10);
	glArrayElement(11);
	glArrayElement(12);
	glEnd();
	*/
}

void bat_body()
{
	glEnableClientState(GL_VERTEX_ARRAY);

	glVertexPointer(2, GL_FLOAT, 0, &bat_body_vertex[0]);

	glScalef(2.0, 2.0, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	glDrawArrays(GL_POLYGON, 0, 9);

}

void bat_leg()
{
	GLfloat bat_legs[] = { 0.071,0.147,
		0.108,0.146,
		0.111,0.155,
		0.072,0.156,
		0.074,0.214,
		0.068,0.233 };
	glEnableClientState(GL_VERTEX_ARRAY);

	glVertexPointer(2, GL_FLOAT, 0, &bat_body_vertex[0]);

//	glTranslatef(-0.5, 0.5, 0.0);
	//glScalef(2.0, 2.0, 0.0);
	glColor3f(0.0, 1.0, 1.0);
	glDrawArrays(GL_POLYGON, 0, 6);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();


	batman();
//	bat_body();
	//bat_leg();


	glutSwapBuffers();
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
	glutCreateWindow("My practice window: The Great Harshal");

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
	//ClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

}

void resize(int width, int height) {

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
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
