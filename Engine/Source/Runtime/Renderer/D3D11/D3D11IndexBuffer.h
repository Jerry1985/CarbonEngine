#pragma once

#include "Renderer\Common\RALIndexBuffer.h"

struct ID3D11Buffer;

class D3D11IndexBuffer : public RALIndexBuffer
{
public:
	D3D11IndexBuffer(unsigned size, unsigned stride, RAL_USAGE usage, void* data);
	~D3D11IndexBuffer();

	// lock the buffer
	RALBufferDesc Map();
	// unlock the buffer
	void Unmap();

	// Release resource
	void Release();

private:
	ID3D11Buffer*	m_buffer;

	friend class D3D11Interface;
};
