#pragma once

#include "Scene.h"

#include <wtypes.h>

class Controls
{
public:

	Scene* scene;

	Controls(Scene* s) : scene(s) {}

	void parseKeyInput(WPARAM input);
	
	//Returns true if input moves camera ... moves camera too ...
	bool camMove(WPARAM input);
	bool camPan(WPARAM input);

	//Camera moving set grainulatity
	bool setMoveGrain(float n) { moveGrain = (n > 0) ? n : moveGrain; }
	bool setPanGrain(float  n) {  panGrain = (n > 0) ? n :  panGrain; }

private:

	float moveGrain = 0.1f, panGrain = 2.5f;
};

