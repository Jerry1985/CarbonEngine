#ifndef CARBON_VECTOR3
#define CARBON_VECTOR3

template<typename T>
class Vector3
{
public:
	Vector3(){}
	Vector3(T ix, T iy, T iz) :x(ix), y(iy), z(iz){}
	Vector3(T d) :x(d), y(d), z(d){}
	Vector3(const Vector3<T>& v) :x(v.x), y(v.y), z(v.z){}
	~Vector3(){}

#define DEFINE_BASIC_OP_METHOD(OPERATOR) \
	OPERATOR(+)\
	OPERATOR(-)\
	OPERATOR(*)\
	OPERATOR(/)

#define DEFINE_BASIC_OP0(op) \
	const Vector3<T> operator op(const Vector3<T>& v) \
	{ \
		Vector3 r; \
		r.data[0] = v.data[0] op data[0]; \
		r.data[1] = v.data[1] op data[1]; \
		r.data[2] = v.data[2] op data[2]; \
		return r; \
	}

#define DEFINE_BASIC_OP1(op) \
	const Vector3<T> operator op(const T& d) \
	{ \
		Vector3 r; \
		data[0] = data[0] op d; \
		data[1] = data[1] op d; \
		data[2] = data[2] op d; \
		return r; \
	}

#define DEFINE_BASIC_OP2(op) \
	const Vector3<T> operator ##op= (const Vector3<T>& v) \
	{ \
		Vector3 r; \
		data[0] ##op= v.data[0]; \
		data[1] ##op= v.data[1]; \
		data[2] ##op= v.data[2]; \
		return r; \
	}

#define DEFINE_BASIC_OP3(op) \
	const Vector3<T> operator ##op= (const T& d) \
	{ \
		Vector3 r; \
		data[0] ##op= d; \
		data[1] ##op= d; \
		data[2] ##op= d; \
		return r; \
	}

	DEFINE_BASIC_OP_METHOD(DEFINE_BASIC_OP0)
	DEFINE_BASIC_OP_METHOD(DEFINE_BASIC_OP1)
	DEFINE_BASIC_OP_METHOD(DEFINE_BASIC_OP2)
	DEFINE_BASIC_OP_METHOD(DEFINE_BASIC_OP3)

	friend T Dot(const Vector3& v0, const Vector3& v1)
	{
		return v0.x * v1.x + v0.y * v1.y + v0.z * v1.z;
	}

	T SquaredLength() const
	{
		return x * x + y * y + z * z;
	}

	T Length() const
	{
		return sqrt(SquaredLength());
	}

	Vector3<T>& Normalize()
	{
		return (*this) / Length();
	}

	float	operator[] (unsigned id) const
	{
		return data[id];
	}

	float&	operator[] (unsigned id)
	{
		return data[id];
	}

	Vector3<T>  operator- () const
	{
		return Vector3<T>(-x, -y, -z);
	}

	bool	operator == (const Vector3<T>& v) const
	{
		return x == v.x && y == v.y && z == v.z;
	}

	bool	operator != (const Vector3<T>& v) const
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

typedef Vector3<float>		Vector3f;
typedef Vector3<int>		Vector3i;
typedef Vector3<double>		Vector3d;

#endif