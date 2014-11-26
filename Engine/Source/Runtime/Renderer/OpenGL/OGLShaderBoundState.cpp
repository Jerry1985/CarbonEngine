#include "OGLShaderBoundState.h"
#include "OGLInterface.h"
#include "OGLShader.h"

RALShaderBoundState* OGLInterface::CreateShaderBoundState(const RALVertexLayout* vl, const RALShader* vs, const RALShader* ps)
{
	return new OGLShaderBoundState(vl,vs,ps);
}

// set shader bound state
void OGLInterface::SetShaderBoundState(const RALShaderBoundState* state)
{
	const OGLShaderBoundState* ogl_state = dynamic_cast<const OGLShaderBoundState*>(state);
	
	glUseProgram(ogl_state->m_programId);
	_setVertexLayout(ogl_state->m_vl);
}

OGLShaderBoundState::OGLShaderBoundState(const RALVertexLayout* vl, const RALShader* vs, const RALShader* ps):
RALShaderBoundState(vl,vs,ps)
{
	const OGLShader* pVS = dynamic_cast<const OGLShader*>(vs);
	const OGLShader* pFS = dynamic_cast<const OGLShader*>(ps);

	m_programId = glCreateProgram();

	glAttachShader(m_programId, pVS->m_shaderId);
	glAttachShader(m_programId, pFS->m_shaderId);

	glLinkProgram(m_programId);

	GLint Result = GL_FALSE;
	int InfoLogLength;
	glGetProgramiv(m_programId, GL_LINK_STATUS, &Result);
	glGetProgramiv(m_programId, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (Result != GL_TRUE && InfoLogLength > 0){
		char* log = new char[InfoLogLength + 1];
		glGetProgramInfoLog(m_programId, InfoLogLength, NULL, log);
		delete[] log;
	}
}

OGLShaderBoundState::~OGLShaderBoundState()
{
	glDeleteProgram(m_programId);
}