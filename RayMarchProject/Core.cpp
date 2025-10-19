#include "Window.h"
#include "Scene.h"
#include "Vec3.h"
#include "Sphere.h"

#include <iostream>
#include <vector>

static void mainLoop(Window* window, Scene* scene)
{
	while (window->ProcessMessages())
	{
		std::vector<std::vector<vec3>> buffer = scene->renderScene();	//Render the scene to buffer

		for (int x = 0; x < window->m_width; x++)	for (int y = 0; y < window->m_height; y++)
		{
			vec3 color = buffer[y][x].clamp(0, 255);						//Get the color from the buffer
			window->setRGB(x, y, (int)color.x, (int)color.y, (int)color.z); //Set the pixel to that color
		}

		window->present();	//Presents the buffered image to the window
		
		Sleep(17);			//Sleep for 17ms to cap at 58.82fps
	}
}
//Initializes the scene with objects and settings
static Scene* initializeScene(const int width, const int height)
{
	Scene* scene = new Scene();
	
	scene->updateDimensions(width, height);

	vec3	camPos    =		vec3(0.0f, 0.0f, 0.0f),
			camTarget =		vec3(0.0f, 1.0f, 0.0f),
			camUp     =		vec3(0.0f, 0.0f, 1.0f);
	float fov = 90.0f;							//Camera FOV

	scene->setCamera(camPos, camTarget, camUp, fov);

	vec3 lightDir = vec3(-0.33f, 0.5f, -1.0f);

	scene->setLightDirection(lightDir);

	SDF* sphere1 = new Sphere(vec3(0.0f, 3.0f, 0.0f), 1.0f);
	sphere1->setColor(vec3(255.0f, 0.0f, 0.0f));

	scene->addSDF(sphere1);

	return scene;
}

int main() 
{
	int width = 500, height = 500;
	Window* window = new Window(&width, &height);

	Scene* scene = initializeScene(width, height);

	mainLoop(window, scene);

	return 0;
}