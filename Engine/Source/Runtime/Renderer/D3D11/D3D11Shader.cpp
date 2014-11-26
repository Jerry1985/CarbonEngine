#include "D3D11Shader.h"
#include "D3D11Interface.h"
#include "Container\CBitArray.h"

extern D3D11Interface* gD3D11Interface;

RALShader*	D3D11Interface::CreateVertexShader()
{
	return new D3D11VertexShader();
}

RALShader*	D3D11Interface::CreatePixelShader()
{
	return new D3D11PixelShader();
}

D3D11Shader::D3D11Shader()
{
}

D3D11Shader::~D3D11Shader()
{
}

D3D11VertexShader::D3D11VertexShader() :m_shader(0)
{
	m_ShaderType = RAL_SHADERTYPE_VERTEXSHADER;
}
D3D11VertexShader::~D3D11VertexShader()
{
	SAFE_RELEASE(m_shader);
}

// create shader from byte code
bool D3D11VertexShader::CreateShader(const CBitArray& bytecode)
{
	SAFE_RELEASE(m_shader);
	gD3D11Interface->m_D3D11Device->CreateVertexShader(bytecode.GetData(), bytecode.GetSize(), 0, &m_shader);

	return m_shader != 0;
}

D3D11PixelShader::D3D11PixelShader() :m_shader(0)
{
	m_ShaderType = RAL_SHADERTYPE_PIXELSHADER;
}
D3D11PixelShader::~D3D11PixelShader()
{
	SAFE_RELEASE(m_shader);
}

// create shader from byte code
bool D3D11PixelShader::CreateShader(const CBitArray& bytecode)
{
	SAFE_RELEASE(m_shader);
	gD3D11Interface->m_D3D11Device->CreatePixelShader(bytecode.GetData(), bytecode.GetSize(), 0, &m_shader);

	return m_shader != 0;
}