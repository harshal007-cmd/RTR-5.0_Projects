//                                       || Shrii ||
//Header Files
#include <gl/freeglut.h>
#define _USE_MATH_DEFINES 1
#include<stdio.h>
#include<math.h>

#define ARRAY_LENGTH(arr) (sizeof(arr)/sizeof(arr[0]))

//Global variable declarations
bool bIsFullScreen = false;

typedef struct tag_vec2
{
	GLfloat data[2];
}vec2;

typedef struct tag_vec3
{
	GLfloat data[3];
}vec3;

vec2 triangle[3] = {
	{0.0f,0.5f},
	{-0.5f,-0.5f},
	{0.5f,-0.5f}
};

vec3 colors[3] = {
	{0.0f,0.0f,1.0f},
	{1.0f,0.0f,0.0f},
	{0.0f,1.0f,0.0f}
};

void MyglTransltef(vec2 vertices[], int size, GLfloat x, GLfloat y)
{

	for (int i = 0; i < size; i++)
	{
		vertices[i].data[0] += x;
		vertices[i].data[1] += y;
	}

}
void MyglScalef(vec2 vertices[], int size, GLfloat x, GLfloat y)
{

	for (int i = 0; i < size; i++)
	{
		vertices[i].data[0] *= x;
		vertices[i].data[1] *= y;
	}

}


void MyglRotatef(vec2 vertices[], int size, GLfloat angle)
{
	angle = M_PI * angle / 180.0;

	for (int i = 0; i < size; i++)
	{
		GLfloat tempx = vertices[i].data[0], tempy = vertices[i].data[1];

		vertices[i].data[0] = tempx * cosf(angle) - tempy * sinf(angle);
		vertices[i].data[1] = tempx * sinf(angle) + tempy * cosf(angle);

	}

}


//Entry-Point Function
int main(int argc, char* argv[])
{
	//Function Declarations
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
	glutCreateWindow("2D Trasnform");

	initialize();

	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutCloseFunc(uninitialize);

	glutMainLoop();

	return 0;
}

void initialize(void)
{
	//code
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void resize(int width, int height)
{
	//code
	if (height <= 0)
		height = 1;

	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (width <= height)
	{
		glOrtho(-1.0f, 1.0f, -1.0f * ((GLfloat)height / (GLfloat)width), 1.0f * ((GLfloat)height / (GLfloat)width), -1.0f, 1.0f);
	}
	else
	{
		glOrtho(-1.0f * ((GLfloat)width / (GLfloat)height), 1.0f * ((GLfloat)width / (GLfloat)height), -1.0f, 1.0f, -1.0f, 1.0f);
	}
}

void display(void)
{
	//code
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//glTranslatef(0, 0, 0);
	//glRotatef(45, 0, 0, 1);
	//glScalef(0.5, 0.5, 0.5);
	glBegin(GL_TRIANGLES);

	for (int i = 0; i < ARRAY_LENGTH(triangle); i++)
	{
		glColor3fv(colors[i].data);
		glVertex2fv(triangle[i].data);
	}

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

	case 'w':
		MyglTransltef(triangle, ARRAY_LENGTH(triangle), 0.0f, 0.5f);
		break;

	case 's':
		MyglTransltef(triangle, ARRAY_LENGTH(triangle), 0.0f, -0.5f);

		break;

	case 'd':
		MyglTransltef(triangle, ARRAY_LENGTH(triangle), 0.5f, 0.0f);

		break;

	case 'a':
		MyglTransltef(triangle, ARRAY_LENGTH(triangle), -0.5f, 0.0f);
		break;

	case 'q':
		MyglScalef(triangle, ARRAY_LENGTH(triangle), 1.5f, 1.5f);
		break;

	case 'e':
		MyglScalef(triangle, ARRAY_LENGTH(triangle), 0.5f, 0.5f);
		break;

	case 'r':
		MyglRotatef(triangle, ARRAY_LENGTH(triangle), 45.0);
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

	glutPostRedisplay();
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

//cl.exe /c /EHsc /I C:\freeglut\include OGL.cpp

//link.exe OGL.obj /LIBPATH:C:\freeglut\lib\x64 /SUBSYSTEM:CONSOLE
