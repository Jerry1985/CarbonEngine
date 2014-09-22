#include "RALBuffer.h"
#include "RALDefine.h"

RALBuffer::RALBuffer(unsigned size, unsigned stride, RAL_USAGE usage):
	m_size(size), m_stride(stride), m_usage(usage)
{
}

RALBuffer::~RALBuffer()
{

}