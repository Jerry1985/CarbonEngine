#pragma once

#include "Platform\PlatformString.h"
#include "Utility\UtilityMacro.h"
#include "Renderer\Common\RALShader.h"
#include "Renderer\Common\RALGlobalMethods.h"
#include "Misc\Assertion.h"
#include "ShaderManater.h"

class Shader;

class ShaderMetaData
{
public:
	ShaderMetaData(RAL_SHADERTYPE type) :m_ShaderType(type)
	{
		ShaderManager::GetSingleton().AddShaderMetaData(this);
	}
	~ShaderMetaData()
	{
		SAFE_DELETE(m_Shader);
	}

	// setup basic data
	void	SetFileName(const TCHAR* filename)
	{
		m_FileName = filename;
	}
	// set shader name
	void	SetShaderName(const TCHAR* shadername)
	{
		m_ShaderName = shadername;
	}
	// set shader entry name
	void	SetShaderEntry(const TCHAR* shaderentry)
	{
		m_ShaderEntry = shaderentry;
	}

	// construct shader
	Shader*	ConstructShader()
	{
		return 0;
	}

	// create shader from high level language
	void CreateShaderFromHL(const uint8* source, uint32 len)
	{
		_createShader(source, len, false);
	}

	// create shader from byte code (GL byte code is hardware and driver dependent. Shader cache needs to be flushed if either of them is changed.)
	void CreateShaderFromBC(const uint8* bytecode, uint32 len)
	{
		_createShader(bytecode, len, true);
	}

	RALShader*		m_Shader = 0;

	const TCHAR*	m_FileName = 0;
	const TCHAR*	m_ShaderName = 0;
	const TCHAR*	m_ShaderEntry = 0;

	RAL_SHADERTYPE	m_ShaderType = RAL_SHADERTYPE_NONE;

private:
	FORCE_INLINE void _createShader(const uint8* code, uint32 len, bool bytecode)
	{
		CASSERT(!m_Shader);

		switch (m_ShaderType)
		{
		case RAL_SHADERTYPE_VERTEXSHADER:
			m_Shader = RALCreateVertexShader();
			break;
		case RAL_SHADERTYPE_PIXELSHADER:
			m_Shader = RALCreatePixelShader();
			break;
		default:
			CASSERT(false);
			break;
		}

		m_Shader->CreateShader((void*)code, len, bytecode);
	}
};

#define DECLARE_SHADER(Shader)				static ShaderMetaData m_ShaderMetaData;
#define DEFINE_SHADER(Shader, ShaderType)	ShaderMetaData Shader::m_ShaderMetaData(RAL_SHADERTYPE_##ShaderType);