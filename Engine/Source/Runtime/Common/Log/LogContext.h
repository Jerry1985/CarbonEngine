#pragma once

class CString;

class LogContext
{
public:
	LogContext(){}
	virtual ~LogContext(){}

	// add one log entry
	virtual void AddLog(const CString& message) = 0;

	static	LogContext*		CreatePlatformContext();
};