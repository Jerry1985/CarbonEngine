#pragma once

#include <assert.h>
#include "Misc\Build.h"

#if CARBON_BUILD_DEBUG

#define	CASSERT(exp)	assert(!!(exp))

#else

#define	CASSERT(exp)	{}

#endif
