#include "Camera.h"
#include <cmath>;

Camera::Camera() {}

//Initialize or reinitialize the camera parameters
void Camera::initalizeCamera(const vec3& pos, const vec3& target, const vec3& upVector, float fieldOfView) {
	position = pos;
	fov = fieldOfView;
	forward = (target - pos).normalize();
	right = forward.cross(upVector).normalize();
	up = right.cross(forward).normalize();
}

//Generate a ray direction for a given pixel coordinate (u, v) in normalized device coordinates
vec3 Camera::getRayDirection(float x, float y, float w, float h) {
	float aspectRatio = w / h;
	float fovRad = fov * (3.14159265f / 180.0f);
	float px = (2.0f * x - 1.0f) * tan(fovRad / 2.0f) * aspectRatio;
	float py = (1.0f - 2.0f * y) * tan(fovRad / 2.0f);
	vec3 rayDir = (forward + right * px + up * py).normalize();
	return rayDir;
}
