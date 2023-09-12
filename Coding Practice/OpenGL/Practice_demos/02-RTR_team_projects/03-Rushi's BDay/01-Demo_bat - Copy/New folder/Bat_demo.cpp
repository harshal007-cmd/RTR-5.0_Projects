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

GLfloat bat_body[] = { 0.273, 0.241 ,
					0.196,0.279,
					0.197,0.321,
					0.235,0.354,
					0.236,0.394,
					0.325,0.388,
					0.326,0.348,
					0.355,0.317,
					0.353,0.277
};
void batman_body()
{	
	glColor3f(0.5, 0.5, 0.5);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, &bat_body[0]);
	glDrawArrays(GL_POLYGON, 0, 9);

	//belt
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 0.0);
		glVertex2f(0.235, 0.393);
		glVertex2f(0.235, 0.422);
		glVertex2f(0.330, 0.418);
		glVertex2f(0.328, 0.390);
	glEnd();
}

void batman()
{
//	glTranslatef(0.0, 0.2, 0.0);
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 0.0);
		glVertex2f(0.273, 0.241);//center pt, cape knot near neck
		glVertex2f(0.155, 0.317);
		glVertex2f(0.155, 0.250);
		glVertex2f(0.243, 0.215);
		glVertex2f(0.248, 0.171);
		glVertex2f(0.252, 0.115);
		glVertex2f(0.261, 0.150);
		glVertex2f(0.281, 0.151);
		glVertex2f(0.288, 0.112);
		glVertex2f(0.296, 0.165);
		glVertex2f(0.301, 0.214);
		glVertex2f(0.391, 0.246);
		glVertex2f(0.398, 0.310);
	glEnd();
	
}



void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	//glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0.0, 0.2, 0.0);
	glScalef(1.0, -1.0, 1.0);
	batman_body();
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
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

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
