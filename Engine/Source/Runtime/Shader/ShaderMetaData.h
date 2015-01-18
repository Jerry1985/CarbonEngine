#pragma once

#include "Platform\PlatformString.h"
#include "Utility\UtilityMacro.h"
#include "Renderer\Common\RALShader.h"
#include "Renderer\Common\RALGlobalMethods.h"
#include "Misc\Assertion.h"
#include "ShaderManager.h"
#include "Container\CBitArray.h"
#include "Core\Name.h"
#include "Core\Archive.h"

class Shader;

struct ShaderKey
{
	Name			shaderName;
	Name			fileName;
	Name			entryName;
	RAL_SHADERTYPE	shaderType;

	ShaderKey(const TCHAR* name, const TCHAR* filename, const TCHAR* entryname, RAL_SHADERTYPE shadertype) : shaderName(name), fileName(filename), entryName(entryname), shaderType(shadertype)
	{
	}
	ShaderKey()
	{
	}

	FORCE_INLINE bool operator == (const ShaderKey& key)
	{
		return	key.fileName == fileName &&
				key.entryName == entryName &&
				key.shaderType == shaderType;
	}
};

class ShaderMetaData
{
public:
	ShaderMetaData(RAL_SHADERTYPE type, const TCHAR* shaderName, const TCHAR* fileName, const TCHAR* entryName) :m_ShaderKey(shaderName,fileName, entryName, type)
	{
		ShaderManager::GetSingleton().AddShaderMetaData(this);
	}
	ShaderMetaData()
	{
	}
	~ShaderMetaData()
	{
		SAFE_DELETE(m_Shader);
	}

	// construct shader
	Shader*	ConstructShader()
	{
		return 0;
	}

	// create shader from byte code (GL byte code is hardware and driver dependent. Shader cache needs to be flushed if either of them is changed.)
	void CreateShader(const CBitArray& bytecode)
	{
		_createShader(bytecode);
	}

	// serialization
	friend Archive& operator & (Archive& ar, ShaderMetaData& md)
	{
		// serialize shader key
		ar & md.m_ShaderKey.shaderName;
		ar & md.m_ShaderKey.fileName;
		ar & md.m_ShaderKey.entryName;

		uint32 shaderType = 0;
		ar & shaderType;
		md.m_ShaderKey.shaderType = (RAL_SHADERTYPE)shaderType;

		return ar;
	}

	RALShader*		m_Shader = 0;		// Compiled Shader of OGL or D3D
	ShaderKey		m_ShaderKey;		// Shader key

private:
	FORCE_INLINE void _createShader(const CBitArray& bytecode)
	{
		CASSERT(!m_Shader);

		switch (m_ShaderKey.shaderType)
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

		m_Shader->CreateShader(bytecode);
	}
};

#define DECLARE_SHADER(Shader)				\
	static ShaderMetaData m_ShaderMetaData; \
	const RALShader* GetRALShader() const { return m_ShaderMetaData.m_Shader; }
	
#define DEFINE_SHADER(Shader, ShaderType, ShaderName, ShaderFile, ShaderEntry)	ShaderMetaData Shader::m_ShaderMetaData(RAL_SHADERTYPE_##ShaderType, ShaderName, ShaderFile, ShaderEntry);