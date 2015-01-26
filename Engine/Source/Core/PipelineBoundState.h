#pragma once

#include "Shader\Shader.h"

struct PipelineBoundStateDesc
{
	RAL_PRIMITIVE			m_PrimitiveType = RAL_PRIMITIVE_TRIANGLELIST;

	const VertexShader*		m_VertexShader = 0;
	const Shader*			m_PixelShader = 0;
	const Shader*			m_HullShader = 0;
	const Shader*			m_DomainShader = 0;
	const Shader*			m_GeometryShader = 0;

	const Shader*			m_ComputeShader = 0;

	const RALVertexLayout*	m_VertexLayout = 0;
};

struct PipelineBoundState
{
public:
	PipelineBoundState();
	~PipelineBoundState();

	// Set PBS Desc
	void	Init(const PipelineBoundStateDesc& desc);

	// bind the shader states
	void	Bind();

	// release shader bound state
	void	Release();

	PipelineBoundStateDesc	m_Desc;
	RALPipelineBoundState*	m_ShaderBoundState = 0;
};