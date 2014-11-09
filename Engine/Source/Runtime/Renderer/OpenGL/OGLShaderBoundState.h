#pragma once

#include "Renderer\Common\RALShaderBoundState.h"
#include "../ThirdParty/Regal/Include/Regal.h"

class OGLShaderBoundState : public RALShaderBoundState
{
public:
	OGLShaderBoundState(RALVertexLayout* vl, RALShader* vs, RALShader* ps);
	~OGLShaderBoundState();

private:
	GLuint m_programId;

	friend class OGLInterface;
};