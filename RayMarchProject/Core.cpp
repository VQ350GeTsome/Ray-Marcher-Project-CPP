#include "Window.h"
#include "Scene.h"
#include "Vec3.h"
#include "Sphere.h"
#include <iostream>

static void march(Window* window) 
{
	for (int x = 0; window->m_width > x; x++) for (int y = 0; window->m_height > y; y++) 
	{
		vec3 hit = Scene::march(&x, &y, &window->m_width, &window->m_height);
		SDF* hitSDF = Scene::getSDFatPos(hit);
		if (hitSDF != nullptr)
		{
			vec3 color = hitSDF->getColor();

			float shadow = Scene::getShadow(hit);

			color = color * shadow;
			color.toInt();

			window->setRGB(x, y, color.x, color.y, color.z);
		}
	}
}

static void mainLoop(Window* window)
{
	SDF* sphere = new Sphere(vec3(0.0f, 0.0f, 3.0f), 1.0f);
	sphere->setColor(vec3(255.0f, 0.0f, 0.0f));
	Scene::addSDF(sphere);

	Scene::initalizeCamera(			//Initialize camera
		vec3(0.0f, 0.0f, 0.0f),		//Camera position
		vec3(0.0f, 0.0f, 1.0f),		//Camera target
		vec3(0.0f, 1.0f, 0.0f),		//Up vector
		90							//Field of view (in degrees)
	);
	Scene::setLightDir(vec3(0.33f, -1.0f, 0.5f));		//Points light down

	while (window->ProcessMessages())
	{
		march(window);		//Marches the scene, renders it, and buffers it to the window

		window->present();	//Presents the buffered image to the window
		
		Sleep(17);			//Sleep for 17ms to cap at 58.82fps
	}
}

int main() 
{
	int width = 500, height = 500;
	Window* window = new Window(&width, &height);

	mainLoop(window);

	return 0;
}