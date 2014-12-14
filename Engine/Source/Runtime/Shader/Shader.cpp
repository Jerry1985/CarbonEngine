#include "Shader.h"
#include "Renderer\Common\RALShader.h"
#include "Renderer\Common\RALVertexLayout.h"
#include "Renderer\Common\RALPipelineBoundState.h"

Shader::Shader()
{
}

Shader::~Shader()
{
}

ShaderBoundState::ShaderBoundState()
{
}

ShaderBoundState::~ShaderBoundState()
{
	Release();
}

void ShaderBoundState::SetupGraphics(RALVertexLayout* layout, Shader* vs, Shader* ps, Shader* hs, Shader* ds, Shader* gs)
{
	// Release shader bound state first
	Release();

	m_VertexLayout = layout;

	m_VertexShader = vs;
	m_PixelShader = ps;
	
	m_HullShader = hs;
	m_DomainShader = ds;
	m_GeometryShader = gs;

	m_ShaderBoundState = RALCreatePipelineBoundState(m_VertexLayout, m_VertexShader->GetRALShader(), m_PixelShader->GetRALShader());
}

// Setup compute shader
void	ShaderBoundState::SetupCompute(Shader* cs)
{
	// Release shader bound state first
	Release();

	m_ComputeShader = cs;
}

// bind the shader states
void ShaderBoundState::Bind()
{
	if (m_ComputeShader)
	{

	}
	else if (m_ShaderBoundState)
		RALSetPipelineBoundState(m_ShaderBoundState);
}

// release shader bound state
void ShaderBoundState::Release()
{
	SAFE_DELETE(m_VertexLayout);

	SAFE_DELETE(m_ShaderBoundState);

	SAFE_DELETE(m_VertexShader);
	SAFE_DELETE(m_PixelShader);
	SAFE_DELETE(m_HullShader);
	SAFE_DELETE(m_DomainShader);
	SAFE_DELETE(m_GeometryShader);
}