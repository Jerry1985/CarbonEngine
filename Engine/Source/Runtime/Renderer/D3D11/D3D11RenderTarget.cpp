#include "D3D11RenderTarget.h"
#include "D3D11Interface.h"
#include "D3D11Define.h"

extern D3D11Interface* gD3D11Interface;

RALRenderTarget* D3D11Interface::CreateRenderTarget(unsigned w, unsigned h, RAL_FORMAT format)
{
	return new D3D11RenderTarget(w, h, format);
}

void D3D11Interface::SetRenderTarget( unsigned index , RALRenderTarget* rt )
{
	if (index >= MAX_RT_COUNT)
		return;

	m_pendingRT[index] = rt;

	// check if render target is changed
	_checkRTChanged();
}

D3D11RenderTarget::D3D11RenderTarget(unsigned width, unsigned height, RAL_FORMAT format)
{
	m_width = width;
	m_height = height;

	D3D11_TEXTURE2D_DESC desc;
	memset(&desc, 0, sizeof(desc));

	desc.Width = width;
	desc.Height = height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGIFORMAT_FROM_RALFORMAT(format);
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_RENDER_TARGET;
	desc.SampleDesc.Count = 1;

	gD3D11Interface->m_D3D11Device->CreateTexture2D(&desc, 0, &m_RTTexture);

	gD3D11Interface->m_D3D11Device->CreateRenderTargetView(m_RTTexture, 0, &m_RTV);
}

D3D11RenderTarget::D3D11RenderTarget(ID3D11Texture2D* tex) :m_RTTexture(tex)
{
	D3D11_TEXTURE2D_DESC desc;
	m_RTTexture->GetDesc(&desc);

	m_width = desc.Width;
	m_height = desc.Height;

	gD3D11Interface->m_D3D11Device->CreateRenderTargetView(m_RTTexture, 0, &m_RTV);
}

D3D11RenderTarget::~D3D11RenderTarget()
{
	Release();
}

// Release resource
void D3D11RenderTarget::Release()
{
	SAFE_RELEASE(m_RTV);
	SAFE_RELEASE(m_RTTexture);
}

// get render target view
ID3D11RenderTargetView*	D3D11RenderTarget::GetRenderTargetView() const
{
	return m_RTV;
}