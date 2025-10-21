#pragma once

#include "Vec3.h"

class Light
{
private:
	vec3 lightDir = vec3(0.0f, 0.0f, -1.0f);;	//Scene Lighting (Default lighting is from straight above)
	float ambientLight = 0.0f;					//Ambient Lighting
public:

	Light();

	//Scene lighting setter and getter
	void setLightDir(const vec3& dir) { lightDir = dir.normalize(); }
	vec3 getLightDir() { return lightDir; }

	//Scene ambient lighting setter and getter
	void setAmbientLight(const float& amLight) { ambientLight = (((((amLight) > (0)) ? (amLight) : (0)) < (1)) ? (((amLight) > (0)) ? (amLight) : (0)) : (1)); }
	float getAmbientLight() { return ambientLight;  }
};