#include "pch.h"

#pragma region Global Variables

WCHAR WindowClass[MAX_NAME_LENGTH]; // Wide Character
WCHAR WindowTitle[MAX_NAME_LENGTH]; // Wide Character

INT WindowWidth = 1280;
INT WindowHeight  = 720;

HICON hIcon;

#pragma endregion
#pragma region Pre-Declarations

VOID InitializeVariables();
VOID CreateWindowClass();
VOID InitializeWindow();
VOID WindowMessageHandler();
#pragma endregion
#pragma region Operations

int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, INT) //HINSTANCE - Instance of the entire Window, HINSTANCE - not used, LPSTR - Uses commands at runtime to change functionality
{
	InitializeVariables();
	CreateWindowClass();
	InitializeWindow();
	WindowMessageHandler();
	return 0;
}
LRESULT CALLBACK WindowProcess(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam)
{

	switch (message)
	{
	case WM_DESTROY: // handles closing the window when the X is clicked
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, message, wparam, lparam);
}


#pragma endregion
#pragma region Functions

VOID InitializeVariables()
{
	LoadString(HInstance(), IDS_PERGAMENAME, WindowTitle, MAX_NAME_LENGTH); // loads resource string table
	LoadString(HInstance(), IDS_WINDOWCLASS, WindowClass, MAX_NAME_LENGTH); // loads resource string table

	hIcon = LoadIcon(HInstance(), MAKEINTRESOURCE(IDI_MAINICON)); // loads resource icon by int reference
}

VOID CreateWindowClass()
{
	WNDCLASSEX window;
	window.cbSize = sizeof(WNDCLASSEX);
	window.style = CS_HREDRAW | CS_VREDRAW;
	window.cbClsExtra = 0; // Extra Runtime Memory
	window.cbWndExtra = 0; // Extra Runtime Memory
	window.hCursor = LoadCursor(nullptr, IDC_ARROW); // Cursor Image
	window.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH); // Background
	window.hIcon = hIcon; // Window Icon
	window.hIconSm = hIcon; // Taskbar Icon
	window.lpszClassName = WindowClass;
	window.lpszMenuName = nullptr;
	window.hInstance = HInstance();
	window.lpfnWndProc = WindowProcess;

	RegisterClassEx(&window);
}

VOID InitializeWindow()
{
	HWND Window = CreateWindow(WindowClass, WindowTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, WindowWidth, WindowHeight, nullptr, nullptr, HInstance(), nullptr);
	

	if (!Window)
	{
		MessageBox(0, L"FAILED TO CREATE WINDOW", 0, 0);
		PostQuitMessage(0);
	}

	ShowWindow(Window, SW_SHOW);
}

VOID WindowMessageHandler()
{
	MSG msg = { 0 };
	while (msg.message != WM_QUIT)
	{
		//Check For window Messages
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			//Process Window Messages
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}

#pragma endregion