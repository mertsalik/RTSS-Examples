#pragma once
#include "Common.h"
#include "UIHelper.h"
class GLHelper
{
private:
	int w_width;
	int w_height;

public:
	GLHelper(void);
	~GLHelper(void);

	void InitGL(GLvoid);
	void BindKeyFunctions();

	/**
	*	Toggles
	*/
	void ToggleDepth();

	static void Draw();
	static void TimerCallback(int value);

	static void KeyF(unsigned char key, int x, int y);
	static void SpecialKeyF(int key, int x, int y);

};

