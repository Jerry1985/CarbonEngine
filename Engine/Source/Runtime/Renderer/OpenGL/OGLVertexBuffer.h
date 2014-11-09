#pragma once

#include "Renderer\Common\RALVertexBuffer.h"
#include "../ThirdParty/Regal/Include/Regal.h"

class OGLVertexBuffer : public RALVertexBuffer
{
public:
	OGLVertexBuffer(unsigned size, unsigned stride, RAL_USAGE usage, void* data);
	~OGLVertexBuffer();

	// lock the buffer
	RALBufferDesc Map();
	// unlock the buffer
	void Unmap();

	// Release resource
	void Release();

private:
	GLuint			m_bufferId;	// index buffer id
	RALBufferDesc	m_pendingDesc;

	friend class OGLInterface;
};
