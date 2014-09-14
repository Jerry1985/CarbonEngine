#include "Matrix.h"
#include <memory.h>

Matrix::Matrix()
{
	_00 = 1.0f; _01 = 0.0f; _02 = 0.0f; _03 = 0.0f;
	_10 = 0.0f; _11 = 1.0f; _12 = 0.0f; _13 = 0.0f;
	_20 = 0.0f; _21 = 0.0f; _22 = 1.0f; _23 = 0.0f;
	_30 = 0.0f; _31 = 0.0f; _32 = 0.0f; _33 = 0.0f;
}

Matrix::Matrix(float d[16])
{
	memcpy(m, d, sizeof(float) * 16);
}

Matrix::Matrix(const Matrix& mat)
{
	memcpy(m, mat.m, sizeof(float)* 16);
}

Matrix::Matrix(	float __00, float __01, float __02, float __03,
				float __10, float __11, float __12, float __13,
				float __20, float __21, float __22, float __23,
				float __30, float __31, float __32, float __33)
{
	_00 = __00; _01 = __01; _02 = __02; _03 = __03;
	_10 = __10; _11 = __11; _12 = __12; _13 = __13;
	_20 = __20; _21 = __21; _22 = __22; _23 = __23;
	_30 = __30; _31 = __31; _32 = __32; _33 = __33;
}

Matrix::~Matrix()
{
}