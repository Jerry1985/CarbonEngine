#pragma once

#include "ShaderMetaData.h"

class RALShader;
class RALVertexLayout;
class RALShaderBoundState;

class Shader
{
public:
	Shader();
	~Shader();

	// get ral shader
	virtual const RALShader*	GetRALShader() const = 0;
};

class ShaderBoundState
{
public:
	ShaderBoundState();
	~ShaderBoundState();

	// Setup shader bound state
	void	SetupGraphics(RALVertexLayout* layout, Shader* vs, Shader* ps, Shader* hs = 0, Shader* ds = 0, Shader* gs = 0);
	// Setup compute shader
	void	SetupCompute(Shader* cs);

	// bind the shader states
	void	Bind();

	// release shader bound state
	void	Release();

private:
	Shader*	m_VertexShader = 0;
	Shader*	m_PixelShader = 0;
	Shader*	m_HullShader = 0;
	Shader*	m_DomainShader = 0;
	Shader*	m_GeometryShader = 0;

	Shader*	m_ComputeShader = 0;

	RALShaderBoundState*	m_ShaderBoundState = 0;

	RALVertexLayout*	m_VertexLayout = 0;
};