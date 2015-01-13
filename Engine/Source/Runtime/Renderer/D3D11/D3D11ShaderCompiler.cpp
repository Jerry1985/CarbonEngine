#include "D3D11Interface.h"
#include "D3Dcompiler.h"
#include "Container\CBitArray.h"
#include "Common\Log\Log.h"

bool D3D11Interface::CompileShader(const uint8* source, uint32 len, uint8 shaderType, CBitArray& bytecode)
{
	static const char* shader_types[] =
	{
		"vs_5_0",
		"ps_5_0",
		"hs_5_0",
		"ds_5_0",
		"gs_5_0",
		"cs_5_0"
	};

	CASSERT(shaderType < RAL_SHADERTYPE_COUNT);

	ID3DBlob* shaderBlob = 0;
	ID3DBlob* errorBlob = 0;

	UINT flags = D3DCOMPILE_ENABLE_STRICTNESS;
	HRESULT hr = D3DCompile(source, len, 0, 0, 0, "main", shader_types[shaderType], flags, 0, &shaderBlob, &errorBlob);
	if (FAILED(hr))
	{
		if (errorBlob)
		{
			CARBON_LOG(LOG_WARNING, LOG_RENDERER, (char*)errorBlob->GetBufferPointer());

			errorBlob->Release();
		}

		if (shaderBlob)
			shaderBlob->Release();

		return false;
	}

	uint8* data = (uint8*)shaderBlob->GetBufferPointer();
	uint32 size = (uint32)shaderBlob->GetBufferSize();

	bytecode.Allocate(size);
	bytecode.Copy(data, size);

	SAFE_RELEASE(shaderBlob);
	SAFE_RELEASE(errorBlob);

	return true;
}