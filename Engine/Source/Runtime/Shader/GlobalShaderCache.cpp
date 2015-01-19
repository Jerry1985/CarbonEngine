#include "GlobalShaderCache.h"
#include "ShaderManager.h"
#include "Platform\PlatformFile.h"
#include "Container\CString.h"
#include "Platform\PlatformFileNames.h"
#include "Container\CBitArray.h"
#include "Shader\ShaderMetaData.h"
#include "Common\Utility\PtrProxy.h"
#include "Core\FileArchive.h"
#include "Common\Log\Log.h"

// Get Shader meta data
ShaderMetaData*	GetShaderMetaData(const ShaderKey& key)
{
	CArray<ShaderMetaData*>& metaDatas = ShaderManager::GetSingleton().GetShaderMetaData();
	CArrayIterator<ShaderMetaData*> it(metaDatas);
	while (!it.IsEnd())
	{
		if ((*it)->m_ShaderKey == key)
			return (*it);
		++it;
	}
	return 0;
}

// Cook Shader cache
bool	SaveGlobalShaderCache()
{
	const CString shaderSourceFolder(GetGlobalShaderCacheFolderName());
	const CString filename(GetGlobalShaderCacheFileName());
	FileWriteArchive ar(shaderSourceFolder+filename);

	CArray<ShaderMetaData*>& metaDatas = ShaderManager::GetSingleton().GetShaderMetaData();
	CArrayIterator<ShaderMetaData*> it(metaDatas);

	// total number of global shaders
	int totalNum = metaDatas.GetCount();
	ar & totalNum;

	while (!it.IsEnd())
	{
		ShaderMetaData* metaData = *it;
		ar & metaData->m_ShaderKey;
		ar & metaData->m_CompiledShader;
		
		++it;
	}

	return true;
}

void	CheckGlobalShaderCache()
{
	bool bSaveGlobalShaderCache = false;

	const CString shaderSourceFolder(GetGlobalShaderCacheFolderName());

	CArray<ShaderMetaData*>& metaDatas = ShaderManager::GetSingleton().GetShaderMetaData();
	CArrayIterator<ShaderMetaData*> it(metaDatas);

	while (!it.IsEnd())
	{
		ShaderMetaData* metaData = *it;

		if (metaData && metaData->m_CompiledShader.IsEmpty())
		{
			CARBON_LOG(LOG_WARNING, LOG_RENDERER, S("Missing global shader ") + metaData->m_ShaderKey.shaderName.ToString() + S(" in global shader cache file.") );

			CString shaderfile = shaderSourceFolder + metaData->m_ShaderKey.fileName.ToString();

			// Load the file
			PtrProxy<PlatformFileHandle> shaderSrc(PlatformFile::OpenFile(shaderfile));
			uint32	data_size = shaderSrc->Size();
			char* data = new char[data_size + 1];
			data[data_size] = 0;
			bool flag = shaderSrc->Read((uint8*)data, data_size);

			// Compile shader
			RALCompileShader((const uint8*)data, data_size, metaData->m_ShaderKey.shaderType, metaData->m_CompiledShader);

			// Delete Data
			delete[] data;

			// save global shade cache
			bSaveGlobalShaderCache = true;
		}

		++it;
	}

	if (bSaveGlobalShaderCache)
	{
		CARBON_LOG(LOG_WARNING, LOG_RENDERER, S("Save global shader cache file."));

		SaveGlobalShaderCache();
	}
}

// Load Global Shaders from Shader Cache
void	LoadFromShaderCache()
{
	const CString shaderSourceFolder(GetGlobalShaderCacheFolderName());
	const CString filename(GetGlobalShaderCacheFileName());
	FileReadArchive ar(shaderSourceFolder + filename);

	CArray<ShaderMetaData*>& metaDatas = ShaderManager::GetSingleton().GetShaderMetaData();
	CArrayIterator<ShaderMetaData*> it(metaDatas);

	int totalNum = 0;
	ar & totalNum;

	for (int i = 0; i < totalNum; ++i)
	{
		ShaderMetaData md;
		ar & md.m_ShaderKey;

		ShaderMetaData* pmd = GetShaderMetaData(md.m_ShaderKey);

		if (!pmd)
		{
			CARBON_LOG(LOG_WARNING, LOG_RENDERER, S("Shader type ") + md.m_ShaderKey.shaderName.ToString() + S(" is not a valid one."));
			continue;
		}else
		{
			// serialize compiled shader
			ar & pmd->m_CompiledShader;
		}
	}
}