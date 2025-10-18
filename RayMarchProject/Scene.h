#pragma once

#include "SDF.h"
#include "Camera.h"
#include <vector>
#include <cmath>

class Scene {
	static std::vector<SDF*> sdfs;		//List of SDFs in the scene
	static int maxDist, maxSteps;		//Ray marching parameters
	static int shadowSteps;				//Number of steps for shadow rays
	static vec3 lightDir;				//Direction of the light source
public:
	//Adds an SDF to the scene
	static void addSDF(SDF* sdf) { sdfs.push_back(sdf); }
	//Removes a specific SDF from the scene
	static void removeSDF(SDF* sdf)
	{
		auto it = std::find(sdfs.begin(), sdfs.end(), sdf);
		if (it != sdfs.end()) {
			sdfs.erase(it);
		}
	}

	//Returns the minimum distance from pos to any SDF in the scene
	static float getMinDistance(const vec3& pos) {
		float minDist = INFINITY;					//Initialize minimum distance to infinity
		for (SDF* sdf : sdfs) {						//For every SDF in the scene
			float dist = sdf->dist(pos);			//Get distance to SDF
			minDist = (dist < minDist) ? dist : minDist;	//Update minimum distance if necessary
		}
		return minDist;
	}
	//Marches a ray from the camera through pixel (x, y)
	static vec3 march(const int* x, const int* y, const int* w, const int* h) {
		vec3 rayDir = Camera::getRayDirection((float)*x / *w, (float)*y / *h, (float)*w, (float)*h);
		vec3 rayPos = Camera::position;

		float totalDistance = 0.0f;
		for (int step = 0; step < maxSteps; step++) {
			float distance = Scene::getMinDistance(rayPos);

			if (distance < 0.001f) { rayPos; }
			if (totalDistance > maxDist) { rayPos; }

			rayPos = rayPos + rayDir * distance;
			totalDistance += distance;

		}
		return rayPos;
	}	
	//Returns the SDF at a given position, or nullptr if none
	static SDF* getSDFatPos(const vec3& pos) {
		for (SDF* sdf : sdfs) {
			if (sdf->dist(pos) < 0.001f) {
				return sdf;
			}
		}
		return nullptr;
	}

	//Initialize camera settings
	static void initalizeCamera(const vec3& pos, const vec3& target, const vec3& upVector, float fieldOfView) {
		Camera::initalizeCamera(pos, target, upVector, fieldOfView);
	}
	
	//Set light direction
	static void setLightDir(const vec3& dir) {
		lightDir = dir.normalize();
	}
	//Get shadow
	static float getShadow(const vec3& origin) {
		float res = 1.0f;				//Totally lit for now
		float t   = 0.1f;				//Start a bit off the surface
		const float softness = 1.0f;	//Penumbra 'width'
		for (int i = 0; i < shadowSteps; i++) {	
			vec3 p = origin - lightDir * t;
			float h = getMinDistance(p);
			if (h < 0.001f) return 0.0f;
			res = (((res) < (softness * h / t)) ? (res) : (softness * h / t)); // tweak softness
			t += h;
			if (t > 100.0f) break;
		}
		return res;
	}
};
