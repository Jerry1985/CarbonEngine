#pragma once

#include "RALResource.h"

class RALShader;
class RALVertexLayout;

class RALShaderBoundState : public RALResource
{
public:
	RALShaderBoundState(const RALVertexLayout* vl,const RALShader* vs,const RALShader* ps);
	virtual ~RALShaderBoundState();

protected:
	const RALShader*	m_vs;
	const RALShader*	m_ps;

	const RALVertexLayout*	m_vl;
};