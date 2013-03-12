#include "UIHelper.h"
#include "RGBpixmap.h"

UIHelper::UIHelper(void)
{
	this->ambient = new float[4];
	float a[4] = {1.0f, 1.0f, 1.0f, 1.0f};
	std::copy(a,a+4,this->ambient);

	this->diffuse = new float[4];
	float d[4] = {1.0f, 1.0f, 1.0f, 1.0f};
	std::copy(d,d+4,this->diffuse);

	this->specular = new float[4];
	float s[4] = {1.0f, 1.0f, 1.0f, 1.0f};
	std::copy(s,s+4,this->specular);

	this->position = new float[4];
	float p[4] = {0.0f, 0.0f, 0.0f, 1.0f};
	std::copy(p,p+4,this->position);

	this->planet_count = PLANETCOUNT;


	this->ParticleTextureIndex = -1;
	this->EarthTextureIndex = 3;
	this->MoonTextureIndex = 4;
	this->SunTextureIndex = 0;
	this->MercuryTextureIndex = 1;
	this->VenusTextureIndex = 2;
	this->MarsTextureIndex = 5;
	this->JupiterTextureIndex = 6;
	this->SaturnTextureIndex = 7;
	this->UranusTextureIndex = 8;
	this->NeptuneTextureIndex = 9;
	this->PlutoTextureIndex = 10;
	this->RingTextureIndex = 11;


	speed = 1.0;
	angle = 0;
	orbitDegreesX = 0;
	orbitDegreesY = 0;
	maxZoomIn = 0.1;
	maxZoomOut = 200;
	currentZoom = 50.0;

	sunRadius = 1.0;
	mercuryRadius = 0.1;
	venusRadius = 0.18;
	marsRadius = 0.3;
	jupiterRadius = 0.6;
	saturnRadius = 0.5;
	uranusRadius = 0.3;
	neptuneRadius = 0.3;
	plutoRadius = 0.05;

	EarthDaysLeft = 0;
	CurrentEarthRotation = 0;

}


UIHelper::~UIHelper(void)
{
}

void UIHelper::CreateSphere(void)
{
	GLUquadric* quadric = gluNewQuadric();
	gluQuadricNormals(quadric, GLU_SMOOTH);

	gluSphere( quadric , 1 , 30 , 30 );
}

void UIHelper::LoadTexture(const char bitmapFilename[], GLuint &TextureIndex){
	RGBpixmap pix;
	pix.readBMPFile(bitmapFilename, false);
	pix.setTexture(TextureIndex);
	return;
}

void UIHelper::LoadTextures(){
	LoadTexture("Bitmaps/earthmap.bmp", EarthTextureIndex);
	LoadTexture("Bitmaps/moonmap.bmp",  MoonTextureIndex);
	LoadTexture("Bitmaps/sunmap.bmp",		SunTextureIndex);
	LoadTexture("Bitmaps/mercurymap.bmp", MercuryTextureIndex);
	LoadTexture("Bitmaps/venusmap.bmp", VenusTextureIndex);
	LoadTexture("Bitmaps/Particle.bmp", ParticleTextureIndex);
	LoadTexture("Bitmaps/marsmap.bmp", MarsTextureIndex);
	LoadTexture("Bitmaps/jupitermap.bmp", JupiterTextureIndex);
	LoadTexture("Bitmaps/saturnmap.bmp", SaturnTextureIndex);
	LoadTexture("Bitmaps/uranusmap.bmp", UranusTextureIndex);
	LoadTexture("Bitmaps/neptunemap.bmp", NeptuneTextureIndex);
	LoadTexture("Bitmaps/plutomap.bmp", PlutoTextureIndex);
	LoadTexture("Bitmaps/saturnringmap.bmp", RingTextureIndex);
	LoadTexture("Bitmaps/starfield/starfield_back.bmp", SkyBoxBackIndex);
	LoadTexture("Bitmaps/starfield/starfield_front.bmp", SkyBoxFrontIndex);
	LoadTexture("Bitmaps/starfield/starfield_left.bmp", SkyBoxLeftIndex);
	LoadTexture("Bitmaps/starfield/starfield_right.bmp", SkyBoxRightIndex);
	LoadTexture("Bitmaps/starfield/starfield_top.bmp", SkyBoxTopIndex);
}

