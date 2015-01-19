#include "GlobalShaders.h"
#include "GlobalShaderCache.h"
#include "Renderer\Common\RALDefine.h"
#include "Container\CBitArray.h"
#include "Container\CArray.h"
#include "Shader\ShaderManager.h"
#include "Shader\ShaderMetaData.h"

extern RAL_RENDERER	gRendererType;

// Global methods about shaders
bool	LoadGlobalShaders()
{
	// Load shader cache
	LoadFromShaderCache();

	// Check Global Shader Cache
	CheckGlobalShaderCache();

	// Initialize global shaders
	InitGlobalShaders();

	return true;
}

// Initialize Global shaders
void	InitGlobalShaders()
{
	CArray<ShaderMetaData*>& metaDatas = ShaderManager::GetSingleton().GetShaderMetaData();
	CArrayIterator<ShaderMetaData*> it(metaDatas);
	while (!it.IsEnd())
	{
		// Create Shaders
		(*it)->CreateShader();
		
		++it;
	}
}