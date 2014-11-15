#pragma once

#include "LogContext.h"
#include "Container\CArray.h"
#include "Container\CString.h"

#define	MAX_LOG_INMEMORY	1024

class FileLogContext : public LogContext
{
public:
	FileLogContext( const TCHAR* filename );
	~FileLogContext();

	// add one log entry
	virtual void AddLog(const CString& message);

	// flush the log
	void Flush();

private:
	CString			m_LogFileName;
	CArray<CString>	m_LogInfo;
};