#include<GL\freeglut.h>
void init()
{
	glClearColor(0.0, 0.0, 0.0,0.0);
	
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();

	glBegin(GL_TRIANGLE_STRIP);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(-50.0, 10.5, 0.0);
	glVertex3f(-10.5, -10.5, 0.0);
	glVertex3f(0.0, 10.5, 0.0);
	glVertex3f(1.5, 0.0, 0.0);
	glVertex3f(20.5, 10.5, 0.0);
	glEnd();
	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-50.0, 50.0, -50.0, 50.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void mouse(int button, int state, int x, int y)
{
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}