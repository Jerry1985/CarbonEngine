#pragma once

#include "Platform\Platform.h"

namespace PlatformString
{
	// the original hash algorithm comes from http://pokristensson.com/strmap.html
	FORCE_INLINE uint32	StrHash(CPCHAR str)
	{
		unsigned long hash = 5381;
		int c;

		while (c = *str++) {
			hash = ((hash << 5) + hash) + c;
		}
		return hash;
	}

	// Not sure if the same algorithm applies well.
	FORCE_INLINE uint32	StrHash(CPWCHAR str)
	{
		unsigned long hash = 5381;
		int c;

		while (c = *str++) {
			hash = ((hash << 5) + hash) + c;
		}
		return hash;
	}
}

#ifdef CARBON_IN_WINDOWS
#include "Windows\WinString.h"
#endif