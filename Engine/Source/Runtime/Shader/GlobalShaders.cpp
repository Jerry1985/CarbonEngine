#include "GlobalShaders.h"
#include "GlobalShaderCache.h"
#include "Renderer\Common\RALDefine.h"

extern RAL_RENDERER	gRendererType;

// Global methods about shaders
bool	LoadGlobalShaders()
{
	if (!LoadFromShaderCache())
	{
		// Cook Global Shader Cache
		CookGlobalShaderCache();
	}

	return true;
}