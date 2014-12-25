#pragma once

#include <string>

namespace PlatformString
{
	FORCE_INLINE int32	Strlen(CPWCHAR str)
	{
		return (int32)wcslen(str);
	}
	FORCE_INLINE int32	StoI(CPWCHAR str)
	{
		return (int32)wcstol(str, 0, 10);
	}
	FORCE_INLINE void	ItoS(int32 data, PWCHAR str, int32 strlen)
	{
		_itow_s(data, str, strlen, 10);
	}
	FORCE_INLINE float	StoF(CPWCHAR str)
	{
		return wcstof(str, 0);
	}
	FORCE_INLINE void	FtoS(float data, PWCHAR str, int32 strlen)
	{
		swprintf(str, strlen, L"%f", data);
	}
	FORCE_INLINE void	Format(PCHAR buf, int32 strlen, CPCHAR format, va_list args)
	{
		vsprintf_s(buf, strlen, format, args);
	}
	FORCE_INLINE void	Strcpy(PCHAR dst, int32 strlen, CPCHAR src)
	{
		strcpy_s(dst, strlen, src);
	}
	FORCE_INLINE int32	Strcmp(CPCHAR src, CPCHAR dst)
	{
		return strcmp(src, dst);
	}

	FORCE_INLINE int32	Strlen(CPCHAR str)
	{
		return (int32)strlen(str);
	}
	FORCE_INLINE int32	StoI(CPCHAR str)
	{
		return atoi(str);
	}
	FORCE_INLINE void	ItoS(int32 data, PCHAR str, int32 strlen)
	{
		_itoa_s(data, str, strlen, 10);
	}
	FORCE_INLINE float	StoF(CPCHAR str)
	{
		return (float)atof(str);
	}
	FORCE_INLINE void	FtoS(float data, PCHAR str, int32 strlen)
	{
		sprintf_s(str, strlen, "%f", data);
	}
	FORCE_INLINE void	Format(PWCHAR buf, int32 strlen, CPWCHAR format, va_list args)
	{
		vswprintf(buf, strlen, format, args);
	}
	FORCE_INLINE void	Strcpy(PWCHAR dst, int32 strlen, CPWCHAR src)
	{
		wcscpy_s(dst, strlen, src);
	}
	FORCE_INLINE int32	Strcmp(CPWCHAR src, CPWCHAR dst)
	{
		return wcscmp(src, dst);
	}
}