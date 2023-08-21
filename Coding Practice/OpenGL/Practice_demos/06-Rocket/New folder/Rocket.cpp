// header files
#include <GL/freeglut.h>

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
void Rocket()
{
	//Middle Cylinder
	glBegin(GL_POLYGON);
	glColor3f(0.9, 0.9, 0.9);
	glVertex3f(-0.045, -0.75, 0.0);//bottom left
	glVertex3f(-0.045, -0.20, 0.0);//top left
	
	glColor3f(0.4, 0.4, 0.4);
	glVertex3f(0.045, -0.20, 0.0);//top right
	glVertex3f(0.045, -0.75, 0.0);//bottom right
	glEnd();

	//Middle Cylinder Head Triangle
	glBegin(GL_TRIANGLES);
	
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(-0.045, -0.20);//bottom left
	
	
	glColor3f(0.7, 0.7, 0.7);
	glVertex2f(0.0, -0.10);   //top
	glVertex2f(0.045, -0.20);  //bottom right
		
	glEnd();

	//Middle cylinder exaust cover
	glBegin(GL_POLYGON);
	glColor3f(0.3, 0.3, 0.3);
	glVertex3f(-0.053, -0.79, 0.0);//bottom left
	glVertex3f(-0.045, -0.75, 0.0);//top left
	glVertex3f(0.045, -0.75, 0.0);//top right
	glVertex3f(0.053, -0.79, 0.0);//bottom right
	glEnd();

	
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx Middle Full Cylinder Ends xxxxxxxxxxxxxxxxxxxxxxxxxx



	//Left Cylinder
	glBegin(GL_POLYGON);
	glColor3f(0.9, 0.9, 0.9);
	glVertex3f(-0.0875, -0.72, 0.0);//bottom left
	glVertex3f(-0.0875, -0.30, 0.0);//top left
	
	glColor3f(0.4, 0.4, 0.4);
	glVertex3f(-0.045, -0.30, 0.0);//top right
	glVertex3f(-0.045, -0.72, 0.0);//bottom right
	glEnd();

	//Left Cylinder Head Triangle
	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(-0.0875, -0.30);//bottom left
	
	glColor3f(0.7, 0.7, 0.7);
	glVertex2f(-0.06625, -0.25);   //top
	glVertex2f(-0.045, -0.30);  //bottom right
	glEnd();

	//Left cylinder exaust cover
	glBegin(GL_POLYGON);
	glColor3f(0.3, 0.3, 0.3);
	glVertex3f(-0.0950, -0.74, 0.0);//bottom left
	glVertex3f(-0.0875, -0.72, 0.0);//top left
	glVertex3f(-0.045, -0.72, 0.0);//top right
	glVertex3f(-0.040, -0.74, 0.0);//bottom right
	glEnd();

	
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx Left Full Cylinder Ends xxxxxxxxxxxxxxxxxxxxxxxxxx

	//Right Cylinder
	glBegin(GL_POLYGON);
	glColor3f(0.9, 0.9, 0.9);
	glVertex3f(0.045, -0.72, 0.0);//bottom left
	glVertex3f(0.045, -0.30, 0.0);//top left
	
	glColor3f(0.4, 0.4, 0.4);
	glVertex3f(0.0875, -0.30, 0.0);//top right
	glVertex3f(0.0875, -0.72, 0.0);//bottom right
	glEnd();
	
	//Right Cylinder Head Triangle
	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(0.0875, -0.30);//bottom left
	
	glColor3f(0.7, 0.7, 0.7);
	glVertex2f(0.06625, -0.25);   //top
	glVertex2f(0.045, -0.30);  //bottom right
	glEnd();

	//Right cylinder exaust cover
	glBegin(GL_POLYGON);
	glColor3f(0.3, 0.3, 0.3);
	glVertex3f(0.040, -0.74, 0.0);//bottom left
	glVertex3f(0.045, -0.72, 0.0);//top left
	glVertex3f(0.0875, -0.72, 0.0);//top right
	glVertex3f(0.0950, -0.74, 0.0);//bottom right
	glEnd();

//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx Right Full Cylinder Ends xxxxxxxxxxxxxxxxxxxxxxxxxx

}



// entry-point function
int main(int argc, char* argv[])
{
	// function declarations
	void initialize(void);
	void resize(int, int);
	void display(void);

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

	glutMainLoop();

	return(0);
}
void initialize(void)
{
	// code
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	

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

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	GridLines();
	Rocket();

//	Points();


	glutSwapBuffers();
}


