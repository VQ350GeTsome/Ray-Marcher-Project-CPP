#include "windows.h"

#include "MainWindow.h"
#include "Vec3.h"

#include <vector>
#include <cstdint>
#include <windowsx.h>

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CLOSE:		{ DestroyWindow(hWnd); break; }

	case WM_DESTROY:	{ PostQuitMessage(0); return 0; }

	case WM_KEYDOWN:	//Parse key presses
		{
			MainWindow* pWindow = reinterpret_cast<MainWindow*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

			if (pWindow && pWindow->controls) {
				pWindow->controls->parseKeyInput(wParam);
			}
			break;
		}
	case WM_COMMAND:	//Parse menu bar commands
		{
			MainWindow* pWindow = reinterpret_cast<MainWindow*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

			if (pWindow && pWindow->menuBar) {
				pWindow->menuBar->parseMenuInput(wParam);
			}
			break;
		}
	}

		return DefWindowProc(hWnd, uMsg, wParam, lParam); //Handles any messages we didn't manually handle
}

//Constructor & deconstructor
MainWindow::MainWindow(const int& w, const int& h)
	: m_hInstance(GetModuleHandle(nullptr)), m_width(w), m_height(h)
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

	RECT rect = { 100, 100, w + 100, h + 100 };        //Create a RECT for the window size

	AdjustWindowRect(&rect, style, false);				//Pass the RECT into AdjustWindowRect

	m_hWnd = CreateWindowEx(
		0,
		CLASS_NAME,
		L"Render: ",                    
		style,                          
		rect.left,
		rect.top,
		rect.right - rect.left,
		rect.bottom - rect.top,
		NULL,
		NULL,
		m_hInstance,
		NULL
	);

	SetWindowLongPtr(m_hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));


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

	makeMenu();

	ShowWindow(m_hWnd, SW_SHOWDEFAULT);
}
MainWindow::~MainWindow()
{
	if (m_hBitmap) {
		DeleteObject(m_hBitmap);
		m_hBitmap = nullptr;
	}

	const wchar_t* CLASS_NAME = L"Window Class";
	UnregisterClass(CLASS_NAME, m_hInstance);
}

//Menu stuff
void MainWindow::makeMenu()
{
	HMENU menu = CreateMenu();		//Main menu bar

	HMENU	fileMenu		= CreatePopupMenu(),			//File   managment menu
			sceneMenu		= CreatePopupMenu(),			//Scene  managment menu
			cameraMenu		= CreatePopupMenu(),			//Camera managment menu
			renderMenu		= CreatePopupMenu();			//Render managment menu

	AppendMenu(fileMenu, MF_STRING, menuBar->ID_FILE_OPEN,		L"Open Scene");		//Submenu of files
	AppendMenu(fileMenu, MF_STRING, menuBar->ID_FILE_SAVE,		L"Save Scene");
	AppendMenu(fileMenu, MF_STRING, menuBar->ID_FILE_EXPORT,	L"Save As Scene");

	HMENU	enviromentMenu	= CreatePopupMenu(),	//Subsubmenus for sceneMenu
			behaviorMenu	= CreatePopupMenu();

	AppendMenu(sceneMenu, MF_STRING, menuBar->ID_SCENE_ADDOBJ,			L"Add Object");		//Submenu of scene
	AppendMenu(sceneMenu, MF_STRING, menuBar->ID_SCENE_EDITFLOOR,		L"Edit Floor");
	AppendMenu(sceneMenu, MF_POPUP, (UINT_PTR)enviromentMenu,			L"Edit Enviroment");
	AppendMenu(sceneMenu, MF_POPUP, (UINT_PTR)behaviorMenu,				L"Change Object Behavior");

	AppendMenu(enviromentMenu, MF_STRING, menuBar->ID_SCENE_EDIT_LIGHTING,	L"Lighting");		//Subsubmenu of edit enviroment
	AppendMenu(enviromentMenu, MF_STRING, menuBar->ID_SCENE_EDIT_FOG,		L"Fog");

	AppendMenu(behaviorMenu, MF_STRING, menuBar->ID_SCENE_BEHA_BLEND,		L"Blending");		//Subsubmenu of object behavior
	
	AppendMenu(cameraMenu, MF_STRING, menuBar->ID_CAMERA_CHANGEPOS,	L"Change Position");	//Submenu of camera
	AppendMenu(cameraMenu, MF_STRING, menuBar->ID_CAMERA_CHANGEFOV,	L"Change FOV");
	AppendMenu(cameraMenu, MF_STRING, menuBar->ID_CAMERA_GRAIN,		L"Change Grainularity");

	AppendMenu(renderMenu, MF_STRING, menuBar->ID_RENDER_RESOLUTION,	L"Resolution");
	AppendMenu(renderMenu, MF_STRING, menuBar->ID_RENDER_MAXDIST,		L"Max Distance");
	AppendMenu(renderMenu, MF_STRING, menuBar->ID_RENDER_SHADOWDIST,	L"Shadow Distance");

	AppendMenu(menu, MF_POPUP, (UINT_PTR)fileMenu,		L"File");		//Append menus of submenus to the bar
	AppendMenu(menu, MF_POPUP, (UINT_PTR)sceneMenu,		L"Scene");
	AppendMenu(menu, MF_POPUP, (UINT_PTR)cameraMenu,	L"Camera");
	AppendMenu(menu, MF_POPUP, (UINT_PTR)renderMenu,	L"Render");

	SetMenu(m_hWnd, menu);		//Append the bar of menus to the window
}

