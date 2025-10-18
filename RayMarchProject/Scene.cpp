#include "Scene.h"

std::vector<SDF*> Scene::sdfs;
int Scene::maxDist = 100;
int Scene::maxSteps = 100;
int Scene::shadowSteps = 50;
vec3 Scene::lightDir = vec3(0.0f, 1.0f, 0.0f).normalize();