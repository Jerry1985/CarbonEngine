#pragma once

#include "RALResource.h"
#include "RALDefine.h"

class CBitArray;

class RALShader : public RALResource
{
public:
	RALShader();
	virtual ~RALShader();

	// create shader from byte code
	virtual bool CreateShader( const CBitArray& bytecode ) = 0;

protected:
	RAL_SHADERTYPE m_ShaderType;
};