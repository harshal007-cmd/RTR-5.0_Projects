// header files
#include <GL/freeglut.h>
#define _USE_MATH_DEFINES 1
#include<math.h>
// global variable declarations
bool bIsFullScreen = false;

void IndiaGate(void);
void india(void);
// entry-point function
int main(int argc, char* argv[])
{
	// function declaration
	void initialize(void);
	void resize(int, int);
	void display(void);
	void keyboard(unsigned char, int, int);
	void mouse(int, int, int, int);
	void uninitialize(void);

	//  code 
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("India Gate");

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
    float x = 314.0f;
    float y = -399.0f;
	// code
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

    glPushMatrix();
    glTranslatef(-0.5, 0.5, 0);
    IndiaGate();
    glPopMatrix();
    
	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
	// code
	switch(key)
	{
	case 27:
		glutLeaveMainLoop();
		break;
	case 'F':
	case 'f':
		if(bIsFullScreen == false)
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
	switch(button)
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





void IndiaGate(void)
{
    float x = 314.0f, y = -399.0f;
    int i = 0;
    glColor3f(187.0f/255.0f, 136.0f/255.0f, 85.0f/255.0f);
    
    glBegin(GL_POLYGON);

    for (i = 0; i <= 50; i++)
    {
        float ang = M_PI * i / 50.0;

        glVertex2f((156.0f / x) + 17.0 / x * cos(ang), (19.0f / y) + 10.0 / x * sin(ang));
    }
   

    glEnd();
    
    glBegin(GL_QUADS);
    //1st
    glVertex2f(100.0f / x, 25.0f / y);
    glVertex2f(215.0f / x, 25.0f / y);
    glVertex2f(215.0f / x, 33.0f / y);
    glVertex2f(100.0f / x, 33.0f / y);

    //2nd 
    glVertex2f(50.0f / x, 33.0f / y);
    glVertex2f(265.0f / x, 33.0f / y);
    glVertex2f(265.0f / x, 52.0f / y);
    glVertex2f(50.0f / x, 52.0f / y);

    //3rd
    glVertex2f(47.0f / x, 52.0f / y);
    glVertex2f(267.0f / x, 52.0f / y);
    glVertex2f(267.0f / x, 85.0f / y);
    glVertex2f(47.0f / x, 85.0f / y);

    //4th
    glVertex2f(23.0f / x, 85.0f / y);
    glVertex2f(291.0f / x, 85.0f / y);
    glVertex2f(291.0f / x, 105.0f / y);
    glVertex2f(23.0f / x, 105.0f / y);

    //5th
    glVertex2f(18.0f / x, 105.0f / y);
    glVertex2f(296.0f / x, 105.0f / y);
    glVertex2f(296.0f / x, 134.0f / y);
    glVertex2f(18.0f / x, 134.0f / y);

    //6th
    glVertex2f(19.0f / x, 142.0f / y);
    glVertex2f(110.0f / x, 142.0f / y);
    glVertex2f(110.0f / x, 395.0f / y);
    glVertex2f(19.0f / x, 395.0f / y);
    /*
    //7th
    glVertex2f(105.0f / x, 142.0f / y);
    glVertex2f(204.0f / x, 142.0f / y);
    glVertex2f(204.0f / x, 213.0f / y);
    glVertex2f(105.0f / x, 213.0f / y);
    */
    //8th
    glVertex2f(204.0f / x, 142.0f / y);
    glVertex2f(297.0f / x, 142.0f / y);
    glVertex2f(297.0f / x, 395.0f / y);
    glVertex2f(204.0f / x, 395.0f / y);

    //9th
    glVertex2f(140.0f / x, 19.0f / y);
    glVertex2f(174.0f / x, 19.0f / y);
    glVertex2f(193.0f / x, 25.0f / y);
    glVertex2f(124.0f / x, 25.0f / y);

    //10th
    glVertex2f(1.0f / x, 134.0f / y);
    glVertex2f(313.0f / x, 134.0f / y);
    glVertex2f(310.0f / x, 138.0f / y);
    glVertex2f(4.0f / x, 138.0f / y);

    //11th
    glVertex2f(4.0f / x, 138.0f / y);
    glVertex2f(310.0f / x, 138.0f / y);
    glVertex2f(310.0f / x, 142.0f / y);
    glVertex2f(4.0f / x, 142.0f / y);

 
    //Small Quads
    //A
    glVertex2f(16.0f / x, 162.0f / y);
    glVertex2f(99.0f / x, 162.0f / y);
    glVertex2f(97.0f / x, 164.0f / y);
    glVertex2f(19.0f / x, 164.0f / y);

    //B
    glVertex2f(19.0f / x, 164.0f / y);
    glVertex2f(97.0f / x, 164.0f / y);
    glVertex2f(97.0f / x, 168.0f / y);
    glVertex2f(19.0f / x, 168.0f / y);

    //C
    glVertex2f(216.0f / x, 162.0f / y);
    glVertex2f(300.0f / x, 162.0f / y);
    glVertex2f(297.0f / x, 164.0f / y);
    glVertex2f(219.0f / x, 164.0f / y);

    //D
    glVertex2f(219.0f / x, 164.0f / y);
    glVertex2f(297.0f / x, 164.0f / y);
    glVertex2f(297.0f / x, 168.0f / y);
    glVertex2f(219.0f / x, 168.0f / y);


    glEnd();

    //BLACK LINES AROUND THE QUADS
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(1);

    glBegin(GL_LINE_LOOP);

    for (i = 0; i <= 50; i++)
    {
        float ang = M_PI * i / 50.0;

        glVertex2f((156.0f / x) + 17.0 / x * cos(ang), (19.0f / y) + 10.0 / x * sin(ang));
    }
    glEnd();

   
    //Left circle
   glBegin(GL_LINE_LOOP);

    for (i = 0; i <= 50; i++)
    {
        float ang =2* M_PI * i / 50.0;

        glVertex2f((97.0f / x) + 10.0 / x * cos(ang), (66.0f / y) + 10.0 / x * sin(ang));
    }
    glEnd();

    //India Box
    glBegin(GL_LINE_LOOP);
    glVertex2f(107.0f / x, 53.0f / y);
    glVertex2f(209.0f / x, 53.0f / y);
    glVertex2f(209.0f / x, 78.0f / y);
    glVertex2f(185.0f / x, 78.0f / y);
    glVertex2f(185.0f / x, 79.0f / y);
    glVertex2f(132.0f / x, 79.0f / y);
    glVertex2f(132.0f / x, 78.0f / y);
    glVertex2f(107.0f / x, 78.0f / y);
    glEnd();

    //right circle
    glBegin(GL_LINE_LOOP);

    for (i = 0; i <= 50; i++)
    {
        float ang = 2 * M_PI * i / 50.0;

        glVertex2f((219.0f / x) + 10.0 / x * cos(ang), (66.0f / y) + 10.0 / x * sin(ang));
    }
    glEnd();

    glBegin(GL_LINE_LOOP);
    //1st
    glVertex2f(100.0f / x, 25.0f / y);
    glVertex2f(215.0f / x, 25.0f / y);
    glVertex2f(215.0f / x, 33.0f / y);
    glVertex2f(100.0f / x, 33.0f / y);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //2nd 
    glVertex2f(50.0f / x, 33.0f / y);
    glVertex2f(265.0f / x, 33.0f / y);
    glVertex2f(265.0f / x, 52.0f / y);
    glVertex2f(50.0f / x, 52.0f / y);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //3rd
    glVertex2f(47.0f / x, 52.0f / y);
    glVertex2f(267.0f / x, 52.0f / y);
    glVertex2f(267.0f / x, 85.0f / y);
    glVertex2f(47.0f / x, 85.0f / y);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //4th
    glVertex2f(23.0f / x, 85.0f / y);
    glVertex2f(291.0f / x, 85.0f / y);
    glVertex2f(291.0f / x, 105.0f / y);
    glVertex2f(23.0f / x, 105.0f / y);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //5th
    glVertex2f(18.0f / x, 105.0f / y);
    glVertex2f(296.0f / x, 105.0f / y);
    glVertex2f(296.0f / x, 134.0f / y);
    glVertex2f(18.0f / x, 134.0f / y);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //6th
    glVertex2f(19.0f / x, 142.0f / y);
    glVertex2f(110.0f / x, 142.0f / y);
    glVertex2f(110.0f / x, 395.0f / y);
    glVertex2f(19.0f / x, 395.0f / y);
    glEnd();

    /*
    glBegin(GL_LINE_STRIP);
    //7th
    glVertex2f(110.0f / x, 142.0f / y);
    glVertex2f(204.0f / x, 142.0f / y);
    glVertex2f(204.0f / x, 189.0f / y);
    glVertex2f(110.0f / x, 189.0f / y);
    glEnd();
    */
    glBegin(GL_LINE_LOOP);
    //8th
    glVertex2f(204.0f / x, 142.0f / y);
    glVertex2f(297.0f / x, 142.0f / y);
    glVertex2f(297.0f / x, 395.0f / y);
    glVertex2f(204.0f / x, 395.0f / y);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //9th
    glVertex2f(140.0f / x, 19.0f / y);
    glVertex2f(174.0f / x, 19.0f / y);
    glVertex2f(193.0f / x, 25.0f / y);
    glVertex2f(124.0f / x, 25.0f / y);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //10th
    glVertex2f(1.0f / x, 134.0f / y);
    glVertex2f(313.0f / x, 134.0f / y);
    glVertex2f(310.0f / x, 138.0f / y);
    glVertex2f(4.0f / x, 138.0f / y);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //11th
    glVertex2f(4.0f / x, 138.0f / y);
    glVertex2f(310.0f / x, 138.0f / y);
    glVertex2f(310.0f / x, 142.0f / y);
    glVertex2f(4.0f / x, 142.0f / y);
    glEnd();

    glColor3f(187.0f / 255.0f, 136.0f / 255.0f, 85.0f / 255.0f);
    glBegin(GL_QUADS);
    //12th
    glVertex2f(19.0f / x, 142.0f / y);
    glVertex2f(298.0f / x, 142.0f / y);
    glVertex2f(298.0f / x, 162.0f / y);
    glVertex2f(19.0f / x, 162.0f / y);

    //7th
    /*
    glVertex2f(105.0f / x, 142.0f / y);
    glVertex2f(204.0f / x, 142.0f / y);
    glVertex2f(204.0f / x, 213.0f / y);
    glVertex2f(105.0f / x, 213.0f / y);
    */
    glEnd();
    
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    //12th
    glVertex2f(19.0f / x, 142.0f / y);
    glVertex2f(298.0f / x, 142.0f / y);
    glVertex2f(298.0f / x, 162.0f / y);
    glVertex2f(19.0f / x, 162.0f / y);
    glEnd();


    //Design in 12 th quads
   
    int n = 0;
    for (i = 0; i < 14; i++)
    {
        glBegin(GL_LINE_LOOP);
        glVertex2f((26.0f+n) / x, 142.0f / y);
        glVertex2f((35.0f + n) / x, 142.0f / y);
        glVertex2f((35.0f + n) / x, 144.0f / y);
        glVertex2f((26.0f + n) / x, 144.0f / y);
        glEnd();

        glBegin(GL_LINE_LOOP);

        glVertex2f((24.0f + n) / x, 144.0f / y);
        glVertex2f((37.0f + n) / x, 144.0f / y);
        glVertex2f((36.0f + n) / x, 148.0f / y);
        glVertex2f((25.0f + n) / x, 148.0f / y);
        glEnd();

        glBegin(GL_LINE_LOOP);

        glVertex2f((26.0f + n) / x, 148.0f / y);
        glVertex2f((35.0f + n) / x, 148.0f / y);
        glVertex2f((35.0f + n) / x, 156.0f / y);
        glVertex2f((26.0f + n) / x, 156.0f / y);
        glEnd();

        glBegin(GL_LINE_LOOP);

        glVertex2f((27.0f + n) / x, 156.0f / y);
        glVertex2f((34.0f + n) / x, 156.0f / y);
        glVertex2f((34.0f + n) / x, 160.0f / y);
        glVertex2f((27.0f + n) / x, 160.0f / y);
        glEnd();

        glBegin(GL_LINE_LOOP);
        glVertex2f((28.0f + n) / x, 160.0f / y);
        glVertex2f((28.0f + n) / x, 162.0f / y);
        glVertex2f((33.0f + n) / x, 162.0 / y);
        glVertex2f((33.0f + n) / x, 160.0f / y);
      

        glEnd();
        n = n + 20;
    }


    glBegin(GL_LINE_LOOP);
    //A
    glVertex2f(16.0f / x, 162.0f / y);
    glVertex2f(99.0f / x, 162.0f / y);
    glVertex2f(97.0f / x, 164.0f / y);
    glVertex2f(19.0f / x, 164.0f / y);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //B
    glVertex2f(19.0f / x, 164.0f / y);
    glVertex2f(97.0f / x, 164.0f / y);
    glVertex2f(97.0f / x, 168.0f / y);
    glVertex2f(19.0f / x, 168.0f / y);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //C
    glVertex2f(216.0f / x, 162.0f / y);
    glVertex2f(300.0f / x, 162.0f / y);
    glVertex2f(297.0f / x, 164.0f / y);
    glVertex2f(219.0f / x, 164.0f / y);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //D
    glVertex2f(219.0f / x, 164.0f / y);
    glVertex2f(297.0f / x, 164.0f / y);
    glVertex2f(297.0f / x, 168.0f / y);
    glVertex2f(219.0f / x, 168.0f / y);
    glEnd();


    glBegin(GL_LINE_LOOP);
    //E
    glVertex2f(19.0f / x, 168.0f / y);
    glVertex2f(97.0f / x, 168.0f / y);
    glVertex2f(96.0f / x, 232.0f / y);
    glVertex2f(19.0f / x, 232.0f / y);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //F
    glVertex2f(219.0f / x, 168.0f / y);
    glVertex2f(297.0f / x, 168.0f / y);
    glVertex2f(297.0f / x, 232.0f / y);
    glVertex2f(219.0f / x, 232.0f / y);
    glEnd();
  
   
   //Side Design on pillars
    glColor3f(187.0f / 255.0f, 136.0f / 255.0f, 85.0f / 255.0f);

    glBegin(GL_QUADS);
   
    //Right side 

    glVertex2f(98.0f  / x, 232.0f / y);
    glVertex2f(117.0f  / x, 232.0f / y);
    glVertex2f(114.0f  / x, 237.0f / y);
    glVertex2f(98.0f  / x, 237.0f / y);

    glVertex2f(98.0f  / x, 237.0f / y);
    glVertex2f(114.0f / x, 237.0f / y);
    glVertex2f(114.0f  / x, 239.0f / y);
    glVertex2f(98.0f  / x, 239.0f / y);

    glVertex2f(98.0f  / x, 239.0f / y);
    glVertex2f(112.0f / x, 239.0f / y);
    glVertex2f(111.0f  / x, 244.0f / y);
    glVertex2f(98.0f  / x, 244.0f / y);

    //Left side
    glVertex2f(197.0f / x, 233.0f / y);
    glVertex2f(217.0f / x, 233.0f / y);
    glVertex2f(217.0f / x, 236.0f / y);
    glVertex2f(200.0f / x, 237.0f / y);

    glVertex2f(201.0f / x, 237.0f / y);
    glVertex2f(215.0f / x, 237.0f / y);
    glVertex2f(216.0f / x, 239.0f / y);
    glVertex2f(201.0f / x, 239.0f / y);

    glVertex2f(202.0f / x, 239.0f / y);
    glVertex2f(217.0f / x, 239.0f / y);
    glVertex2f(217.0f / x, 243.0f / y);
    glVertex2f(203.0f / x, 243.0f / y);



    
    glEnd();

    glColor3f(0, 0, 0);

    //Lines around above quads
   /* glBegin(GL_LINE_STRIP);
    glVertex2f(85.0f  / x, 232.0f / y);
    glVertex2f(98.0f / x, 232.0f / y);
    glVertex2f(98.0f  / x, 237.0f / y);
    glVertex2f(85.0f / x, 237.0f / y);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2f(86.0f  / x, 237.0f / y);
    glVertex2f(99.0f  / x, 237.0f / y);
    glVertex2f(98.0f  / x, 242.0f / y);
    glVertex2f(85.0f  / x, 242.0f / y);
    glEnd();
    */
    glBegin(GL_LINE_STRIP);
    glVertex2f(98.0f / x, 232.0f / y);
    glVertex2f(117.0f  / x, 232.0f / y);
    glVertex2f(114.0f  / x, 237.0f / y);
    glVertex2f(98.0f / x, 237.0f / y);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2f(98.0f / x, 237.0f / y);
    glVertex2f(114.0f   / x, 237.0f / y);
    glVertex2f(114.0f   / x, 239.0f / y);
    glVertex2f(98.0f  / x, 239.0f / y);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2f(98.0f  / x, 239.0f / y);
    glVertex2f(112.0f  / x, 239.0f / y);
    glVertex2f(111.0f  / x, 244.0f / y);
    glVertex2f(97.0f   / x, 244.0f / y);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex2f(197.0f / x, 233.0f / y);
    glVertex2f(217.0f / x, 233.0f / y);
    glVertex2f(217.0f / x, 236.0f / y);
    glVertex2f(200.0f / x, 237.0f / y);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex2f(201.0f / x, 237.0f / y);
    glVertex2f(215.0f / x, 237.0f / y);
    glVertex2f(216.0f / x, 239.0f / y);
    glVertex2f(201.0f / x, 239.0f / y);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex2f(202.0f / x, 239.0f / y);
    glVertex2f(217.0f / x, 239.0f / y);
    glVertex2f(217.0f / x, 243.0f / y);
    glVertex2f(203.0f / x, 243.0f / y);
    glEnd();
    /*  glBegin(GL_LINE_STRIP);
    
    glVertex2f(31.0f   / x, 232.0f / y);
    glVertex2f(19.0f / x, 232.0f / y);
    glVertex2f(19.0f  / x, 237.0f / y);
    glVertex2f(29.0f / x, 237.0f / y);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2f(29.0f / x, 237.0f / y);
    glVertex2f(15.0f   / x, 237.0f / y);
    glVertex2f(19.0f / x, 243.0f / y);
    glVertex2f(32.0f / x, 243.0f / y);
    glEnd();

    */

    //Design on the Two Pillars
    n = 0;
    int nx = 0;
    for (i = 0; i < 2; i++)
    {
        //GL_QUADS

        glColor3f(187.0f / 255.0f, 136.0f / 255.0f, 85.0f / 255.0f);
        glBegin(GL_QUADS);

        //upper
        glVertex2f((85.0f + nx) / x, 232.0f / y);
        glVertex2f((98.0f + nx) / x, 232.0f / y);
        glVertex2f((98.0f + nx) / x, 237.0f / y);
        glVertex2f((85.0f + nx) / x, 237.0f / y);

        glVertex2f((85.0f + nx) / x, 237.0f / y);
        glVertex2f((103.0f + nx) / x, 237.0f / y);
        glVertex2f((98.0f + nx) / x, 242.0f / y);
        glVertex2f((85.0f + nx) / x, 242.0f / y);

        glVertex2f((17.0f + nx) / x, 232.0f / y);
        glVertex2f((31.0f + nx) / x, 232.0f / y);
        glVertex2f((31.0f + nx) / x, 237.0f / y);
        glVertex2f((17.0f + nx) / x, 237.0f / y);

        glVertex2f((15.0f + nx) / x, 237.0f / y);
        glVertex2f((31.0f + nx) / x, 237.0f / y);
        glVertex2f((32.0f + nx) / x, 243.0f / y);
        glVertex2f((19.0f + nx) / x, 243.0f / y);

       //middle right
        glVertex2f((86.0f + nx) / x, 274.0f / y);
        glVertex2f((98.0f + nx) / x, 274.0f / y);
        glVertex2f((98.0f + nx) / x, 278.0f / y);
        glVertex2f((86.0f + nx) / x, 278.0f / y);

        glVertex2f((88.0f + nx) / x, 278.0f / y);
        glVertex2f((102.0f + nx) / x, 278.0f / y);
        glVertex2f((98.0f + nx) / x, 283.0f / y);
        glVertex2f((87.0f + nx) / x, 283.0f / y);

        glVertex2f((85.0f + nx) / x, 283.0f / y);
        glVertex2f((98.0f + nx) / x, 283.0f / y);
        glVertex2f((98.0f + nx) / x, 287.0f / y);
        glVertex2f((85.0f + nx) / x, 287.0f / y);

        glVertex2f((85.0f + nx) / x, 287.0f / y);
        glVertex2f((99.0f + nx) / x, 287.0f / y);
        glVertex2f((99.0f + nx) / x, 291.0f / y);
        glVertex2f((85.0f + nx) / x, 291.0f / y);

        //middle left
        glVertex2f((17.0f + nx) / x, 274.0f / y);
        glVertex2f((30.0f + nx) / x, 274.0f / y);
        glVertex2f((30.0f + nx) / x, 278.0f / y);
        glVertex2f((17.0f + nx) / x, 278.0f / y);

        glVertex2f((13.0f + nx) / x, 278.0f / y);
        glVertex2f((28.0f + nx) / x, 278.0f / y);
        glVertex2f((30.0f + nx) / x, 283.0f / y);
        glVertex2f((18.0f + nx) / x, 283.0f / y);

        glVertex2f((19.0f + nx) / x, 283.0f / y);
        glVertex2f((30.0f + nx) / x, 283.0f / y);
        glVertex2f((30.0f + nx) / x, 287.0f / y);
        glVertex2f((19.0f + nx) / x, 287.0f / y);

        glVertex2f((17.0f + nx) / x, 287.0f / y);
        glVertex2f((30.0f + nx) / x, 287.0f / y);
        glVertex2f((30.0f + nx) / x, 291.0f / y);
        glVertex2f((17.0f + nx) / x, 291.0f / y);

        //lower right
        glVertex2f((85.0f + nx) / x, 345.0f / y);
        glVertex2f((99.0f + nx) / x, 345.0f / y);
        glVertex2f((99.0f + nx) / x, 349.0f / y);
        glVertex2f((85.0f + nx) / x, 349.0f / y);

        glVertex2f((87.0f + nx) / x, 349.0f / y);
        glVertex2f((99.0f + nx) / x, 349.0f / y);
        glVertex2f((99.0f + nx) / x, 362.0f / y);
        glVertex2f((87.0f + nx) / x, 362.0f / y);

        glVertex2f((86.0f + nx) / x, 361.0f / y);
        glVertex2f((100.0f + nx) / x, 361.0f / y);
        glVertex2f((100.0f + nx) / x, 366.0f / y);
        glVertex2f((86.0f + nx) / x, 366.0f / y);

        glVertex2f((86.0f + nx) / x, 365.0f / y);
        glVertex2f((101.0f + nx) / x, 365.0f / y);
        glVertex2f((101.0f + nx) / x, 377.0f / y);
        glVertex2f((86.0f + nx) / x, 377.0f / y);

        glVertex2f((86.0f + nx) / x, 377.0f / y);
        glVertex2f((100.0f + nx) / x, 377.0f / y);
        glVertex2f((100.0f + nx) / x, 390.0f / y);
        glVertex2f((86.0f + nx) / x, 390.0f / y);

            //lower left
        glVertex2f((17.0f + nx) / x, 345.0f / y);
        glVertex2f((30.0f + nx) / x, 345.0f / y);
        glVertex2f((30.0f + nx) / x, 349.0f / y);
        glVertex2f((17.0f + nx) / x, 349.0f / y);

        glVertex2f((17.0f + nx) / x, 349.0f / y);
        glVertex2f((30.0f + nx) / x, 349.0f / y);
        glVertex2f((30.0f + nx) / x, 362.0f / y);
        glVertex2f((17.0f + nx) / x, 362.0f / y);

        glVertex2f((16.0f + nx) / x, 361.0f / y);
        glVertex2f((30.0f + nx) / x, 361.0f / y);
        glVertex2f((30.0f + nx) / x, 366.0f / y);
        glVertex2f((16.0f + nx) / x, 366.0f / y);

        glVertex2f((16.0f + nx) / x, 365.0f / y);
        glVertex2f((29.0f + nx) / x, 365.0f / y);
        glVertex2f((29.0f + nx) / x, 377.0f / y);
        glVertex2f((16.0f + nx) / x, 377.0f / y);

        glVertex2f((16.0f + nx) / x, 377.0f / y);
        glVertex2f((30.0f + nx) / x, 377.0f / y);
        glVertex2f((30.0f + nx) / x, 390.0f / y);
        glVertex2f((16.0f + nx) / x, 390.0f / y);

        glEnd();

        //Lines around above quads
        glColor3f(0, 0, 0);
        
        glBegin(GL_LINE_LOOP);

        for (int j = 0; j <= 100; j++)
        {
            float ang = 2 * M_PI * j / 100.0;

            glVertex2f(((58.0f +nx) / x) + 8.0 / x * cos(ang), (189.0f / y) + 8.0 / x * sin(ang));
        }
        glEnd();

        glBegin(GL_LINE_LOOP);

        for (int j = 0; j <= 100; j++)
        {
            float ang = 2 * M_PI * j / 100.0;

            glVertex2f(((58.0f + nx) / x) + 12.0 / x * cos(ang), (189.0f / y) + 12.0 / x * sin(ang));
        }
        glEnd();
        

        glBegin(GL_LINE_LOOP);
        glVertex2f((85.0f + nx) / x, 232.0f / y);
        glVertex2f((98.0f + nx) / x, 232.0f / y);
        glVertex2f((98.0f + nx) / x, 237.0f / y);
        glVertex2f((85.0f + nx) / x, 237.0f / y);
        glEnd();

        glBegin(GL_LINE_LOOP);
        glVertex2f((85.0f + nx) / x, 237.0f / y);
        glVertex2f((101.0f + nx) / x, 237.0f / y);
        glVertex2f((98.0f + nx) / x, 242.0f / y);
        glVertex2f((85.0f + nx) / x, 242.0f / y);
        glEnd();

        glBegin(GL_LINE_LOOP);
        glVertex2f((17.0f + nx) / x, 232.0f / y);
        glVertex2f((31.0f + nx) / x, 232.0f / y);
        glVertex2f((31.0f + nx) / x, 237.0f / y);
        glVertex2f((17.0f + nx) / x, 237.0f / y);
        glEnd();

        glBegin(GL_LINE_LOOP);
        glVertex2f((15.0f + nx) / x, 237.0f / y);
        glVertex2f((31.0f + nx) / x, 237.0f / y);
        glVertex2f((32.0f + nx) / x, 243.0f / y);
        glVertex2f((19.0f + nx) / x, 243.0f / y);
        glEnd();

        glBegin(GL_LINE_LOOP);
        glVertex2f((86.0f + nx) / x, 274.0f / y);
        glVertex2f((98.0f + nx) / x, 274.0f / y);
        glVertex2f((98.0f + nx) / x, 278.0f / y);
        glVertex2f((86.0f + nx) / x, 278.0f / y);
        glEnd();

        glBegin(GL_LINE_LOOP);
        glVertex2f((88.0f + nx) / x, 278.0f / y);
        glVertex2f((102.0f + nx) / x, 278.0f / y);
        glVertex2f((98.0f + nx) / x, 283.0f / y);
        glVertex2f((87.0f + nx) / x, 283.0f / y);
        glEnd();

        glBegin(GL_LINE_LOOP);
        glVertex2f((85.0f + nx) / x, 283.0f / y);
        glVertex2f((98.0f + nx) / x, 283.0f / y);
        glVertex2f((98.0f + nx) / x, 287.0f / y);
        glVertex2f((85.0f + nx) / x, 287.0f / y);
        glEnd();

        glBegin(GL_LINE_LOOP);
        glVertex2f((85.0f + nx) / x, 287.0f / y);
        glVertex2f((99.0f + nx) / x, 287.0f / y);
        glVertex2f((99.0f + nx) / x, 291.0f / y);
        glVertex2f((85.0f + nx) / x, 291.0f / y);
        glEnd();

        //
        glBegin(GL_LINE_LOOP);
        glVertex2f((17.0f + nx) / x, 274.0f / y);
        glVertex2f((30.0f + nx) / x, 274.0f / y);
        glVertex2f((30.0f + nx) / x, 278.0f / y);
        glVertex2f((17.0f + nx) / x, 278.0f / y);
        glEnd();

        glBegin(GL_LINE_LOOP);
        glVertex2f((13.0f + nx) / x, 278.0f / y);
        glVertex2f((28.0f + nx) / x, 278.0f / y);
        glVertex2f((30.0f + nx) / x, 283.0f / y);
        glVertex2f((18.0f + nx) / x, 283.0f / y);
        glEnd();

        glBegin(GL_LINE_LOOP);
        glVertex2f((19.0f + nx) / x, 283.0f / y);
        glVertex2f((30.0f + nx) / x, 283.0f / y);
        glVertex2f((30.0f + nx) / x, 287.0f / y);
        glVertex2f((19.0f + nx) / x, 287.0f / y);
        glEnd();

        glBegin(GL_LINE_LOOP);
        glVertex2f((17.0f + nx) / x, 287.0f / y);
        glVertex2f((30.0f + nx) / x, 287.0f / y);
        glVertex2f((30.0f + nx) / x, 291.0f / y);
        glVertex2f((17.0f + nx) / x, 291.0f / y);
        glEnd();

        //lower right
        glBegin(GL_LINE_LOOP);
        glVertex2f((86.0f + nx) / x, 345.0f / y);
        glVertex2f((99.0f + nx) / x, 345.0f / y);
        glVertex2f((99.0f + nx) / x, 349.0f / y);
        glVertex2f((86.0f + nx) / x, 349.0f / y);
        glEnd();

        glBegin(GL_LINE_LOOP);
        glVertex2f((86.0f + nx) / x, 349.0f / y);
        glVertex2f((99.0f + nx) / x, 349.0f / y);
        glVertex2f((99.0f + nx) / x, 362.0f / y);
        glVertex2f((86.0f + nx) / x, 362.0f / y);
        glEnd();

        glBegin(GL_LINE_LOOP);
        glVertex2f((87.0f + nx) / x, 362.0f / y);
        glVertex2f((100.0f + nx) / x, 362.0f / y);
        glVertex2f((100.0f + nx) / x, 366.0f / y);
        glVertex2f((87.0f + nx) / x, 366.0f / y);
        glEnd();

        glBegin(GL_LINE_LOOP);
        glVertex2f((88.0f + nx) / x, 366.0f / y);
        glVertex2f((101.0f + nx) / x, 366.0f / y);
        glVertex2f((101.0f + nx) / x, 377.0f / y);
        glVertex2f((88.0f + nx) / x, 377.0f / y);
        glEnd();

        glBegin(GL_LINE_LOOP);
        glVertex2f((89.0f + nx) / x, 377.0f / y);
        glVertex2f((100.0f + nx) / x, 377.0f / y);
        glVertex2f((100.0f + nx) / x, 390.0f / y);
        glVertex2f((89.0f + nx) / x, 390.0f / y);
        glEnd();

        //lower left
        glBegin(GL_LINE_LOOP);
        glVertex2f((17.0f + nx) / x, 345.0f / y);
        glVertex2f((30.0f + nx) / x, 345.0f / y);
        glVertex2f((30.0f + nx) / x, 349.0f / y);
        glVertex2f((17.0f + nx) / x, 349.0f / y);
        glEnd();

        glBegin(GL_LINE_LOOP);
        glVertex2f((17.0f + nx) / x, 349.0f / y);
        glVertex2f((30.0f + nx) / x, 349.0f / y);
        glVertex2f((30.0f + nx) / x, 362.0f / y);
        glVertex2f((17.0f + nx) / x, 362.0f / y);
        glEnd();

        glBegin(GL_LINE_LOOP);
        glVertex2f((16.0f + nx) / x, 362.0f / y);
        glVertex2f((28.0f + nx) / x, 362.0f / y);
        glVertex2f((28.0f + nx) / x, 366.0f / y);
        glVertex2f((16.0f + nx) / x, 366.0f / y);
        glEnd();

        glBegin(GL_LINE_LOOP);
        glVertex2f((16.0f + nx) / x, 366.0f / y);
        glVertex2f((28.0f + nx) / x, 366.0f / y);
        glVertex2f((28.0f + nx) / x, 377.0f / y);
        glVertex2f((16.0f + nx) / x, 377.0f / y);
        glEnd();

        glBegin(GL_LINE_LOOP);
        glVertex2f((16.0f + nx) / x, 377.0f / y);
        glVertex2f((27.0f + nx) / x, 377.0f / y);
        glVertex2f((27.0f + nx) / x, 390.0f / y);
        glVertex2f((16.0f + nx) / x, 390.0f / y);
        glEnd();
        //7
        glBegin(GL_LINE_LOOP);
        glVertex2f((33.0f + n) / x, 208.0f / y);
        glVertex2f((82.0f + n) / x, 208.0f / y);
        glVertex2f((82.0f + n) / x, 211.0f / y);
        glVertex2f((33.0f + n) / x, 211.0f / y);
        glEnd();

            //8
        glBegin(GL_LINE_LOOP);
        glVertex2f((30.0f + n) / x, 211.0f / y);
        glVertex2f((85.0f + n) / x, 211.0f / y);
        glVertex2f((85.0f + n) / x, 226.0f / y);
        glVertex2f((30.0f + n) / x, 226.0f / y);
        glEnd();

            //9
        glBegin(GL_LINE_LOOP);
        glVertex2f((32.0f + n) / x, 226.0f / y);
        glVertex2f((84.0f + n) / x, 226.0f / y);
        glVertex2f((84.0f + n) / x, 232.0f / y);
        glVertex2f((32.0f + n) / x, 232.0f / y);
        glEnd();

            //10
        glBegin(GL_LINE_LOOP);
        glVertex2f((30.0f + n) / x, 232.0f / y);
        glVertex2f((84.0f + n) / x, 232.0f / y);
        glVertex2f((84.0f + n) / x, 236.0f / y);
        glVertex2f((30.0f + n) / x, 236.0f / y);
        glEnd();

        glBegin(GL_LINE_LOOP);
            //11
        glVertex2f((28.0f + n) / x, 236.0f / y);
        glVertex2f((86.0f + n) / x, 236.0f / y);
        glVertex2f((86.0f + n) / x, 239.0f / y);
        glVertex2f((28.0f + n) / x, 239.0f / y);
        glEnd();

        //12
        glBegin(GL_LINE_LOOP);
        glVertex2f((31.0f + n) / x, 239.0f / y);
        glVertex2f((85.0f + n) / x, 239.0f / y);
        glVertex2f((85.0f + n) / x, 242.0f / y);
        glVertex2f((31.0f + n) / x, 242.0 / y);
        glEnd();

        //13
        glBegin(GL_LINE_LOOP);
        glVertex2f((32.0f + n) / x, 242.0f / y);
        glVertex2f((84.0f + n) / x, 242.0f / y);
        glVertex2f((84.0f + n) / x, 274.0f / y);
        glVertex2f((32.0f + n) / x, 274.0f / y);
        glEnd();

        //14
        glBegin(GL_LINE_LOOP);
        glVertex2f((36.0f + n) / x, 245.0f / y);
        glVertex2f((79.0f + n) / x, 245.0f / y);
        glVertex2f((79.0f + n) / x, 266.0f / y);
        glVertex2f((36.0f + n) / x, 266.0f / y);
        glEnd();

        //15
        glBegin(GL_LINE_LOOP);
        glVertex2f((30.0f + n) / x, 274.0f / y);
        glVertex2f((86.0f + n) / x, 274.0f / y);
        glVertex2f((86.0f + n) / x, 278.0f / y);
        glVertex2f((30.0f + n) / x, 278.0f / y);
        glEnd();

        //16
        glBegin(GL_LINE_LOOP);
        glVertex2f((28.0f + n) / x, 278.0f / y);
        glVertex2f((87.0f + n) / x, 278.0f / y);
        glVertex2f((87.0f + n) / x, 283.0f / y);
        glVertex2f((28.0f + n) / x, 283.0f / y);
        glEnd();

        //17
        glBegin(GL_LINE_LOOP);
        glVertex2f((30.0f + n) / x, 283.0f / y);
        glVertex2f((85.0f + n) / x, 283.0f / y);
        glVertex2f((85.0f + n) / x, 287.0f / y);
        glVertex2f((30.0f + n) / x, 287.0f / y);
        glEnd();

        //18
        glBegin(GL_LINE_LOOP);
        glVertex2f((29.0f + n) / x, 287.0f / y);
        glVertex2f((86.0f + n) / x, 287.0f / y);
        glVertex2f((86.0f + n) / x, 291.0f / y);
        glVertex2f((29.0f + n) / x, 291.0f / y);
        glEnd();

        //19
        glBegin(GL_LINE_LOOP);
        glVertex2f((31.0f + n) / x, 291.0f / y);
        glVertex2f((85.0f + n) / x, 291.0f / y);
        glVertex2f((85.0f + n) / x, 344.0f / y);
        glVertex2f((31.0f + n) / x, 344.0f / y);
        glEnd();

        //20
        glBegin(GL_LINE_LOOP);
        glVertex2f((30.0f + n) / x, 345.0f / y);
        glVertex2f((86.0f + n) / x, 345.0f / y);
        glVertex2f((86.0f + n) / x, 350.0f / y);
        glVertex2f((30.0f + n) / x, 350.0f / y);
        glEnd();

        //21
        glBegin(GL_LINE_LOOP);
        glVertex2f((30.0f + n) / x, 350.0f / y);
        glVertex2f((86.0f + n) / x, 350.0f / y);
        glVertex2f((86.0f + n) / x, 362.0f / y);
        glVertex2f((30.0f + n) / x, 362.0f / y);
        glEnd();

        //22
        glBegin(GL_LINE_LOOP);
        glVertex2f((29.0f + n) / x, 362.0f / y);
        glVertex2f((87.0f + n) / x, 362.0f / y);
        glVertex2f((87.0f + n) / x, 366.0f / y);
        glVertex2f((29.0f + n) / x, 366.0f / y);
        glEnd();

        //23
        glBegin(GL_LINE_LOOP);
        glVertex2f((28.0f + n) / x, 366.0f / y);
        glVertex2f((88.0f + n) / x, 366.0f / y);
        glVertex2f((88.0f + n) / x, 378.0f / y);
        glVertex2f((28.0f + n) / x, 378.0f / y);
        glEnd();

        //24
        glBegin(GL_LINE_LOOP);
        glVertex2f((27.0f + n) / x, 378.0f / y);
        glVertex2f((89.0f + n) / x, 378.0f / y);
        glVertex2f((89.0f + n) / x, 390.0f / y);
        glVertex2f((27.0f + n) / x, 390.0f / y);
        glEnd();

        glBegin(GL_LINES);
        //lines
        glVertex2f((97.0f) / x, 242.0f / y);
        glVertex2f((97.0f) / x, 274.0f / y);

        glVertex2f((99.0f) / x, 291.0f / y);
        glVertex2f((99.0f) / x, 345.0f / y);

        glVertex2f(219.0f / x, 242.0f / y);
        glVertex2f(219.0f / x, 274.0f / y);

        glVertex2f(217 / x, 292.0f / y);
        glVertex2f(217 / x, 345.0f / y);

       
        glEnd();




        n += 200;
        nx += 200;
     
    }

    //middle circular portion
  
    glColor3f(187.0f / 255.0f, 136.0f / 255.0f, 85.0f / 255.0f);
    glBegin(GL_TRIANGLE_STRIP);
    float centerx = 157.0f / x, centery = 232.0f / y, radius = 53.0f / x, radius2 = 45.5f / x;;
    float angle;
   
    float fx = 218.0f / x, fy = 162.5f / y;
    for (i = 0; i < 200; i++)
    {
        angle =  M_PI * i / 200.0f;
        glVertex2f(fx, fy);
        glVertex2f(centerx + radius2 * cos(angle), centery + radius2 * sin(angle));
        fx = fx - (0.61) / x;

    }
 
    glEnd();
   
    glBegin(GL_QUADS);

    glVertex2f(112.0f / x, 231.0f / y);
    glVertex2f(112.0f / x, 225.0f / y);
    glVertex2f(104.0f / x, 225.0f / y);
    glVertex2f(104.0f / x, 231.0f / y);

    glVertex2f((112.0f+98) / x, 231.0f / y);
    glVertex2f((112.0f+98) / x, 225.0f / y);
    glVertex2f((104.0f+98) / x, 225.0f / y);
    glVertex2f((104.0f+98) / x, 231.0f / y);

    glEnd();

    glColor3f(0, 0, 0);


    glBegin(GL_LINES);
    glVertex2f(97.0f / x, 170.0f / y);
    glVertex2f(137.0f / x, 170.0f / y);

    glVertex2f(177.0f / x, 170.0f / y);

    glVertex2f(219.0f / x, 170.0f / y);
    glEnd();

    //Lines around circle
    glBegin(GL_LINE_LOOP);
     radius = 53.0f / x;
  
    for (i = 0; i < 200; i++)
    {
        angle = M_PI * i / 200.0f;
        glVertex2f(centerx + radius * cos(angle), centery + radius * sin(angle));
       
    }

    radius = 45.5f / x;
    
    for (i = 200; i > 0; i--)
    {
        angle = M_PI * i / 200.0f;
        glVertex2f(centerx + radius * cos(angle), centery + radius * sin(angle));


    }

    glEnd();

    glColor3f(187.0f / 255.0f, 136.0f / 255.0f, 85.0f / 255.0f);

    glBegin(GL_QUADS);

    glVertex2f(152.0f / x, 162.0f / y);
    glVertex2f(161.0f / x, 162.0f / y);
    glVertex2f(161.0f / x, 175.0f / y);
    glVertex2f(152.0f / x, 175.0f / y);

    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);

    glBegin(GL_LINE_LOOP);
    glVertex2f(152.0f / x, 162.0f / y);
    glVertex2f(161.0f / x, 162.0f / y);
    glVertex2f(161.0f / x, 175.0f / y);
    glVertex2f(152.0f / x, 175.0f / y);
    glEnd();

    //INDIA 
    glPushMatrix();
    glTranslatef(0.5f, -0.164f,0);
    glScalef(0.07f, 0.05f, 0);
    india();

    glPopMatrix();
}

void india(void)
{

    glColor3f(0, 0, 0);
    //I
    glBegin(GL_QUADS);
    glVertex2f(-0.9f, 0.5f);
    glVertex2f(-0.9f, -0.5f);
    glVertex2f(-0.8f, -0.5f);
    glVertex2f(-0.8f, 0.5f);
    glEnd();

    //N
    glBegin(GL_QUADS);
    glVertex2f(-0.6f, 0.5f);
    glVertex2f(-0.6f, -0.5f);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(-0.5f, 0.5f);
    

    glVertex2f(-0.6f, 0.5f);
    glVertex2f(-0.5f, 0.5f);
    glVertex2f(-0.2f, -0.5f);
    glVertex2f(-0.3f, -0.5f);

    /*
    glVertex2f(-0.5f, 0.5f);
    glVertex2f(-0.3f, -0.4f);
    glVertex2f(-0.3f, -0.5f);
    glVertex2f(-0.5f, 0.4f);
    */
    glVertex2f(-0.3f, 0.5f);
    glVertex2f(-0.3f, -0.5f);
    glVertex2f(-0.2f, -0.5f);
    glVertex2f(-0.2f, 0.5f);
    glEnd();

    //D
    glBegin(GL_QUADS);
    glVertex2f(-0.0f, 0.5f);
    glVertex2f(-0.0f, -0.5f);
    glVertex2f(0.1f, -0.5f);
    glVertex2f(0.1f, 0.5f);
    
    glVertex2f(0.1f, 0.5f);
    glVertex2f(0.3f, 0.3f);
    glVertex2f(0.4f, 0.2f);
    glVertex2f(0.1f, 0.4f);
    
    glVertex2f(0.3f, 0.3f);
    glVertex2f(0.3f, -0.3f);
    glVertex2f(0.4f, -0.2f);
    glVertex2f(0.4f, 0.2f);
   
   
    glVertex2f(0.4f, -0.2f);
    glVertex2f(0.3f, -0.3f);
    glVertex2f(0.1f, -0.5f);
    glVertex2f(0.1f, -0.4f);
    glEnd();

    //I
    glBegin(GL_QUADS);
    glVertex2f(0.5f, 0.5f);
    glVertex2f(0.6f, 0.5f);
    glVertex2f(0.6f, -0.5f);
    glVertex2f(0.5f, -0.5f);
    glEnd();

    //A
    glBegin(GL_QUADS);
    glVertex2f(1.0f, 0.5f);
    glVertex2f(0.9f, 0.5f);
    glVertex2f(0.7f, -0.5f);
    glVertex2f(0.8f, -0.5f);

    glVertex2f(1.0f, 0.5f);
    glVertex2f(0.9f, 0.5f);
    glVertex2f(1.1f, -0.5f);
    glVertex2f(1.2f, -0.5f);

    glVertex2f(0.86 ,0.00);
    glVertex2f(0.96,0.00);
    glVertex2f(1.1,-0.1);
    glVertex2f(0.86,-0.1);
    glEnd();
}

