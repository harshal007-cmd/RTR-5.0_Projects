#include<GL\freeglut.h>

#include<cmath>
int bIsScreenFull = false;
#define M_PI 3.145
const int width = 800;
const int height = 600;


void sineWave(GLfloat xStart, GLfloat yStart, GLfloat Amp, GLfloat WavCount)
{
	GLfloat angle;

	for (int i = 0; i < 100; i++)
	{
		float x = (float)i;
		angle = WavCount * M_PI * (i / 100.0);
		float y = yStart + Amp * sin(angle);

		glVertex2f(x, y);

		xStart = xStart + 0.01f;

	}


}

/*
void sineWave(float amplitude, float frequency, float phase, float yOffset)
{
	
	glBegin(GL_LINE_STRIP);
	glColor3f(1.0, 0.0, 0.0);
	for (int i = 0; i < 800; i++)
	{
		float x = static_cast<float>(i);
		float y = amplitude * sin(2 * M_PI * frequency * (x / width) + phase) + yOffset;
		//float y = 50.0f * sin(2 * 3.145f * 2.0f * (x / 800) + 0.0f)+100;
		glVertex2f(x, y);
	}
	glEnd();
	
}
*/
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
	glutInitWindowSize(width,height);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("My practice window: The Great Harshal");

	initialize();

	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	//glutTimerFunc(1000 / 60, update, 0);
	glutCloseFunc(uninitialize);

	glutMainLoop();

	return 0;


}

void initialize(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

}

void resize(int width, int height) {

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	gluOrtho2D(0.1, width, 0.1, height);
	glMatrixMode(GL_MODELVIEW);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glBegin(GL_LINE_STRIP);
	sineWave(-1.0,0.0,50.0,100);
	glEnd();
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
