#include "OGLVertexBuffer.h"
#include "OGLInterface.h"
#include "OGLDefine.h"

RALVertexBuffer* OGLInterface::CreateVertexBuffer(unsigned size, unsigned stride, RAL_USAGE usage, void* data)
{
	return new OGLVertexBuffer(size, stride, usage, data);
}

void OGLInterface::SetVertexBuffers(unsigned startSlot, unsigned numBuffers, const RALVertexBuffer* vbs)
{
	OGLVertexBuffer* ogl_vbs = (OGLVertexBuffer*)vbs;

	GLuint			buffers[MAX_VB_SLOT_COUNT];
	unsigned		strides[MAX_VB_SLOT_COUNT];
	unsigned		offsets[MAX_VB_SLOT_COUNT];

	unsigned endSlot = startSlot + numBuffers;
	for (unsigned i = startSlot; i < endSlot; ++i)
	{
		buffers[i] = ogl_vbs[i].m_bufferId;
		strides[i] = ogl_vbs[i].GetBufferStride();
		offsets[i] = 0;

		glBindBuffer(GL_ARRAY_BUFFER, ogl_vbs[i].m_bufferId);
	}
}

OGLVertexBuffer::OGLVertexBuffer(unsigned size, unsigned stride, RAL_USAGE usage, void* data) :
RALVertexBuffer(size, stride, usage), m_bufferId(0)
{
	// generate element array buffer id
	glGenBuffers(1, &m_bufferId);

	// bind element array buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_bufferId);

	// submit data to the buffer
	if (data)
	{
		GLuint gl_usage = OGLUSAGE_FROM_RALUSAGE(usage);
		glBufferData(GL_ARRAY_BUFFER, size, data, gl_usage);
	}

	// setup pending desc
	m_pendingDesc.bufferSize = m_size;
	m_pendingDesc.stride = m_stride;
	m_pendingDesc.usage = m_usage;
	m_pendingDesc.pData = new char[m_pendingDesc.bufferSize];
}

OGLVertexBuffer::~OGLVertexBuffer()
{
	Release();
}

// lock the buffer
RALBufferDesc OGLVertexBuffer::Map()
{
	return m_pendingDesc;
}

// unlock the buffer
void OGLVertexBuffer::Unmap()
{
	// bind element array buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_bufferId);

	// submit data to the buffer
	if (m_pendingDesc.pData)
	{
		GLuint gl_usage = OGLUSAGE_FROM_RALUSAGE(m_pendingDesc.usage);
		glBufferData(GL_ARRAY_BUFFER, m_pendingDesc.bufferSize, m_pendingDesc.pData, gl_usage);
	}
}

// Release resource
void OGLVertexBuffer::Release()
{
	if (m_bufferId)
		glDeleteBuffers(1, &m_bufferId);

	if (m_pendingDesc.pData)
		delete[] m_pendingDesc.pData;
}