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

#include "Container\CLinkedList.h"

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

	CLinkedList<int>		list;
	CLinkedListNode<int>	node[10];
	for (int i = 0; i < 10; ++i)
	{
		node[i].m_Data = i;
		list.Link(&node[i]);
	}
	node[3].UnLink();
	node[5].UnLink();
	node[0].UnLink();
	node[9].UnLink();

	list.Link(&node[9]);

	CLinkedListIterator<int> it(list);
	while (!it.IsEnd())
		CARBON_LOG(LOG_NORMAL, LOG_GENERAL, STR("%d", *it++));

	LogManager::DeleteSingleton();

	return a.exec();
}