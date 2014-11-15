#pragma once

#include <string>

class WinString
{
public:
	WinString(){}
	~WinString(){}

	static int32	Strlen(CPWCHAR str);
	static int32	StoI(CPWCHAR str);
	static void		ItoS(int32 data, PWCHAR str, int32 strlen);
	static float	StoF(CPWCHAR str);
	static void		FtoS(float data, PWCHAR str, int32 strlen);
	static void		Format(PCHAR buf, int32 strlen, CPCHAR format, va_list);

	static int32	Strlen(CPCHAR str);
	static int32	StoI(CPCHAR str);
	static void		ItoS(int32 data, PCHAR str, int32 strlen);
	static float	StoF(CPCHAR str);
	static void		FtoS(float data, PCHAR str, int32 strlen);
	static void		Format(PWCHAR str, int32 strlen, CPWCHAR format, va_list);
};

FORCE_INLINE int32	WinString::Strlen(CPWCHAR str)
{
	return (int32)wcslen(str);
}
FORCE_INLINE int32	WinString::StoI(CPWCHAR str)
{
	return (int32)wcstol(str, 0, 10);
}
FORCE_INLINE void	WinString::ItoS(int32 data, PWCHAR str, int32 strlen)
{
	_itow_s(data, str, strlen, 10);
}
FORCE_INLINE float	WinString::StoF(CPWCHAR str)
{
	return wcstof(str, 0);
}
FORCE_INLINE void	WinString::FtoS(float data, PWCHAR str, int32 strlen)
{
	swprintf(str, strlen, L"%f", data);
}
FORCE_INLINE void	WinString::Format(PCHAR buf, int32 strlen, CPCHAR format, va_list args)
{
	vsprintf_s(buf, strlen, format, args);
}

FORCE_INLINE int32	WinString::Strlen(CPCHAR str)
{
	return (int32)strlen(str);
}
FORCE_INLINE int32	WinString::StoI(CPCHAR str)
{
	return atoi(str);
}
FORCE_INLINE void	WinString::ItoS(int32 data, PCHAR str, int32 strlen)
{
	_itoa_s(data, str, strlen, 10);
}
FORCE_INLINE float	WinString::StoF(CPCHAR str)
{
	return (float)atof(str);
}
FORCE_INLINE void	WinString::FtoS(float data, PCHAR str, int32 strlen)
{
	sprintf_s(str, strlen, "%f", data);
}

FORCE_INLINE void	WinString::Format(PWCHAR buf, int32 strlen, CPWCHAR format, va_list args)
{
	vswprintf(buf, strlen, format, args);
}

typedef	WinString	PlatformString;
