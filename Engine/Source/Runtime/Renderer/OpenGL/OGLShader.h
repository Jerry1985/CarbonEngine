#pragma once

#include "Renderer\Common\RALShader.h"
#include "../ThirdParty/Regal/Include/Regal.h"

class OGLShader : public RALShader
{
public:
	OGLShader();
	virtual ~OGLShader();

protected:
	GLuint	m_shaderId;

	friend class OGLShaderBoundState;
};

class OGLVertexShader : public OGLShader
{
public:
	OGLVertexShader();
	virtual ~OGLVertexShader();

	// create shader from byte code
	bool CreateShader(void* data, unsigned length, bool bytecode = true);
};

class OGLPixelShader : public OGLShader
{
public:
	OGLPixelShader();
	virtual ~OGLPixelShader();

	// create shader from byte code
	bool CreateShader(void* data, unsigned length, bool bytecode = true);
};
