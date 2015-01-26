#include "PipelineBoundState.h"
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

// Set PBS Desc
void PipelineBoundState::Init(const PipelineBoundStateDesc& desc){
	// Release shader bound state first
	Release();

	m_Desc = desc;

	m_ShaderBoundState = RALCreatePipelineBoundState(m_Desc.m_VertexLayout, m_Desc.m_VertexShader->GetRALShader(), m_Desc.m_PixelShader->GetRALShader());
}

// bind the shader states
void PipelineBoundState::Bind()
{
	if (m_Desc.m_ComputeShader)
	{

	}
	else if (m_ShaderBoundState)
	{
		RALSetPipelineBoundState(m_ShaderBoundState);
		RALSetPrimitiveType(m_Desc.m_PrimitiveType);
	}
}

// release shader bound state
void PipelineBoundState::Release()
{
	SAFE_DELETE(m_ShaderBoundState);
}