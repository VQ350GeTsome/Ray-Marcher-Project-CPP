#pragma once

#include "Vec3.h"
#include <cmath>

class Camera 
{
public:

	static vec3 position, forward, up, right;	//Camera basis vectors
	static float fov;							//Field of view in degrees

	static void initalizeCamera(const vec3& pos, const vec3& target, const vec3& upVector, float fieldOfView) {
		position = pos;
		fov = fieldOfView;
		forward = (target - pos).normalize();
		right = forward.cross(upVector).normalize();
		up = right.cross(forward).normalize();
	}
	// Generate a ray direction for a given pixel coordinate (u, v) in normalized device coordinates
	static vec3 getRayDirection(float x, float y, float w, float h) {
		float aspectRatio = w / h;
		float fovRad = fov * (3.14159265f / 180.0f);
		float px = (2.0f * x - 1.0f) * tan(fovRad / 2.0f) * aspectRatio;
		float py = (1.0f - 2.0f * y) * tan(fovRad / 2.0f);
		vec3 rayDir = (forward + right * px + up * py).normalize();
		return rayDir;
	}
};
