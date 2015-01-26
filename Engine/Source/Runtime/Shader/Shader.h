#pragma once

#include "Core\Resource.h"
#include "ShaderMetaData.h"
#include "Common\Container\CArray.h"
#include "Renderer\Common\RALVertexLayout.h"

class RALShader;
class RALVertexLayout;
class RALPipelineBoundState;

class Shader : public Resource
{
public:
	// get ral shader
	virtual const RALShader*	GetRALShader() const = 0;
};

class VertexShader : public Shader
{
public:
	// get vertex layout desc
	virtual const CArray<RALVertexElementDesc>& GetVertexLayoutDesc() const = 0;
	virtual const RALVertexLayout* GetRALVertexLayout() const = 0;
};

class PipelineBoundState
{
public:
	PipelineBoundState();
	~PipelineBoundState();

	// Setup shader bound state
	void	SetupGraphics(VertexShader* vs, Shader* ps, Shader* hs = 0, Shader* ds = 0, Shader* gs = 0);
	// Setup compute shader
	void	SetupCompute(Shader* cs);

	// bind the shader states
	void	Bind();

	// release shader bound state
	void	Release();

private:
	VertexShader*	m_VertexShader = 0;
	Shader*	m_PixelShader = 0;
	Shader*	m_HullShader = 0;
	Shader*	m_DomainShader = 0;
	Shader*	m_GeometryShader = 0;

	Shader*	m_ComputeShader = 0;

	RALPipelineBoundState*	m_ShaderBoundState = 0;

	const RALVertexLayout*	m_VertexLayout = 0;
};