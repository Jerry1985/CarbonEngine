#include "FlipViewShader.h"

DEFINE_SHADER(FlipViewVertexShader, VERTEXSHADER, S("FlipViewVertexShader"), S("vs.shader"), S("main"))
DEFINE_SHADER(FlipViewPixelShader, PIXELSHADER, S("FlipViewPixelShader"), S("ps.shader"), S("main"))

DEFINE_SHADER_VERTEX_LAYOUT(FlipViewVertexShader)

FlipViewVertexShader::FlipViewVertexShader()
{
	// Initialize vertex layout
	if (m_VertexLayoutDesc.IsEmpty())
	{
		RALVertexElementDesc layoutDesc;
		layoutDesc.attributeIndex = 0;
		layoutDesc.offset = 0;
		layoutDesc.streamIndex = 0;
		layoutDesc.type = RAL_VERTEXELEMENTTYPE_FLOAT3;
		layoutDesc.useInstanceIndex = false;

		m_VertexLayoutDesc.Add(layoutDesc);
	}
}

// Initialize
void FlipViewVertexShader::Init()
{
	Shader::Init();

	if (!m_VertexLayout)
		m_VertexLayout = RALCreateVertexLayout(m_VertexLayoutDesc, m_ShaderMetaData.m_CompiledShader);
}

// Release
void FlipViewVertexShader::Release()
{
	SAFE_DELETE(m_VertexLayout);
}