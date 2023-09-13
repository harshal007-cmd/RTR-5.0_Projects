#include<GL\freeglut.h>

int bIsScreenFull = false;

GLfloat batman_vertex[] = { 0.399,0.310,
							0.393,0.243,
							0.303,0.215,
							0.295,0.166,
							0.286,0.114,
							0.281,0.149,
							0.261,0.152,
							0.251,0.119,
							0.247,0.174,
							0.246,0.216,
							0.157,0.248,
							0.151,0.318,
							0.275,0.237,
							0.399,0.310

};

GLfloat bat_body[] = { 0.273, 0.241 ,
						0.196,0.279,
						0.197,0.321,
						0.235,0.354,
						0.236,0.394,
						0.325,0.388,
						0.326,0.348,
						0.355,0.317,
						0.353,0.277
};

GLfloat back_cape[] = { 0.395,0.270,
						0.155,0.276,
						0.187,0.728,
						0.221,0.701,
						0.261,0.718,
						0.299,0.689,
						0.335,0.714,
						0.367,0.693,
						0.402,0.711

};

GLfloat bat_leftHand[] = { 0.199,0.282,
						0.187,0.356,
						0.191,0.422,
						0.151,0.407,
						0.162,0.363,
						0.154,0.320
};

GLfloat bat_leftForearm[] = {
							0.189,0.421,
							0.141,0.401,
							0.163,0.432,
							0.151,0.433,
							0.176,0.472,
							0.195,0.467

};
GLfloat bat_leftFist[] = {
							0.195,0.467,
							0.204,0.474,
							0.211,0.493,
							0.199,0.507,
							0.181,0.507,
							0.176,0.472

};

GLfloat bat_rightHand[] = { 0.399,0.310,
							0.395,0.356,
							0.409,0.396,
							0.375,0.414,
							0.373,0.363,
							0.350,0.280

};
GLfloat bat_rightForearm[] = { 0.377,0.413,
							0.423,0.388,
							0.403,0.426,
							0.413,0.428,
							0.393,0.453,
							0.379,0.459
};
GLfloat bat_rightFist[] = { 0.394,0.455,
							0.391,0.492,
							0.373,0.500,
							0.361,0.487,
							0.375,0.455
	
};

void BackCape()
{
	glColor3f(0.3, 0.3, 0.3);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, &back_cape[0]);
	glDrawArrays(GL_POLYGON, 0, 9);


}


void batman_body()
{	
	//Upper body-------------------
	glColor3f(0.5, 0.5, 0.5);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, &bat_body[0]);
	glDrawArrays(GL_POLYGON, 0, 9);

//Legs-----------------
	/////Left leg
	glBegin(GL_POLYGON);//thigh part
		glColor3f(0.0, 0.0, 0.0);
		glVertex2f(0.285, 0.468);
		glVertex2f(0.269, 0.569);
		glVertex2f(0.247, 0.566);
		glVertex2f(0.237, 0.426);
	glEnd();
	glBegin(GL_POLYGON);//lower leg
		glColor3f(0.0, 0.0, 0.0);
		glVertex2f(0.269, 0.569);
		glVertex2f(0.267, 0.648);
		glVertex2f(0.265, 0.725);
		glVertex2f(0.249, 0.725);
		glVertex2f(0.229, 0.613);
		glVertex2f(0.247, 0.566);
	glEnd();
	glBegin(GL_POLYGON);//shoes
		glColor3f(0.0, 0.0, 0.0);
		glVertex2f(0.265, 0.725);
		glVertex2f(0.277, 0.736);
		glVertex2f(0.246, 0.740);
		glVertex2f(0.249, 0.725);
	glEnd();

	//Right Leg
	glBegin(GL_POLYGON);//thigh part right
		glColor3f(0.0, 0.0, 0.0);
		glVertex2f(0.285, 0.468);
		glVertex2f(0.313, 0.573);
		glVertex2f(0.335, 0.572);
		glVertex2f(0.329, 0.420);
		glVertex2f(0.237, 0.426);
	glEnd();
	glBegin(GL_POLYGON);//lower right leg
		glColor3f(0.0, 0.0, 0.0);
		glVertex2f(0.335, 0.572);
		glVertex2f(0.352, 0.601);
		glVertex2f(0.353, 0.694);
		glVertex2f(0.343, 0.714);
		glVertex2f(0.329, 0.714);
		glVertex2f(0.313, 0.573);
	glEnd();
	glBegin(GL_POLYGON);//right shoe
		glColor3f(0.0, 0.0, 0.0);
		glVertex2f(0.341, 0.714);
		glVertex2f(0.352, 0.732);
		glVertex2f(0.322, 0.734);
		glVertex2f(0.329, 0.714);
	glEnd();