void UIHelper::ClearColor(){
	glClearColor(0.0, 0.0, 0.0, 1.0);
}

void UIHelper::SetupLights(){
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}


void UIHelper::InitLightnings(){
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

void UIHelper::DisplayCallback(int value){

	UIHelper::getInstance().CurrentEarthRotation += 0.01;
	UIHelper::getInstance().EarthDaysLeft += 0.01;
	if (UIHelper::getInstance().EarthDaysLeft == 365)
		UIHelper::getInstance().EarthDaysLeft = 0;

	UIHelper::getInstance().angle += UIHelper::getInstance().getSpeed();
	glutTimerFunc(10, UIHelper::DisplayCallback, value);
	glutPostRedisplay();
}


/**
PLANET DRAWINGS
*/
void UIHelper::DrawSun(){
	GLUquadricObj* quadro = gluNewQuadric();							
	gluQuadricNormals(quadro, GLU_SMOOTH);		
	gluQuadricTexture(quadro, GL_TRUE);			
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glPushMatrix();
		glRotatef( -90.0, 1.0, 0.0, 0.0 );
		glBindTexture(GL_TEXTURE_2D, SunTextureIndex);
		gluSphere(quadro, sunRadius, 48, 48);
	glPopMatrix();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	gluDeleteQuadric(quadro);
}


void UIHelper::DrawOtherPlanets(){

	drawGenericPlanet(7, 88, 1.5,
		59, MercuryTextureIndex, 0.1);
	drawGenericPlanet(3, 225, 2.0,
		-243, VenusTextureIndex, 0.18);

	//drawGenericPlanet(2, MARS_ORBIT_DUR, 3.5,
	//MARS_ROTATION_DUR, MarsTextureName, MARS_RADIUS);

	drawGenericPlanet(1, 4333, 5.0,
		0.4, JupiterTextureIndex, 0.6);
	drawGenericPlanet(2, 10759, 7.0,
		0.4, SaturnTextureIndex, 0.5);
	drawGenericPlanet(1, 30685, 8.5,
		-0.7, UranusTextureIndex, 0.3);
	drawGenericPlanet(2, 60190, 9.0,
		0.7, NeptuneTextureIndex, 0.3);
	drawGenericPlanet(1, 90800, 10.0,
		-6, PlutoTextureIndex, 0.05);

}

void UIHelper::drawGenericPlanet(GLfloat inclination, GLfloat orbitDuration,
								 GLfloat orbitRadius, GLfloat rotationDuration, GLuint texturename, GLfloat radius)
{

	GLUquadricObj* quadro = gluNewQuadric();							
	gluQuadricNormals(quadro, GLU_SMOOTH);		
	gluQuadricTexture(quadro, GL_TRUE);			
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glPushMatrix();
			glRotatef( inclination, 0.0, 0.0, 1.0);
			glRotatef( 360.0 * (EarthDaysLeft/orbitDuration), 0.0, 1.0, 0.0);
			glTranslatef(orbitRadius, 0.0, 0.0 );
			glRotatef( 360.0 * (CurrentEarthRotation/rotationDuration), 0.0, 1.0, 0.0 );
			glRotatef( -90.0, 1.0, 0.0, 0.0 );
			glBindTexture(GL_TEXTURE_2D, texturename);
			gluSphere(quadro, radius, 48, 48);
		glPopMatrix();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	gluDeleteQuadric(quadro);

}

void UIHelper::DrawEarthAndMoon(){
	GLfloat MoonRevolution = EarthDaysLeft / 30;
	GLUquadricObj* quadro = gluNewQuadric();							
	gluQuadricNormals(quadro, GLU_SMOOTH);		
	gluQuadricTexture(quadro, GL_TRUE);			
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
		// earth
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glPushMatrix();
			glRotatef(365, 0.0, 0.0, 1.0);
			glRotatef( 360.0 * (EarthDaysLeft/365), 0.0, 1.0, 0.0);
			glTranslatef(3.0, 0.0, 0.0 );
			glRotatef( 360.0 * CurrentEarthRotation, 0.0, 1.0, 0.0 );
			glRotatef( -90.0, 1.0, 0.0, 0.0 );
			glBindTexture(GL_TEXTURE_2D, EarthTextureIndex);
			gluSphere(quadro, 0.18, 48, 48);
		glPopMatrix();
		// moon
		glRotatef(7, 0.0, 0.0, 1.0);
		glRotatef( 360.0 * (EarthDaysLeft/365), 0.0, 1.0, 0.0);
		glTranslatef(3.0, 0.0, 0.0 );
		glRotatef( 360.0 * MoonRevolution, 0.0, 1.0, 0.0 );
		glTranslatef( 0.50, 0.0, 0.0 );
		glBindTexture(GL_TEXTURE_2D, MoonTextureIndex);
		gluSphere(quadro, 0.04, 48, 48);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	gluDeleteQuadric(quadro);
}

void UIHelper::DrawMarsPhobosAndDeimos(){
	GLfloat PhobosRevolution = EarthDaysLeft / 30;
	GLUquadricObj* quadro = gluNewQuadric();							
	gluQuadricNormals(quadro, GLU_SMOOTH);		
	gluQuadricTexture(quadro, GL_TRUE);			
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glPushMatrix();
			// mars
			glRotatef(2, 0.0, 0.0, 1.0);
			glRotatef( 360.0 * (EarthDaysLeft/686), 0.0, 1.0, 0.0);
			glTranslatef(3.5, 0.0, 0.0 );
			glRotatef( 360.0 * (CurrentEarthRotation/1), 0.0, 1.0, 0.0 );
			glRotatef( -90.0, 1.0, 0.0, 0.0 );
			glBindTexture(GL_TEXTURE_2D, MarsTextureIndex);
			gluSphere(quadro, 0.3, 48, 48);
		
		glPushMatrix();
		// phobos
		glRotatef(5, 0.0, 0.0, 1.0);
		glRotatef( 360.0 * (EarthDaysLeft/365), 0.0, 1.0, 0.0);
		glTranslatef(3.0, 0.0, 0.0 );
		glRotatef( 360.0 * PhobosRevolution, 0.0, 1.0, 0.0 );
		glTranslatef( 0.50, 0.0, 0.0 );
		glBindTexture(GL_TEXTURE_2D, MoonTextureIndex);
		gluSphere(quadro, 0.02, 48, 48);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	gluDeleteQuadric(quadro);

}

void UIHelper::DrawSkyBox(){
	double OFFSET = 1;
	glPushMatrix();
	glRotated(0.0, 1.0, 0.0, 0.0);	//Rotate around the x axis
	glRotated(0.0, 0.0, 1.0, 0.0);	//Rotate around the y axis

	glColor3f(1.0f,1.0f,1.0f);			//Set colour to White
	glEnable(GL_TEXTURE_2D);			//Enable texture mapping
	glDisable (GL_DEPTH_TEST);			//Disable depth testing

		//before you can use a texture you have to bind it
	glBindTexture(GL_TEXTURE_2D, SkyBoxBackIndex);

		glBegin (GL_QUADS);		//before you can draw you have to tell OpenGL
								//what you want to draw.  With GL_QUADS you have to
								//specify 4 verticies.  If you are using a texture
								//you also need to specify texture co-ordinates


				//glTexCoord2d allows you to specify the x and y values (range of 0.0 to 1.0)
				//the OFFSET value compensates for a seam that appears at the edges of the
				//skybox.  Try setting OFFSET to 0.0 to see what I mean.

				//glVertex3d allows you to specify the x,y, and z locations of that vertex
		
				glNormal3d (0.0,0.0,1.0); glTexCoord2d (0.0 + OFFSET,0.0 + OFFSET);	glVertex3d (-10.0,-10.0,10.0);
				glNormal3d (0.0,0.0,1.0); glTexCoord2d (1.0 - OFFSET,0.0 + OFFSET);	glVertex3d (-10.0,-10.0,-10.0);
				glNormal3d (0.0,0.0,1.0); glTexCoord2d (1.0 - OFFSET,1.0 - OFFSET);	glVertex3d (-10.0,10.0,-10.0);
				glNormal3d (0.0,0.0,1.0); glTexCoord2d (0.0 + OFFSET,1.0 - OFFSET);	glVertex3d (-10.0,10.0,10.0);

		glEnd ();				//Make sure that after you are finished call the glEnd() or
								//the program will crash really fast.

		glBindTexture(GL_TEXTURE_2D, SkyBoxTopIndex);
		glBegin (GL_QUADS);
		
				glNormal3d (0.0,0.0,1.0); glTexCoord2d (0.0 + OFFSET,0.0 + OFFSET);	glVertex3d (-10.0,-10.0,-10.0);
				glNormal3d (0.0,0.0,1.0); glTexCoord2d (1.0 - OFFSET,0.0 + OFFSET);	glVertex3d (10.0,-10.0,-10.0);
				glNormal3d (0.0,0.0,1.0); glTexCoord2d (1.0 - OFFSET,1.0 - OFFSET);	glVertex3d (10.0,10.0,-10.0);
				glNormal3d (0.0,0.0,1.0); glTexCoord2d (0.0 + OFFSET,1.0 - OFFSET);	glVertex3d (-10.0,10.0,-10.0);
		glEnd ();

		glBindTexture(GL_TEXTURE_2D, SkyBoxFrontIndex);
		glBegin (GL_QUADS);
		
				glNormal3d (0.0,0.0,1.0); glTexCoord2d (0.0 + OFFSET ,0.0 + OFFSET); glVertex3d (10.0,-10.0,-10.0);
				glNormal3d (0.0,0.0,1.0); glTexCoord2d (1.0 - OFFSET ,0.0 + OFFSET); glVertex3d (10.0,-10.0,10.0);
				glNormal3d (0.0,0.0,1.0); glTexCoord2d (1.0 - OFFSET ,1.0 - OFFSET); glVertex3d (10.0,10.0,10.0);
				glNormal3d (0.0,0.0,10.0); glTexCoord2d (0.0 + OFFSET ,1.0 - OFFSET); glVertex3d (10.0,10.0,-10.0);

		glEnd ();

		glBindTexture(GL_TEXTURE_2D, SkyBoxLeftIndex);	
		glBegin (GL_QUADS);
			
			glNormal3d (0.0,0.0,1.0); glTexCoord2d (0.0 + OFFSET ,0.0 + OFFSET); glVertex3d (10.0,-10.0,10.0);
			glNormal3d (0.0,0.0,1.0); glTexCoord2d (1.0 - OFFSET ,0.0 + OFFSET); glVertex3d (-10.0,-10.0,10.0);
			glNormal3d (0.0,0.0,1.0); glTexCoord2d (1.0 - OFFSET ,1.0 - OFFSET); glVertex3d (-10.0,10.0,10.0);
			glNormal3d (0.0,0.0,1.0); glTexCoord2d (0.0 + OFFSET ,1.0 - OFFSET); glVertex3d (10.0,10.0,10.0);
		
		glEnd ();

		glBindTexture(GL_TEXTURE_2D, SkyBoxRightIndex);	
		glBegin (GL_QUADS);
			
			glNormal3d (0.0,0.0,1.0); glTexCoord2d (0.0 + OFFSET ,0.0 + OFFSET); glVertex3d (-10.0,-10.0,10.0);
			glNormal3d (0.0,0.0,1.0); glTexCoord2d (1.0 - OFFSET ,0.0 + OFFSET); glVertex3d (10.0,-10.0,10.0);
			glNormal3d (0.0,0.0,1.0); glTexCoord2d (1.0 - OFFSET ,1.0 - OFFSET); glVertex3d (10.0,-10.0,-10.0);
			glNormal3d (0.0,0.0,1.0); glTexCoord2d (0.0 + OFFSET ,1.0 - OFFSET); glVertex3d (-10.0,-10.0,-10.0);
		
		glEnd ();

		glBindTexture(GL_TEXTURE_2D, SkyBoxTopIndex);
		glBegin (GL_QUADS);
		
				glNormal3d (0.0,0.0,1.0); glTexCoord2d (0.0 + OFFSET ,0.0 + OFFSET); glVertex3d (-10.0,10.0,-10.0);
				glNormal3d (0.0,0.0,1.0); glTexCoord2d (1.0 - OFFSET ,0.0 + OFFSET); glVertex3d (10.0,10.0,-10.0);
				glNormal3d (0.0,0.0,1.0); glTexCoord2d (1.0 - OFFSET ,1.0 - OFFSET); glVertex3d (10.0,10.0,10.0);
				glNormal3d (0.0,0.0,1.0); glTexCoord2d (0.0 + OFFSET ,1.0 - OFFSET); glVertex3d (-10.0,10.0,10.0);
				
		glEnd ();

	//Re-Enable the depth test
	glEnable(GL_DEPTH_TEST);
	//disable texture mapping
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}