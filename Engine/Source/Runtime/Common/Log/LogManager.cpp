#include "LogManager.h"
#include "Utility\UtilityMacro.h"

DEFINE_SINGLETON(LogManager)

LogManager::LogManager()
{
}
LogManager::~LogManager()
{
	_releaseLogContexts();
}

void LogManager::AddLog(uint32 type, uint32 catagory, CPCHAR message)
{
	if (!(m_LogFilter&catagory) || type < m_LogMinLevel)
		return;

	TCHAR	desc[4096];
	PlatformString::StringConvert(message, desc);

	// add log
	_addLog(type, catagory, desc);
}

void LogManager::AddLog(uint32 type, uint32 catagory, CPWCHAR message)
{
	if (!(m_LogFilter&catagory) || type < m_LogMinLevel)
		return;

	TCHAR	desc[4096];
	PlatformString::StringConvert(message, desc);

	// add log
	_addLog(type, catagory, desc);
}

void LogManager::_addLog(uint32 type, uint32 catagory, const TCHAR* message)
{
	CString formated_log = _formatLog(type, catagory, message);

	CArrayIterator<LogContext*> it(m_Contexts);
	while (!it.IsEnd())
	{
		(*it)->AddLog(formated_log);
		++it;
	}
}

void	LogManager::AddLogContext(LogContext* context)
{
	if ( context )
		m_Contexts.Add(context);
}

void	LogManager::_releaseLogContexts()
{
	CArrayIterator<LogContext*> it(m_Contexts);
	while (!it.IsEnd())
	{
		SAFE_DELETE(*it);
		++it;
	}
	m_Contexts.Release();
}

bool	LogManager::EnableLog(bool enable)
{
	return m_LogEnabled = enable;
}
bool	LogManager::IsLogEnabled() const
{
	return m_LogEnabled;
}
void	LogManager::SetMinLogLevel(uint32 level)
{
	m_LogMinLevel = level;
}
uint32	LogManager::GetMinLogLevel() const
{
	return m_LogMinLevel;
}

void	LogManager::SetLogFilter(uint32 filter)
{
	m_LogFilter = filter;
}
bool	LogManager::IsLogCatagoryEnabled(uint32 catagory) const
{
	return !!(m_LogFilter & catagory);
}

uint32 LogManager::GetLogFilter() const
{
	return m_LogFilter;
}

CString	LogManager::_formatLog(uint32 type, uint32 catagory, const TCHAR* message)
{
	return STR(S("[%s]\t[%s]\t%s\r\n"), (const TCHAR*)_formatLevel(type), (const TCHAR*)_formatCatagory(catagory), message);
}

const CString&	LogManager::_formatLevel(uint32 level)
{
	static const CString strLogLevels[] = {
		S("LOG_NORMAL"),
		S("LOG_WARNING"),
		S("LOG_CRITICAL"),
		S("LOG_DEBUG")
	};

	return strLogLevels[level];
}

const CString&	LogManager::_formatCatagory(uint32 level)
{
#define	DEFINE_LOG_STR(log)	static const CString str##log(S(#log))
	DEFINE_LOG_STR(LOG_GENERAL);
	DEFINE_LOG_STR(LOG_RENDERER);
	DEFINE_LOG_STR(LOG_FILE);
	DEFINE_LOG_STR(LOG_NONE);

	if (LOG_GENERAL & level)
		return strLOG_GENERAL;
	else if (LOG_RENDERER & level)
		return strLOG_RENDERER;
	else if (LOG_FILE & level)
		return strLOG_FILE;

	return strLOG_NONE;
}