// Win32Project1.cpp : Defines the entry point for the application.
//

#include <windows.h>
#include "Core\Engine.h"

int APIENTRY WinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow)
{
	Engine engine = GetEngine();

	// Initialize Game Engine
	engine.Init();

	// Run Game Engine
	engine.Run();

	// Destroy Game Engine
	engine.Destroy();

	return 0;
}