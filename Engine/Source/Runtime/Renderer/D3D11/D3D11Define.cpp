#include "D3D11Define.h"
#include <d3d11.h>

DXGI_FORMAT DXGIFORMAT_FROM_RALFORMAT(RAL_FORMAT ral_format)
{
	static DXGI_FORMAT convert[RAL_FORMAT_COUNT] = {
		DXGI_FORMAT_R32G32B32A32_FLOAT,
		DXGI_FORMAT_R32G32B32A32_UINT,
		DXGI_FORMAT_R32G32B32A32_SINT,
		DXGI_FORMAT_R32G32B32_FLOAT,
		DXGI_FORMAT_R32G32B32_UINT,
		DXGI_FORMAT_R32G32B32_SINT,
		DXGI_FORMAT_R16G16B16A16_FLOAT,
		DXGI_FORMAT_R16G16B16A16_UINT,
		DXGI_FORMAT_R16G16B16A16_SINT,
		DXGI_FORMAT_R32G32_FLOAT,
		DXGI_FORMAT_R32G32_UINT,
		DXGI_FORMAT_R32G32_SINT,
		DXGI_FORMAT_R10G10B10A2_UNORM,
		DXGI_FORMAT_R10G10B10A2_UINT,
		DXGI_FORMAT_R11G11B10_FLOAT,
		DXGI_FORMAT_R8G8B8A8_UNORM,
		DXGI_FORMAT_R8G8B8A8_UNORM_SRGB,
		DXGI_FORMAT_R8G8B8A8_UINT,
		DXGI_FORMAT_R8G8B8A8_SNORM,
		DXGI_FORMAT_R8G8B8A8_SINT,
		DXGI_FORMAT_R16G16_FLOAT,
		DXGI_FORMAT_R16G16_UNORM,
		DXGI_FORMAT_R16G16_UINT,
		DXGI_FORMAT_R16G16_SNORM,
		DXGI_FORMAT_R16G16_SINT,
		DXGI_FORMAT_D32_FLOAT,
		DXGI_FORMAT_R32_FLOAT,
		DXGI_FORMAT_R32_UINT,
		DXGI_FORMAT_R32_SINT,
		DXGI_FORMAT_D24_UNORM_S8_UINT,
		DXGI_FORMAT_R24_UNORM_X8_TYPELESS,
		DXGI_FORMAT_R8G8_UNORM,
		DXGI_FORMAT_R8G8_UINT,
		DXGI_FORMAT_R8G8_SNORM,
		DXGI_FORMAT_R8G8_SINT,
		DXGI_FORMAT_R16_FLOAT,
		DXGI_FORMAT_D16_UNORM,
		DXGI_FORMAT_R16_UNORM,
		DXGI_FORMAT_R16_UINT,
		DXGI_FORMAT_R16_SNORM,
		DXGI_FORMAT_R16_SINT,
		DXGI_FORMAT_R8_UNORM,
		DXGI_FORMAT_R8_UINT,
		DXGI_FORMAT_R8_SNORM,
		DXGI_FORMAT_R8_SINT,
		DXGI_FORMAT_A8_UNORM,
		DXGI_FORMAT_R1_UNORM
	};

	return convert[ral_format];
}

D3D11_USAGE D3D11USAGE_FROM_RALUSAGE(RAL_USAGE ral_usage)
{
	static D3D11_USAGE usages[RAL_USAGE_COUNT] = {
		D3D11_USAGE_IMMUTABLE,
		D3D11_USAGE_DYNAMIC
	};

	return usages[ral_usage];
}

D3D_PRIMITIVE_TOPOLOGY	D3DPRIMITIVETOPOLOGY_FROM_RALPRIMITIVE(RAL_PRIMITIVE ral_primitive)
{
	static D3D_PRIMITIVE_TOPOLOGY primitives[RAL_PRIMITIVE_COUNT] = {
		D3D_PRIMITIVE_TOPOLOGY_POINTLIST,
		D3D_PRIMITIVE_TOPOLOGY_LINELIST,
		D3D_PRIMITIVE_TOPOLOGY_LINESTRIP,
		D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
		D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP
	};

	return primitives[ral_primitive];
}

DXGI_FORMAT DXGIFORMAT_FROM_RAL_VERTEXELEMENTTYPE(RAL_VERTEXELEMENTTYPE ral_vertexelementtype)
{
	static DXGI_FORMAT vertexelementtypes[RAL_VERTEXELEMENTTYPE_COUNT] = {
		DXGI_FORMAT_R32_FLOAT,
		DXGI_FORMAT_R32G32_FLOAT,
		DXGI_FORMAT_R32G32B32_FLOAT,
		DXGI_FORMAT_R32G32B32A32_FLOAT
	};

	return vertexelementtypes[ral_vertexelementtype];
}