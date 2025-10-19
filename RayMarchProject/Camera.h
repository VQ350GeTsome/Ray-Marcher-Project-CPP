#pragma once

#include "Vec3.h"
#include <cmath>

class Camera 
{
private:
	vec3 position, forward, up, right;	//Camera basis vectors
	float fov;							//Field of view in degrees
public:

	Camera();

	//Initialize or reinitialize the camera parameters
	void initalizeCamera(const vec3& pos, const vec3& target, const vec3& upVector, float fieldOfView);

	//Generate a ray direction for a given pixel coordinate (u, v) in normalized device coordinates
	vec3 getRayDirection(float x, float y, float w, float h);	

	//Returns the vec3 camera position
	vec3 getPosition() const { return position; }
};
