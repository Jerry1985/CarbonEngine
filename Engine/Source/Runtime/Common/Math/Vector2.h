#ifndef CARBON_VECTOR2
#define CARBON_VECTOR2

#include "VectorCommon.h"

template<typename T>
class Vector2
{
public:
	Vector2(){}
	Vector2(T ix, T iy) :x(ix), y(iy){}
	Vector2(T d) :x(d), y(d){}
	Vector2(const Vector2<T>& v) :x(v.x), y(v.y){}
	~Vector2(){}

#define BASIC_METHOD0(op) \
	Vector2<T>	operator op (const Vector2<T>& v) const\
	{\
		return Vector2<T>(x op v.x, y op v.y); \
	}

#define BASIC_METHOD1(op) \
	const Vector2<T>& operator ##op= (const Vector2<T>& v) \
	{\
		x = x op v.x; \
		y = y op v.y; \
		return *this; \
	}

#define BASIC_METHOD2(op)	\
	Vector2<T>	operator op (T s) const \
	{\
		return Vector2<T>(x op s, y op s); \
	}

	DEFINE_ALL_BASIC_METHODS

#undef BASIC_METHOD0
#undef BASIC_METHOD1
#undef BASIC_METHOD2

	FORCE_INLINE friend T Dot(const Vector2& v0, const Vector2& v1)
	{
		return v0.x * v1.x + v0.y * v1.y;
	}

	FORCE_INLINE T SquaredLength() const
	{
		return x * x + y * y;
	}

	FORCE_INLINE T Length() const
	{
		return sqrt(SquaredLength());
	}

	FORCE_INLINE Vector2<T>& Normalize()
	{
		return (*this) / Length();
	}

	FORCE_INLINE float	operator[] (unsigned id) const
	{
		return data[id];
	}

	FORCE_INLINE float&	operator[] (unsigned id)
	{
		return data[id];
	}

	FORCE_INLINE Vector2<T>  operator- () const
	{
		return Vector2<T>(-x, -y);
	}

	FORCE_INLINE bool	operator == (const Vector2<T>& v) const
	{
		return x == v.x && y == v.y && z == v.z;
	}

	FORCE_INLINE bool	operator != (const Vector2<T>& v) const
	{
		return !(*this == v);
	}

public:
	union
	{
		T data[2];
		struct{ T x; T y; };
	};
};

VECTOR_TYPE(Vector2)

// rename vector2d as point
typedef Vector2i Point2D;

#endif