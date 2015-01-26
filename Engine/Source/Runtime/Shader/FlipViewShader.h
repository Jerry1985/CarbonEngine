#pragma once

#include "Shader.h"

class FlipViewVertexShader : public VertexShader
{
public:
	DECLARE_SHADER(FlipViewVertexShader);
	DECLARE_SHADER_VERTEX_LAYOUT(FlipViewVertexShader);

	FlipViewVertexShader();
	~FlipViewVertexShader();

	// Initialize
	void Init();
	// Release
	void Release();
};

class FlipViewPixelShader : public Shader
{
public:
	DECLARE_SHADER(FlipViewPixelShader);
};