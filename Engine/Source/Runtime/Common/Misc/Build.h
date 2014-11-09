#pragma once

#ifdef CARBON_DEBUG_BUILD
	#define	CARBON_BUILD_DEBUG	1
#endif

#if CARBON_RELEASE_BUILD
	#define	CARBON_BUILD_DEBUG	0
#endif