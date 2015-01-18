#pragma once

#include "Utility\Singleton.h"
#include "Container\CArray.h"

class ShaderMetaData;

class ShaderManager : public Singleton<ShaderManager>
{
public:
	ShaderManager();
	~ShaderManager();

	// Add Shader metadata
	void	AddShaderMetaData(ShaderMetaData* metadata);

	// Get Shader metadata list
	CArray<ShaderMetaData*>& GetShaderMetaData();

private:
	CArray<ShaderMetaData*>	m_ShaderMetaData;

	// clear shader metadata
	void	_clearShaderMetaData();
};