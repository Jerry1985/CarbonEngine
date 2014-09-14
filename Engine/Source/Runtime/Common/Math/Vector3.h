#ifndef CARBON_VECTOR3
#define CARBON_VECTOR3

#include "VectorCommon.h"

template<typename T>
class Vector3
{
public:
	Vector3(){}
	Vector3(T ix, T iy, T iz) :x(ix), y(iy), z(iz){}
	Vector3(T d) :x(d), y(d), z(d){}
	Vector3(const Vector3<T>& v) :x(v.x), y(v.y), z(v.z){}
	~Vector3(){}

#define BASIC_METHOD0(op) \
	Vector3<T>	operator op (const Vector3<T>& v) const\
	{\
		return Vector3<T>(x op v.x, y op v.y, z op v.z); \
	}

#define BASIC_METHOD1(op) \
	const Vector3<T>& operator ##op= (const Vector3<T>& v) \
	{\
		x = x op v.x; \
		y = y op v.y; \
		z = z op v.z; \
		return *this; \
	}

#define BASIC_METHOD2(op)	\
	Vector3<T>	operator op (T s) const \
	{\
		return Vector3<T>(x op s, y op s, z op s); \
	}

	DEFINE_ALL_BASIC_METHODS

#undef BASIC_METHOD0
#undef BASIC_METHOD1
#undef BASIC_METHOD2

	FORCE_INLINE friend Vector3<T> operator * (T s, const Vector3<T>& v)
	{
		return v * s;
	}

	FORCE_INLINE friend T Dot(const Vector3& v0, const Vector3& v1)
	{
		return v0.x * v1.x + v0.y * v1.y + v0.z * v1.z;
	}

	FORCE_INLINE T SquaredLength() const
	{
		return x * x + y * y + z * z;
	}

	FORCE_INLINE T Length() const
	{
		return sqrt(SquaredLength());
	}

	FORCE_INLINE Vector3<T>& Normalize()
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

	FORCE_INLINE Vector3<T>  operator- () const
	{
		return Vector3<T>(-x, -y, -z);
	}

	FORCE_INLINE bool	operator == (const Vector3<T>& v) const
	{
		return x == v.x && y == v.y && z == v.z;
	}

	FORCE_INLINE bool	operator != (const Vector3<T>& v) const
	{
		return !(*this == v);
	}

public:
	union
	{
		T data[3];
		struct{ T x; T y; T z; };
	};
};

VECTOR_TYPE(Vector3)

// rename vector3d as point
typedef Vector3f Point3D;

#endif