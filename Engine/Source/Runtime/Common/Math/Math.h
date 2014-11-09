#pragma once

#include "Platform\Platform.h"

class Math
{
public:
	Math(){}
	~Math(){}

	template< class T >
	static T	Min(T x, T y);

	template< class T >
	static T	Max(T x, T y);

	template< class T >
	static T	Clamp(T t, T _min, T _max);
};

template< class T > FORCE_INLINE
T Math::Min(T x, T y)
{
	return (x < y) ? x : y;
}

template< class T > FORCE_INLINE
T Math::Max(T x, T y)
{
	return (x > y) ? x : y;
}

template< class T > FORCE_INLINE
T Math::Clamp(T t, T _min, T _max)
{
	return Max(_max, Min(_min, t));
}