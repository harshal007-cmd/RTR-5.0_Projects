#include<GL/gl.h>
#include<stdbool.h>
#include<GL/freeglut.h>
#include<stdio.h>
#include<math.h>
#include<time.h>

// OpenAL Based Libraries
#include<AL/al.h>
#include<AL/alc.h>
#include<AL/alut.h>

#define AUDIO 0

// global variables
static bool start = false;
static bool scene_done = false;

GLint scene = 1;
GLint state = -1;

bool b_FullScreen = false;
GLint delta = 0;
GLfloat fade = 1.0f;

float SunPositionY = 0.0f;
float SunFactor = 0.0;

GLfloat boatX = -2.0f, boatY = 0.0f;
GLfloat happy_x_mov = -3.5;
GLfloat happy_y_mov = 0.5;
GLfloat happy_z_mov = 0;

GLfloat birthday_x_mov = 4.5;
GLfloat birthday_y_mov = 0;
GLfloat birthday_z_mov = 0;

GLfloat hemalata_x_mov = -0.5;
GLfloat hemalata_y_mov = -4.5;
GLfloat hemalata_z_mov = 0;

// Display Functions
void scene_one_display();
void scene_two_display();

// Update Functions we can pass seconds to these
void scene_one_update(GLint seconds);
void scene_two_update(GLint seconds);

// Scene One Objects
void ppb_trees(void);

void grp_draw_sky(void);
void grp_draw_sun(void);
void grp_draw_greenland(void);
void grp_draw_mountains(void);

//ALPHABETS
void A(float LetterColor[]);
void B(float LetterColor[]);
void D(float LetterColor[]);
void E(float LetterColor[]);
void H(float LetterColor[]);
void I(float LetterColor[]);

void L(float LetterColor[]);
void M(float LetterColor[]);
void P(float LetterColor[]);

void R(float LetterColor[]);
void T(float LetterColor[]);
void Y(float LetterColor[]);

void DrawHappy(void);
void DrawBirthday(void);
void DrawHemalata(void);


void sum_House(void);
void sum_circle(void);
void sum_rooflines(void);
void sum_windowgrid(void);

void vmk_trees(void);

void kpr_river(void);
void kpr_boat(void);

// Utility functions

#if AUDIO
// OpenAL Global Variables
ALCdevice *deviceOAL;
ALCcontext *contextOAL;
ALuint bufferOAL, sourceOAL;
ALboolean loop = AL_FALSE;
ALsizei sizeOAL, freqOAL;
ALenum formatOAL;
ALint source_state;
ALfloat listenerOri[] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f };
ALvoid *dataOAL;
#endif
// Entry-point Function
int main(int argc, char* argv[])
{
    // local function declarations
    void initialize(void);
    void resize(int,int);
    void display(void);
    void update(void);
    void keyboard(unsigned char,int,int);
    void mouse(int,int,int,int);
    void uninitialize(void);

    // code
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);

    glutInitWindowSize(600,600);
    glutInitWindowPosition(200,200);
    glutCreateWindow("Timer");
    initialize();
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutIdleFunc(update);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutCloseFunc(uninitialize);
    glutMainLoop();

    return 0;
}
void initialize(void)
{

	#if AUDIO
    deviceOAL = alcOpenDevice(NULL);
    if(!deviceOAL)
    {
        printf("Failed To Get ALC Open Device\n");
    }

	contextOAL = alcCreateContext(deviceOAL,NULL);
    if(!alcMakeContextCurrent(contextOAL))
        printf("Failed To make current context\n");
    
    alListener3f(AL_POSITION,0,0,1.0f);
    alListener3f(AL_VELOCITY,0,0,0);
    alListenerfv(AL_ORIENTATION, listenerOri);
        
    alGenSources((ALuint)1,&sourceOAL);

    alSourcef(sourceOAL, AL_PITCH, 1);
    alSourcef(sourceOAL, AL_GAIN, 1);
    alSource3f(sourceOAL, AL_POSITION, 0, 0, 0);
    alSource3f(sourceOAL, AL_VELOCITY, 0, 0, 0);
    alSourcei(sourceOAL, AL_LOOPING, AL_FALSE);

    alGenBuffers(1, &bufferOAL);
	alutLoadWAVFile("flute.wav", &formatOAL, &dataOAL, &sizeOAL, &freqOAL, &loop);
    alBufferData(bufferOAL, formatOAL, dataOAL, sizeOAL, freqOAL);
	alSourcei(sourceOAL, AL_BUFFER, bufferOAL);
	#endif

    glClearColor(0.0f,0.0f,0.0f,1.0f);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0);
}

