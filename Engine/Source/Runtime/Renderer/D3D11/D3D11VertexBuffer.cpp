#include "D3D11VertexBuffer.h"
#include "D3D11Interface.h"
#include "D3D11Define.h"
#include <d3d11.h>

extern D3D11Interface* gD3D11Interface;

RALVertexBuffer* D3D11Interface::CreateVertexBuffer(unsigned size, unsigned stride, RAL_USAGE usage, void* data )
{
	return new D3D11VertexBuffer(size, stride, usage, data);
}

// set vertex buffers
void D3D11Interface::SetVertexBuffers(unsigned startSlot, unsigned numBuffers, RALVertexBuffer* vbs)
{
	D3D11VertexBuffer* d3d_vbs = (D3D11VertexBuffer*)vbs;

	ID3D11Buffer*	buffers[MAX_VB_SLOT_COUNT];
	unsigned		strides[MAX_VB_SLOT_COUNT];
	unsigned		offsets[MAX_VB_SLOT_COUNT];

	unsigned endSlot = startSlot + numBuffers;
	for (unsigned i = startSlot; i < endSlot; ++i)
	{
		buffers[i] = d3d_vbs[i].m_buffer;
		strides[i] = d3d_vbs[i].GetBufferStride();
		offsets[i] = 0;
	}

	m_D3D11DeviceContext->IASetVertexBuffers(startSlot, numBuffers, buffers, strides, offsets);
}

D3D11VertexBuffer::D3D11VertexBuffer(unsigned size, unsigned stride, RAL_USAGE usage, void* data) :
RALVertexBuffer(size, stride, usage )
{
	// Fill in a buffer description.
	D3D11_BUFFER_DESC bufferDesc;
	memset(&bufferDesc, 0, sizeof(D3D11_BUFFER_DESC));

	bufferDesc.Usage = D3D11USAGE_FROM_RALUSAGE(usage);
	bufferDesc.ByteWidth = size;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = (usage == RAL_USAGE_DYNAMIC) ? D3D11_CPU_ACCESS_WRITE : 0;
	bufferDesc.MiscFlags = 0;

	if (data)
	{
		// Fill in the subresource data. 
		D3D11_SUBRESOURCE_DATA InitData;
		InitData.pSysMem = data;
		InitData.SysMemPitch = 0;
		InitData.SysMemSlicePitch = 0;

		gD3D11Interface->m_D3D11Device->CreateBuffer(&bufferDesc, &InitData, &m_buffer);
	}else
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

	RALBufferDesc desc;
	desc.bufferSize = m_size;
	desc.stride = m_stride;
	desc.pData = res.pData;
	desc.usage = m_usage;

	return desc;
}

// unlock the buffer
void D3D11VertexBuffer::Unmap()
{
	gD3D11Interface->m_D3D11DeviceContext->Unmap(m_buffer, 0);
}