//Batman Hands=====================
	//Left hand
	glVertexPointer(2, GL_FLOAT, 0, &bat_leftHand[0]);
	glColor3f(0.5, 0.5, 0.5);
	glDrawArrays(GL_POLYGON, 0, 6);

		glVertexPointer(2, GL_FLOAT, 0, &bat_leftForearm[0]);//left forearm
		glColor3f(0.0, 0.0, 0.0);
		glDrawArrays(GL_POLYGON, 0, 6);


		glVertexPointer(2, GL_FLOAT, 0, &bat_leftFist[0]);//left fist
		glColor3f(0.0, 0.0, 0.0);
		glDrawArrays(GL_POLYGON, 0, 6);
	
	//Right hand-------------
	glVertexPointer(2, GL_FLOAT, 0, &bat_rightHand[0]);
	glColor3f(0.5, 0.5, 0.5);
	glDrawArrays(GL_POLYGON, 0, 6);

		glVertexPointer(2, GL_FLOAT, 0, &bat_rightForearm[0]);//right forearm
		glColor3f(0.0, 0.0, 0.0);
		glDrawArrays(GL_POLYGON, 0, 6);

		glVertexPointer(2, GL_FLOAT, 0, &bat_rightFist[0]);//right fist
		glColor3f(0.0, 0.0, 0.0);
		glDrawArrays(GL_POLYGON, 0, 5);

		//Belt
		glBegin(GL_POLYGON);
			glColor3f(1.0, 1.0, 0.0);
			glVertex2f(0.235, 0.394);//ul
			glVertex2f(0.235, 0.429);//lb
			glVertex2f(0.330, 0.420);//lr
			glVertex2f(0.328, 0.386);//ur
		glEnd();

}

void batman_cape()
{
//	glTranslatef(0.0, 0.2, 0.0);
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 0.0);
		glVertex2f(0.273, 0.241);//center pt, cape knot near neck
		glVertex2f(0.155, 0.317);
		glVertex2f(0.155, 0.250);
		glVertex2f(0.243, 0.215);
		glVertex2f(0.248, 0.171);
		glVertex2f(0.252, 0.115);
		glVertex2f(0.261, 0.150);
		glVertex2f(0.281, 0.151);
		glVertex2f(0.288, 0.112);
		glVertex2f(0.296, 0.165);
		glVertex2f(0.301, 0.214);
		glVertex2f(0.391, 0.246);
		glVertex2f(0.398, 0.310);
	glEnd();
	
}



void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	//glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0.0, 0.2, 0.0);
	glScalef(1.0, -1.0, 1.0);
	BackCape();
	batman_body();
	batman_cape();



	glutSwapBuffers();
}


int main(int argc, char* argv[])
{
	void initialize(void);
	void display(void);
	void resize(int, int);
	void keyboard(unsigned char, int, int);
	void mouse(int, int, int, int);
	void uninitialize(void);

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(800,700);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("My practice window: The Great Harshal");

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
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

}

void resize(int width, int height) {

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
}


void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{	
	case 27:
		glutLeaveMainLoop();
			break;
	case 'F':
	case 'f':
		if (bIsScreenFull == false)
		{
			glutFullScreen();
			bIsScreenFull = true;
		}
		else
		{
			glutLeaveFullScreen();
			bIsScreenFull = false;
		}
		break;

	default:
		break;
	}
}

void mouse(int button, int state, int x, int y)
{
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

}
