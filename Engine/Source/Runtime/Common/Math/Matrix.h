#pragma once

#include "Vector4.h"
#include "Vector3.h"

#include <math.h>

class Matrix
{
public:
	Matrix();
	Matrix(float d[16]);
	Matrix(const Matrix& m);
	Matrix(float __00, float __01, float __02, float __03,
		float __10, float __11, float __12, float __13,
		float __20, float __21, float __22, float __23,
		float __30, float __31, float __32, float __33);
	~Matrix();

	inline Matrix operator * (const Matrix& m) const;

	inline Point3D operator * (const Point3D& p) const;
	inline Point3D operator () (const Point3D& p) const { return *this * p; }

	inline Vector4f operator * (const Vector4f& v) const;
	inline Vector4f operator () (const Vector4f& v) const { return *this * v; }
	
	inline Matrix	Transpose() const;
	inline float	Determinant() const;
	inline bool		Inverse(Matrix& out) const;
	inline bool		HasScale() const;

private:
	// Row major matrix
	union
	{
		float	m[16];
		struct{
			float _00, _01, _02, _03;
			float _10, _11, _12, _13;
			float _20, _21, _22, _23;
			float _30, _31, _32, _33;
		};
		float	d[4][4];
	};
};

Matrix Matrix::operator * (const Matrix& mat) const
{
	// to be optimized
	float data[16];
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			int offset = i * 4 + j;
			data[offset] = 0.0f;

			for (int k = 0; k < 4; k++)
				data[offset] += m[i * 4 + k] * mat.m[k * 4 + j];
		}
	}

	return Matrix(data);
}

Point3D Matrix::operator * (const Point3D& p) const
{
	float x, y, z;
	x = _00 * p.x + _01 * p.y + _02 * p.z;
	y = _10 * p.x + _11 * p.y + _12 * p.z;
	z = _20 * p.x + _21 * p.y + _22 * p.z;
	return Point3D(x, y, z);
}

Vector4f Matrix::operator * (const Vector4f& v) const
{
	float x, y, z, w;
	x = _00 * v.x + _01 * v.y + _02 * v.z + _03 * v.w;
	y = _10 * v.x + _11 * v.y + _12 * v.z + _13 * v.w;
	z = _20 * v.x + _21 * v.y + _22 * v.z + _23 * v.w;
	w = _30 * v.x + _31 * v.y + _32 * v.z + _33 * v.w;
	return Vector4f(x, y, z, w);
}

inline Matrix Matrix::Transpose() const
{
	return Matrix(	_00, _10, _20, _30,
					_01, _11, _21, _31,
					_02, _12, _22, _32,
					_03, _13, _23, _33);
}

inline float Matrix::Determinant() const
{
	return (m[0] * m[5] - m[1] * m[4]) * (m[10] * m[15] - m[11] * m[14]) -
		(m[0] * m[6] - m[2] * m[4]) * (m[9] * m[15] - m[11] * m[13]) +
		(m[0] * m[7] - m[3] * m[4]) * (m[9] * m[14] - m[10] * m[13]) +
		(m[1] * m[6] - m[2] * m[5]) * (m[8] * m[15] - m[11] * m[12]) -
		(m[1] * m[7] - m[3] * m[5]) * (m[8] * m[14] - m[10] * m[12]) +
		(m[2] * m[7] - m[3] * m[6]) * (m[8] * m[13] - m[9] * m[12]);
}

