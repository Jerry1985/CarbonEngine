#pragma once

#include "RALResource.h"
#include "RALDefine.h"

class RALShader : public RALResource
{
public:
	RALShader();
	virtual ~RALShader();

	// create shader from byte code
	// if "bytecode" is false, HLSL or GLSL will be parsed
	virtual bool CreateShader(void* data, unsigned length, bool bytecode = true) = 0;

protected:
	RAL_SHADERTYPE m_ShaderType;
};