#include<gl\freeglut.h>
#define _USE_MATH_DEFINES 0
#include<math.h>
#include"MyMath.h"
#define ARRAY_LENGTH(arr) (sizeof(arr)/sizeof(arr[0]))

GLfloat fade = 0.0f;

static GLfloat t =0.0f;

vec2 p0={-0.5f,0.0f};
vec2 p1={-0.3f,0.5f};
vec2 p2={0.3f,0.5f};
vec2 p3={0.5f,0.0f};
vec2 c1,c2,c3;
vec2 a1,a2,p;

vec2* selected=&p0;

void vec2_translation(vec2*result,float x,float y)
{
	result->data[0]+=x;
	result->data[1]+=y;
	
}

float lerp(float start, float end, float t)
{
	return start + t * (end - start);
}


int main(int argc, char* argv[])
{
	void init(void);
	void display(void);
	void resize(int, int);
	void update(int val);
    void keyboard(unsigned char key,int x,int y);


	//code
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("GRP");

	init();

	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(1000 / 60, update, 0);
	glutMainLoop();
	

	return 0;
}

void init(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void resize(int width, int height)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glEnable(GL_BLEND);

	
}
void keyboard(unsigned char key,int x,int y)
{
	switch(key)
	{
		case 'w':
		vec2_translation(selected,0.0f,0.1f);

		
		break;

		case 's':
		vec2_translation(selected,0.0f,-0.1f);

		

		break;

		case 'd':
		vec2_translation(selected,0.1f,0.0f);

  			 //vec2_translation(p1,0.01,0);
		break;

		case 'a':
		vec2_translation(selected,-0.1f,0.0f);

		break;

		case 'q':
		if(t <= 1.0f)
			t+=0.1f;
		break;

		case 'e':
		if(t>0.1f)
			t-=0.1f;
		break;

		case '1':
		selected=&p0;
		break;

		case '2':
		selected=&p1;
		break;

		case '3':
		selected=&p2;

		break;

		case '4':
		selected=&p3;
		break;

	}
}


void update(int val)
{

	if (fade < 1.0)
		fade += 0.005f;

	glutPostRedisplay();

	glutTimerFunc(1000 / 60, update, 0);
}

void display(void)
{
	//code
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    glEnable(GL_LINE_SMOOTH);
	 glEnable(GL_POINT_SMOOTH);
	
	vec2_lerp(&c1,&p0,&p1,t);
	vec2_lerp(&c2,&p1,&p2,t);
	vec2_lerp(&c3,&p2,&p3,t);
	
	vec2_lerp(&a1,&c1,&c2,t);
	vec2_lerp(&a2,&c2,&c3,t);
	vec2_lerp(&p,&a1,&a2,t);
	

	
    glLineWidth(5);
  
	glColor3f(0.0f,1.0f,0.0f);
	
	glBegin(GL_LINES);
		glVertex2fv(p0.data);
		glVertex2fv(p1.data);

		glVertex2fv(p1.data);
		glVertex2fv(p2.data);
		
		glVertex2fv(p2.data);
		glVertex2fv(p3.data);
	/*
	glColor3f(0.0f,0.0f,1.0f);
		
		glVertex2fv(c1.data);
		glVertex2fv(c2.data);
		
		glVertex2fv(c2.data);
		glVertex2fv(c3.data);
	
	glColor3f(1.0f,0.0f,1.0f);
		
		glVertex2fv(a1.data);
		glVertex2fv(a2.data);
*/
	glEnd();
    
	
   glPointSize(5);
	glColor3f(1.0f,0.0f,0.0f);
		
		glBegin(GL_POINTS);
		glVertex2fv(c1.data);
		glVertex2fv(c2.data);
		glVertex2fv(c3.data);
		glVertex2fv(a1.data);
		glVertex2fv(a2.data);
	
		glColor3f(1.0f,0.0f,1.0f);
		glVertex2fv(p.data);
	glEnd();


	glBegin(GL_LINE_STRIP);
		glColor3f(0.0f,0.0f,0.0f);

		for(float i=0.0f;i<=1.1f;i=i+0.1f)
		{
			
			vec2_lerp(&c1,&p0,&p1,i);
			vec2_lerp(&c2,&p1,&p2,i);
			vec2_lerp(&c3,&p2,&p3,i);
			
			vec2_lerp(&a1,&c1,&c2,i);
			vec2_lerp(&a2,&c2,&c3,i);
			vec2_lerp(&p,&a1,&a2,i);
			

			glVertex2fv(p.data);
		}

	glEnd();

	glutSwapBuffers();
}



