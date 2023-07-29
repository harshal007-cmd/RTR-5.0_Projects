// header files
#include <GL\freeglut.h>


float x = 0, y = 0;
float rocket_speed = 0.0004f;
float rocket_acceleration = 0.000003f;

// global variable declarations
void GridLines()
{
	
	//grid lines
	glBegin(GL_LINES);
	glColor3f(0.0, 0.8, 0.0);
	glVertex3f(-1.0, 0.0, 0.0);
	glVertex3f(1.0, 0.0, 0.0);
	glVertex3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, -1.0, 0.0);
	glEnd();

}
void background()
{
	//ground
	glBegin(GL_POLYGON);
	glColor3f(0.7, 0.39, 0.1137);
	glVertex3f(-1.0, -1.0, 0.0);//bl
	glVertex3f(-1.0, -0.75, 0.0);//tl
	glVertex3f(1.0, -0.75, 0.0);//tr
	glVertex3f(1.0, -1.0, 0.0);//br
	glEnd();

	//sky
	glBegin(GL_POLYGON);
	glColor3f(0.40, 0.80, 0.92);
	glVertex3f(-1.0, -0.75, 0.0);//bl
	glVertex3f(-1.0, 1.0, 0.0);//tl
	glVertex3f(1.0, 1.0, 0.0);//tr
	glVertex3f(1.0, -0.75, 0.0);
	glEnd();

}

void Rocket()
{
	//Middle Cylinder
	glBegin(GL_POLYGON);
	glColor3f(0.9, 0.9, 0.9);
	glVertex3f(-0.045, y- 0.75, 0.0);//bottom left
	glVertex3f(-0.045, y- 0.20, 0.0);//top left
	
	glColor3f(0.4, 0.4, 0.4);
	glVertex3f(0.045, y- 0.20, 0.0);//top right
	glVertex3f(0.045, y- 0.75, 0.0);//bottom right
	glEnd();

	//Middle Cylinder Head Triangle
	glBegin(GL_TRIANGLES);
	
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(-0.045, y-0.20);//bottom left
	
	
	glColor3f(0.7, 0.7, 0.7);
	glVertex2f(0.0, y-0.10);   //top
	glVertex2f(0.045, y-0.20);  //bottom right
		
	glEnd();
		
	//Middle cylinder exaust cover
	glBegin(GL_POLYGON);
	glColor3f(0.3, 0.3, 0.3);
	glVertex3f(-0.053, y-0.79, 0.0);//bottom left
	glVertex3f(-0.045, y-0.75, 0.0);//top left
	glVertex3f(0.045, y-0.75, 0.0);//top right
	glVertex3f(0.053, y-0.79, 0.0);//bottom right
	glEnd();

	//Middle Cylinder exhust fire
	glBegin(GL_TRIANGLES);

	glColor3f(1.0, 1.0, 0.0);
	glVertex2f(-0.053, y - 0.79);//top left
	glVertex2f(0.053, y - 0.79);  //top right


	glColor3f(0.9, 0.0, 0.0);
	glVertex2f(0.0, y - 0.9);   //down

	glEnd();


	
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx Middle Full Cylinder Ends xxxxxxxxxxxxxxxxxxxxxxxxxx



	//Left Cylinder
	glBegin(GL_POLYGON);
	glColor3f(0.9, 0.9, 0.9);
	glVertex3f(-0.0875, y-0.72, 0.0);//bottom left
	glVertex3f(-0.0875, y-0.30, 0.0);//top left
	
	glColor3f(0.4, 0.4, 0.4);
	glVertex3f(-0.045, y-0.30, 0.0);//top right
	glVertex3f(-0.045, y-0.72, 0.0);//bottom right
	glEnd();

	//Left Cylinder Head Triangle
	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(-0.0875, y-0.30);//bottom left
	
	glColor3f(0.7, 0.7, 0.7);
	glVertex2f(-0.06625, y-0.25);   //top
	glVertex2f(-0.045, y-0.30);  //bottom right
	glEnd();

	//Left cylinder exaust cover
	glBegin(GL_POLYGON);
	glColor3f(0.3, 0.3, 0.3);
	glVertex3f(-0.0950, y-0.74, 0.0);//bottom left
	glVertex3f(-0.0875, y-0.72, 0.0);//top left
	glVertex3f(-0.045, y-0.72, 0.0);//top right
	glVertex3f(-0.040, y-0.74, 0.0);//bottom right
	glEnd();

	//Left Cylinder exhust fire
	glBegin(GL_TRIANGLES);

	glColor3f(1.0, 1.0, 0.0);
	glVertex2f(-0.0950, y - 0.74);//top left
	glVertex2f(-0.040, y - 0.74);  //top right


	glColor3f(0.9, 0.0, 0.0);
	glVertex2f(-0.06625, y - 0.82);   //down

	glEnd();


	
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx Left Full Cylinder Ends xxxxxxxxxxxxxxxxxxxxxxxxxx

	//Right Cylinder
	glBegin(GL_POLYGON);
	glColor3f(0.9, 0.9, 0.9);
	glVertex3f(0.045, y-0.72, 0.0);//bottom left
	glVertex3f(0.045, y-0.30, 0.0);//top left
	
	glColor3f(0.4, 0.4, 0.4);
	glVertex3f(0.0875, y-0.30, 0.0);//top right
	glVertex3f(0.0875, y-0.72, 0.0);//bottom right
	glEnd();
	
	//Right Cylinder Head Triangle
	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(0.0875, y-0.30);//bottom left
	
	glColor3f(0.7, 0.7, 0.7);
	glVertex2f(0.06625, y-0.25);   //top
	glVertex2f(0.045, y-0.30);  //bottom right
	glEnd();

	//Right cylinder exaust cover
	glBegin(GL_POLYGON);
	glColor3f(0.3, 0.3, 0.3);
	glVertex3f(0.040, y-0.74, 0.0);//bottom left
	glVertex3f(0.045, y-0.72, 0.0);//top left
	glVertex3f(0.0875, y-0.72, 0.0);//top right
	glVertex3f(0.0950, y-0.74, 0.0);//bottom right
	glEnd();


	//Left Cylinder exhust fire
	glBegin(GL_TRIANGLES);

	glColor3f(1.0, 1.0, 0.0);
	glVertex2f(0.040, y - 0.74);//top left
	glVertex2f(0.0950, y - 0.74);  //top right


	glColor3f(0.9, 0.0, 0.0);
	glVertex2f(0.06625, y - 0.82);   //down

	glEnd();


//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx Right Full Cylinder Ends xxxxxxxxxxxxxxxxxxxxxxxxxx

}

void updateRocket() {
	rocket_speed += rocket_acceleration;
	y += rocket_speed;

}
void updateScene(int val)
{
	updateRocket();
	glutPostRedisplay();
	glutTimerFunc(15, updateScene, 0);
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

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowSize(800, 800);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Rocket");

	initialize();


	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutTimerFunc(0, updateScene, 0);
	
	glutMainLoop();

	return(0);
}
void initialize(void)
{
	// code
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

}
void resize(int width, int height)
{
	// code
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
}

void display(void)
{
	// code
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	//GridLines();
	background();
	Rocket();

	glutSwapBuffers();
}
