#ifndef CARBON_D3D11VERTEXBUFFER
#define	CARBON_D3D11VERTEXBUFFER

#include "Renderer\Common\RALVertexBuffer.h"

struct ID3D11Buffer;

class D3D11VertexBuffer : public RALVertexBuffer
{
public:
	D3D11VertexBuffer(unsigned size, RAL_USAGE usage);
	~D3D11VertexBuffer();

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
