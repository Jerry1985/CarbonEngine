#pragma once

#include "Renderer\Common\RALShaderBoundState.h"
#include "../ThirdParty/Regal/Include/Regal.h"

class OGLShaderBoundState : public RALShaderBoundState
{
public:
	OGLShaderBoundState(const RALVertexLayout* vl, const RALShader* vs, const RALShader* ps);
	~OGLShaderBoundState();

private:
	GLuint m_programId;

	friend class OGLInterface;
};