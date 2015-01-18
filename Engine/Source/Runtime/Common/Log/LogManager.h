#pragma once

#include "Utility\Singleton.h"
#include "Container\CArray.h"
#include "Container\CString.h"
#include "LogContext.h"

enum LOG_LEVEL
{
	LOG_NORMAL = 0,
	LOG_WARNING,
	LOG_CRITICAL,
	LOG_DEBUG,
};

enum LOG_CATAGORY
{
	LOG_NONE = 0,
	LOG_GENERAL = 1,
	LOG_RENDERER = 2,
	LOG_FILE = 4,
	LOG_ALL = LOG_GENERAL | LOG_RENDERER | LOG_FILE,
	GOG_CATAGORY_COUNT = 3,
};

class LogManager : public Singleton<LogManager>
{
public:
	LogManager();
	~LogManager();

	// enable log
	bool		EnableLog(bool enable);
	bool		IsLogEnabled() const;

	void		SetMinLogLevel(uint32 level);
	uint32		GetMinLogLevel() const;

	void		SetLogFilter(uint32 filter);
	uint32		GetLogFilter() const;
	bool		IsLogCatagoryEnabled(uint32 catagory) const;

	void		AddLogContext(LogContext* context);

	void		AddLog(uint32 type, uint32 catagory, CPCHAR message);
	void		AddLog(uint32 type, uint32 catagory, CPWCHAR message);

private:
	bool			m_LogEnabled = true;
	uint32			m_LogFilter = LOG_ALL;
	uint32			m_LogMinLevel = LOG_NORMAL;

	CArray<LogContext*>	m_Contexts;

	const CString&	_formatLevel(uint32 level);
	const CString&	_formatCatagory(uint32 level);
	CString			_formatLog(uint32 type, uint32 catagory, const TCHAR* message);
	void			_releaseLogContexts();
	void			_addLog(uint32 type, uint32 catagory, const TCHAR* message);
};