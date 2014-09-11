#ifndef CARBON_VECTOR4
#define CARBON_VECTOR4

#include "VectorCommon.h"

template<typename T>
class Vector4
{
public:
	Vector4(){}
	Vector4(T ix , T iy , T iz , T iw):x(ix),y(iy),z(iz),w(iw){}
	Vector4(T d) :x(d), y(d), z(d), w(d){}
	Vector4(const Vector4<T>& v) :x(v.x), y(v.y), z(v.z), w(v.w){}
	~Vector4(){}

#define BASIC_METHOD0(op) \
	Vector4<T>	operator op (const Vector4<T>& v) const\
	{\
		return Vector4<T>(x op v.x, y op v.y, z op v.z, w op v.w); \
	}

#define BASIC_METHOD1(op) \
	const Vector4<T>& operator ##op= (const Vector4<T>& v) \
	{\
		x = x op v.x;\
		y = y op v.y;\
		z = z op v.z;\
		w = w op v.w;\
		return *this;\
	}

#define BASIC_METHOD2(op)	\
	Vector4<T>	operator op (T s) const \
	{\
		return Vector4<T>(x op s, y op s, z op s, w op s); \
	}

	DEFINE_ALL_BASIC_METHODS

#undef BASIC_METHOD0
#undef BASIC_METHOD1
#undef BASIC_METHOD2

	friend Vector4<T> operator * (T s , const Vector4<T>& v )
	{
		return v * s;
	}

	friend T Dot3(const Vector4<T>& v0, const Vector4<T>& v1)
	{
		return v0.x * v1.x + v0.y * v1.y + v0.z * v1.z;
	}

	friend T Dot4(const Vector4<T>& v0, const Vector4<T>& v1)
	{
		return v0.x * v1.x + v0.y * v1.y + v0.z * v1.z + v0.w * v1.w;
	}

	T SquaredLength4() const
	{
		return x * x + y * y + z * z + w * w;
	}

	T SquaredLength3() const
	{
		return x * x + y * y + z * z;
	}

	T Length3() const
	{
		return sqrt(SquaredLength4());
	}

	T Length4() const
	{
		return sqrt(SquaredLength3());
	}

	Vector4<T>& Normalize()
	{
		return (*this) / Length4();
	}

	float	operator[] (unsigned id) const
	{
		return data[id];
	}

	float&	operator[] (unsigned id)
	{
		return data[id];
	}

	Vector4<T>  operator- () const
	{
		return Vector4<T>(-x, -y, -z, -w);
	}

	bool	operator == (const Vector4<T>& v) const
	{
		return x == v.x && y == v.y && z == v.z && w == v.w;
	}

	bool	operator != (const Vector4<T>& v) const
	{
		return !(*this == v );
	}
	
public:
	union
	{
		T data[4];
		struct{ T x; T y; T z; T w; };
	};
};

VECTOR_TYPE(Vector4)

#endif