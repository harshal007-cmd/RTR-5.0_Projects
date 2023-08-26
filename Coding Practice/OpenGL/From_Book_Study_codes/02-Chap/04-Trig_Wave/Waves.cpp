#include<GL\freeglut.h>

#include<cmath>
int bIsScreenFull = false;
#define M_PI 3.145
const int width = 800;
const int height = 600;


void sineWave()
{
	GLfloat angle;

	for ( angle_wave ; angle_wave <= 2 * pi ; angle_wave = angle_wave + 0.001f)
    {
        glColor3f(1.0,1.0,1.0);
        float x_edge =  x;
        float y_edge = radius* sin(angle_wave);
        glVertex3f(x_edge, y + y_edge , 0.0f);
        glColor3f(1.0,1.0,1.0);
        glVertex3f(x_edge,y + y_edge, 0.0f);
        x = x + 0.001f;
        if (x > 1.0f)
            break;
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
	glBegin(GL_LINE);
	sineWave(-1.0,0.0);
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
