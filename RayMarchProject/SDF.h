#pragma once

#include "Vec3.h"

class SDF
{
private: 

	vec3 color;				//Color of the SDF object

public:
	
	vec3 position;			//Position of the SDF object

	//Abstract method for getting the distance from pos to surface
	virtual float dist(const vec3& ray) const = 0;	

	//Color setter & getter
	virtual void setColor(vec3 newColor) { color = newColor; }
	virtual vec3 getColor() const { return color; }	//Gets the color of the SDF object
};