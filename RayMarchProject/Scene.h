#pragma once

#include "SDF.h"

#include "Camera.h"
#include "Light.h"
#include "SDFManager.h"
#include "RayMarcher.h"

#include <vector>
#include <cmath>

//Scene class managing all components, abstracting away some complexity ...
class Scene {
private:

	Camera* camera = new Camera();				//Components
	Light* light = new Light();			
	SDFManager* sdfMgr = new SDFManager();
	RayMarcher* rayMchr = new RayMarcher(camera, light, sdfMgr);
	
	int width{}, height{};		//Window dimensions

public:

	//Update local width and height, and inform ray marcher
	void updateDimensions(int w, int h) 
	{
		width = w; height = h;
		rayMchr->updateDimensions(w, h);
	}
	
	//Initialize or reinitialize the camera parameters
	void setCamera(const vec3& pos, const vec3& target, const vec3& upVector, float fieldOfView) { camera->initalizeCamera(pos, target, upVector, fieldOfView); }

	//Set light direction
	void setLightDirection(const vec3& dir) { light->setLightDir(dir); }

	//Add an SDF to the scene
	void addSDF(SDF* sdf) { sdfMgr->addSDF(sdf); }

	//Remove a specific SDF from the scene
	void removeSDF(SDF* sdf) { sdfMgr->removeSDF(sdf); }

	//Renders the scene and returns a 2D array of pixel colors
	std::vector<std::vector<vec3>> renderScene() { return rayMchr->marchScreen(); }

	//Set background color
	void setBackground(vec3 color) { rayMchr->setBackgroundColor(color); }
};
