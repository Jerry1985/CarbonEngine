#pragma once

#include "Log\LogContext.h"

class WinLogContext : public LogContext
{
public:
	virtual void AddLog(const CString& message);
};