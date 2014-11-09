#include "LogManager.h"
#include "Utility\UtilityMacro.h"

DEFINE_SINGLETON(LogManager)

LogManager::LogManager()
{
}
LogManager::~LogManager()
{
}

void LogManager::AddLog(uint32 type, uint32 catagory, const TCHAR* message)
{
	if (!(m_LogFilter&catagory))
		return;

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
	CString	formated_log;

	formated_log = S("[") + _formatLevel(type) + S("]\t[") + _formatCatagory(catagory) + S("]\t");
	formated_log += message;
	formated_log += "\n";

	return formated_log;
}

CString	LogManager::_formatLevel(uint32 level)
{
	static const CString strLogLevels[] = {
		"LOG_NORMAL",
		"LOG_WARNING",
		"LOG_CRITICAL"
	};

	return strLogLevels[level];
}

CString	LogManager::_formatCatagory(uint32 level)
{
#define	DEFINE_LOG_STR(log)	static const CString str##log(#log)
	DEFINE_LOG_STR(LOG_GENERAL);
	DEFINE_LOG_STR(LOG_RENDERER);

	bool hit = false;
	CString ret;
	if (LOG_GENERAL & level)
	{
		ret += strLOG_GENERAL;
		hit = true;
	}
	if (LOG_RENDERER & level)
	{
		if (hit)
			ret += " ";
		ret += (LOG_RENDERER & level) ? strLOG_RENDERER : "";
		hit = true;
	}
	
	return ret;
}