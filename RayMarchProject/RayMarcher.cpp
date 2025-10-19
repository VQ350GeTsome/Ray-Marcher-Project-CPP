#include "RayMarcher.h"
#include "Vec3.h"
#include "Camera.h"
#include "Light.h"
#include "SDFManager.h"

#include <iostream>

RayMarcher::RayMarcher(Camera* camera, Light* light, SDFManager* sdfMgr)
	: camera(camera), light(light), sdfMgr(sdfMgr)
{}

//Marches a ray from the camera through pixel (x, y)
vec3 RayMarcher::march(int x, int y)
{
	vec3 rayDir = camera->getRayDirection((float)x / width, (float)y / height, (float)width, (float)height);
	vec3 rayPos = camera->getPosition();

	float totalDistance = 0.0f;
	for (int step = 0; step < maxSteps; step++) {
		float distance = sdfMgr->getMinDistance(rayPos);

		if (distance < 0.001f) { rayPos; }
		if (totalDistance > maxDist) { rayPos; }

		rayPos = rayPos + rayDir * distance;
		totalDistance += distance;

	}
	return rayPos;
}
//Get shadow amount [0.0f - 1.0f]
float RayMarcher::getShadow(const vec3& origin)
{
	float res = 1.0f;				//Totally lit for now
	float t = 0.1f;					//Start a bit off the surface
	const float softness = 1.0f;	//Penumbra 'width'
	for (int i = 0; i < shadowSteps; i++) {
		vec3 p = origin - light->getLightDir() * t;
		float h = sdfMgr->getMinDistance(p);
		if (h < 0.001f) return 0.0f;
		res = (((res) < (softness * h / t)) ? (res) : (softness * h / t)); // tweak softness
		t += h;
		if (t > 100.0f) break;
	}
	return res;
}
//March the entire screen
std::vector<std::vector<vec3>> RayMarcher::marchScreen() 
{
	std::vector<std::vector<vec3>> framebuffer(height, std::vector<vec3>(width));
	for (int x = 0; x < width; x++) for (int y = 0; y < height; y++) 
	{
		vec3 hit = march(x, y);									//March ray through pixel
		SDF* hitSDF = sdfMgr->getSDFatPos(hit);						//Get SDF at hit position

		if (hitSDF != nullptr) 
		{															//If we hit an SDF
			vec3 baseColor = hitSDF->getColor();					//Get the hit SDFs color
			float shadow = getShadow(hit);							//Calculate the shadow amount
			vec3 finalColor = baseColor * shadow;					//Apply shadow to SDFs color
			vec3 lightDir = light->getLightDir();
			framebuffer[y][x] = finalColor.clamp(0, 255).toInt();	//Set pixel to SDFs color
		} else {																
			framebuffer[y][x] = backgroundColor;					//Else set pixel to background color
		}
	}
	return framebuffer;
}