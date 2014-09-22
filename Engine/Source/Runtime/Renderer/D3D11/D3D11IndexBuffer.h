#ifndef CARBON_D3D11INDEXBUFFER
#define	CARBON_D3D11INDEXBUFFER

#include "Renderer\Common\RALIndexBuffer.h"

struct ID3D11Buffer;

class D3D11IndexBuffer : public RALIndexBuffer
{
public:
	D3D11IndexBuffer(unsigned size, unsigned stride, RAL_USAGE usage);
	~D3D11IndexBuffer();

	// lock the buffer
	RALBufferDesc Map();
	// unlock the buffer
	void Unmap();

	// Release resource
	void Release();

private:
	ID3D11Buffer*	m_buffer;
};

#endif
