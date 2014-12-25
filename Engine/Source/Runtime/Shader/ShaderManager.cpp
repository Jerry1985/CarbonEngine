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
CLinkedList<ShaderMetaData*>& ShaderManager::GetShaderMetaData()
{
	return m_ShaderMetaData;
}

// Add Shader metadata
void ShaderManager::AddShaderMetaData(ShaderMetaData* metadata)
{
	CASSERT(metadata);
	m_ShaderMetaData.Link(new CLinkedListNode<ShaderMetaData*>(metadata));
}

void ShaderManager::_clearShaderMetaData()
{
	CLinkedListIterator<ShaderMetaData*> it(m_ShaderMetaData);
	while (!it.IsEnd())
		SAFE_DELETE(*it++);

	// clear the list
	m_ShaderMetaData.Clear();
}