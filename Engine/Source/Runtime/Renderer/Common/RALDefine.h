#ifndef CARBON_RALDEFINE
#define CARBON_RALDEFINE

#define	MAX_RT_COUNT		8		// maximum number of render target set
#define MAX_VB_SLOT_COUNT	8		// maximum number of vertex buffer bound
#define MAX_VP_COUNT		8		// maximum number of viewport
#define	MAX_VERTEX_ELEMENT_COUNT	8	// maximum number of elements in vertex

enum RAL_RENDERER
{
	RAL_RENDERER_D3D11 = 0,
	RAL_RENDERER_OPENGL = 1,

	RAL_RENDERER_COUNT
};

enum RAL_FORMAT
{
	RAL_FORMAT_R32G32B32A32_FLOAT,
	RAL_FORMAT_R32G32B32A32_UINT,
	RAL_FORMAT_R32G32B32A32_SINT,
	RAL_FORMAT_R32G32B32_FLOAT,
	RAL_FORMAT_R32G32B32_UINT,
	RAL_FORMAT_R32G32B32_SINT,
	RAL_FORMAT_R16G16B16_FLOAT,
	RAL_FORMAT_R16G16B16_UINT,
	RAL_FORMAT_R16G16B16_SINT,
	RAL_FORMAT_R32G32_FLOAT,
	RAL_FORMAT_R32G32_UINT,
	RAL_FORMAT_R32G32_SINT,
	RAL_FORMAT_R10G10B10A2_UNORM,
	RAL_FORMAT_R10G10B10A2_UINT,
	RAL_FORMAT_R11G11B10_FLOAT,
	RAL_FORMAT_R8G8B8A8_UNORM,
	RAL_FORMAT_R8G8B8A8_UNORM_SRGB,
	RAL_FORMAT_R8G8B8A8_UINT,
	RAL_FORMAT_R8G8B8A8_SNORM,
	RAL_FORMAT_R8G8B8A8_SINT,
	RAL_FORMAT_R16G16_FLOAT,
	RAL_FORMAT_R16G16_UNORM,
	RAL_FORMAT_R16G16_UINT,
	RAL_FORMAT_R16G16_SNORM,
	RAL_FORMAT_R16G16_SINT,
	RAL_FORMAT_D32_FLOAT,
	RAL_FORMAT_R32_FLOAT,
	RAL_FORMAT_R32_UINT,
	RAL_FORMAT_R32_SINT,
	RAL_FORMAT_D24_UNORM_S8_UINT,
	RAL_FORMAT_R24_UNORM_X8_TYPELESS,
	RAL_FORMAT_R8G8_UNORM,
	RAL_FORMAT_R8G8_UINT,
	RAL_FORMAT_R8G8_SNORM,
	RAL_FORMAT_R8G8_SINT,
	RAL_FORMAT_R16_FLOAT,
	RAL_FORMAT_D16_UNORM,
	RAL_FORMAT_R16_UNORM,
	RAL_FORMAT_R16_UINT,
	RAL_FORMAT_R16_SNORM,
	RAL_FORMAT_R16_SINT,
	RAL_FORMAT_R8_UNORM,
	RAL_FORMAT_R8_UINT,
	RAL_FORMAT_R8_SNORM,
	RAL_FORMAT_R8_SINT,
	RAL_FORMAT_A8_UNORM,
	RAL_FORMAT_R1_UNORM,

	RAL_FORMAT_COUNT
};

enum RAL_USAGE
{
	RAL_USAGE_DEFAULT = 0,
	RAL_USAGE_DYNAMIC,
	RAL_USAGE_IMMUTABLE,

	RAL_USAGE_COUNT
};

enum RAL_PRIMITIVE
{
	RAL_PRIMITIVE_POINT = 0,
	RAL_PRIMITIVE_LINELIST,
	RAL_PRIMITIVE_LINESTRIP,
	RAL_PRIMITIVE_TRIANGLELIST,
	RAL_PRIMITIVE_TRIANGLESTRIP,

	RAL_PRIMITIVE_COUNT
};

enum RAL_VERTEXELEMENTTYPE
{
	RAL_VERTEXELEMENTTYPE_FLOAT1 = 0,
	RAL_VERTEXELEMENTTYPE_FLOAT2,
	RAL_VERTEXELEMENTTYPE_FLOAT3,
	RAL_VERTEXELEMENTTYPE_FLOAT4,
	RAL_VERTEXELEMENTTYPE_COLOR,
	RAL_VERTEXELEMENTTYPE_COUNT
};
#endif