#pragma once

#include "Core\Resource.h"
#include "ShaderMetaData.h"
#include "Common\Container\CArray.h"
#include "Renderer\Common\RALVertexLayout.h"

class RALShader;
class RALVertexLayout;
class RALPipelineBoundState;

class Shader : public Resource
{
public:
	// get ral shader
	virtual const RALShader*	GetRALShader() const = 0;
};

class VertexShader : public Shader
{
public:
	// get vertex layout desc
	virtual const CArray<RALVertexElementDesc>& GetVertexLayoutDesc() const = 0;
	virtual const RALVertexLayout* GetRALVertexLayout() const = 0;
};