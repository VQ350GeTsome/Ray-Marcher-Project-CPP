#include "MainWindow.h"
#include "Scene.h"

#include "Vec3.h"
#include "Sphere.h"

#include <iostream>
#include <vector>
#include <omp.h>

static void mainLoop(MainWindow* window, Scene* scene)
{
	while (window->ProcessMessages())
	{
		window->processBuffer(scene->renderScene());	//Renders scene & then processes it into the window buffer then presents it
		
		Sleep(34);			//Sleep for 17ms to cap at 58.82fps
	}
}

//Initializes the scene with objects and settings
static Scene* initializeScene(const int width, const int height)
{
	Scene* scene = new Scene();
	
	scene->updateDimensions(width, height);

	//Camera settings
	vec3	camPos    =		vec3(-1.0f,  0.0f,  0.0f),
			camTarget =		vec3( 1.0f,  0.0f,  0.0f),
			camUp     =		vec3( 0.0f,  1.0f,  0.0f);
	float fov = 90.0f;							
	scene->setCamera(camPos, camTarget, camUp, fov);
	
	//Set lighting settings
	scene->setSceneLight(vec3(0.5f, -1.0f, -0.33f));
	scene->setAmbientLight(0.05f);

	SDF* sphere1 = new Sphere(vec3(3.0f, 0.0f, 0.0f), 1.0f);
	sphere1->setColor(vec3(255.0f, 0.0f, 0.0f));

	scene->addSDF(sphere1);

	return scene;
}

int main() 
{
	omp_set_num_threads(8);	//Will make settings panel for this later ... 

	int w_width = 500, w_height = 500;

	MainWindow* window = new MainWindow(w_width, w_height);

	float scale = 2.0f;		//Ill have to also make a setting for this somewhere ... at some point ... at some time

	Scene* scene		= initializeScene((int)(w_width / scale), (int)(w_height / scale));
	Controls* controls	= new Controls(scene);		//Instatiates the controls and gives it access to the scene
	MenuBar*  menuBar	= new MenuBar (scene);		//Does the same for the menu bar 

	window->giveControlsAccess(controls);			//Gives the window access the controls
	window->giveMenuBarAccess(menuBar);				//Gives the window access to the menuBar

	mainLoop(window, scene);

	return 0;
}