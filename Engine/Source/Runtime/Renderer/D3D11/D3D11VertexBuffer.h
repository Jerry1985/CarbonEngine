#pragma once

#include "Renderer\Common\RALVertexBuffer.h"

struct ID3D11Buffer;

class D3D11VertexBuffer : public RALVertexBuffer
{
public:
	D3D11VertexBuffer(unsigned size, unsigned stride, RAL_USAGE usage, void* data);
	~D3D11VertexBuffer();

	// lock the buffer
	RALBufferDesc Map();
	// unlock the buffer
	void Unmap();

	// Release resource
	void Release();

private:
	ID3D11Buffer*	m_buffer;

	friend class D3D11Interface;

	// TEMP_BEGIN
	friend class MyApp;
	// TEMP_END
};
