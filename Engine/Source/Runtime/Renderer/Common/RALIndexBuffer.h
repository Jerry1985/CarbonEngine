#ifndef CARBON_RALINDEXBUFFER
#define	CARBON_RALINDEXBUFFER

#include "RALBuffer.h"

class RALIndexBuffer : public RALBuffer
{
public:
	RALIndexBuffer(unsigned size, unsigned stride, RAL_USAGE usage);
	~RALIndexBuffer();
};
#endif