#ifndef CARBON_VECTOR2
#define CARBON_VECTOR2

template<typename T>
class Vector2
{
public:
	Vector2(){}
	Vector2(T ix, T iy) :x(ix), y(iy){}
	Vector2(T d) :x(d), y(d){}
	Vector2(const Vector2<T>& v) :x(v.x), y(v.y){}
	~Vector2(){}

#define DEFINE_BASIC_OP_METHOD(OPERATOR) \
	OPERATOR(+)\
	OPERATOR(-)\
	OPERATOR(*)\
	OPERATOR(/ )

#define DEFINE_BASIC_OP0(op) \
	const Vector2<T> operator op(const Vector2<T>& v) \
	{ \
		Vector2 r; \
		r.data[0] = v.data[0] op data[0]; \
		r.data[1] = v.data[1] op data[1]; \
		return r; \
	}

#define DEFINE_BASIC_OP1(op) \
	const Vector2<T> operator op(const T& d) \
	{ \
		Vector2 r; \
		r.data[0] = v.data[0] op d; \
		r.data[1] = v.data[1] op d; \
		return r; \
	}

#define DEFINE_BASIC_OP2(op) \
	const Vector2<T> operator ##op= (const Vector2<T>& v) \
	{ \
		Vector2 r; \
		data[0] ##op= v.data[0]; \
		data[1] ##op= v.data[1]; \
		return r; \
	}

#define DEFINE_BASIC_OP3(op) \
	const Vector2<T> operator ##op= (const T& d) \
	{ \
		Vector2 r; \
		data[0] ##op= d; \
		data[1] ##op= d; \
		return r; \
	}

	DEFINE_BASIC_OP_METHOD(DEFINE_BASIC_OP0)
	DEFINE_BASIC_OP_METHOD(DEFINE_BASIC_OP1)
	DEFINE_BASIC_OP_METHOD(DEFINE_BASIC_OP2)
	DEFINE_BASIC_OP_METHOD(DEFINE_BASIC_OP3)

	friend T Dot(const Vector2& v0, const Vector2& v1)
	{
		return v0.x * v1.x + v0.y * v1.y;
	}

	T SquaredLength() const
	{
		return x * x + y * y;
	}

	T Length() const
	{
		return sqrt(SquaredLength());
	}

	Vector2<T>& Normalize()
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

	Vector2<T>  operator- () const
	{
		return Vector2<T>(-x, -y);
	}

	bool	operator == (const Vector2<T>& v) const
	{
		return x == v.x && y == v.y && z == v.z;
	}

	bool	operator != (const Vector2<T>& v) const
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

typedef Vector2<float>		Vector2f;
typedef Vector2<int>		Vector2i;
typedef Vector2<double>		Vector2d;

#endif