void resize(int width,int height)
{
    if(height == 0)
        height = 1;
    
    glViewport(0,0,(GLsizei)width,(GLsizei)height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Loot at function setup if needed
    //gluLookAt(0.0f, 0.0f, -4.0f,0.0f, 0.0f, 0.0f,0.0, 1.0, 0.0);
    glTranslatef(0.0f, 0.0f, -4.0f);

	if (!scene_done)
    {
        switch (scene)
        {
        case 1:
            scene_one_display();
        break;
        case 2:
            scene_two_display();
        break;
        default:
            break;
        }
    }
    // Save All Translations before odifying mv matrix
    glPushMatrix();
    //glRotatef(delta, 0.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS);
	glColor4f(0.0f, 0.0f, 0.0f, fade);
	glVertex3f(-10.f, 5.0f, 0.0f);
	glVertex3f(10.0f, 5.0f, 0.0f);
	glVertex3f(10.0f, -5.0f, 0.0f);
	glVertex3f(-10.0f, -5.0f, 0.0f);
	glEnd();
    glPopMatrix();

    glutSwapBuffers();
}

void scene_one_display(void){
    
	glPushMatrix(); // save global tranlation matrix

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f);
    glScalef(5.0f, 2.0f, 0.0f);

    // Sky Draw Call
    grp_draw_sky();
    glPopMatrix();

    // Sun Translation
    glPushMatrix();
        glTranslatef(0.5f, SunPositionY, 0.0f);
        grp_draw_sun();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f);
    glScalef(5.0f, 2.0f, 0.0f);
    grp_draw_greenland();
    glPopMatrix();

	float Mountain_Base_x = 3.4, Mountain_Base_y = -1.0;
	float x_scale = 1.0, y_scale = 1.0;
	
	for (int i = 0; i < 10; i++)
	{
		glPushMatrix();

		glTranslatef(0, 0.6, 0);
		glScalef(x_scale, y_scale, 0);
		glTranslatef(Mountain_Base_x, Mountain_Base_y, 0);
		
		grp_draw_mountains();
		glPopMatrix();
		
		//Drawing Mountains from right to left
		Mountain_Base_x = Mountain_Base_x - ((i % 2 == 0) ? 0.7 : 0.3);
	}

	ppb_trees();

	glPushMatrix();
	{
		glTranslatef(0.0f, -0.5f, 0.0f);
		vmk_trees();
	}
	glPopMatrix();


	// Draw House
	{
		glPushMatrix();

			glTranslatef(0.5f, -1.0f, 0.0f);
			glScalef(2.5f, 1.5f, 1.5f);
			sum_House();
			sum_circle();
			sum_rooflines();
			sum_windowgrid();
		glPopMatrix();
	}

	// Draw River & Boat

	glPushMatrix();
	{
		glPushMatrix();
		glTranslatef(-1.0f, -0.4f, 0.0f);
		glScalef(2.5f, 1.27f, 0.0f);
		kpr_river();
		glPopMatrix();
		glTranslatef(boatX, boatY, 0.0f);
		kpr_boat();
	}
	glPopMatrix();
	

    glPopMatrix();
}

void scene_two_display(void){

	glPushMatrix();

	glBegin(GL_QUADS);
	{
		glColor3f(0.0f,(102.0f/255.0f),(102.f/255.0f));
		glVertex2f(10.0f, -10.0f);
		glVertex2f(10.0f, 10.0f);
		glVertex2f(-10.0f, 10.0f);
		glVertex2f(-10.0f, -10.0f);
	}
	glEnd();

		glPushMatrix();
			DrawHappy();
		glPopMatrix();

		glPushMatrix();
			DrawBirthday();
		glPopMatrix();

		glPushMatrix();
			DrawHemalata();
		glPopMatrix();
	glPopMatrix();
}
void update(void){

    // update all events and stuff here

    static time_t now;
    static int current;

    if (start)
    {
		if(now != time(NULL))
		{
			delta += 1;
			now = time(NULL);
			printf("Time in Sec %d\n",delta);
		}

        if (!scene_done)
        {
            switch (scene)
            {
				case 1:
					scene_one_update(delta);
					break;
				case 2:
					scene_two_update(delta);
					break;
				default:
					break;
            }
        }
    }
    glutPostRedisplay();
}

void scene_one_update(GLint sec){

	switch(state){

		case -1:
			if(fade >= 0.0f)
				fade -= 0.01f;

			if(fade <= 0.0f)
				state = 0;
		break;

		case 0:
			if(SunPositionY <= 1.0f)
				SunPositionY += (0.002f);
			
			if(SunFactor <= 1.0f)
				SunFactor += 0.001f;

			if(SunFactor >= 1.0f)
				state = 1;	
		break;
		case 1:

			if(boatX <= 0.0f)
				boatX += 0.001f;

			if(boatY >= -2.0f)
				boatY -= 0.001f;

			if(sec > 21)
				state = 2;
		break;
		case 2:

			if(fade <= 1.0f)
				fade += 0.01f;
			
			if(fade >= 1.0f)
				state = 3;
		break;
		case 3:
		state = -1;
		fade = 1.0f;
		scene = 2;
		printf("Scene 2");
		break;
	}
}

void scene_two_update(GLint sec){

	switch(state){

		case -1:
			if(fade >= 0.0f)
				fade -= 0.01f;

			if(fade <= 0.0f)
				state = 0;
		break;

		case 0:

			if(happy_x_mov <= -0.5f)
				happy_x_mov += 0.01f;

			if(happy_x_mov >= -0.5f)
				state = 1;
		break;
		case 1:
			if(birthday_x_mov >= -0.5f)
				birthday_x_mov -= 0.01f;

			if(birthday_x_mov <= -0.5f)
				state = 2;
		break;

		case 2:

			if(hemalata_y_mov <= -0.5f)
				hemalata_y_mov += 0.01f;

			if(hemalata_y_mov >= -0.5f)
				state = 3;
		break;
		case 3:
		break;
	}
}


void keyboard(unsigned char key,int x,int y)
{
    switch(key)
    {
        case 27:
            glutLeaveMainLoop();
        break;
        case 'F':
        case 'f':
            if(b_FullScreen == false)
            {
                glutFullScreen();
                b_FullScreen = true;
            }else
            {
                glutLeaveFullScreen();
                b_FullScreen = false;
            }
        break;
		case ' ':
			printf("Start\n");
			start = true;
			// Play Music Code
			scene_done = false;
			state = -1;
			#if AUDIO
			alSourcePlay(sourceOAL);
            alGetSourcei(sourceOAL, AL_SOURCE_STATE, &source_state);
			#endif
		break;
        default:
        break;
    }
}

void mouse(int button,int state,int x,int y)
{
    switch(button)
    {
        case GLUT_LEFT_BUTTON:
            glutLeaveMainLoop();
        break;
        default:
        break;
    }
}

void uninitialize(void)
{

	#if AUDIO
	alDeleteSources(1, &sourceOAL);
    alDeleteBuffers(1, &bufferOAL);
    deviceOAL = alcGetContextsDevice(contextOAL);
    alcMakeContextCurrent(NULL);
    alcDestroyContext(contextOAL);
    alcCloseDevice(deviceOAL);
	#endif

}

