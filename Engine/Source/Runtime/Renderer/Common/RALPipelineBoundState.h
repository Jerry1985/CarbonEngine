#pragma once

#include "RALResource.h"

class RALShader;
class RALVertexLayout;

class RALPipelineBoundState : public RALResource
{
public:
	RALPipelineBoundState(const RALVertexLayout* vl, const RALShader* vs, const RALShader* ps);
	virtual ~RALPipelineBoundState();

protected:
	const RALShader*	m_vs;
	const RALShader*	m_ps;

	const RALVertexLayout*	m_vl;
};