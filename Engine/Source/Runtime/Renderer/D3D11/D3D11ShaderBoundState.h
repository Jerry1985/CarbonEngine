#pragma once

#include "Renderer\Common\RALShaderBoundState.h"

class D3D11ShaderBoundState : public RALShaderBoundState
{
public:
	D3D11ShaderBoundState(RALVertexLayout* vl, RALShader* vs, RALShader* ps);
	~D3D11ShaderBoundState();

	friend class D3D11Interface;
};