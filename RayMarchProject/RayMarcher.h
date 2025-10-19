#pragma once

#include "Camera.h"
#include "SDFManager.h"
#include "Light.h"

class RayMarcher
{
private:

	Camera* camera;
	Light* light;
	SDFManager* sdfMgr;

	vec3 backgroundColor = vec3(0, 0, 0); // Background color

	int width{}, height{};		//Window dimensions

	int shadowSteps = 50;	//Number of steps for shadow ray marching
	int maxSteps = 100;		//Maximum number of steps for ray marching
	float maxDist = 1000.0f;	//Maximum distance for ray marching

public:
	RayMarcher(Camera* camera, Light* light, SDFManager* sdfMgr);

	//Marches a ray from the camera through pixel (x, y)
	vec3 march(int x, int y);

	//Get shadow amount [0.0f - 1.0f]
	float getShadow(const vec3& origin);

	//March the entire screen
	std::vector<std::vector<vec3>> marchScreen();

	//Update height and width
	void updateDimensions(int w, int h) { width = w; height = h; }

	//Set background color
	void setBackgroundColor(vec3 color) { backgroundColor = color.clamp(0, 255); }
};