// Object Drawing Calls

void ppb_trees(void){
	// variable declarations
	float x_center, y_center, radius;

	// code
	glBegin(GL_TRIANGLES);

	glColor3f(0.4f * SunFactor, 0.1f * SunFactor, 0.1f * SunFactor);
	glVertex3f(-0.8f, -0.4f, 0.0f);
	glVertex3f(-0.9f, -0.9f, 0.0f);
	glVertex3f(-0.7f, -0.9f, 0.0f);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0.0f * SunFactor, 0.6f * SunFactor, 0.1f * SunFactor);
	x_center = -0.8f;
	y_center = -0.30f;
	radius = 0.15f;
	for (int iLoop = 0; iLoop < 100; iLoop++)
	{
		float angle = 2.0f * M_PI * iLoop / 100;
		glVertex2f((x_center + (radius * cos(angle))), (y_center + (radius * sin(angle))));
	}
	glEnd();

	glBegin(GL_POLYGON);
	x_center = -0.8f;
	y_center = -0.08f;
	radius = 0.1f;
	glColor3f(0.0f * SunFactor, 0.6f * SunFactor, 0.1f * SunFactor);
	for (int iLoop = 0; iLoop < 100; iLoop++)
	{
		float angle = 2.0f * M_PI * iLoop / 100;
		glVertex2f((x_center + (radius * cos(angle))), (y_center + (radius * sin(angle))));
	}
	glEnd();

	glBegin(GL_POLYGON);
	x_center = -0.8f;
	y_center = 0.07f;
	radius = 0.05f;
	glColor3f(0.0f * SunFactor, 0.6f * SunFactor, 0.1f * SunFactor);
	for (int iLoop = 0; iLoop < 100; iLoop++)
	{
		float angle = 2.0f * M_PI * iLoop / 100;
		glVertex2f((x_center + (radius * cos(angle))), (y_center + (radius * sin(angle))));
	}
	glEnd();

	glBegin(GL_TRIANGLES);

	glColor3f(0.4f * SunFactor, 0.1f * SunFactor, 0.1f * SunFactor);
	glVertex2f(2.5f, -0.25f);
	glVertex2f(2.5f, -1.25f);
	glVertex2f(2.55f, -0.25f);
	glVertex2f(2.55f, -0.25f);
	glVertex2f(2.5f, -1.25f);
	glVertex2f(2.55f, -1.25f);

	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.0f * SunFactor, 0.6f * SunFactor, 0.1f * SunFactor);
	x_center = 2.52f;
	y_center = -0.50f;
	radius = 0.15f;
	for (int iLoop = 0; iLoop < 100; iLoop++)
	{
		float angle = 2.0f * M_PI * iLoop / 100;
		glVertex2f((x_center + (radius * cos(angle))), (y_center + (radius * sin(angle))));
	}
	glEnd();

	glBegin(GL_POLYGON);
	x_center = 2.52f;
	y_center = -0.30f;
	radius = 0.1f;
	glColor3f(0.0f * SunFactor, 0.6f * SunFactor, 0.1f * SunFactor);
	for (int iLoop = 0; iLoop < 100; iLoop++)
	{
		float angle = 2.0f * M_PI * iLoop / 100;
		glVertex2f((x_center + (radius * cos(angle))), (y_center + (radius * sin(angle))));
	}
	glEnd();

	glBegin(GL_POLYGON);
	x_center = 2.52f;
	y_center = -0.16f;
	radius = 0.05f;
	glColor3f(0.0f * SunFactor, 0.6f * SunFactor, 0.1f * SunFactor);
	for (int iLoop = 0; iLoop < 100; iLoop++)
	{
		float angle = 2.0f * M_PI * iLoop / 100;
		glVertex2f((x_center + (radius * cos(angle))), (y_center + (radius * sin(angle))));
	}
	glEnd();
}

void grp_draw_sky(void)
{
    glBegin(GL_QUADS);
	{
		glColor3f(1 * SunFactor, 1 * SunFactor, 0.4 * SunFactor);
		glVertex2f(1.0f, 0.0f);
		glColor3f(0.6 * SunFactor, 0.7 * SunFactor, 0.7 * SunFactor);
		glVertex2f(1.0f, 1.0f);
		glColor3f(0.6 * SunFactor, 0.7 * SunFactor, 0.7 * SunFactor);
		glVertex2f(-1.0f, 1.0f);
		glColor3f(1 * SunFactor, 1 * SunFactor, 0.4 * SunFactor);
		glVertex2f(-1.0f, 0.0f);
	}
	glEnd();
    glPopMatrix();
}

