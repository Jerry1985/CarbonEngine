#include "WinLogContext.h"
#include "Container\CString.h"
#include <Windows.h>

LogContext*	 LogContext::CreatePlatformContext()
{
	return new WinLogContext();
}

void WinLogContext::AddLog(const CString& message)
{
	OutputDebugString(message);
}