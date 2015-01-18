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
ShaderMetaData*	GetShaderMetaData(const ShaderMetaData* metaData)
{
	CArray<ShaderMetaData*>& metaDatas = ShaderManager::GetSingleton().GetShaderMetaData();
	CArrayIterator<ShaderMetaData*> it(metaDatas);
	while (!it.IsEnd())
	{
		if ((*it)->m_ShaderKey == metaData->m_ShaderKey)
			return (*it);
		++it;
	}
	return 0;
}

// Cook Shader cache
bool	CookGlobalShaderCache()
{
	const CString shaderSourceFolder(GetGlobalShaderCacheFolderName());
	const CString filename(GetGlobalShaderCacheFileName());
	FileWriteArchive ar(shaderSourceFolder+filename);

	CArray<ShaderMetaData*>& metaDatas = ShaderManager::GetSingleton().GetShaderMetaData();
	CArrayIterator<ShaderMetaData*> it(metaDatas);

	// total number of global shaders
	int totalNum = metaDatas.GetSize();
	ar & totalNum;

	while (!it.IsEnd())
	{
		ShaderMetaData* metaData = *it;
		/*
		PlatformFileHandle* shaderSrc = PlatformFile::OpenFile(shaderfile);
		uint32	data_size = shaderSrc->Size();
		char* data = new char[data_size + 1];
		data[data_size] = 0;
		bool flag = shaderSrc->Read((uint8*)data, data_size);
		delete shaderSrc;

		CBitArray bytecode;
		RALCompileShader((const uint8*)data, data_size, metaData->m_ShaderKey.shaderType, bytecode);

		delete[] data;
		*/
		ar & *metaData;
		
		++it;
	}

	return true;
}

// Load Global Shaders from Shader Cache
bool	LoadFromShaderCache()
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
		ar & md;

		bool found = false;
		while (!it.IsEnd())
		{
			ShaderMetaData* metaData = *it;

			if (md.m_ShaderKey == metaData->m_ShaderKey)
			{
				found = true;
				break;
			}

			++it;
		}

		if (!found)
		{
			int a = 0;
		}
	}

	return false;
}