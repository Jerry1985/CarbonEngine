#ifndef CARBON_VECTOR4
#define CARBON_VECTOR4

template<typename T>
class Vector4
{
public:
	Vector4(){}
	Vector4(T ix , T iy , T iz , T iw):x(ix),y(iy),z(iz),w(iw){}
	Vector4(T d) :x(d), y(d), z(d), w(d){}
	Vector4(const Vector4<T>& v) :x(v.x), y(v.y), z(v.z), w(v.w){}
	~Vector4(){}

#define DEFINE_BASIC_OP_METHOD(OPERATOR) \
	OPERATOR(+)\
	OPERATOR(-)\
	OPERATOR(*)\
	OPERATOR(/ )

#define DEFINE_BASIC_OP0(op) \
	const Vector3<T> operator op(const Vector3<T>& v) \
	{ \
	Vector3 r; \
	r.data[0] = v.data[0] op data[0]; \
	r.data[1] = v.data[1] op data[1]; \
	r.data[2] = v.data[2] op data[2]; \
	r.data[3] = v.data[3] op data[3]; \
	return r; \
	}

#define DEFINE_BASIC_OP1(op) \
	const Vector3<T> operator op(const T& d) \
	{ \
		Vector3 r; \
		data[0] = data[0] op d; \
		data[1] = data[1] op d; \
		data[2] = data[2] op d; \
		data[3] = data[3] op d; \
		return r; \
	}

#define DEFINE_BASIC_OP2(op) \
	const Vector3<T> operator ##op= (const Vector3<T>& v) \
	{ \
		Vector3 r; \
		data[0] ##op= v.data[0]; \
		data[1] ##op= v.data[1]; \
		data[2] ##op= v.data[2]; \
		data[2] ##op= v.data[3]; \
		return r; \
	}

#define DEFINE_BASIC_OP3(op) \
	const Vector3<T> operator ##op= (const T& d) \
	{ \
		Vector3 r; \
		data[0] ##op= d; \
		data[1] ##op= d; \
		data[2] ##op= d; \
		data[3] ##op= d; \
		return r; \
	}

	DEFINE_BASIC_OP_METHOD(DEFINE_BASIC_OP0)
	DEFINE_BASIC_OP_METHOD(DEFINE_BASIC_OP1)
	DEFINE_BASIC_OP_METHOD(DEFINE_BASIC_OP2)
	DEFINE_BASIC_OP_METHOD(DEFINE_BASIC_OP3)


	friend T Dot3(const Vector4& v0, const Vector4& v1)
	{
		return v0.x * v1.x + v0.y * v1.y + v0.z * v1.z;
	}

	friend T Dot4(const Vector4& v0, const Vector4& v1)
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

typedef Vector4<float>		Vector4f;
typedef Vector4<int>		Vector4i;
typedef Vector4<double>		Vector4d;

#endif