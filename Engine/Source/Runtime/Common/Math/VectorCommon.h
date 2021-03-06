#pragma once

#include "Platform\Platform.h"

#define DEFINE_ALL_OPS(DEFINE_METHOD) \
	FORCE_INLINE DEFINE_METHOD(+)\
	FORCE_INLINE DEFINE_METHOD(-)\
	FORCE_INLINE DEFINE_METHOD(*)\
	FORCE_INLINE DEFINE_METHOD(/ )\

#define DEFINE_BASIC_METHOD0	DEFINE_ALL_OPS(BASIC_METHOD0)
#define DEFINE_BASIC_METHOD1	DEFINE_ALL_OPS(BASIC_METHOD1)
#define DEFINE_BASIC_METHOD2	DEFINE_ALL_OPS(BASIC_METHOD2)

#define DEFINE_ALL_BASIC_METHODS \
	DEFINE_BASIC_METHOD0 \
	DEFINE_BASIC_METHOD1 \
	DEFINE_BASIC_METHOD2 

#define VECTOR_TYPE(type) \
	typedef type<float>		type##f; \
	typedef type<int>		type##i; \
	typedef type<double>	type##d;