#pragma once

#include "Renderer\Common\RALShaderBoundState.h"

class D3D11ShaderBoundState : public RALShaderBoundState
{
public:
	D3D11ShaderBoundState(const RALVertexLayout* vl, const RALShader* vs, const RALShader* ps);
	~D3D11ShaderBoundState();

	friend class D3D11Interface;
};