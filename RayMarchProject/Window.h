#pragma once

#include <Windows.h>

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

class Window
{
public:

	int m_width, m_height;

	Window(const int* w, const int* h);				//Default constructor
	Window(const Window&) = delete;					//Delete copy constructor
	Window& operator =(const Window&) = delete;		//Delete equal operator
	~Window();										//Destructor

	bool setRGB(int x, int y, int r, int g, int b);	//Sets a pixel (x, y) to a certain RGB value

	bool ProcessMessages();							//Process all messages in the queue, return false if quit message

	void present();
private:
	HINSTANCE m_hInstance;
	HWND m_hWnd;

	

	HBITMAP m_hBitmap = nullptr;
	void* m_pPixels = nullptr;
};

