#include "Log.h"
#include "LogManager.h"

bool	EnableLog()
{
#if !CARBON_ENABLE_LOG
	return false;
#endif
	return LogManager::GetSingleton().EnableLog(true);
}

bool	DisableLog()
{
#if !CARBON_ENABLE_LOG
	return false;
#endif
	return LogManager::GetSingleton().EnableLog(false);
}

bool	IsLogEnabled()
{
#if !CARBON_ENABLE_LOG
	return false;
#endif
	return LogManager::GetSingleton().IsLogEnabled();
}

void	SetMinLogLevel(uint32 level)
{
#if !CARBON_ENABLE_LOG
	return;
#endif
	LogManager::GetSingleton().SetMinLogLevel(level);
}

uint32	GetMinLogLevel()
{
#if !CARBON_ENABLE_LOG
	return LOG_NORMAL;
#endif
	return LogManager::GetSingleton().GetMinLogLevel();
}

void	SetLogFilter(uint32 filter)
{
#if !CARBON_ENABLE_LOG
	return;
#endif
	LogManager::GetSingleton().SetLogFilter(filter);
}

bool	IsLogCatagoryEnabled(uint32 catagory)
{
#if !CARBON_ENABLE_LOG
	return false;
#endif
	return LogManager::GetSingleton().IsLogCatagoryEnabled(catagory);
}

void	AddPlatformLogContext()
{
	LogManager::GetSingleton().AddLogContext(LogContext::CreatePlatformContext());
}

void	EnableLogCatagory(uint32 catagory)
{
	uint32 filter = LogManager::GetSingleton().GetLogFilter();
	LogManager::GetSingleton().SetLogFilter(catagory | filter);
}

void	DisbleLogCatagory(uint32 catagory)
{
	uint32 filter = LogManager::GetSingleton().GetLogFilter();
	LogManager::GetSingleton().SetLogFilter(~catagory & filter);
}