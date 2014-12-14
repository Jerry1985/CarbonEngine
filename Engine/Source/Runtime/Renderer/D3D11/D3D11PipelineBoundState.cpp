#include "D3D11PipelineBoundState.h"
#include "D3D11Interface.h"

RALPipelineBoundState* D3D11Interface::CreatePipelineBoundState(const RALVertexLayout* vl, const RALShader* vs, const RALShader* ps)
{
	return new D3D11PipelineBoundState(vl, vs, ps);
}

// set shader bound state
void D3D11Interface::SetPipelineBoundState(const RALPipelineBoundState* state)
{
	const D3D11PipelineBoundState* d3d11_state = dynamic_cast<const D3D11PipelineBoundState*>(state);
	_setVertexLayout(d3d11_state->m_vl);
	_setVertexShader(d3d11_state->m_vs);
	_setPixelShader(d3d11_state->m_ps);
}

D3D11PipelineBoundState::D3D11PipelineBoundState(const RALVertexLayout* vl, const RALShader* vs, const RALShader* ps) :
RALPipelineBoundState(vl, vs, ps)
{
}
D3D11PipelineBoundState::~D3D11PipelineBoundState()
{
}