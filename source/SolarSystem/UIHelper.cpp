#include "UIHelper.h"


UIHelper::UIHelper(void)
{
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
