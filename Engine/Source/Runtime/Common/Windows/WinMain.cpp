// Win32Project1.cpp : Defines the entry point for the application.
//

#include <windows.h>
#include <QtWidgets/QApplication>
#include "../UI/Base/basewindow.h"


// to be deleted
#include "Container\CString.h"
#include "Container\CArray.h"
#include "Platform\PlatformFile.h"
#include "Utility\PtrProxy.h"
#include "Log\Log.h"
#include "Container\CLinkedList.h"
#include "Shader\FlipViewShader.h"

int APIENTRY WinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow)
{
	EnableLog();
	AddPlatformLogContext();
	AddFileLogContext(S("carbon.log"));

	// No need to pass the real parameter to QT
	int argc = 0;
	char argv[] = "";
	QApplication a(argc, (char**)&argv);

	BaseWindow p;
	p.show();

	LogManager::DeleteSingleton();

	return a.exec();
}