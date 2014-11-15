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

class Test
{
public:
	Test()
	{
		CARBON_LOG(LOG_NORMAL, LOG_GENERAL, S("Constructor."));
	}
	Test(const Test& t)
	{
		CARBON_LOG(LOG_NORMAL, LOG_GENERAL, S("Copy Constructor."));
	}
	~Test()
	{
		CARBON_LOG(LOG_NORMAL, LOG_GENERAL, S("Destructor."));
	}
};

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
	/*
	{
		CString a(S("asfsa"));


	}
	CString str(S("123213"));
	
	float t = str.ToFloat();

	str.FromFloat(23423.23423424f);*/
	/*
	bool exist = PlatformFile::IsFileExist(S("d:\\data.txt"));
	int32 size = PlatformFile::FileSize(S("d:\\data.txt"));
	bool readonly = PlatformFile::IsFileReadOnly(S("d:\\data.txt"));
	exist = PlatformFile::IsDirExist(S("d:\\data.txt"));
	readonly = PlatformFile::IsDirReadOnly(S("d:\\data.txt"));
	*/
/*	PlatformFileHandle* handle = PlatformFile::OpenFile(S("data.txt"),false);
	bool flag = handle->Write((uint8*)(const TCHAR*)str, str.StrSizeInBytes());
	delete handle;

	{
		PtrProxy<PlatformFileHandle> read_handle(PlatformFile::OpenFile(S("data.txt")));
		uint8 data1[1024];
		flag = read_handle->Read((uint8*)data1, read_handle->Size());
		str.FromBytes((uint8*)data1, read_handle->Size());
	}
	*/
	EnableLog();
	AddPlatformLogContext();
	AddFileLogContext(S("carbon.log"));
	//	DisbleLogCatagory(LOG_GENERAL);

	//CARBON_LOG(LOG_NORMAL, LOG_GENERAL, S("First Log comes out."));
	//CARBON_LOG(LOG_WARNING, LOG_RENDERER, S("Second Log comes out."));

	{
		Test tasf;

		CArray<Test> a;
		a.Add(tasf);
	}

	CArray<int> ta;
	for (int i = 0; i < 100;++i)
		ta.Add(i);

//	ta.Remove(10, 20);
//	ta.Add(10, 23123);
//	ta.Add(10, 234234);

	int data[] = { 2, 123, 423423, 5324, 245234, 235, 23, 234, 234, 2334, 54, 23 };

//	ta.Add(2, data, 12);
	ta.Add(2, ta);

	int i = 0;
	CArrayIterator<int> it(ta);
	while (it.IsEnd() == false)
	{
		CString log(S("Index ") + CString(i) + S(" : ") + CString(*it));
		CARBON_LOG(LOG_NORMAL, LOG_GENERAL, log);
		++it;
		++i;
	}
	LogManager::DeleteSingleton();
	
	return a.exec();
}