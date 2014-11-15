#pragma once

#include "Misc\Build.h"
#include "LogManager.h"

#if CARBON_ENABLE_LOG
	#define	CARBON_LOG(type,catagory,message)	LogManager::GetSingleton().AddLog(type,catagory,message)
#else
	#define	CARBON_LOG(type,catagory,message)	{}
#endif

bool		EnableLog();
bool		DisableLog();
bool		IsLogEnabled();

void		SetMinLogLevel(uint32 level);
uint32	GetMinLogLevel();

void		SetLogFilter(uint32 filter);
void		EnableLogCatagory(uint32 catagory);
void		DisbleLogCatagory(uint32 catagory);
bool		IsLogCatagoryEnabled(uint32 catagory);

void		AddPlatformLogContext();
void		AddFileLogContext(const TCHAR* filename);