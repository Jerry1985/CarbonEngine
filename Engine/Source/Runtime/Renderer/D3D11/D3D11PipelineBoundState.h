#pragma once

#include "Renderer\Common\RALPipelineBoundState.h"

class D3D11PipelineBoundState : public RALPipelineBoundState
{
public:
	D3D11PipelineBoundState(const RALVertexLayout* vl, const RALShader* vs, const RALShader* ps);
	~D3D11PipelineBoundState();

	friend class D3D11Interface;
};