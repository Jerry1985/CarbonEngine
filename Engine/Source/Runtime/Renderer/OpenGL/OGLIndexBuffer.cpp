#include "OGLIndexBuffer.h"
#include "OGLInterface.h"
#include "OGLDefine.h"

RALIndexBuffer* OGLInterface::CreateIndexBuffer(unsigned size, unsigned stride, RAL_USAGE usage, void* data)
{
	return new OGLIndexBuffer(size, stride, usage, data);
}

void OGLInterface::SetIndexBuffer(const RALIndexBuffer* ibs)
{
	OGLIndexBuffer* ogl_ibs = (OGLIndexBuffer*)ibs;

	// bind element array buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ogl_ibs->m_bufferId);

	// set data type
	m_elementArrayType = (ogl_ibs->GetBufferStride() == 4) ? GL_UNSIGNED_INT : GL_UNSIGNED_SHORT;
}

OGLIndexBuffer::OGLIndexBuffer(unsigned size, unsigned stride, RAL_USAGE usage, void* data) :
RALIndexBuffer(size, stride, usage), m_bufferId(0)
{
	// generate element array buffer id
	glGenBuffers(1, &m_bufferId);

	// bind element array buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferId);

	// submit data to the buffer
	if (data)
	{
		GLuint gl_usage = OGLUSAGE_FROM_RALUSAGE(usage);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, gl_usage);
	}

	// setup pending desc
	m_pendingDesc.bufferSize = m_size;
	m_pendingDesc.stride = m_stride;
	m_pendingDesc.usage = m_usage;
	m_pendingDesc.pData = new char[m_pendingDesc.bufferSize];
}

OGLIndexBuffer::~OGLIndexBuffer()
{
	Release();
}

// lock the buffer
RALBufferDesc OGLIndexBuffer::Map()
{
	return m_pendingDesc;
}

// unlock the buffer
void OGLIndexBuffer::Unmap()
{
	// bind element array buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferId);

	// submit data to the buffer
	if (m_pendingDesc.pData)
	{
		GLuint gl_usage = OGLUSAGE_FROM_RALUSAGE(m_pendingDesc.usage);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_pendingDesc.bufferSize, m_pendingDesc.pData, gl_usage);
	}
}

// Release resource
void OGLIndexBuffer::Release()
{
	if (m_bufferId)
		glDeleteBuffers(1, &m_bufferId);

	if (m_pendingDesc.pData)
		delete[] m_pendingDesc.pData;
}