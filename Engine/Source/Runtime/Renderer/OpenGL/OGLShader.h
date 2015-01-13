#pragma once

#include "Renderer\Common\RALShader.h"
#include "../ThirdParty/Regal/Include/Regal.h"
#include "Common\Platform\Platform.h"

class OGLShader : public RALShader
{
public:
	OGLShader();
	virtual ~OGLShader();

	// create shader from byte code
	bool CreateShader(const CBitArray& bytecode);

protected:
	GLuint	m_shaderId;

	// get ogl shader type
	uint32	_getShaderType() const;

	friend class OGLPipelineBoundState;
};

class OGLVertexShader : public OGLShader
{
public:
	OGLVertexShader();
	virtual ~OGLVertexShader();
};

class OGLPixelShader : public OGLShader
{
public:
	OGLPixelShader();
	virtual ~OGLPixelShader();
};
