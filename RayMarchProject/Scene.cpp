#include "Scene.h"
#include "Light.h"
#include "SDFManager.h"
#include "Camera.h"
#include "RayMarcher.h"

Light* light;			//Components
SDFManager* sdfMgr;
Camera* camera;
RayMarcher* rayMchr;

int width{}, height{};		//Window dimensions
