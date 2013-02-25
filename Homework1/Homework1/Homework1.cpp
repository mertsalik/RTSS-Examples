// Homework1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <GL/glut.h>


static void DrawBox();

GLenum doubleBuffer;

float angle=0;

static void Init(){
	// Background Color
	glClearColor(1.0, 0.0, 0.0, 1.0);

	// Draw Lines (Wireframe)
	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	
}

static void Draw(void)
{
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	// Set Angle
	glRotatef(angle, 1, 1, 1);
	DrawBox(); 
		
	glutSwapBuffers();
}
static void Key(unsigned char key, int x, int y)
{
	switch (key) {
		case 27:
			exit(0);
	}
}

static void timerCallback (int value)
{
	// Do timer processing
	angle+=1;
	
	// call back again after 10ms have passed
	glutTimerFunc(10, timerCallback, value);
	// Re-draw
	glutPostRedisplay();
}

int main(int argc,  char * argv[])
{
	GLenum type;
	
	glutInit(&argc, argv);
	
	type = GLUT_RGB;
	type |= GLUT_DOUBLE;
	glutInitDisplayMode(type);
	glutCreateWindow("Ders 1");
	
    Init();
	glutKeyboardFunc(Key);
	glutDisplayFunc(Draw);
	timerCallback(0);
	glutMainLoop();
	return 0;
}

static void DrawBox(){
	glPushMatrix();
	glTranslatef(-0.5f, -0.5f, -0.5f);
	glBegin(GL_POLYGON);/* f1: front */
	glNormal3f(-1.0f,0.0f,0.0f);
	glVertex3f(0.0f,0.0f,0.0f);
	glVertex3f(0.0f,0.0f,1.0f);
	glVertex3f(1.0f,0.0f,1.0f);
	glVertex3f(1.0f,0.0f,0.0f);
	glEnd();
	glBegin(GL_POLYGON);/* f2: bottom */
	glNormal3f(0.0f,0.0f,-1.0f);
	glVertex3f(0.0f,0.0f,0.0f);
	glVertex3f(1.0f,0.0f,0.0f);
	glVertex3f(1.0f,1.0f,0.0f);
	glVertex3f(0.0f,1.0f,0.0f);
	glEnd();
	glBegin(GL_POLYGON);/* f3:back */
	glNormal3f(1.0f,0.0f,0.0f);
	glVertex3f(1.0f,1.0f,0.0f);
	glVertex3f(1.0f,1.0f,1.0f);
	glVertex3f(0.0f,1.0f,1.0f);
	glVertex3f(0.0f,1.0f,0.0f);
	glEnd();
	glBegin(GL_POLYGON);/* f4: top */
	glNormal3f(0.0f,0.0f,1.0f);
	glVertex3f(1.0f,1.0f,1.0f);
	glVertex3f(1.0f,0.0f,1.0f);
	glVertex3f(0.0f,0.0f,1.0f);
	glVertex3f(0.0f,1.0f,1.0f);
	glEnd();
	glBegin(GL_POLYGON);/* f5: left */
	glNormal3f(0.0f,1.0f,0.0f);
	glVertex3f(0.0f,0.0f,0.0f);
	glVertex3f(0.0f,1.0f,0.0f);
	glVertex3f(0.0f,1.0f,1.0f);
	glVertex3f(0.0f,0.0f,1.0f);
	glEnd();
	glBegin(GL_POLYGON);/* f6: right */
	glNormal3f(0.0f,-1.0f,0.0f);
	glVertex3f(1.0f,0.0f,0.0f);
	glVertex3f(1.0f,0.0f,1.0f);
	glVertex3f(1.0f,1.0f,1.0f);
	glVertex3f(1.0f,1.0f,0.0f);
	glEnd();
	glPopMatrix();
}

