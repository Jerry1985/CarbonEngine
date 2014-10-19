#include "D3D11ShaderBoundState.h"
#include "D3D11Interface.h"

RALShaderBoundState* D3D11Interface::CreateShaderBoundState(RALVertexLayout* vl, RALShader* vs, RALShader* ps)
{
	return new D3D11ShaderBoundState(vl,vs,ps);
}

// set shader bound state
void D3D11Interface::SetShaderBoundState(const RALShaderBoundState* state)
{
	const D3D11ShaderBoundState* d3d11_state = dynamic_cast<const D3D11ShaderBoundState*>(state);
	_setVertexLayout(d3d11_state->m_vl);
	_setVertexShader(d3d11_state->m_vs);
	_setPixelShader(d3d11_state->m_ps);
}

D3D11ShaderBoundState::D3D11ShaderBoundState(RALVertexLayout* vl, RALShader* vs, RALShader* ps):
RALShaderBoundState(vl,vs,ps)
{
}
D3D11ShaderBoundState::~D3D11ShaderBoundState()
{
}