#pragma once

#include "RALBuffer.h"

class RALIndexBuffer : public RALBuffer
{
public:
	RALIndexBuffer(unsigned size, unsigned stride, RAL_USAGE usage);
	~RALIndexBuffer();
};
