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
	virtual void setColor(vec3 newColor) { color = newColor.clamp(0, 255).toInt(); }
	virtual vec3 getColor() const { return color.clamp(0, 255).toInt(); }	//Gets the color of the SDF object
};