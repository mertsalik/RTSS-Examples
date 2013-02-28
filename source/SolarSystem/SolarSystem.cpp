// Homework1.cpp : Defines the entry point for the console application.


#include <iostream>
#include <Windows.h>
#include <GL/glut.h>
#include "UIHelper.h"

GLdouble angle = 0;
UIHelper *helper;

static void Draw(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();



	glTranslatef(0.f, 0.f, -20.f);
	glPushMatrix();// universe

	// sun
	glRotated(angle, 0, 1, 0);
	glColor3ub(255, 0, 0);
	glColor3f(1, 0, 0);
	helper->CreateSphere();

	glPushMatrix();// based on sun

	// earth
	glRotated(angle, 0, 1, 0);
	glTranslatef(10.f,0.f,0.f);
	glColor3ub(0,255,0);
	glRotated(angle, 0, 1, 0);
	helper->CreateSphere();

	glPushMatrix(); // based on earth

	// moon
	glRotated(angle, 0, 1, 0);
	glTranslatef(2.f,0.f,0.f);
	glColor3ub(0,0,255);
	glRotated(angle, 0, 1, 0);
	helper->CreateSphere();

	glPopMatrix(); // base turned to earth

	
	glPopMatrix(); // base turned to sun

	glPushMatrix(); // based on venus

	// venus
	glRotated(angle, 0, 1, 0);
	glTranslatef(5.f,0.f,0.f);
	glColor3ub(255,0,255);
	glRotated(angle, 0, 1, 0);
	helper->CreateSphere();



	glPushMatrix(); // based on satellite of venus

	// satellite
	glRotated(angle, 0, 1, 0);
	glTranslatef(2.f,0.f,0.f);
	glColor3ub(255,255,255);
	glRotated(angle, 0, 1, 0);
	helper->CreateSphere();

	glPopMatrix(); // base turned to venus

	glPopMatrix(); // base turned to sun

	// base turned to universe
	glPopMatrix();
	glutSwapBuffers();

}

static void timerCallback (int value)
{

	angle ++;

	glutTimerFunc(10, timerCallback, 0);
	glutPostRedisplay();
}

int main (int argc, char ** argv)
{

	GLenum type;
	helper = new UIHelper();

	glutInit(&argc, argv);
	glutInitWindowSize(800,600);
	type = GLUT_RGB;
	type |= GLUT_DOUBLE;
	type |= GLUT_DEPTH;
	type |= GLUT_MULTISAMPLE;
	glutInitDisplayMode(type);
	glutCreateWindow("Solar System");

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glEnable(GL_DEPTH_TEST);


	glMatrixMode(GL_PROJECTION);
	gluPerspective(55, 800/600, 0.1, 100);

	glMatrixMode(GL_MODELVIEW);

	timerCallback(0);
	glutDisplayFunc(Draw);
	glutMainLoop();
	// insert code here...
	std::cout << "Preparing solar system !\n";
	return 0;
}

