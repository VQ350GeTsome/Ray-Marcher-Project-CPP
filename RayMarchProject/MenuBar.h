#pragma once

#include "Scene.h"

class MenuBar
{
private:
	Scene* scene;
public:
	MenuBar(Scene* s) : scene(s) {}

	void parseMenuInput(WPARAM input);
};

