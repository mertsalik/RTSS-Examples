#include "Common.h"
#pragma once
class UIHelper
{
private:
	void LoadTexture(const char bitmapFilename[], GLuint &TextureIndex);
	int planet_count;
	GLdouble speed;
	GLdouble angle;


	GLfloat currentZoom;
	GLfloat maxZoomOut;
	GLfloat maxZoomIn;
	GLint orbitDegreesX;
	GLint orbitDegreesY;


	GLfloat mercuryRadius;
	GLfloat venusRadius;
	GLfloat marsRadius ;
	GLfloat jupiterRadius;
	GLfloat saturnRadius ;
	GLfloat uranusRadius;
	GLfloat neptuneRadius;
	GLfloat plutoRadius;
	GLfloat sunRadius;




	/**
	*	Singleton
	*/
	UIHelper(void);
	UIHelper(UIHelper const&);
	void operator=(UIHelper const&);

public:
	static UIHelper& getInstance()
	{
		static UIHelper    instance; // Guaranteed to be destroyed.
		// Instantiated on first use.
		return instance;
	}
	~UIHelper(void);

	/**
	* Public Properties
	*/
	float *ambient;
	float *diffuse; 
	float *specular;
	float *position;
	GLuint ParticleTextureIndex;
	GLuint EarthTextureIndex;
	GLuint MoonTextureIndex;
	GLuint SunTextureIndex;
	GLuint MercuryTextureIndex;
	GLuint VenusTextureIndex;
	GLuint MarsTextureIndex;
	GLuint JupiterTextureIndex;
	GLuint SaturnTextureIndex;
	GLuint UranusTextureIndex;
	GLuint NeptuneTextureIndex;
	GLuint PlutoTextureIndex;
	GLuint RingTextureIndex;
	GLuint SkyBoxBackIndex;
	GLuint SkyBoxFrontIndex;
	GLuint SkyBoxLeftIndex;
	GLuint SkyBoxRightIndex;
	GLuint SkyBoxTopIndex;

	GLfloat CurrentEarthRotation;
	GLfloat EarthDaysLeft;

	/**
	*	Methods
	*/
	void CreateSphere();

	void LoadTextures();

	void ClearColor();

	void SetupLights();

	void InitLightnings();

	void speedUp(){
		speed += 0.1;
	}
	void speedDown(){
		speed -= 0.1;
	}
	GLdouble getSpeed(){
		return speed;
	}

	void zoomIn(){
		if(currentZoom >= maxZoomIn)
			currentZoom -= 0.1;
	}
	void zoomOut(){
		if(currentZoom <= maxZoomOut)
			currentZoom += 0.1;
	}

	void increaseOrbitX(){
		orbitDegreesX++;
	}
	void decreaseOrbitX(){
		orbitDegreesX--;
	}

	void increaseOrbitY(){
		orbitDegreesY++;
	}
	void decreaseOrbitY(){
		orbitDegreesY--;
	}
	int getOrbitDegreeX(){return orbitDegreesX;}
	int getOrbitDegreeY(){return orbitDegreesY;}
	float getCurrentZoom(){return currentZoom;}
	float getMaxZoomOut(){return maxZoomOut;}
	float getMaxZoomIn(){return maxZoomIn;}
	float getAspectRatio(){return (float)800/(float)600;}

	float* getGlowing(){
		GLfloat on[] = {1.0f, 1.0f, 1.0f, 1.0f};
		return on;
	}
	float* getUnglowing(){
		GLfloat off[] = {0.0f, 0.0f, 0.0f, 1.0f};
		return off;
	}
	double getAngle(){return angle;}

	/**
	*	Static Methods
	*/

	static void DisplayCallback(int value);


	/**
	*	Planet oriented Methods
	*/
	void DrawSun();
	void DrawOtherPlanets();
	void drawGenericPlanet(GLfloat inclination, GLfloat orbitDuration,
		GLfloat orbitRadius, GLfloat rotationDuration, GLuint texturename, GLfloat radius);
	void DrawEarthAndMoon();
	void DrawMarsPhobosAndDeimos();
	void DrawSkyBox();

};

