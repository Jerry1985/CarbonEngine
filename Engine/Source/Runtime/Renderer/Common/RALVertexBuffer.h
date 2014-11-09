#pragma once

#include "RALBuffer.h"

class RALVertexBuffer : public RALBuffer
{
public:
	RALVertexBuffer( unsigned size , unsigned stride , RAL_USAGE usage );
	virtual ~RALVertexBuffer();
};
