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
	gluLookAt(0, 0, -80, 0, 0, 0, 0, 1, 0);
	glRotated(UIHelper::getInstance().getOrbitDegreeX(), 0, 1, 0);
	glRotated(UIHelper::getInstance().getOrbitDegreeY(), 1, 0, 0);
	glLightfv(GL_LIGHT0, GL_POSITION, UIHelper::getInstance().position);

	glEnable(GL_TEXTURE_2D);
	GLUquadric* quadric = gluNewQuadric();
	gluQuadricNormals(quadric, GLU_SMOOTH);
	gluQuadricTexture(quadric, GL_TRUE);


	//Sun
	glBindTexture(GL_TEXTURE_2D, UIHelper::getInstance().SunTextureIndex);
	glMaterialfv(GL_FRONT, GL_EMISSION, UIHelper::getInstance().getGlowing());
    gluSphere(quadric, 3, 24, 24);
	glMaterialfv(GL_FRONT, GL_EMISSION, UIHelper::getInstance().getUnglowing());
    glPushMatrix();

	//Earth
	glBindTexture(GL_TEXTURE_2D, UIHelper::getInstance().EarthTextureIndex);
	glRotated(2*UIHelper::getInstance().getAngle(), 0, 1, 0);
    glTranslatef(7.f, 0.f, 0.f);
    glRotated(UIHelper::getInstance().getAngle(), 0, 1, 0);
    gluSphere(quadric, 1, 24, 24);
    glPushMatrix();

	//Moon
	glBindTexture(GL_TEXTURE_2D, UIHelper::getInstance().MoonTextureIndex);
    glRotated(4*UIHelper::getInstance().getAngle(), 0, 1, 0);
    glTranslatef(2.f, 0.f, 0.f);
    glRotated(UIHelper::getInstance().getAngle(), 0, 1, 0);
    gluSphere(quadric, 0.5, 24, 24);
    
    glPopMatrix();
    glPopMatrix();
	
	//Mars
	glBindTexture(GL_TEXTURE_2D, UIHelper::getInstance().MarsTextureIndex);
    glRotated(UIHelper::getInstance().getAngle(), 0, 1, 0);
    glTranslatef(20.0f, 0.f, 0.f);
    glRotated(UIHelper::getInstance().getAngle(), 0, 1, 0);
    gluSphere(quadric, 1.5, 24, 24);
    glPushMatrix();
    
	//Phobos (1st moon of Mars)
	glBindTexture(GL_TEXTURE_2D, UIHelper::getInstance().NeptuneTextureIndex);
    glRotated(4*UIHelper::getInstance().getAngle(), 0, 1, 0);
    glTranslatef(4.f, 0.f, 0.f);
    glRotated(UIHelper::getInstance().getAngle(), 0, 1, 0);
    gluSphere(quadric, 0.5, 24, 24);
    glPopMatrix();
    
	//Deimos (2nd moon of Mars)
	glBindTexture(GL_TEXTURE_2D, UIHelper::getInstance().PlutoTextureIndex);
    glRotated(4*UIHelper::getInstance().getAngle() + 150 , 0, 1, 0);
    glTranslatef(7.f, 0.f, 0.f);
    glRotated(UIHelper::getInstance().getAngle(), 0, 1, 0);
    gluSphere(quadric, 1, 24, 24);

	glPopMatrix();
	glPopMatrix();

	glLoadIdentity();

	//Setting camera location and angle
	gluLookAt(0, 0, -100, 0, 0, 0, 0, 1,  0);

    glutSwapBuffers();

}
