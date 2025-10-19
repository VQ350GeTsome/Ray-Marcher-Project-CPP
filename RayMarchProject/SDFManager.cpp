#include "SDFManager.h"
#include "Vec3.h"
#include "SDF.h"

#include <cmath>
#include <algorithm>
#include <vector>

SDFManager::SDFManager() {}

//Adds an SDF to the scene
void SDFManager::addSDF(SDF * sdf) { sdfs.push_back(sdf); }

//Removes a specific SDF from the scene
void SDFManager::removeSDF(SDF* sdf)
	{
		auto it = std::find(sdfs.begin(), sdfs.end(), sdf);
		if (it != sdfs.end()) {
			sdfs.erase(it);
		}
	}

//Returns the minimum distance from pos to any SDF in the scene
float SDFManager::getMinDistance(const vec3& pos) {
		float minDist = INFINITY;					//Initialize minimum distance to infinity
		for (SDF* sdf : sdfs) {						//For every SDF in the scene
			float dist = sdf->dist(pos);			//Get distance to SDF
			minDist = (dist < minDist) ? dist : minDist;	//Update minimum distance if necessary
		}
		return minDist;
}

//Returns the SDF at a given position, or nullptr if none
SDF* SDFManager::getSDFatPos(const vec3& pos) {
		for (SDF* sdf : sdfs) {
			if (sdf->dist(pos) < 0.001f) {
				return sdf;
			}
		}
		return nullptr;
	}

