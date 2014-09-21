#include "D3D11VertexBuffer.h"
#include "D3D11Interface.h"
#include "D3D11Define.h"
#include <d3d11.h>

extern D3D11Interface* gD3D11Interface;

RALVertexBuffer* D3D11Interface::CreateVertexBuffer(unsigned size, RAL_USAGE usage)
{
	return new D3D11VertexBuffer(size, usage);
}

D3D11VertexBuffer::D3D11VertexBuffer(unsigned size, RAL_USAGE usage):
RALVertexBuffer(size, usage )
{
	// Fill in a buffer description.
	D3D11_BUFFER_DESC bufferDesc;
	memset(&bufferDesc, 0, sizeof(D3D11_BUFFER_DESC));

	bufferDesc.Usage = D3D11USAGE_FROM_RALUSAGE(usage);
	bufferDesc.ByteWidth = size;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = (usage == RAL_USAGE_DYNAMIC) ? D3D11_CPU_ACCESS_WRITE : 0;
	bufferDesc.MiscFlags = 0;

	// Create the vertex buffer.
	gD3D11Interface->m_D3D11Device->CreateBuffer(&bufferDesc, 0, &m_buffer);
}

D3D11VertexBuffer::~D3D11VertexBuffer()
{
	Release();
}

// Release resource
void D3D11VertexBuffer::Release()
{
	SAFE_RELEASE(m_buffer);
}

// lock the buffer
RALBufferDesc D3D11VertexBuffer::Map()
{
	D3D11_MAPPED_SUBRESOURCE res;
	memset(&res, 0, sizeof(res));
	gD3D11Interface->m_D3D11DeviceContext->Map(m_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &res);
	return RALBufferDesc(res.pData, m_size);
}

// unlock the buffer
void D3D11VertexBuffer::Unmap()
{
	gD3D11Interface->m_D3D11DeviceContext->Unmap(m_buffer, 0);
}