inline bool	 Matrix::Inverse(Matrix& out) const
{
	float d = Determinant();
	if (fabs(d) < 0.00000001f)
		return false;

	// use Cramers' rule

	d = 1.0f / d;

	out.m[0] = d * (m[5] * (m[10] * m[15] - m[11] * m[14]) + m[6] * (m[11] * m[13] - m[9] * m[15]) + m[7] * (m[9] * m[14] - m[10] * m[13]));
	out.m[1] = d * (m[9] * (m[2] * m[15] - m[3] * m[14]) + m[10] * (m[3] * m[13] - m[1] * m[15]) + m[11] * (m[1] * m[14] - m[2] * m[13]));
	out.m[2] = d * (m[13] * (m[2] * m[7] - m[3] * m[6]) + m[14] * (m[3] * m[5] - m[1] * m[7]) + m[15] * (m[1] * m[6] - m[2] * m[5]));
	out.m[3] = d * (m[1] * (m[7] * m[10] - m[6] * m[11]) + m[2] * (m[5] * m[11] - m[7] * m[9]) + m[3] * (m[6] * m[9] - m[5] * m[10]));
	out.m[4] = d * (m[6] * (m[8] * m[15] - m[11] * m[12]) + m[7] * (m[10] * m[12] - m[8] * m[14]) + m[4] * (m[11] * m[14] - m[10] * m[15]));
	out.m[5] = d * (m[10] * (m[0] * m[15] - m[3] * m[12]) + m[11] * (m[2] * m[12] - m[0] * m[14]) + m[8] * (m[3] * m[14] - m[2] * m[15]));
	out.m[6] = d * (m[14] * (m[0] * m[7] - m[3] * m[4]) + m[15] * (m[2] * m[4] - m[0] * m[6]) + m[12] * (m[3] * m[6] - m[2] * m[7]));
	out.m[7] = d * (m[2] * (m[7] * m[8] - m[4] * m[11]) + m[3] * (m[4] * m[10] - m[6] * m[8]) + m[0] * (m[6] * m[11] - m[7] * m[10]));
	out.m[8] = d * (m[7] * (m[8] * m[13] - m[9] * m[12]) + m[4] * (m[9] * m[15] - m[11] * m[13]) + m[5] * (m[11] * m[12] - m[8] * m[15]));
	out.m[9] = d * (m[11] * (m[0] * m[13] - m[1] * m[12]) + m[8] * (m[1] * m[15] - m[3] * m[13]) + m[9] * (m[3] * m[12] - m[0] * m[15]));
	out.m[10] = d * (m[15] * (m[0] * m[5] - m[1] * m[4]) + m[12] * (m[1] * m[7] - m[3] * m[5]) + m[13] * (m[3] * m[4] - m[0] * m[7]));
	out.m[11] = d * (m[3] * (m[5] * m[8] - m[4] * m[9]) + m[0] * (m[7] * m[9] - m[5] * m[11]) + m[1] * (m[4] * m[11] - m[7] * m[8]));
	out.m[12] = d * (m[4] * (m[10] * m[13] - m[9] * m[14]) + m[5] * (m[8] * m[14] - m[10] * m[12]) + m[6] * (m[9] * m[12] - m[8] * m[13]));
	out.m[13] = d * (m[8] * (m[2] * m[13] - m[1] * m[14]) + m[9] * (m[0] * m[14] - m[2] * m[12]) + m[10] * (m[1] * m[12] - m[0] * m[13]));
	out.m[14] = d * (m[12] * (m[2] * m[5] - m[1] * m[6]) + m[13] * (m[0] * m[6] - m[2] * m[4]) + m[14] * (m[1] * m[4] - m[0] * m[5]));
	out.m[15] = d * (m[0] * (m[5] * m[10] - m[6] * m[9]) + m[1] * (m[6] * m[8] - m[4] * m[10]) + m[2] * (m[4] * m[9] - m[5] * m[8]));

	return true;
}

inline bool	Matrix::HasScale() const
{
	float l0 = Vector3f(m[0], m[4], m[8]).Length();
	float l1 = Vector3f(m[1], m[5], m[9]).Length();
	float l2 = Vector3f(m[2], m[6], m[7]).Length();

#define	IS_ONE(x) ((x)>0.999f && (x)<1.001f )
	return !(IS_ONE(l0) && IS_ONE(l1) && IS_ONE(l2));
#undef IS_ONE
}
