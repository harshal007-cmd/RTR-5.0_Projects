// header files
#include <GL/freeglut.h>

#define _USE_MATH_DEFINES
#include <math.h>

// global variable declarations
bool bIsFullScreen = false;

GLenum currenttype = GL_POLYGON;

void House(void);
void circle(void);
void rooflines(void);
void windowgrid(void);

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
	glutCreateWindow("House");

	initialize();

	
	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutCloseFunc(uninitialize);

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

	House();
	circle();
	rooflines();
	windowgrid();
	
	glutSwapBuffers();
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

void uninitialize(void)
{
	// code
}


// House()
void House(void)
{	
	
	glBegin(GL_POLYGON); // Rectangle - 3	

	glColor3f(0.412, 0.412, 0.412); // Dim Grey
	glVertex3f(0.3f, 0.0f, 0.0f);

	glColor3f(0.663, 0.663, 0.663); // Dark Grey
	glVertex3f(0.3f, 0.5f, 0.0f); 

	glColor3f(0.412, 0.412, 0.412); // Dim Grey
	glVertex3f(0.7f, 0.5f, 0.0f);

	glColor3f(0.412, 0.412, 0.412); // Dim Grey
	glVertex3f(0.7f, 0.0f, 0.0f);

	glEnd();

	glBegin(GL_POLYGON); // Rectangle - 4

	glColor3f(0.412, 0.412, 0.412); // Dim Grey
	glVertex3f(0.0f, 0.0f, 0.0f);

	glColor3f(0.663, 0.663, 0.663);  // Dark Grey
	glVertex3f(0.0f, 0.5f, 0.0f);

	glColor3f(0.412, 0.412, 0.412); // Dim Grey
	glVertex3f(0.3f, 0.5f, 0.0f);

	glColor3f(0.412, 0.412, 0.412); // Dim Grey
	glVertex3f(0.3f, 0.0f, 0.0f);

	glEnd();

	glBegin(GL_POLYGON); // Polygon - 2

	glColor3f(0.545, 0.271, 0.075); // Saddle Brown
	glVertex3f(0.3f, 0.5f, 0.0f);

	glColor3f(0.804, 0.522, 0.247); // Peru
	glVertex3f(0.15f, 0.7f, 0.0f);

	glColor3f(0.804, 0.522, 0.247); // Peru
	glVertex3f(0.55f, 0.7f, 0.0f);

	glColor3f(0.545, 0.271, 0.075); // Saddle Brown
	glVertex3f(0.7f, 0.5f, 0.0f);

	glEnd();


	glBegin(GL_POLYGON); // Triangle - 1

	glColor3f(0.804, 0.522, 0.247); // Peru
	glVertex3f(0.0f, 0.5f, 0.0f);

	glColor3f(0.545, 0.271, 0.075); // Saddle Brown
	glVertex3f(0.15f, 0.7f, 0.0f);

	glColor3f(0.545, 0.271, 0.075); // Saddle Brown
	glVertex3f(0.3f, 0.5f, 0.0f);

	glEnd();

	
	// glColor3f(0.66, 0.66, 0.66);
	glBegin(GL_POLYGON); // Window - L	

	glColor3f(0.529, 0.808, 0.980); // Light Sky Blue
	glVertex3f(0.35f, 0.15f, 0.0f);

	glColor3f(0.118, 0.564, 1.0); // Deep Sky Blue
	glVertex3f(0.35f, 0.35f, 0.0f);

	glColor3f(0.529, 0.808, 0.980); // Light Sky Blue
	glVertex3f(0.45f, 0.35f, 0.0f);

	glColor3f(0.529, 0.808, 0.980); // Light Sky Blue
	glVertex3f(0.45f, 0.15f, 0.0f);

	glEnd();

	glColor3f(0.529, 0.808, 0.980);
	// glColor3f(0.66, 0.66, 0.66);
	glBegin(GL_POLYGON); // Window - R	

	glColor3f(0.529, 0.808, 0.980); // Light Sky Blue
	glVertex3f(0.55f, 0.15f, 0.0f);

	glColor3f(0.118, 0.564, 1.0); // Deep Sky Blue
	glVertex3f(0.55f, 0.35f, 0.0f);

	glColor3f(0.529, 0.808, 0.980); // Light Sky Blue
	glVertex3f(0.65f, 0.35f, 0.0f);

	glColor3f(0.529, 0.808, 0.980); // Light Sky Blue
	glVertex3f(0.65f, 0.15f, 0.0f);

	glEnd();

	
	glBegin(GL_POLYGON); // Door - 1

	glColor3f(0.804, 0.522, 0.247); // Peru
	glVertex3f(0.07f, 0.0f, 0.0f);

	glColor3f(0.804, 0.522, 0.247); // Peru
	glVertex3f(0.07f, 0.27f, 0.0f);

	glColor3f(0.545, 0.271, 0.075); // Saddle Brown
	glVertex3f(0.23f, 0.27f, 0.0f);

	glColor3f(0.545, 0.271, 0.075); // Saddle Brown
	glVertex3f(0.23f, 0.0f, 0.0f);

	glEnd();

	glColor3f(0.647, 0.165, 0.165); // Brown
	glBegin(GL_LINE_STRIP); // Door Frame - 1

	glVertex3f(0.07f, 0.0f, 0.0f);
	glVertex3f(0.07f, 0.27f, 0.0f);
	glVertex3f(0.23f, 0.27f, 0.0f);
	glVertex3f(0.23f, 0.0f, 0.0f);

	glEnd();

}

// House - Circle
void circle(void)
{
	
	glBegin(GL_POLYGON);

	float radius = 0.035f;
	float x_centre = 0.15f;
	float y_centre = 0.5656f;
	for (int i = 0; i < 1000; i++)
	{
		float angle = 2.0f * M_PI * i / 1000;
		glVertex2f(x_centre + radius * cos(angle), y_centre + radius * sin(angle));
		glColor3f(0.647, 0.165, 0.165); // Brown
	
	}
	glEnd();
}
void rooflines(void)
{
	float x1 = 0.325f;
	float x2 = 0.175f;
	float y1 = 0.50f;
	float y2 = 0.70f;

	for (int line_count = 0; line_count < 16; line_count++)
	{
		glColor3f(0.698, 0.133, 0.133); // Fire Brick
		glBegin(GL_LINES);

		glVertex3f(x1, y1, 0);
		glVertex3f(x2, y2, 0);

		glEnd();
		x1 = x1 + 0.025;
		x2 = x2 + 0.025;
	}
}

// Window Grid
void windowgrid(void)
{
	glColor3f(0.682, 0.933, 0.933);  // Pale Turquoise
	glBegin(GL_LINES); 

	glVertex3f(0.40f, 0.15f, 0.0f);  // Window - L
	glVertex3f(0.40f, 0.35f, 0.0f);

	glVertex3f(0.35f, 0.25f, 0.0f);  
	glVertex3f(0.45f, 0.25f, 0.0f);

	glVertex3f(0.60f, 0.15f, 0.0f);  // Window - R
	glVertex3f(0.60f, 0.35f, 0.0f);

	glVertex3f(0.55f, 0.25f, 0.0f);  
	glVertex3f(0.65f, 0.25f, 0.0f);

	glEnd();

}





