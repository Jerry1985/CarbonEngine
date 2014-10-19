#include "RALShaderBoundState.h"

RALShaderBoundState::RALShaderBoundState(RALVertexLayout* vl, RALShader* vs, RALShader* ps):
m_vs(vs), m_ps(ps), m_vl(vl)
{
}

RALShaderBoundState::~RALShaderBoundState()
{
}