// header files
#include <GL/freeglut.h>
#include<stdlib.h>
GLfloat diffuseMaterial[4] = { 0.5, 0.5, 0.5, 1.0 };
void init(void)
{
	GLfloat mat_specular[] = { 0.8, 0.8, 0.8, 1.0 }; 
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMaterial);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 50.0);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
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
	glutInitWindowSize(900, 900);
	glutInitWindowPosition(100, 100); glutCreateWindow(argv[0]);
	init(); 
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutMouseFunc(mouse);
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
*/
void mouse(int button, int state, int x, int y)
{
	switch (button) {
	case GLUT_LEFT_BUTTON:
				if (state == GLUT_DOWN) { /* change red */
					diffuseMaterial[0] += 0.1;
					if (diffuseMaterial[0] > 1.0)
						diffuseMaterial[0] = 0.0;
					glColor4fv(diffuseMaterial);
					glutPostRedisplay();
				}
				break; 
	case GLUT_MIDDLE_BUTTON:
						if (state == GLUT_DOWN) { /* change green */
							diffuseMaterial[1] += 0.1;
							if (diffuseMaterial[1] > 1.0)
								diffuseMaterial[1] = 0.0;
							glColor4fv(diffuseMaterial)
								;
							glutPostRedisplay();
						}
						break; 
	case GLUT_RIGHT_BUTTON:
								if (state == GLUT_DOWN) { /* change blue */
									diffuseMaterial[2] += 0.1;
									if (diffuseMaterial[2] > 1.0)
										diffuseMaterial[2] = 0.0;
									glColor4fv(diffuseMaterial);
									glutPostRedisplay();
								}
								break;
						default:
							break;
	}

}
void uninitialize(void)
{
	// code
}
