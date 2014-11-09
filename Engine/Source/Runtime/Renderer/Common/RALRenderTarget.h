#pragma once

#include "RALResource.h"

enum RAL_FORMAT;

class RALRenderTarget : public RALResource
{
public:
	RALRenderTarget();
	virtual ~RALRenderTarget();

	RAL_FORMAT	GetFormat() const { return m_format; }
	
protected:
	unsigned	m_width;
	unsigned	m_height;

	RAL_FORMAT	m_format;
};