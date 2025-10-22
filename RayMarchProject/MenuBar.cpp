#include "MenuBar.h"
#include "Scene.h"

#include <wtypes.h>
#include <iostream>
#include <vector>
#include <string>

void MenuBar::parseMenuInput(WPARAM input) {
	switch (input / 100) {						//Gets first digit ( ... or last i dunno ... whatever the left most is called)
	case 1: { file(input);		break; }		//1 == file
	case 2: { sceneq(input);	break; }		//2 == scene
	case 3: { camera(input);	break; }		//3 == camera
	case 4: { render(input);	break; }		//4 == render
	}
}

void MenuBar::file(WPARAM input) {
	switch (input) {
	case ID_FILE_OPEN:
		//Open file explorer
		break;
	case ID_FILE_SAVE:

		break;
	}
}

void MenuBar::sceneq(WPARAM input){

}

void MenuBar::camera(WPARAM input){

}

void MenuBar::render(WPARAM input){

}