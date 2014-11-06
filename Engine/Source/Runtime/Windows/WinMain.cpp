// Win32Project1.cpp : Defines the entry point for the application.
//
#include <windows.h>
#include <QtWidgets/QApplication>
#include "../UI/Base/basewindow.h"

#include "../Common/Container/CString.h"

int APIENTRY WinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow)
{
	// No need to pass the real parameter to QT
	int argc = 0;
	char argv[] = "";
	QApplication a(argc, (char**)&argv);

	BaseWindow p;
	p.show();

	return a.exec();
}