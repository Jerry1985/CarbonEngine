#ifndef CARBON_RALVERTEXBUFFER
#define	CARBON_RALVERTEXBUFFER

#include "RALBuffer.h"

class RALVertexBuffer : public RALBuffer
{
public:
	RALVertexBuffer( unsigned size , unsigned stride , RAL_USAGE usage );
	virtual ~RALVertexBuffer();
};

#endif
