#include "window.h"

#include "Window.h"
#include <cstdint>

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam); //Handles any messages we didn't manually handle
}

Window::Window(const int* w, const int* h)
	: m_hInstance(GetModuleHandle(nullptr)), m_width(*w), m_height(*h)
{
	const wchar_t* CLASS_NAME = L"Window Class";

	WNDCLASS windowClass = {};
	windowClass.lpszClassName = CLASS_NAME;
	windowClass.hInstance = m_hInstance;
	windowClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClass.lpfnWndProc = WindowProc;

	RegisterClass(&windowClass);

	DWORD style = WS_CAPTION | WS_MINIMIZE | WS_SYSMENU;

	RECT rect = { 100, 100, *w + 100, *h + 100 };        //Create a RECT for the window size

	AdjustWindowRect(&rect, style, false); //Pass the RECT into AdjustWindowRect

	m_hWnd = CreateWindowEx(
		0,
		CLASS_NAME,
		L"Title",                       // Window text
		style,                          // Window style
		rect.left,
		rect.top,
		rect.right - rect.left,
		rect.bottom - rect.top,
		NULL,
		NULL,
		m_hInstance,
		NULL
	);

	BITMAPINFO bmi = {};	// Creates a 32-bit DIB section for the buffer
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = m_width;
	bmi.bmiHeader.biHeight = -m_height; // negative for top-down
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biCompression = BI_RGB;

	HDC hdc = GetDC(m_hWnd);
	m_hBitmap = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, &m_pPixels, nullptr, 0);
	ReleaseDC(m_hWnd, hdc);

	ShowWindow(m_hWnd, SW_SHOWDEFAULT);
}

Window::~Window()
{
	if (m_hBitmap) {
		DeleteObject(m_hBitmap);
		m_hBitmap = nullptr;
	}

	const wchar_t* CLASS_NAME = L"Window Class";
	UnregisterClass(CLASS_NAME, m_hInstance);
}

bool Window::ProcessMessages()
{
	MSG msg = {};

	while (PeekMessage(&msg, nullptr, 0u, 0u, PM_REMOVE)) //Runs until all messages are processed in the queue
	{
		if (msg.message == WM_QUIT) //If we get a quit message return false
		{
			return false;
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return true;
}

bool Window::setRGB(int x, int y, int r, int g, int b)
{
	if (!m_pPixels) return false;
	if (x < 0 || x >= m_width || y < 0 || y >= m_height) return false;
	uint32_t* pixels = static_cast<uint32_t*>(m_pPixels);
	uint32_t color = (uint8_t)b | ((uint8_t)g << 8) | ((uint8_t)r << 16);
	pixels[y * m_width + x] = color;
	return true;
}

void Window::present()
{
	HDC hdc = GetDC(m_hWnd);
	HDC memDC = CreateCompatibleDC(hdc);
	HGDIOBJ oldBitmap = SelectObject(memDC, m_hBitmap);
	BitBlt(hdc, 0, 0, m_width, m_height, memDC, 0, 0, SRCCOPY);
	SelectObject(memDC, oldBitmap);
	DeleteDC(memDC);
	ReleaseDC(m_hWnd, hdc);
}