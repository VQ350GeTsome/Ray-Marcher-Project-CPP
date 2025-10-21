#pragma once

#include "Vec3.h"
#include "Scene.h"
#include "Controls.h"

#include <Windows.h>
#include <vector>

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

class Window
{
public:

	int m_width, m_height;

	Controls* controls;

	Window(const int& w, const int& h);				//Default constructor
	Window(const Window&) = delete;					//Delete copy constructor
	Window& operator =(const Window&) = delete;		//Delete equal operator
	~Window();										//Destructor
		
	bool ProcessMessages();							//Process all messages in the queue, return false if quit message

	bool setRGB(int x, int y, int r, int g, int b);				//Sets a pixel (x, y) to a certain RGB value
	void present();												//Present the buffer (repaint)
	void processBuffer(std::vector<std::vector<vec3>> buffer);	//Pass in a buffer and present it

	void giveControlsAccess(Controls* controls) { this->controls = controls;  }

private:

	HINSTANCE m_hInstance;
	HWND m_hWnd;

	HBITMAP m_hBitmap = nullptr;
	void* m_pPixels = nullptr;

	void makeMenu();
};

