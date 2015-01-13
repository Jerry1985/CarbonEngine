#include "GlobalShaderCache.h"
#include "ShaderManager.h"
#include "Platform\PlatformFile.h"
#include "Container\CString.h"
#include "Platform\PlatformFileNames.h"
#include "Container\CBitArray.h"
#include "Shader\ShaderMetaData.h"

// Cook Shader cache
bool	CookGlobalShaderCache()
{
	const TCHAR* shaderSourceFolder = GetGlobalShaderCacheFolderName();
	const TCHAR* filename = GetGlobalShaderCacheFileName();
	WinFileHandle* handle = PlatformFile::OpenFile(filename, false);

	CLinkedList<ShaderMetaData*>& metaDatas = ShaderManager::GetSingleton().GetShaderMetaData();
	CLinkedListIterator<ShaderMetaData*> it(metaDatas);
	while (!it.IsEnd())
	{
		ShaderMetaData* metaData = *it;
		const CString& shaderfile = shaderSourceFolder + metaData->m_ShaderKey.fileName.ToString();
		
		PlatformFileHandle* shaderSrc = PlatformFile::OpenFile(shaderfile);
		uint32	data_size = shaderSrc->Size();
		char* data = new char[data_size + 1];
		data[data_size] = 0;
		bool flag = shaderSrc->Read((uint8*)data, data_size);
		delete shaderSrc;

		CBitArray bytecode;
		RALCompileShader((const uint8*)data, data_size, metaData->m_ShaderKey.shaderType, bytecode);

		delete[] data;

		// write shader cache data
		handle->Write((uint8*)bytecode.GetData(), bytecode.GetSize());
		
		++it;
	}

	SAFE_DELETE(handle);

	return true;
}

// Load Global Shaders from Shader Cache
bool	LoadFromShaderCache()
{

	return false;
}