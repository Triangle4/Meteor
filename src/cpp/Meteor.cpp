#include "pch.h"
#include <string.h>

#pragma region Local Definitions

#define ID_MENU_EXIT 1
#pragma endregion
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
VOID FileMenu(HMENU hMenuBar, HMENU hFile);
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
		case WM_CREATE: 
		{

			HMENU hMenuBar = CreateMenu();
			HMENU hFile = CreateMenu();
			HMENU hEdit = CreateMenu();
			HMENU hAssets = CreateMenu();
			HMENU hGameObject = CreateMenu();
			HMENU hComponent = CreateMenu();
			HMENU hWindow = CreateMenu();
			HMENU hHelp = CreateMenu();

			FileMenu(hMenuBar, hFile);
			

			AppendMenu(hMenuBar, MF_POPUP, NULL, L"Edit");
			AppendMenu(hMenuBar, MF_POPUP, NULL, L"Assets");
			AppendMenu(hMenuBar, MF_POPUP, NULL, L"GameObject");
			AppendMenu(hMenuBar, MF_POPUP, NULL, L"Component");
			AppendMenu(hMenuBar, MF_POPUP, NULL, L"Window");
			AppendMenu(hMenuBar, MF_POPUP, NULL, L"Help");

			SetMenu(hWnd, hMenuBar);
			break;
		}
		
		case WM_DESTROY: // handles closing the window when the X is clicked
		{
			PostQuitMessage(0);
			break;
		}
		case WM_COMMAND:
		{
			
			switch LOWORD(wparam)
			{
				case ID_MENU_EXIT:
				PostQuitMessage(0);
				break;
			}
		}
		
	}
	return DefWindowProc(hWnd, message, wparam, lparam);
}

#pragma region Menu Functions
VOID FileMenu(HMENU hMenuBar, HMENU hFile)
{
	AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hFile, L"File");
	AppendMenu(hFile, MF_STRING, NULL, L"New Scene				Ctrl+N");
	AppendMenu(hFile, MF_STRING, NULL, L"Open Scene				Ctrl+O");
	AppendMenu(hFile, MF_MENUBREAK, NULL, NULL);
	AppendMenu(hFile, MF_STRING, NULL, L"Save					Ctrl+S");
	AppendMenu(hFile, MF_STRING, NULL, L"Save As...				Ctrl+Shift+S");
	AppendMenu(hFile, MF_MENUBREAK, NULL, NULL);
	AppendMenu(hFile, MF_STRING, NULL, L"New Project...");
	AppendMenu(hFile, MF_STRING, NULL, L"Open Project...");
	AppendMenu(hFile, MF_STRING, NULL, L"Save Project			Ctrl+Alt+S");
	AppendMenu(hFile, MF_MENUBREAK, NULL, NULL);
	AppendMenu(hFile, MF_STRING, NULL, L"Build Settings...		Ctrl+Shift+B");
	AppendMenu(hFile, MF_STRING, NULL, L"Build And Run			Ctrl+B");
	AppendMenu(hFile, MF_MENUBREAK, NULL, NULL);
	AppendMenu(hFile, MF_STRING, ID_MENU_EXIT, L"Exit");
}
#pragma endregion

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