void grp_draw_sun(void){
    
	int i;
	float angle;
	float SunRadius = 0.1f, RaysLength = 0.15f;
	float x_center = 0.0f, y_center = 0.0f;

	glColor3f(1, 0.7, 0);
	float GreenColor = 0.65f;

	//Drawing Sun Rays
	glBegin(GL_LINES);
	{

		for (i = 0; i < 100; i++)
		{
			glVertex2f(0, 0);
			angle = (2.0f * M_PI) * (i / 100.0f);
			glVertex2f((x_center + (RaysLength - ((i % 2 == 0) ? 0.025 : 0)) * cos(angle)), (y_center + (RaysLength - ((i % 2 == 0) ? 0.025 : 0)) * sin(angle)));


		}
	}
	glEnd();

	//Drawing Sun Core
	for (int j = 0; j < 30; j++)
	{
		glColor3f(1, GreenColor, 0);

		glBegin(GL_POLYGON);
		{
			for (i = 0; i < 100; i++)
			{
				angle = (2.0f * M_PI) * (i / 100.0f);
				glVertex2f((x_center + SunRadius * cos(angle)), (y_center + SunRadius * sin(angle)));

			}
		}
		glEnd();
		
		if (SunRadius > 0)
			SunRadius -= 0.005f;
		
		GreenColor += 0.01f;
	}
}
void grp_draw_greenland(void){

    //Green Land
	glBegin(GL_QUADS);
	{

		glColor3f(0.6 * SunFactor, 0.9 * SunFactor, 0.0 * SunFactor);
		glVertex2f(1, -1);
		glColor3f(0.2 * SunFactor, 0.9 * SunFactor, 0);
		glVertex2f(1, 0.0);
		glColor3f(0.2 * SunFactor, 0.9 * SunFactor, 0);
		glVertex2f(-1, 0.0);
		glColor3f(0.6 * SunFactor, 0.9 * SunFactor, 0.0);
		glVertex2f(-1, -1);
	}

	glEnd();
}
void grp_draw_mountains(void){

    float ShadedMounatainColor[3] = { 0.7f * SunFactor, 0.2f * SunFactor, 0.9f * SunFactor };
	float SunRaysMountainColor[3] = { 0.7f * SunFactor, 0.8f * SunFactor, 0.9f * SunFactor };
	float MountainTopColor[3] = { 1.0f * SunFactor, 1.0f * SunFactor, 0 };
	float MountainShadowColor[3] = { 0, 0.6f * SunFactor, 0 };
	float ShadowTrianglePositionY = (SunPositionY - 0.7) >= 0.3 ? 0.3 : (SunPositionY - 0.7);
	
	glBegin(GL_TRIANGLES);
	//Right Mountain 
	glColor3fv(ShadedMounatainColor);
	glVertex2f(1, 0.3);
	glColor3fv(MountainTopColor);
	glVertex2f(0.8, 0.55);
	glColor3fv(ShadedMounatainColor);
	glVertex2f(0.4, 0.3);

	glColor3fv(ShadedMounatainColor);
	glVertex2f(1, 0.3);
	glColor3fv(SunRaysMountainColor);
	glVertex2f(0.8, 0.55);
	glColor3fv(ShadedMounatainColor);
	glVertex2f(0.75, 0.3);
	
	//Right Mountain Shadow
	glColor3fv(MountainShadowColor);
	glVertex2f(1, 0.3);
	glVertex2f(0.75, 0.3);
	glVertex2f(0.97, ShadowTrianglePositionY);

	
	//Middle Mountain
	glColor3fv(ShadedMounatainColor);
	glVertex2f(0.6, 0.3);
	glColor3fv(MountainTopColor);
	glVertex2f(0.1, 0.7);
	glColor3fv(ShadedMounatainColor);
	glVertex2f(-0.5, 0.3);

	glColor3fv(ShadedMounatainColor);
	glVertex2f(0.6,0.3);
	glColor3fv(SunRaysMountainColor);
	glVertex2f(0.1, 0.7);
	glColor3fv(ShadedMounatainColor);
	glVertex2f(0, 0.3);
	
	//Middle Mountain Shadow
	glColor3fv(MountainShadowColor);
	glVertex2f(0.6, 0.3);
	glVertex2f(0, 0.3);
	glVertex2f(0.6, ShadowTrianglePositionY);
	

	//Left mountain
	glColor3fv(ShadedMounatainColor);
	glVertex2f(-0.3, 0.3);
	glColor3fv(MountainTopColor);
	glVertex2f(-1, 1.3);
	glColor3fv(ShadedMounatainColor);
	glVertex2f(-1.7, 0.3);

	glColor3fv(ShadedMounatainColor);
	glVertex2f(-0.3, 0.3);
	glColor3fv(SunRaysMountainColor);
	glVertex2f(-1, 1.3);
	glColor3fv(ShadedMounatainColor);
	glVertex2f(-1.2, 0.3);

	//Left Mountain Shadow
	glColor3fv(MountainShadowColor);
	glVertex2f(-0.3, 0.3);
	glVertex2f(-1.1, 0.3);
	glVertex2f(-1.1, ShadowTrianglePositionY);
	glEnd();
}


// Srushti Functions

