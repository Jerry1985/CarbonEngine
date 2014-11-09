#pragma once

#include "Renderer\Common\RALShader.h"

struct ID3D11VertexShader;
struct ID3D11PixelShader;

class D3D11Shader : public RALShader
{
public:
	D3D11Shader();
	virtual ~D3D11Shader();
};

class D3D11VertexShader : public D3D11Shader
{
public:
	D3D11VertexShader();
	virtual ~D3D11VertexShader();

	// create shader from byte code
	bool CreateShader(void* data, unsigned length);

private:
	ID3D11VertexShader*	m_shader;

	friend class D3D11Interface;
};

class D3D11PixelShader : public D3D11Shader
{
public:
	D3D11PixelShader();
	virtual ~D3D11PixelShader();

	// create shader from byte code
	bool CreateShader(void* data, unsigned length);

private:
	ID3D11PixelShader* m_shader;

	friend class D3D11Interface;
};