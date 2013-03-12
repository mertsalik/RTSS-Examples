// Homework1.cpp : Defines the entry point for the console application.

#include "Common.h"
#include "UIHelper.h"
#include "GLHelper.h"

GLdouble angle = 0;
GLHelper *gl;

static void Draw(void)
{
	/*
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();



	glTranslatef(0.f, 0.f, -20.f);
	glPushMatrix();// universe

	// sun
	glRotated(angle, 0, 1, 0);
	glColor3ub(255, 0, 0);
	glColor3f(1, 0, 0);
	ui->CreateSphere();

	glPushMatrix();// based on sun

	// earth
	glRotated(angle, 0, 1, 0);
	glTranslatef(10.f,0.f,0.f);
	glColor3ub(0,255,0);
	glRotated(angle, 0, 1, 0);
	ui->CreateSphere();

	glPushMatrix(); // based on earth

	// moon
	glRotated(angle, 0, 1, 0);
	glTranslatef(2.f,0.f,0.f);
	glColor3ub(0,0,255);
	glRotated(angle, 0, 1, 0);
	ui->CreateSphere();

	glPopMatrix(); // base turned to earth


	glPopMatrix(); // base turned to sun

	glPushMatrix(); // based on venus

	// venus
	glRotated(angle, 0, 1, 0);
	glTranslatef(5.f,0.f,0.f);
	glColor3ub(255,0,255);
	glRotated(angle, 0, 1, 0);
	ui->CreateSphere();



	glPushMatrix(); // based on satellite of venus

	// satellite
	glRotated(angle, 0, 1, 0);
	glTranslatef(2.f,0.f,0.f);
	glColor3ub(255,255,255);
	glRotated(angle, 0, 1, 0);
	ui->CreateSphere();

	glPopMatrix(); // base turned to venus

	glPopMatrix(); // base turned to sun

	// base turned to universe
	glPopMatrix();
	glutSwapBuffers();
	*/
}

int main (int argc, char ** argv)
{

	gl = new GLHelper();
	glutInit(&argc, argv);

	gl->InitGL();

	UIHelper::getInstance().ClearColor();
	UIHelper::getInstance().LoadTextures();
	UIHelper::getInstance().SetupLights();

	//glMatrixMode(GL_PROJECTION);
	//gluPerspective(55, 800/600, 0.1, 100);

	//glMatrixMode(GL_MODELVIEW);

	UIHelper::DisplayCallback(0);
	glutDisplayFunc(gl->Draw);
	glutMainLoop();

	return 0;
}

