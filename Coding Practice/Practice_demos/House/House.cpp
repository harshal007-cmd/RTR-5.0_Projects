// Header files
#include <GL/freeglut.h>

//global variable declaration
bool bIsFullScreen = false;
void Mountains();
void sky();

//entry-point function

int main(int argc, char* argv[])
{
	//function declarations
	void initialize(void);
	void resize(int, int);
	void display(void);
	void keyboard(unsigned char, int, int);
	void mouse(int, int, int, int);
	void uninitialize(void);

	//code
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("My First RTR 5 Program : Harshal Vijay Sali");

	initialize();

	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutCloseFunc(uninitialize);

	glutMainLoop();
	return (0);

}

void initialize(void)
{
	//code
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

}

void resize(int width, int height)
{
	//code
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

}

void display(void)
{
	//code
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	sky();
	Mountains();
	//--- Big Rectangle code
	glBegin(GL_POLYGON);

	glColor3f(0.91f, 0.8f, 0.70f);
	glVertex3f(0.0f, -0.2f, 0.0f); //top left

	glColor3f(0.89f, 0.57f, 0.50f);
	glVertex3f(0.5f, -0.2f, 0.0f); //top right

	glColor3f(0.89f, 0.57f, 0.50f);
	glVertex3f(0.5f, -0.7f, 0.0f); //bottom right

	glColor3f(0.89f, 0.57f, 0.50f);
	glVertex3f(0.0f, -0.7f, 0.0f); //bottom left

	glEnd();
	//--Ends-----------

	
    //----------Door Rectangle code ------------
	glBegin(GL_POLYGON);	
	
	glColor3f(0.91f, 0.8f, 0.70f);
	glVertex3f(0.0f, -0.2f, 0.0f); //top left

	glColor3f(0.54f, 0.32f, 0.28f);
	glVertex3f(0.15f, -0.2f, 0.0f); //top right

	glColor3f(0.54f, 0.32f, 0.28f);
	glVertex3f(0.15f, -0.7f, 0.0f); //bottom right

	glColor3f(0.91f, 0.8f, 0.70f);
	glVertex3f(0.0f, -0.7f, 0.0f); //bottom left

	glEnd();
	// ---------------Door Rectagle code end---------------- */
	
	//----------- Triangle code -------------
	glBegin(GL_POLYGON);

	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, -0.2f, 0.0f); //bottom left

	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(0.075f, 0.0f, 0.0f); //top 

	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(0.15f, -0.2f, 0.0f); //bottom right

	glEnd();
	// ----------Triangle ends ----------
	
	// ---------- - Trapazium code------------ -
	glBegin(GL_POLYGON);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.15f, -0.2f, 0.0f); //bottom left

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.075f, 0.0f, 0.0f); //top left

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.425f, 0.0f, 0.0f); // top right

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.5f, -0.2f, 0.0f); //bottom right
	glEnd();
	// ----------Trapazium ends ----------	*/

	
	

// -------------- Small Rectangles 

	// Window 1
	glBegin(GL_POLYGON);

	glColor3f(0.412, 0.412, 0.412);
	glVertex3f(0.225f, -0.415f, 0.0f); //bottom left

	glColor3f(0.663, 0.663, 0.663);
	glVertex3f(0.225f, -0.3335f, 0.0f); //top left

	glColor3f(0.412, 0.412, 0.412);
	glVertex3f(0.3065f, -0.3335f, 0.0f); // top right

	glColor3f(0.412, 0.412, 0.412);
	glVertex3f(0.3065f, -0.415f, 0.0f); //bottom right

	glEnd();


	// 2nd Window 
	glBegin(GL_POLYGON);

	glColor3f(0.412, 0.412, 0.412);
	glVertex3f(0.345f, -0.415f, 0.0f); //bottom left

	glColor3f(0.663, 0.663, 0.663);
	glVertex3f(0.345f, -0.3335f, 0.0f); //top left

	glColor3f(0.412, 0.412, 0.412);
	glVertex3f(0.4265f, -0.3335f, 0.0f); // top right

	glColor3f(0.412, 0.412, 0.412);
	glVertex3f(0.4265f, -0.415f, 0.0f); //bottom right

	glEnd();
	//---------------- Small Rectangle Ends


	/*
	//Door 
	glBegin(GL_POLYGON);

	glColor3f(0.412, 0.412, 0.412);
	glVertex3f(0.345f, 0.035f, 0.0f); //bottom left

	glColor3f(0.663, 0.663, 0.663);
	glVertex3f(0.345f, 0.1165f, 0.0f); //top left

	glColor3f(0.412, 0.412, 0.412);
	glVertex3f(0.4265f, 0.1165f, 0.0f); // top right

	glColor3f(0.412, 0.412, 0.412);
	glVertex3f(0.4265f, 0.035f, 0.0f); //bottom right

	glEnd();

	*/

	

	//Axis lines
	glBegin(GL_LINES);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, -1.0, 0.0);
	
	glVertex3f(-1.0, 0.0, 0.0);
	glVertex3f(1.0, 0.0, 0.0);
	glEnd();
	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
	//code
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
	//code
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
	//code 
}

void Mountains()
{

	//Mid mountain
	glBegin(GL_POLYGON);
	glColor3f(0.0f, 0.41f, 0.0f);//dark green
	glVertex3f(0.15f, 0.75f, 0.0);//top
	glColor3f(0.0f, 1.0f, 0.0f);//dark green
	glVertex3f(0.30f, 0.25f, 0.0);//right
	glColor3f(0.0f, 0.81f, 0.0f);//dark green
	glVertex3f(-0.30f, 0.25f, 0.0);//left
	glEnd();

	//Left Mountain
	glBegin(GL_POLYGON);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, 0.25f, 0.0);//left
	glVertex3f(0.0f, 0.25f, 0.0);//

	glColor3f(0.0f, 0.41f, 0.0f);//dark green
	glVertex3f(-0.75f, 0.75f, 0.0);//top

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 0.25f, 0.0);//
	glEnd();


	
	//Right Mountain
	glBegin(GL_POLYGON);
	glColor3f(0.0f, 0.9f, 0.0f);
	glVertex3f(1.0f, 0.25f, 0.0);//right
	
	glColor3f(0.0f, 0.61f, 0.0f);//dark green
	glVertex3f(-0.3f, 0.25f, 0.0);//left
	
	glColor3f(0.0f, 0.9f, 0.0f);//dark green
	glVertex3f(0.70f, 0.95f, 0.0);//topmost
	glEnd();
}

void sky()
{
	glBegin(GL_POLYGON);
	glColor3f(0.58f, 0.88f, 0.98f);
	
	glVertex3f(-1.0f, 0.25f, 0.0f);// bottom left
	glVertex3f(1.0f, 0.25f, 0.0f);// bottom right
	
	glVertex3f(1.0f, 1.0f, 0.0f);// top right
	glVertex3f(-1.0f, 1.0f, 0.0f);// top left
	glEnd();

}




