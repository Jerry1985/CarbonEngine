// Win32Project1.cpp : Defines the entry point for the application.
//

#include <windows.h>
#include <QtWidgets/QApplication>
#include "../UI/Base/basewindow.h"

#include "Container\CString.h"
#include "Container\CArray.h"
#include "Platform\PlatformFile.h"

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

	CString str(S("123213"));
	
	float t = str.ToFloat();

	str.FromFloat(23423.23423424f);

	bool exist = PlatformFile::IsFileExist("d:\\data.txt");

	CArray<int> arry;
	return a.exec();
}