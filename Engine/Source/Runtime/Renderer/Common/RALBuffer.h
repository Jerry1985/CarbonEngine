#ifndef CARBON_RALBUFFER
#define CARBON_RALBUFFER

#include "RALResource.h"

enum RAL_USAGE;

struct RALBufferDesc
{
	void*		pData;
	unsigned	bufferSize;

	RALBufferDesc()
	{
		pData = 0;
		bufferSize = 0;
	}
	RALBufferDesc(void* data, unsigned size) :pData(data), bufferSize(size)
	{
	}
};

class RALBuffer : public RALResource
{
public:
	RALBuffer(unsigned size, RAL_USAGE usage);
	virtual ~RALBuffer();

	// Get Buffer Size
	virtual unsigned	GetBufferSize() const { return m_size; }
	// lock the buffer
	virtual RALBufferDesc Map() = 0;
	// unlock the buffer
	virtual void Unmap() = 0;

protected:
	unsigned	m_size;
	RAL_USAGE	m_usage;
};

#endif