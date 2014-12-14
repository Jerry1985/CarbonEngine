#pragma once

#include "Renderer\Common\RALPipelineBoundState.h"
#include "../ThirdParty/Regal/Include/Regal.h"

class OGLPipelineBoundState : public RALPipelineBoundState
{
public:
	OGLPipelineBoundState(const RALVertexLayout* vl, const RALShader* vs, const RALShader* ps);
	~OGLPipelineBoundState();

private:
	GLuint m_programId;

	friend class OGLInterface;
};