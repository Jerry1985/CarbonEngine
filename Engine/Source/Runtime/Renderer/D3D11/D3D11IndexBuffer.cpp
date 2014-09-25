#include "D3D11IndexBuffer.h"
#include "D3D11Interface.h"
#include "D3D11Define.h"

extern D3D11Interface* gD3D11Interface;

RALIndexBuffer* D3D11Interface::CreateIndexBuffer(unsigned size, unsigned stride, RAL_USAGE usage, void* data)
{
	return new D3D11IndexBuffer(size, stride, usage, data);
}

void D3D11Interface::SetIndexBuffer(const RALIndexBuffer* ibs)
{
	D3D11IndexBuffer* d3d_ibs = (D3D11IndexBuffer*)ibs;
	DXGI_FORMAT format = (d3d_ibs->GetBufferStride() == 4) ? DXGI_FORMAT_R32_UINT : DXGI_FORMAT_R16_UINT;
	m_D3D11DeviceContext->IASetIndexBuffer(d3d_ibs->m_buffer, format, 0);
}

D3D11IndexBuffer::D3D11IndexBuffer(unsigned size, unsigned stride, RAL_USAGE usage, void* data) :
RALIndexBuffer(size, stride, usage), m_buffer(0)
{
	// Fill in a buffer description.
	D3D11_BUFFER_DESC bufferDesc;
	memset(&bufferDesc, 0, sizeof(D3D11_BUFFER_DESC));

	bufferDesc.Usage = D3D11USAGE_FROM_RALUSAGE(usage);
	bufferDesc.ByteWidth = size;
	bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bufferDesc.CPUAccessFlags = (usage == RAL_USAGE_DYNAMIC) ? D3D11_CPU_ACCESS_WRITE : 0;
	bufferDesc.MiscFlags = 0;

	if (data != 0)
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
D3D11IndexBuffer::~D3D11IndexBuffer()
{
	Release();
}

// lock the buffer
RALBufferDesc D3D11IndexBuffer::Map()
{
	if (m_buffer == 0)
		return RALBufferDesc();

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
void D3D11IndexBuffer::Unmap()
{
	if (m_buffer)
		gD3D11Interface->m_D3D11DeviceContext->Unmap(m_buffer, 0);
}

// Release resource
void D3D11IndexBuffer::Release()
{
	SAFE_RELEASE(m_buffer);
}