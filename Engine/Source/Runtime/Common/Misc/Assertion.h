#ifndef CARBON_ASSERTION
#define CARBON_ASSERTION

#include <assert.h>

#if CARBON_BUILD_DEBUG

#define	CASSERT(exp)	assert((bool)(exp))

#else

#define	CASSERT(exp)	{}

#endif

#endif
