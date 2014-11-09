#pragma once

#include "RALResource.h"

class RALShader;
class RALVertexLayout;

class RALShaderBoundState : public RALResource
{
public:
	RALShaderBoundState(RALVertexLayout* vl,RALShader* vs,RALShader* ps);
	virtual ~RALShaderBoundState();

protected:
	RALShader*	m_vs;
	RALShader*	m_ps;

	RALVertexLayout*	m_vl;
};