#include "RALPipelineBoundState.h"

RALPipelineBoundState::RALPipelineBoundState(const RALVertexLayout* vl, const RALShader* vs, const RALShader* ps) :
m_vs(vs), m_ps(ps), m_vl(vl)
{
}

RALPipelineBoundState::~RALPipelineBoundState()
{
}