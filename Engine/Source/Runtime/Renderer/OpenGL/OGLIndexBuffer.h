#ifndef CARBON_OGLINDEXBUFFER
#define	CARBON_OGLINDEXBUFFER

#include "Renderer\Common\RALIndexBuffer.h"
#include "../ThirdParty/Regal/Include/Regal.h"

class OGLIndexBuffer : public RALIndexBuffer
{
public:
	OGLIndexBuffer(unsigned size, unsigned stride, RAL_USAGE usage, void* data);
	~OGLIndexBuffer();

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

#endif