// House()
void sum_House(void)
{	
	
	glBegin(GL_POLYGON); // Rectangle - 3	

	glColor3f(0.412 * SunFactor, 0.412 * SunFactor, 0.412 * SunFactor); // Dim Grey
	glVertex3f(0.3f, 0.0f, 0.0f);

	glColor3f(0.663 * SunFactor, 0.663 * SunFactor, 0.663 * SunFactor); // Dark Grey
	glVertex3f(0.3f, 0.5f, 0.0f); 

	glColor3f(0.412 * SunFactor, 0.412 * SunFactor, 0.412 * SunFactor); // Dim Grey
	glVertex3f(0.7f, 0.5f, 0.0f);

	glColor3f(0.412 * SunFactor, 0.412 * SunFactor, 0.412 * SunFactor); // Dim Grey
	glVertex3f(0.7f, 0.0f, 0.0f);

	glEnd();

	glBegin(GL_POLYGON); // Rectangle - 4

	glColor3f(0.412 * SunFactor, 0.412 * SunFactor, 0.412 * SunFactor); // Dim Grey
	glVertex3f(0.0f, 0.0f, 0.0f);

	glColor3f(0.663 * SunFactor, 0.663 * SunFactor, 0.663 * SunFactor);  // Dark Grey
	glVertex3f(0.0f, 0.5f, 0.0f);

	glColor3f(0.412 * SunFactor, 0.412* SunFactor, 0.412* SunFactor); // Dim Grey
	glVertex3f(0.3f, 0.5f, 0.0f);

	glColor3f(0.412* SunFactor, 0.412* SunFactor, 0.412* SunFactor); // Dim Grey
	glVertex3f(0.3f, 0.0f, 0.0f);

	glEnd();

	glBegin(GL_POLYGON); // Polygon - 2

	glColor3f(0.545 * SunFactor, 0.271 * SunFactor, 0.075 * SunFactor); // Saddle Brown
	glVertex3f(0.3f, 0.5f, 0.0f);

	glColor3f(0.804 * SunFactor, 0.522 * SunFactor, 0.247 * SunFactor); // Peru
	glVertex3f(0.15f, 0.7f, 0.0f);

	glColor3f(0.804 * SunFactor, 0.522 * SunFactor, 0.247 * SunFactor); // Peru
	glVertex3f(0.55f, 0.7f, 0.0f);

	glColor3f(0.545 * SunFactor, 0.271 * SunFactor, 0.075 * SunFactor); // Saddle Brown
	glVertex3f(0.7f, 0.5f, 0.0f);

	glEnd();


	glBegin(GL_POLYGON); // Triangle - 1

	glColor3f(0.804 * SunFactor, 0.522 * SunFactor, 0.247 * SunFactor); // Peru
	glVertex3f(0.0f, 0.5f, 0.0f);

	glColor3f(0.545 * SunFactor, 0.271 * SunFactor, 0.075 * SunFactor); // Saddle Brown
	glVertex3f(0.15f, 0.7f, 0.0f);

	glColor3f(0.545 * SunFactor, 0.271 * SunFactor, 0.075 * SunFactor); // Saddle Brown
	glVertex3f(0.3f, 0.5f, 0.0f);

	glEnd();

	
	// glColor3f(0.66, 0.66, 0.66);
	glBegin(GL_POLYGON); // Window - L	

	glColor3f(0.529 * SunFactor, 0.808 * SunFactor, 0.980 * SunFactor); // Light Sky Blue
	glVertex3f(0.35f, 0.15f, 0.0f);

	glColor3f(0.118 * SunFactor, 0.564 * SunFactor, 1.0 * SunFactor); // Deep Sky Blue
	glVertex3f(0.35f, 0.35f, 0.0f);

	glColor3f(0.529 * SunFactor, 0.808 * SunFactor, 0.980 * SunFactor); // Light Sky Blue
	glVertex3f(0.45f, 0.35f, 0.0f);

	glColor3f(0.529 * SunFactor, 0.808 * SunFactor, 0.980 * SunFactor); // Light Sky Blue
	glVertex3f(0.45f, 0.15f, 0.0f);

	glEnd();

	glColor3f(0.529* SunFactor, 0.808* SunFactor, 0.980* SunFactor);
	// glColor3f(0.66, 0.66, 0.66);
	glBegin(GL_POLYGON); // Window - R	

	glColor3f(0.529* SunFactor, 0.808* SunFactor, 0.980* SunFactor); // Light Sky Blue
	glVertex3f(0.55f, 0.15f, 0.0f);

	glColor3f(0.118* SunFactor, 0.564* SunFactor, 1.0* SunFactor); // Deep Sky Blue
	glVertex3f(0.55f, 0.35f, 0.0f);

	glColor3f(0.529 * SunFactor, 0.808* SunFactor, 0.980* SunFactor); // Light Sky Blue
	glVertex3f(0.65f, 0.35f, 0.0f);

	glColor3f(0.529* SunFactor, 0.808* SunFactor, 0.980* SunFactor); // Light Sky Blue
	glVertex3f(0.65f, 0.15f, 0.0f);

	glEnd();

	
	glBegin(GL_POLYGON); // Door - 1

	glColor3f(0.804 * SunFactor, 0.522 * SunFactor, 0.247 * SunFactor); // Peru
	glVertex3f(0.07f, 0.0f, 0.0f);

	glColor3f(0.804 * SunFactor, 0.522 * SunFactor, 0.247 * SunFactor); // Peru
	glVertex3f(0.07f, 0.27f, 0.0f);

	glColor3f(0.545 * SunFactor, 0.271 * SunFactor, 0.075 * SunFactor); // Saddle Brown
	glVertex3f(0.23f, 0.27f, 0.0f);

	glColor3f(0.545 * SunFactor, 0.271 * SunFactor, 0.075 * SunFactor); // Saddle Brown
	glVertex3f(0.23f, 0.0f, 0.0f);

	glEnd();

	glColor3f(0.647 * SunFactor, 0.165 * SunFactor, 0.165 * SunFactor); // Brown
	glBegin(GL_LINE_STRIP); // Door Frame - 1

	glVertex3f(0.07f, 0.0f, 0.0f);
	glVertex3f(0.07f, 0.27f, 0.0f);
	glVertex3f(0.23f, 0.27f, 0.0f);
	glVertex3f(0.23f, 0.0f, 0.0f);

	glEnd();

}

// House - Circle
void sum_circle(void)
{
	
	glBegin(GL_POLYGON);

	float radius = 0.035f;
	float x_centre = 0.15f;
	float y_centre = 0.5656f;
	for (int i = 0; i < 1000; i++)
	{
		float angle = 2.0f * M_PI * i / 1000;
		glVertex2f(x_centre + radius * cos(angle), y_centre + radius * sin(angle));
		glColor3f(0.647 * SunFactor, 0.165 * SunFactor, 0.165 * SunFactor); // Brown
	
	}
	glEnd();
}

void sum_rooflines(void)
{
	float x1 = 0.325f;
	float x2 = 0.175f;
	float y1 = 0.50f;
	float y2 = 0.70f;

	for (int line_count = 0; line_count < 16; line_count++)
	{
		glColor3f(0.698 * SunFactor, 0.133 * SunFactor, 0.133 * SunFactor); // Fire Brick
		glBegin(GL_LINES);

		glVertex3f(x1, y1, 0);
		glVertex3f(x2, y2, 0);

		glEnd();
		x1 = x1 + 0.025;
		x2 = x2 + 0.025;
	}
}

