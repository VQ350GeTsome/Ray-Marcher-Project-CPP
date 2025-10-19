#pragma once

#include "Vec3.h"

class Light
{
private:
	vec3 lightDir;				//Default light direction
public:
	Light();
	//Set light direction
	void setLightDir(const vec3& dir) { lightDir = dir.normalize(); }
	//Returns the vec3 light direction
	vec3 getLightDir() { return lightDir; }
};