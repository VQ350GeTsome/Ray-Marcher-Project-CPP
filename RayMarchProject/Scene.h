#pragma once

#include "SDF.h"

#include "Camera.h"
#include "Light.h"
#include "SDFManager.h"
#include "RayMarcher.h"

#include <vector>
#include <cmath>
#include <tuple>

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
	void setCamera(const vec3 &pos, const vec3 &target, const vec3 &upVector, float fieldOfView) { camera->initalizeCamera(pos, target, upVector, fieldOfView); }
	void moveCamera(const vec3 &m) { camera->move(m); }
	void rotateCamera(const float& y, const float& p) { camera->rotate(y, p); }
	std::tuple<vec3, vec3, vec3> getCameraOrien() { return std::make_tuple(camera->getForward(), camera->getRight(), camera->getUp()); }

	//Set light direction
	void setSceneLight(const vec3 &dir) { light->setLightDir(dir); }
	void setAmbientLight(const float &l) { light->setAmbientLight(l); }

	//SDF adder & remover
	void addSDF(SDF* sdf) { sdfMgr->addSDF(sdf); }
	void removeSDF(SDF* sdf) { sdfMgr->removeSDF(sdf); }

	//Renders the scene and returns a 2D array of pixel colors
	std::vector<std::vector<vec3>> renderScene() { return rayMchr->marchScreen(); }

	//Set background color
	void setBackground(vec3 color) { rayMchr->setBackgroundColor(color); }
};