//Process messages
bool MainWindow::ProcessMessages()
{
	MSG msg = {};

	while (PeekMessage(&msg, nullptr, 0u, 0u, PM_REMOVE)) //Runs until all messages are processed in the queue
	{
		switch (msg.message)
		{
		case(WM_QUIT):
			return false;
			break;
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return true;
}

//Imaging stuff
bool MainWindow::setRGB(int x, int y, int r, int g, int b)
{
	if (!m_pPixels) return false;
	if (x < 0 || x >= m_width || y < 0 || y >= m_height) return false;
	uint32_t* pixels = static_cast<uint32_t*>(m_pPixels);
	uint32_t color = (uint8_t)b | ((uint8_t)g << 8) | ((uint8_t)r << 16);
	pixels[y * m_width + x] = color;
	return true;
}
void MainWindow::present()
{
	HDC hdc = GetDC(m_hWnd);
	HDC memDC = CreateCompatibleDC(hdc);
	HGDIOBJ oldBitmap = SelectObject(memDC, m_hBitmap);
	BitBlt(hdc, 0, 0, m_width, m_height, memDC, 0, 0, SRCCOPY);
	SelectObject(memDC, oldBitmap);
	DeleteDC(memDC);
	ReleaseDC(m_hWnd, hdc);
}
void MainWindow::processBuffer(const std::vector<std::vector<vec3>>& buffer) {
	if (!m_pPixels) return;
	int srcW = (int)buffer[0].size();
	int srcH = (int)buffer.size();
	int dstW = m_width;
	int dstH = m_height;
	uint32_t* dst = static_cast<uint32_t*>(m_pPixels);

	// compute scale to preserve aspect ratio
	float scaleX = (float)dstW / srcW;
	float scaleY = (float)dstH / srcH;
	float scale = (((scaleX) < (scaleY)) ? (scaleX) : (scaleY));
	int outW = (int)std::round(srcW * scale);
	int outH = (int)std::round(srcH * scale);
	int offsetX = (dstW - outW) / 2;
	int offsetY = (dstH - outH) / 2;

	// clear to background (optional)
	uint32_t bg = 0x000000; // black
	for (int y = 0; y < dstH; ++y)
		for (int x = 0; x < dstW; ++x)
			dst[y * dstW + x] = bg;

	// nearest-neighbor upscale
	for (int sy = 0; sy < srcH; ++sy) {
		int dy0 = offsetY + (int)std::floor(sy * scale);
		int dy1 = offsetY + (int)std::floor((sy + 1) * scale);
		if (dy1 <= dy0) dy1 = dy0 + 1;
		for (int sx = 0; sx < srcW; ++sx) {
			vec3 c = buffer[sy][sx].clamp(0, 255);
			uint8_t r = static_cast<uint8_t>(c.x);
			uint8_t g = static_cast<uint8_t>(c.y);
			uint8_t b = static_cast<uint8_t>(c.z);
			uint32_t color = b | (g << 8) | (r << 16);

			int dx0 = offsetX + (int)std::floor(sx * scale);
			int dx1 = offsetX + (int)std::floor((sx + 1) * scale);
			if (dx1 <= dx0) dx1 = dx0 + 1;

			for (int dy = dy0; dy < dy1 && dy < dstH; ++dy) {
				uint32_t* row = dst + dy * dstW;
				for (int dx = dx0; dx < dx1 && dx < dstW; ++dx) {
					row[dx] = color;
				}
			}
		}
	}

	present();
}