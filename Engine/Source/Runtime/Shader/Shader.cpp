#include "Shader.h"
#include "Renderer\Common\RALShader.h"
#include "Renderer\Common\RALVertexLayout.h"
#include "Renderer\Common\RALPipelineBoundState.h"


PipelineBoundState::PipelineBoundState()
{
}

PipelineBoundState::~PipelineBoundState()
{
	Release();
}

void PipelineBoundState::SetupGraphics(VertexShader* vs, Shader* ps, Shader* hs, Shader* ds, Shader* gs)
{
	// Release shader bound state first
	Release();

	m_VertexLayout = vs->GetRALVertexLayout();

	m_VertexShader = vs;
	m_PixelShader = ps;
	
	m_HullShader = hs;
	m_DomainShader = ds;
	m_GeometryShader = gs;

	m_ShaderBoundState = RALCreatePipelineBoundState(m_VertexLayout, m_VertexShader->GetRALShader(), m_PixelShader->GetRALShader());
}

// Setup compute shader
void	PipelineBoundState::SetupCompute(Shader* cs)
{
	// Release shader bound state first
	Release();

	m_ComputeShader = cs;
}

// bind the shader states
void PipelineBoundState::Bind()
{
	if (m_ComputeShader)
	{

	}
	else if (m_ShaderBoundState)
		RALSetPipelineBoundState(m_ShaderBoundState);
}

// release shader bound state
void PipelineBoundState::Release()
{
	SAFE_DELETE(m_ShaderBoundState);
}