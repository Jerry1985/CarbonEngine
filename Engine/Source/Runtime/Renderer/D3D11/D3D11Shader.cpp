#include "D3D11Shader.h"
#include "D3D11Interface.h"

extern D3D11Interface* gD3D11Interface;

RALShader*	D3D11Interface::CreateVertexShader()
{
	return new D3D11VertexShader();
}

RALShader*	D3D11Interface::CreatePixelShader()
{
	return new D3D11PixelShader();
}

void D3D11Interface::SetVertexShader(const RALShader* shader)
{
	const D3D11VertexShader* vs = dynamic_cast<const D3D11VertexShader*>(shader);
	if (vs)
		gD3D11Interface->m_D3D11DeviceContext->VSSetShader(vs->m_shader, 0, 0);
}

void D3D11Interface::SetPixelShader(const RALShader* shader)
{
	const D3D11PixelShader* ps = dynamic_cast<const D3D11PixelShader*>(shader);
	if (ps)
		gD3D11Interface->m_D3D11DeviceContext->PSSetShader(ps->m_shader, 0, 0);
}

D3D11Shader::D3D11Shader()
{
}

D3D11Shader::~D3D11Shader()
{
}

D3D11VertexShader::D3D11VertexShader() :m_shader(0)
{
}
D3D11VertexShader::~D3D11VertexShader()
{
	SAFE_RELEASE(m_shader);
}

// create shader from byte code
bool D3D11VertexShader::CreateShader(void* data, unsigned length)
{
	SAFE_RELEASE(m_shader);

	gD3D11Interface->m_D3D11Device->CreateVertexShader(data, length, 0, &m_shader);

	return m_shader != 0;
}

D3D11PixelShader::D3D11PixelShader() :m_shader(0)
{
}
D3D11PixelShader::~D3D11PixelShader()
{
	SAFE_RELEASE(m_shader);
}

// create shader from byte code
bool D3D11PixelShader::CreateShader(void* data, unsigned length)
{
	SAFE_RELEASE(m_shader);

	gD3D11Interface->m_D3D11Device->CreatePixelShader(data, length, 0, &m_shader);

	return m_shader != 0;
}