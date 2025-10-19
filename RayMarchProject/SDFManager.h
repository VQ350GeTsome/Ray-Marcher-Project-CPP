#pragma once

#include "Vec3.h"
#include "SDF.h"

#include <vector>

class SDFManager
{
private:
	std::vector<SDF*> sdfs;		//List of SDFs in the scene
public:
	SDFManager();

	//Adds an SDF to the scene
	void addSDF(SDF* sdf);

	//Removes a specific SDF from the scene
	void removeSDF(SDF* sdf);

	//Returns the minimum distance from pos to any SDF in the scene
	float getMinDistance(const vec3& pos);

	//Returns the SDF at a given position, or nullptr if none
	SDF* getSDFatPos(const vec3& pos);
};

