#pragma once

// Define platform types
typedef unsigned char			uint8;
typedef unsigned short int		uint16;
typedef unsigned int			uint;
typedef unsigned int			uint32;
typedef unsigned long long		uint64;

typedef signed char				int8;
typedef signed short int		int16;
typedef signed int				int32;
typedef signed long long		int64;

typedef char					CHAR;
typedef	wchar_t					WCHAR;

typedef	char*					PCHAR;
typedef wchar_t*				PWCHAR;

typedef const char*				CPCHAR;
typedef const wchar_t*			CPWCHAR;

// switch between mbcs and unicode
#ifdef UNICODE
#define	S(str)		(L##str)
#else
#define S(str)		(str)
#endif
