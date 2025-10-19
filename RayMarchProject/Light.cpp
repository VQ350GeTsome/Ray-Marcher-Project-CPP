#include "Light.h"
#include "Vec3.h"


vec3 lightDir = vec3(0.0f, 0.0f, -1.0f);	//Default light direction

Light::Light() {
	lightDir = vec3(0.0f, 0.0f, -1.0f);
}
;