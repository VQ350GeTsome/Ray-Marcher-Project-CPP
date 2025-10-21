#pragma once

#include "Vec3.h"
#include <cmath>

class Camera
{
private:
	vec3 position, forward, up, right;	//Camera basis vectors
	float fov;							//Field of view in degrees
	float yawDeg = 90.0f, pitchDeg = 0.0f;		//Yaw & pitch
	vec3 worldUp = vec3(0.0f, 1.0f, 0.0f);
public:

	Camera();

	//Initialize or reinitialize the camera parameters
	void initalizeCamera(const vec3& pos, const vec3& target, const vec3& upVector, float fieldOfView);

	//Generate a ray direction for a given pixel coordinate (x, y) in normalized device coordinates
	vec3 getRayDirection(float x, float y, float w, float h);

	//Returns the vec3 camera position
	vec3 getPosition() const { return position; }
	
	//Getters for the camera oreiantation vectors
	vec3 getForward() const { return forward; }
	vec3 getUp() const { return up; }
	vec3 getRight() const { return right; }

	void move(const vec3 &m) { position = position + m; }
	void rotate(const float &yawDelta, const float &pitchDelta);
};
