#pragma once

#include "Utility\Singleton.h"
#include "Container\CLinkedList.h"

class ShaderMetaData;

class ShaderManager : public Singleton<ShaderManager>
{
public:
	ShaderManager();
	~ShaderManager();

	// Add Shader metadata
	void	AddShaderMetaData(ShaderMetaData* metadata);

	// Get Shader metadata list
	CLinkedList<ShaderMetaData*>& GetShaderMetaData();

private:
	CLinkedList<ShaderMetaData*>	m_ShaderMetaData;

	// clear shader metadata
	void	_clearShaderMetaData();
};