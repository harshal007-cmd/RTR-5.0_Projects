// header files
#include <GL/freeglut.h>
#include<stdlib.h>

void init(void)
{
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 }; 
//	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 }; 
	GLfloat white_light[] = { 1.0, 0.0, 0.0, 1.0 }; 
	GLfloat white_light2[] = { 1.0, 0.7, 0.7, 0.0 }; 
	GLfloat lmodel_ambient[] = { 0.2, 0.1, 0.1, 1.0 }; 
	
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
//	glMaterialfv(GL_FRONT, GL_SPECULAR, light_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
//	glMaterialfv(GL_LIGHT0, GL_DIFFUSE, white_light);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white_light2);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
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

	// code
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100); glutCreateWindow(argv[0]);
	init(); 
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutMainLoop();
	return 0;


}
void initialize(void)
{
	// code
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
}
void resize(int width, int height)
{
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (width <= height)
		glOrtho(-1.5, 1.5, -1.5 * (GLfloat)height / (GLfloat)width, 1.5 * (GLfloat)height / (GLfloat)width, -10.0, 10.0);
	else
		glOrtho(-1.5 * (GLfloat)width / (GLfloat)height,1.5 * (GLfloat)width / (GLfloat)height, -1.5, 1.5, -10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void display(void)
{
	// code
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutSolidSphere(1.0, 100, 100);
	glFlush();

//	glutSwapBuffers();
}
/*
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

*/
void uninitialize(void)
{
	// code
}
