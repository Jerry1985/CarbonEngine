#include "OGLPipelineBoundState.h"
#include "OGLInterface.h"
#include "OGLShader.h"

RALPipelineBoundState* OGLInterface::CreatePipelineBoundState(const RALVertexLayout* vl, const RALShader* vs, const RALShader* ps)
{
	return new OGLPipelineBoundState(vl, vs, ps);
}

// set shader bound state
void OGLInterface::SetPipelineBoundState(const RALPipelineBoundState* state)
{
	const OGLPipelineBoundState* ogl_state = dynamic_cast<const OGLPipelineBoundState*>(state);
	
	glUseProgram(ogl_state->m_programId);
	_setVertexLayout(ogl_state->m_vl);
}

OGLPipelineBoundState::OGLPipelineBoundState(const RALVertexLayout* vl, const RALShader* vs, const RALShader* ps) :
RALPipelineBoundState(vl, vs, ps)
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

OGLPipelineBoundState::~OGLPipelineBoundState()
{
	glDeleteProgram(m_programId);
}