// Window Grid
void sum_windowgrid(void)
{
	glColor3f(0.682 * SunFactor, 0.933 * SunFactor, 0.933 * SunFactor);  // Pale Turquoise
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

void vmk_trees(void){

	//code
	glBegin(GL_TRIANGLES);

	// Triangle 1(top of tree)
	glColor3f(0.0f * SunFactor, 0.39f * SunFactor, 0.0f* SunFactor); // colors (RGB) 
	glVertex3f(0.0f, 0.2f, 0.0f); //apex vertex(upper) // 0.7f size for apex triangle is perfect  
	glVertex3f(-0.1f, 0.0f, 0.0f); //left vertex
	glVertex3f(0.1f, 0.0f, 0.0f); //right vertex 

	//Triangle 2(Middle Part Of Tree) vertex and colors
	glVertex3f(0.0f, 0.1f, 0.0f); //apex vertex(upper)
	glVertex3f(-0.2f, -0.2f, 0.0f); //left vertex
	glVertex3f(0.2f, -0.2f, 0.0f); //right vertex 

	//triangle 3(end Of tree) vertex and color change
	glVertex3f(0.0f, -0.1f, 0.0f); //apex vertex(bottom)
	glVertex3f(-0.25f, -0.5f, 0.0f); //left vertex
	glVertex3f(0.25f, -0.5f, 0.0f); //right vertex 

	glEnd();

	glBegin(GL_POLYGON);

	// Branch of tree
	glColor3f(0.7* SunFactor, 0.3* SunFactor, 0.1* SunFactor);
	glVertex3f(0.08, -0.5, 0.0);
	glVertex3f(-0.08, -0.5, 0.0);
	glVertex3f(-0.08, -1.0, 0.0);
	glVertex3f(0.08, -1.0, 0.0);

	glEnd();

	glBegin(GL_TRIANGLES);

	// Grass
	glColor3f(0.0f* SunFactor, 0.39* SunFactor, 0.0f* SunFactor);
	glVertex3f(-0.08f, -1.0f, 0.0f);
	glVertex3f(-0.10f, -0.9f, 0.0f);
	glVertex3f(-0.12f, -1.0f, 0.0f);

	glVertex3f(0.08f, -1.0f, 0.0f);
	glVertex3f(0.10f, -0.9f, 0.0f);
	glVertex3f(0.12f, -1.0f, 0.0f);

	glVertex3f(-0.12f, -1.0f, 0.0f);
	glVertex3f(-0.14f, -0.9f, 0.0f);
	glVertex3f(-0.16f, -1.0f, 0.0f);

	glVertex3f(0.12f, -1.0f, 0.0f);
	glVertex3f(0.14f, -0.9f, 0.0f);
	glVertex3f(0.16f, -1.0f, 0.0f);

	glVertex3f(-0.16f, -1.0f, 0.0f);
	glVertex3f(-0.18f, -0.9f, 0.0f);
	glVertex3f(-0.20f, -1.0f, 0.0f);

	glVertex3f(0.16f, -1.0f, 0.0f);
	glVertex3f(0.18f, -0.9f, 0.0f);
	glVertex3f(0.20f, -1.0f, 0.0f);
	glEnd();
}

void kpr_river(void){
	glBegin(GL_POLYGON);
	glColor3f(0.3f * SunFactor, 0.3f * SunFactor, 1.0f * SunFactor);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glColor3f(0.5f * SunFactor, 0.5f * SunFactor, 1.0f * SunFactor);
	glVertex3f(-1.0f, 0.25f, 0.0f);
	glVertex3f(-0.1f, 0.25f, 0.0f);
	glVertex3f(-0.15f, 0.05f, 0.0f);
	glVertex3f(-0.125f, -0.15f, 0.0f);
	glVertex3f(-0.15f, -0.4f, 0.0f);
	glVertex3f(-0.1f, -0.6f, 0.0f);
	glVertex3f(0.05f, -0.8f, 0.0f);
	glColor3f(0.3f * SunFactor, 0.3f * SunFactor, 1.0f * SunFactor);
	glVertex3f(0.5f, -1.0f, 0.0f);
	glEnd();
}

void kpr_boat(void){

	glBegin(GL_POLYGON);
	glColor3f(0.3 * SunFactor, 0.3 * SunFactor, 0.4 * SunFactor);
	glVertex3f(-0.7f, -0.5f, 0.0f);
	glColor3f(0.5* SunFactor, 0.3 * SunFactor, 0.2 * SunFactor);
	glVertex3f(-0.8f, -0.3f, 0.0f);
	glVertex3f(-0.2f, -0.3f, 0.0f);
	glColor3f(0.3 * SunFactor, 0.3 * SunFactor, 0.4 * SunFactor);
	glVertex3f(-0.3f, -0.5f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.3 * SunFactor, 0.3 * SunFactor, 0.4 * SunFactor);
	glVertex3f(-0.51f, -0.3f, 0.0f);
	glColor3f(0.5 * SunFactor, 0.5 * SunFactor, 0.4 * SunFactor);
	glVertex3f(-0.51f, -0.1f, 0.0f);
	glVertex3f(-0.49f, -0.1f, 0.0f);
	glColor3f(0.3 * SunFactor, 0.3 * SunFactor, 0.4 * SunFactor);
	glVertex3f(-0.49f, -0.3f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0 * SunFactor, 0.5 * SunFactor, 0.0* SunFactor);
	glVertex3f(-0.5f, -0.1f, 0.0f);
	glVertex3f(-0.5f, 0.0f, 0.0f);
	glColor3f(1.0 * SunFactor, 0.8 * SunFactor, 0.3 * SunFactor);
	glVertex3f(-0.58f, -0.1f, 0.0f);
	glEnd();
}

void DrawHappy()
{
	float LetColor[3] = { 1,0.70,0 };

	//glLoadIdentity();
	glTranslatef(happy_x_mov, happy_y_mov, happy_z_mov);

	glScalef(0.3, 0.3, 0);
	
	glTranslatef(-0.9, 0, 0);
	H(LetColor);

	glTranslatef(0.6, 0, 0);
	A(LetColor);
	
	glTranslatef(0.6, 0, 0);
	P(LetColor);
	
	glTranslatef(0.6, 0, 0);
	P(LetColor);
	
	glTranslatef(0.6, 0, 0);
	Y(LetColor);
	

}

void DrawBirthday(void)
{
	float LetColor[3] = { 1,0.70,0 };

	//glLoadIdentity();

	glTranslatef(birthday_x_mov, birthday_y_mov, birthday_z_mov);
	glScalef(0.3, 0.3, 0);

	glTranslatef(-0.9, 0, 0);
	B(LetColor);

	glTranslatef(0.6, 0, 0);
	I(LetColor);

	glTranslatef(0.6, 0, 0);
	R(LetColor);
	
	glTranslatef(0.6, 0, 0);
	T(LetColor);

	glTranslatef(0.6, 0, 0);
	H(LetColor);
	
	glTranslatef(0.6, 0, 0);
	D(LetColor);
	
	glTranslatef(0.6, 0, 0);
	A(LetColor);
	
	glTranslatef(0.6, 0, 0);
	Y(LetColor);
	

}
void DrawHemalata(void)
{
	float LetColor[3] = { 1,0.70,0 };

	//glLoadIdentity();

	glTranslatef(hemalata_x_mov, hemalata_y_mov, hemalata_z_mov);
	glScalef(0.3, 0.3, 0);

	glTranslatef(-0.9, 0, 0);
	H(LetColor);
	
	glTranslatef(0.6, 0, 0);
	E(LetColor);
	
	glTranslatef(0.6, 0, 0);
	M(LetColor);
	
	glTranslatef(0.6, 0, 0);
	A(LetColor);
	
	glTranslatef(0.6, 0, 0);
	L(LetColor);
	
	glTranslatef(0.6, 0, 0);
	A(LetColor);
	
	glTranslatef(0.6, 0, 0);
	T(LetColor);
	
	glTranslatef(0.6, 0, 0);
	A(LetColor);
	
}

void A(float LetterColor[])
{
	glColor3fv(LetterColor);
	glBegin(GL_QUADS);

	glVertex2f(0, 0.6);
	glVertex2f(0, 0.5);
	glVertex2f(-0.2, 0);
	glVertex2f(-0.25, 0);

	glVertex2f(0.1, 0.25);
	glVertex2f(0.15, 0.25);
	glVertex2f(0.25, 0);
	glVertex2f(0.2, 0);

	glVertex2f(0.1, 0.25);
	glVertex2f(0.13, 0.2);
	glVertex2f(0, 0.2);
	glVertex2f(0, 0.25);

	glEnd();
}

void H(float LetterColor[])
{
	glColor3fv(LetterColor);
	glBegin(GL_QUADS);

	glVertex2f(-0.25, 0.6);
	glVertex2f(-0.2, 0.6);
	glVertex2f(-0.2, 0);
	glVertex2f(-0.25, 0);

	glVertex2f(0.2, 0.27);
	glVertex2f(0.2, 0.33);
	glVertex2f(-0.1, 0.33);
	glVertex2f(-0.1, 0.27);

	glVertex2f(0.25, 0.6);
	glVertex2f(0.2, 0.6);
	glVertex2f(0.2, 0);
	glVertex2f(0.25, 0);
	glEnd();
}

void Y(float LetterColor[])
{
	glColor3fv(LetterColor);
	glBegin(GL_QUADS);

	glVertex2f(-0.25, 0.6);
	glVertex2f(-0.2, 0.6);
	glVertex2f(0.025, 0.3);
	glVertex2f(-0.025, 0.3);

	glVertex2f(0.25, 0.6);
	glVertex2f(0.2, 0.6);
	glVertex2f(0.1, 0.45);
	glVertex2f(0.1, 0.38);

	glVertex2f(-0.025, 0.3);
	glVertex2f(0.025, 0.3);
	glVertex2f(0.025, 0);
	glVertex2f(-0.025, 0);

	glEnd();
}

void T(float LetterColor[])
{
	glColor3fv(LetterColor);
	glBegin(GL_QUADS);

	glVertex2f(0.25, 0.6);
	glVertex2f(0.25, 0.55);
	glVertex2f(-0.25, 0.55);
	glVertex2f(-0.25, 0.6);

	glVertex2f(-0.025, 0.53);
	glVertex2f(0.025, 0.53);
	glVertex2f(0.025, 0);
	glVertex2f(-0.025, 0);

	glEnd();
}

void L(float LetterColor[])
{
	glColor3fv(LetterColor);
	glBegin(GL_QUADS);

	glVertex2f(-0.25, 0.6);
	glVertex2f(-0.2, 0.6);
	glVertex2f(-0.2, 0);
	glVertex2f(-0.25, 0);

	glVertex2f(-0.18, 0);
	glVertex2f(-0.18, 0.05);
	glVertex2f(0.25, 0.05);
	glVertex2f(0.25, 0);

	glEnd();
}

void E(float LetterColor[])
{
	glColor3fv(LetterColor);
	glBegin(GL_QUADS);

	glVertex2f(-0.25, 0.6);
	glVertex2f(-0.2, 0.6);
	glVertex2f(-0.2, 0);
	glVertex2f(-0.25, 0);

	glVertex2f(-0.18, 0);
	glVertex2f(-0.18, 0.05);
	glVertex2f(0.25, 0.05);
	glVertex2f(0.25, 0);

	glVertex2f(-0.18, 0.325);
	glVertex2f(-0.18, 0.275);
	glVertex2f(0, 0.275);
	glVertex2f(0, 0.325);

	glVertex2f(-0.18, 0.6);
	glVertex2f(-0.18, 0.55);
	glVertex2f(0.25, 0.55);
	glVertex2f(0.25, 0.6);

	glEnd();
}

void M(float LetterColor[])
{
	glColor3fv(LetterColor);
	glBegin(GL_QUADS);

	glVertex2f(-0.25, 0.6);
	glVertex2f(-0.2, 0.6);
	glVertex2f(-0.2, 0);
	glVertex2f(-0.25, 0);
	
	glVertex2f(0, 0.03);
	glVertex2f(0, 0.12);
	glVertex2f(0.20,0.6);
	glVertex2f(0.25, 0.6);
	
	glVertex2f(0, 0.03);
	glVertex2f(0, 0.12);
	glVertex2f(-0.20, 0.6);
	glVertex2f(-0.25, 0.6);

	glVertex2f(0.25, 0.47);
	glVertex2f(0.2, 0.37);
	glVertex2f(0.2, 0);
	glVertex2f(0.25, 0);
	glEnd();
}

void P(float LetterColor[])
{
	glColor3fv(LetterColor);
	glBegin(GL_QUADS);

	glVertex2f(-0.25, 0.6);
	glVertex2f(-0.2, 0.6);
	glVertex2f(-0.2, 0);
	glVertex2f(-0.25, 0);

	glVertex2f(-0.18, 0.6);
	glVertex2f(-0.18, 0.55);
	glVertex2f(0.25, 0.55);
	glVertex2f(0.25, 0.6);

	glVertex2f(0.25,0.6);
	glVertex2f(0.2,0.6);
	glVertex2f(0.2,0.275);
	glVertex2f(0.25,0.275);

	glVertex2f(-0.18, 0.325);
	glVertex2f(-0.18, 0.275);
	glVertex2f(0.25, 0.275);
	glVertex2f(0.25, 0.325);
	glEnd();
	
}

void B(float LetterColor[])
{
	glColor3fv(LetterColor);
	glBegin(GL_QUADS);

	glVertex2f(-0.25, 0.6);
	glVertex2f(-0.2, 0.6);
	glVertex2f(-0.2, 0);
	glVertex2f(-0.25, 0);

	glVertex2f(-0.18, 0);
	glVertex2f(-0.18, 0.05);
	glVertex2f(0.25, 0.05);
	glVertex2f(0.25, 0);

	glVertex2f(-0.18, 0.325);
	glVertex2f(-0.18, 0.275);
	glVertex2f(0.25, 0.275);
	glVertex2f(0.25, 0.325);

	glVertex2f(-0.18, 0.6);
	glVertex2f(-0.18, 0.55);
	glVertex2f(0.25, 0.55);
	glVertex2f(0.25, 0.6);

	glVertex2f(0.25, 0.6);
	glVertex2f(0.2, 0.6);
	glVertex2f(0.2, 0);
	glVertex2f(0.25, 0);
	glEnd();
}

void D(float LetterColor[])
{
	glColor3fv(LetterColor);
	glBegin(GL_QUADS);

	glVertex2f(-0.25, 0.6);
	glVertex2f(-0.2, 0.6);
	glVertex2f(-0.2, 0);
	glVertex2f(-0.25, 0);

	glVertex2f(-0.18, 0.6);
	glVertex2f(-0.18, 0.55);
	glVertex2f(0.15, 0.55);
	glVertex2f(0.15, 0.6);

	glVertex2f(0.15, 0.55);
	glVertex2f(0.15, 0.6);
	glVertex2f(0.25, 0.45);
	glVertex2f(0.23, 0.40);

	glVertex2f(-0.18, 0);
	glVertex2f(-0.18, 0.05);
	glVertex2f(0.15, 0.05);
	glVertex2f(0.15, 0);

	glVertex2f(0.15, 0.05);
	glVertex2f(0.15, 0);
	glVertex2f(0.25, 0.1);
	glVertex2f(0.25, 0.15);

	glVertex2f(0.20, 0.45);
	glVertex2f(0.25, 0.45);
	glVertex2f(0.25, 0.1);
	glVertex2f(0.20, 0.1);

	glEnd();
}


void R(float LetterColor[])
{
	glColor3fv(LetterColor);
	glBegin(GL_QUADS);

	glVertex2f(-0.25, 0.6);
	glVertex2f(-0.2, 0.6);
	glVertex2f(-0.2, 0);
	glVertex2f(-0.25, 0);


	glVertex2f(-0.18, 0.6);
	glVertex2f(-0.18, 0.55);
	glVertex2f(0.25, 0.55);
	glVertex2f(0.25, 0.6);

	glVertex2f(0.25, 0.6);
	glVertex2f(0.2, 0.6);
	glVertex2f(0.2, 0.275);
	glVertex2f(0.25, 0.275);

	glVertex2f(-0.18, 0.325);
	glVertex2f(-0.18, 0.275);
	glVertex2f(0.25, 0.275);
	glVertex2f(0.25, 0.325);

	glVertex2f(-0.18, 0.25);
	glVertex2f(-0.12, 0.25);
	glVertex2f(0.25,0);
	glVertex2f(0.18,0);
	glEnd();
}

void I(float LetterColor[])
{
	glColor3fv(LetterColor);
	glBegin(GL_QUADS);

	glVertex2f(0.25, 0.6);
	glVertex2f(0.25, 0.55);
	glVertex2f(-0.25, 0.55);
	glVertex2f(-0.25, 0.6);

	glVertex2f(-0.025, 0.53);
	glVertex2f(0.025, 0.53);
	glVertex2f(0.025, 0.07);
	glVertex2f(-0.025, 0.07);

	glVertex2f(-0.25, 0);
	glVertex2f(-0.25, 0.05);
	glVertex2f(0.25, 0.05);
	glVertex2f(0.25, 0);

	glEnd();
}
