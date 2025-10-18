#pragma once

#include "SDF.h"

class Sphere : public SDF
{
private:
	float radius;
	vec3 color = vec3(0, 0, 0);
public:
	
	vec3 position = vec3(0, 0, 0);

	Sphere(const vec3& position, float radius, vec3 color)
		: position(position), radius(radius), color(color) {
	}
	Sphere(const vec3& position, float radius)
		: position(position), radius(radius) {
	}

	//Returns the distance from pos to the surface of the sphere
	float dist(const vec3& ray) const override
	{
		return (ray - position).length() - radius;
	}
};
