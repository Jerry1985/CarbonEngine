#include "WinNames.h"
#include "Renderer\Common\RALDefine.h"

extern RAL_RENDERER gRendererType;

// Get file name of global shader cache
const TCHAR* GetGlobalShaderCacheFileName()
{
	if (gRendererType == RAL_RENDERER_D3D11)
		return S("GlobalD3D11ShaderCache.cache");

	return S("GlobalOGLShaderCache.cache");
}

// Get folder name of global shader cache
const TCHAR* GetGlobalShaderCacheFolderName()
{
	if (gRendererType == RAL_RENDERER_D3D11)
		return S("../Shader/D3D11/");

	return S("../Shader/OpenGL/");
}