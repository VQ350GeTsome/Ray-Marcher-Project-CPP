#include "Camera.h"
#include "vec3.h"

#include <cmath>
#include <iostream>

Camera::Camera() {}

//Initialize or reinitialize the camera parameters
void Camera::initalizeCamera(const vec3& pos, const vec3& target, const vec3& upVector, float fieldOfView) 
{
    position = pos;
    fov = fieldOfView;
    worldUp = upVector;
    forward = (target - pos).normalize();

    const float rad2deg = 180.0f / 3.14159265358979323846f;
    yawDeg = std::atan2(forward.x, forward.z) * rad2deg;
    float fy = forward.y;
    if (fy > 1.0f) fy = 1.0f;
    if (fy < -1.0f) fy = -1.0f;
    pitchDeg = std::asin(fy) * rad2deg;

    right = forward.cross(worldUp).normalize();
    up = right.cross(forward).normalize();
}

//Generate a ray direction for a given pixel coordinate (x, y) in normalized device coordinates
vec3 Camera::getRayDirection(float x, float y, float w, float h) 
{
	float aspectRatio = w / h;
	float fovRad = fov * (3.14159265f / 180.0f);
	float px = (2.0f * x - 1.0f) * tan(fovRad / 2.0f) * aspectRatio;
	float py = (1.0f - 2.0f * y) * tan(fovRad / 2.0f);
	vec3 rayDir = (forward + right * px + up * py).normalize();
	return rayDir;
}

void Camera::rotate(const float &yawDelta, const float &pitchDelta) 
{
    yawDeg += yawDelta;
    pitchDeg += pitchDelta;

    const float d2r = 3.14159265358979323846f / 180.0f;
    float y = yawDeg * d2r;
    float p = pitchDeg * d2r;
    forward.x = std::cosf(p) * std::sinf(y);
    forward.y = std::sinf(p);
    forward.z = std::cosf(p) * std::cosf(y);
    forward = forward.normalize();
    right = forward.cross(worldUp).normalize(); 
    up = right.cross(forward).normalize();  //Does the same order as the initalize camera
}