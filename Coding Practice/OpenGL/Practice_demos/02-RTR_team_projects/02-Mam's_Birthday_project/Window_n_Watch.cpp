// header files
#include <GL/freeglut.h>
#include<stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>
static GLfloat t = 0.0f;
static GLfloat t2 = 0.0f;

// global variable declarations
bool bIsFullScreen = false;

float lerp(float start, float end, float t)
{
	return start + t * (end - start);
}
void windowGrid()
{
	//Window gril Lines
	glEnable(GL_LINE_SMOOTH);
	glLineWidth(1.0);
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.275, 0.0);
	glVertex2f(-0.275, 0.55);
	glEnd();

	glLineWidth(1.0);
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.55, 0.275);
	glVertex2f(0.0, 0.275);
	glEnd();
	glDisable(GL_LINE_SMOOTH);
}
void window()
{
	
// --------- Window --------- 
	//outer window
	glPolygonMode(GL_BACK, GL_FILL);
	glBegin(GL_POLYGON);
	glColor3f(0.5, 0.5, 0.5);  ///window color
	glVertex3f(-0.6, -0.0, 0.0);//Bottom Left point
	glVertex3f(-0.6, 0.6, 0.0);
	glVertex3f(0.0, 0.6, 0.0);
	glVertex3f(0.0, 0.0, 0.0);//Bottom right point
	glEnd();
	
	//Borders for outer window
	glLineWidth(2.0);
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.6, -0.0);//Bottom Left point
	glVertex2f(-0.6, 0.6);
	glVertex2f(0.0, 0.6);
	glVertex2f(0.0, 0.0);//Bottom right point
	glEnd();
	//Borders for outer window Ends
//--------------------- Outer Window Ends ---------------------------//

	//Inner window
	glBegin(GL_POLYGON);
	glColor3f(lerp(0.0,0.5294,t), lerp(0.0,0.8078,t), lerp(0.0, 0.9215, t));// 135, 206, 235
	glVertex3f(-0.55, 0.0, 0.0);//BL point
	glVertex3f(-0.55, 0.55, 0.0);
	glVertex3f(0.0, 0.55, 0.0);
	glVertex3f(0.0, 0.0, 0.0);//BR point
	glEnd();

	
	//Borders Lines for inner window
	//glLineWidth(1.0);
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.55, 0.0);//BL
	glVertex2f(-0.55, 0.55);//TL
	glVertex2f(0.0, 0.55);//TR
	glVertex2f(0.0, 0.0);//BR
	glEnd();

//------------------ Inner Window Ends ------------------------//


	//Upper left corner line
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.6, 0.6);
	glVertex2f(-0.55, 0.55);
	glEnd();
	//---------

	//Window gril Lines
	glEnable(GL_LINE_SMOOTH);
	glLineWidth(1.0);
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.275, 0.0);
	glVertex2f(-0.275, 0.55);
	glEnd();

	glLineWidth(1.0);
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.55, 0.275);
	glVertex2f(0.0, 0.275);
	glEnd();
	glDisable(GL_LINE_SMOOTH);
}

void stars()
{
	//glEnable(GL_POINT_SMOOTH);
//	glPointSize(0.5);
	glBegin(GL_POINTS);
	//glColor3f(lerp(0.0,1.0,t2), lerp(0.0, 1.0, t2), lerp(0.0, 1.0, t2));
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(-0.45, 0.45);
	glVertex2f(-0.35, 0.25);
	glVertex2f(-0.25, 0.15);
	glVertex2f(-0.20, 0.23);
	glVertex2f(-0.29, 0.40);
	glVertex2f(-0.38, 0.12);
	glEnd();
}
void watch_border(float cx, float cy, float r, int num_segments)
{
	//watch border
	
	glEnable(GL_LINE_SMOOTH);
	glLineWidth(4.0);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2f(cx, cy);
	for (int i = 0; i <= num_segments; ++i) {
		float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);
		float x = r * cosf(theta);
		float y = r * sinf(theta);
		glVertex2f(cx + x, cy + y);
	}
	glEnd();
	glDisable(GL_LINE_SMOOTH);
	
	
}
void watch_on_Wall(float cx, float cy, float r, int num_segments)
{
	//Watch background
	glColor3f(0.8f, 0.8f, 0.8f);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(cx, cy);
	for (int i = 0; i <= num_segments; ++i) {
		float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);
		float x = r * cosf(theta);
		float y = r * sinf(theta);
		glVertex2f(cx + x, cy + y);
	}
	glEnd();

	//time showing dots
	glEnable(GL_POINT_SIZE);
	glPointSize(2.0);
	glBegin(GL_POINTS);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.4, 0.6);//center
	glVertex2f(0.4, 0.68);//12
	glVertex2f(0.48, 0.6);//3
	glVertex2f(0.4, 0.52);//6
	glVertex2f(0.32, 0.6);//9
	glEnd();
	glDisable(GL_POINT_SIZE);


	
}

void display(void)
{
	// code
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	window();
	windowGrid();
	stars();
	//glEnable(GL_LINE_WIDTH);
	watch_border(0.4f, 0.6f, 0.1f, 100);
	//glDisable(GL_LINE_WIDTH);
	watch_on_Wall(0.4f, 0.6f, 0.1f, 100);
	
	glutSwapBuffers();
}


// entry-point function
int main(int argc, char* argv[])
{
	// function declarations
	void initialize(void);
	void resize(int, int);
	void display(void);
	void keyboard(unsigned char, int, int);
	void mouse(int, int, int, int);
	void uninitialize(void);
	void update(int val);
	void update2(int val);

	// code
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowSize(800, 800);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Clouds");

	initialize();

	
	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutTimerFunc(1000 / 60, update, 0);
	glutTimerFunc(1000 / 60, update2, 0);
	glutCloseFunc(uninitialize);

	glutMainLoop();

	return(0);
}
void initialize(void)
{
	// code
	glClearColor(0.8f, 0.8f, 0.0f, 1.0f);
}
void resize(int width, int height)
{
	// code
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
}


void keyboard(unsigned char key, int x, int y)
{
	// code
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
	// code
	switch (button)
	{
	case GLUT_RIGHT_BUTTON:
		glutLeaveMainLoop();
		break;
	default:
		break;
	}

}


void update(int val)
{
	static int flag = 0;

	if (t < 1.0)
	{
		t += 0.008f;
		
	}
	
	glutPostRedisplay();
	glutTimerFunc(1000 / 60, update, 0);
}
void update2(int val)
{
	static int flag = 0;

	if (t2 < 1.0 && flag == 0)
	{
		t2 += 1.0f;
		if (t2 >= 1.0)
			flag = 1;
	}
	else if (t2 > 0.0f && flag == 1)
	{
		t2 -= 1.0f;
		if (t2 <= 0.0f)
			flag = 0;
	}

	glutPostRedisplay();
	glutTimerFunc(1000/60, update2, 0);
}

void uninitialize(void)
{
	// code
}







