#include "ShaderManager.h"
#include "ShaderMetaData.h"

DEFINE_SINGLETON(ShaderManager)

ShaderManager::ShaderManager()
{
}

ShaderManager::~ShaderManager()
{
	_clearShaderMetaData();
}

// Get Shader metadata list
CArray<ShaderMetaData*>& ShaderManager::GetShaderMetaData()
{
	return m_ShaderMetaData;
}

// Add Shader metadata
void ShaderManager::AddShaderMetaData(ShaderMetaData* metadata)
{
	CASSERT(metadata);
	m_ShaderMetaData.Add(metadata);
}

void ShaderManager::_clearShaderMetaData()
{
	CArrayIterator<ShaderMetaData*> it(m_ShaderMetaData);
	while (!it.IsEnd())
		SAFE_DELETE(*it++);
}