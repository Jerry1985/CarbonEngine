#include "OGLDefine.h"

GLuint OGLUSAGE_FROM_RALUSAGE(RAL_USAGE ral_usage)
{
	static GLuint usages[RAL_USAGE_COUNT] = {
		GL_DYNAMIC_DRAW,
		GL_DYNAMIC_DRAW,
		GL_STATIC_DRAW
	};

	return usages[ral_usage];
}

GLuint OGLPRIMITIVE_FROM_RALPRIMITIVE(RAL_PRIMITIVE ral_type)
{
	static GLuint type[RAL_PRIMITIVE_COUNT] = {
		GL_POINTS,
		GL_LINES,
		GL_LINE_STRIP,
		GL_TRIANGLES,
		GL_TRIANGLE_STRIP,
	};

	return type[ral_type];
}

GLuint OGLVERTEXELEMENTTYPE_FROM_VERTEXELEMENTTYPE(RAL_VERTEXELEMENTTYPE ral_type)
{
	GLuint type[] = {
		GL_FLOAT,
		GL_FLOAT,
		GL_FLOAT,
		GL_FLOAT,
		GL_UNSIGNED_SHORT
	};

	return type[ral_type];
}

GLuint OGLVERTEXELEMENTTYPECOUNT_FROM_VERTEXELEMENTTYPE(RAL_VERTEXELEMENTTYPE ral_type)
{
	GLuint count[] = {
		1,
		2,
		3,
		4,
		4,
	};
	return count[ral_type];
}