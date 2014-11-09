#pragma once

#include <assert.h>

#if CARBON_BUILD_DEBUG

#define	CASSERT(exp)	assert((bool)(exp))

#else

#define	CASSERT(exp)	{}

#endif
