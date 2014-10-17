#ifndef CARBON_OGLVERTEXBUFFER
#define	CARBON_OGLVERTEXBUFFER

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
	GLuint	m_bufferId;	// index buffer id

	friend class OGLInterface;
};

#endif
