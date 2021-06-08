#include <windows.h>


#define MAX_NAME_LENGTH 256 // Used simply to make the codre more readable
#define HInstance() GetModuleHandle(NULL) // Used to call back our HINSTANCE
WCHAR WindowClass[MAX_NAME_LENGTH]; // Wide Character
WCHAR WindowTitle[MAX_NAME_LENGTH]; // Wide Character
INT WindowWidth = 1280;
INT WindowHeight  = 720;


LRESULT CALLBACK WindowProcess(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam)
{

	switch (message)
	{
		case WM_DESTROY: // handles closing the window when the X is clicked
			PostQuitMessage(0);
			break;
	}
	return DefWindowProc(hWnd,  message, wparam, lparam);
}

int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, INT) //HINSTANCE - Instance of the entire Window, HINSTANCE - not used, LPSTR - Uses commands at runtime to change functionality
{
	// Initialize Global Variables
	wcscpy_s(WindowClass, TEXT("Meteor"));
	wcscpy_s(WindowTitle, TEXT("Core"));

	// Create Window class
	WNDCLASSEX window;
	window.cbSize = sizeof(WNDCLASSEX);
	window.style = CS_HREDRAW | CS_VREDRAW;
	window.cbClsExtra = 0; // Extra Runtime Memory
	window.cbWndExtra = 0; // Extra Runtime Memory

	window.hCursor = LoadCursor(nullptr, IDC_ARROW); // Cursor Image
	window.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH); // Background

	window.hIcon = LoadIcon(0, IDI_APPLICATION); // Window Icon
	window.hIconSm = LoadIcon(0, IDI_APPLICATION); // Taskbar Icon

	window.lpszClassName = WindowClass;

	window.lpszMenuName = nullptr;

	window.hInstance = HInstance();

	window.lpfnWndProc = WindowProcess;

	RegisterClassEx(&window);

	// Create Window (Name, Title, Stylem XPos, YPos, Width, Height, ParentWindow, Menu, HInstance, Instructions)
	HWND Window = CreateWindow(WindowClass, WindowTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, WindowWidth, WindowHeight, nullptr, nullptr, HInstance(), nullptr);
	ShowWindow(Window, SW_SHOW);

	if (!Window)
	{
		MessageBox(0, L"FAILED TO CREATE WINDOW",0,0);
		return 0;
	}

	// listen for events
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
	return 0;
}