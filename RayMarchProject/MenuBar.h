#pragma once

#include "Scene.h"

#include <wtypes.h>

class MenuBar
{
private:
	Scene* scene;
    
    //Parse input for specific menu
    void file(WPARAM input);
    void sceneq(WPARAM input);  //q becuase scene is a var
    void camera(WPARAM input);
    void render(WPARAM input);

public:
            
    //Menubar ID's
    enum MenuID {
        ID_FILE_OPEN = 101,
        ID_FILE_SAVE = 102,
        ID_FILE_EXPORT = 103,

        ID_SCENE_ADDOBJ = 201,
        ID_SCENE_EDITFLOOR = 202,
        ID_SCENE_EDIT_LIGHTING = 203,
        ID_SCENE_EDIT_FOG = 204,
        ID_SCENE_BEHA_BLEND = 205,

        ID_CAMERA_CHANGEPOS = 301,
        ID_CAMERA_CHANGEFOV = 302,
        ID_CAMERA_GRAIN = 303,

        ID_RENDER_RESOLUTION = 401,
        ID_RENDER_MAXDIST = 402,
        ID_RENDER_SHADOWDIST = 403
    };

	MenuBar(Scene* s) : scene(s) {}

    //Gets input and does stuff
	void parseMenuInput(WPARAM input);
};

