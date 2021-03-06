#pragma once

#define	ENABLE_RELEASE_BUILD_LOG	1

#ifdef CARBON_DEBUG_BUILD
	#define	CARBON_BUILD_DEBUG	1
	#define	CARBON_ENABLE_LOG	1
#endif

#if CARBON_RELEASE_BUILD
	#define	CARBON_BUILD_DEBUG	0
	#define	CARBON_ENABLE_LOG	ENABLE_RELEASE_BUILD_LOG
#endif

#define	CARBON_DEVELOPMENT_BUILD	1