#include "Controls.h"
#include "Vec3.h"
#include "Scene.h"

#include <iostream>
#include <tuple>

void Controls::parseKeyInput(WPARAM input) 
{
	if (camMove(input))     return;     //Move camera if needed
    if (camPan(input))      return;     //Else pan the camera
}

bool Controls::camMove(WPARAM input)
{
    vec3 m = vec3(0.0f, 0.0f, 0.0f);
    bool move = true;
    bool shiftHeld = (GetAsyncKeyState(VK_SHIFT) & 0x8000);

    std::tuple<vec3, vec3, vec3> camOrien = scene->getCameraOrien();    //Gets camera orientation, (forward, right, up)

    vec3    forward    = std::get<0>(camOrien),        //Get forward vector
            right      = std::get<1>(camOrien),        //Get right vector
            up         = std::get<2>(camOrien);        //Get up vector

    switch (input) 
    {
    case 'W':   m = shiftHeld ? up *  moveGrain : forward *  moveGrain;   break;    //If shift + up then move camera up, else forward
    case 'S':   m = shiftHeld ? up * -moveGrain : forward * -moveGrain;   break;  //If shift + down then move camera down, else backwards
    case 'A':   m = right * -moveGrain;  break; //Move camera left
    case 'D':   m = right *  moveGrain;   break; //Move camera right

    default: move = false;
    }
    if (move) scene->moveCamera(m);     //Implement the movement
    return move;
}

bool Controls::camPan(WPARAM input) 
{
    boolean pan = true;

    switch (input) 
    {
    case VK_UP:     scene->rotateCamera( 0.0f,  panGrain);   break;
    case VK_DOWN:   scene->rotateCamera( 0.0f, -panGrain);   break;
    case VK_RIGHT:  scene->rotateCamera(-panGrain,  0.0f);   break;
    case VK_LEFT:   scene->rotateCamera( panGrain, 0.0f);    break;

    default: pan = false;
    }
    return pan;
}