#include "GLHelper.h"


GLHelper::GLHelper(void)
{
	this->w_height = 600;
	this->w_width = 800;
}


GLHelper::~GLHelper(void)
{
}

void GLHelper::InitGL(GLvoid){
	GLenum type;
	glutInitWindowSize(this->w_width, this->w_height);
	type = GLUT_RGB;
	type |= GLUT_DOUBLE;
	type |= GLUT_DEPTH;
	type |= GLUT_MULTISAMPLE;
	glutInitDisplayMode(type);
	//glutCreateWindow(strcat(DEVELOPER,PROJNAME));
	glutCreateWindow(PROJNAME);

	// enable depth
	ToggleDepth();

	// set poly mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void GLHelper::BindKeyFunctions(){
	glutKeyboardFunc(KeyF);
	glutSpecialFunc(SpecialKeyF);
}

void GLHelper::ToggleDepth(){
	if(glIsEnabled(GL_DEPTH_TEST)){
		glDisable(GL_DEPTH_TEST);
	}else{
		glEnable(GL_DEPTH_TEST);
	}
}

void GLHelper::KeyF(unsigned char key, int x, int y){
	switch (key) {
        case 27: // ESC
			exit(0);
            break;
		case 'z':
		case 'Z':
			UIHelper::getInstance().speedUp();
			break;
		case 'x':
		case 'X':
			UIHelper::getInstance().speedDown();
			break;

    }
}

void GLHelper::SpecialKeyF(int key, int x, int y){
	switch (key) {
        case GLUT_KEY_LEFT:
			UIHelper::getInstance().increaseOrbitX();
            break;
        case GLUT_KEY_RIGHT:
			UIHelper::getInstance().decreaseOrbitX();
            break;
        case GLUT_KEY_UP:
			UIHelper::getInstance().decreaseOrbitY();
            break;
        case GLUT_KEY_DOWN:
			UIHelper::getInstance().increaseOrbitY();
            break;
        case GLUT_KEY_PAGE_UP:
			UIHelper::getInstance().zoomIn();
            break;
        case GLUT_KEY_PAGE_DOWN:
			UIHelper::getInstance().zoomOut();
            break;
    }
}

void GLHelper::Draw(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(UIHelper::getInstance().getCurrentZoom(), UIHelper::getInstance().getAspectRatio(), UIHelper::getInstance().getMaxZoomIn(), UIHelper::getInstance().getMaxZoomOut());
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, -40, 0, 0, 0, 0, 1, 0);
	glRotated(UIHelper::getInstance().getOrbitDegreeX(), 0, 1, 0);
	glRotated(UIHelper::getInstance().getOrbitDegreeY(), 1, 0, 0);
	glLightfv(GL_LIGHT0, GL_POSITION, UIHelper::getInstance().position);

	glEnable(GL_TEXTURE_2D);

	UIHelper::getInstance().DrawSun();
	UIHelper::getInstance().DrawEarthAndMoon();
	UIHelper::getInstance().DrawOtherPlanets();
	UIHelper::getInstance().DrawMarsPhobosAndDeimos();
	// UIHelper::getInstance().DrawSkyBox();
		
	
	glLoadIdentity();
	
	//Setting camera location and angle
	gluLookAt(0, 0, -100, 0, 0, 0, 0, 1,  0);

    glutSwapBuffers();
	

}
