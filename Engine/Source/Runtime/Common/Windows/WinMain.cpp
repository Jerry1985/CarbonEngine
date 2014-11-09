// Win32Project1.cpp : Defines the entry point for the application.
//

#include <windows.h>
#include <QtWidgets/QApplication>
#include "../UI/Base/basewindow.h"

#include "Container\CString.h"
#include "Container\CArray.h"
#include "Platform\PlatformFile.h"

#include "Utility\PtrProxy.h"
#include "Log\Log.h"

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

	bool exist = PlatformFile::IsFileExist(S("d:\\data.txt"));
	int32 size = PlatformFile::FileSize(S("d:\\data.txt"));
	bool readonly = PlatformFile::IsFileReadOnly(S("d:\\data.txt"));
	exist = PlatformFile::IsDirExist(S("d:\\data.txt"));
	readonly = PlatformFile::IsDirReadOnly(S("d:\\data.txt"));

	PlatformFileHandle* handle = PlatformFile::OpenFile(S("data.txt"),false);
	bool flag = handle->Write((uint8*)(const TCHAR*)str, str.StrSizeInBytes());
	delete handle;

	{
		PtrProxy<PlatformFileHandle> read_handle(PlatformFile::OpenFile(S("data.txt")));
		uint8 data1[1024];
		flag = read_handle->Read((uint8*)data1, read_handle->Size());
		str.FromBytes((uint8*)data1, read_handle->Size());
	}

	EnableLog();
	AddPlatformLogContext();
	DisbleLogCatagory(LOG_GENERAL);

	CARBON_LOG(LOG_NORMAL, LOG_GENERAL, "First Log comes out.");
	CARBON_LOG(LOG_WARNING, (LOG_GENERAL | LOG_RENDERER), "Second Log comes out.");

	LogManager::DeleteSingleton();
	
	return a.exec();
}