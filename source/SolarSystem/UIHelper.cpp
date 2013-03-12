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
	UIHelper::getInstance().angle += UIHelper::getInstance().getSpeed();
	glutTimerFunc(10, UIHelper::DisplayCallback, value);
	glutPostRedisplay();
}