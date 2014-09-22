#ifndef CARBON_RALBUFFER
#define CARBON_RALBUFFER

#include "RALResource.h"
#include "RALDefine.h"

enum RAL_USAGE;

struct RALBufferDesc
{
	void*		pData;			// buffer data
	unsigned	bufferSize;		// total buffer size in bytes
	unsigned	stride;			// per element size in bytes

	RAL_USAGE	usage;			// buffer usage

	RALBufferDesc()
	{
		pData = 0;
		bufferSize = 0;
		stride = 0;
		usage = RAL_USAGE_DEFAULT;
	}
};

class RALBuffer : public RALResource
{
public:
	RALBuffer(unsigned size, unsigned stride, RAL_USAGE usage);
	virtual ~RALBuffer();

	// Get Buffer Size
	virtual unsigned	GetBufferSize() const { return m_size; }
	// Get Buffer Stride
	virtual unsigned	GetBufferStride() const { return m_stride; }
	// lock the buffer
	virtual RALBufferDesc Map() = 0;
	// unlock the buffer
	virtual void Unmap() = 0;

protected:
	unsigned	m_size;		// total buffer size
	unsigned	m_stride;	// per element size
	RAL_USAGE	m_usage;
};

#endif