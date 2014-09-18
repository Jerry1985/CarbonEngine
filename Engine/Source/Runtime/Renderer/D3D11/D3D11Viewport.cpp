#include "D3D11Viewport.h"
#include "D3D11Interface.h"
#include "D3D11RenderTarget.h"
#include "D3D11Define.h"

extern D3D11Interface* gD3D11Interface;

// create viewport
RALViewport* D3D11Interface::CreateViewport(void* WindowHandle, unsigned width, unsigned height, bool bIsFullscreen, RAL_FORMAT format)
{
	return new D3D11Viewport(WindowHandle, width, height, bIsFullscreen, format);
}

D3D11Viewport::D3D11Viewport(void* windowHandle, unsigned width, unsigned height, bool bIsFullscreen, RAL_FORMAT format) :
RALViewport(windowHandle, width, height, bIsFullscreen)
{
	DXGI_SWAP_CHAIN_DESC scDesc;
	memset(&scDesc, 0, sizeof(scDesc));
	scDesc.BufferDesc.Format = DXGIFORMAT_FROM_RALFORMAT(format);
	scDesc.BufferDesc.Width = width;
	scDesc.BufferDesc.Height = height;
	scDesc.BufferCount = 1;
	scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scDesc.OutputWindow = (HWND)m_wnd;
	scDesc.SampleDesc.Count = 1;
	scDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	scDesc.Windowed = !bIsFullscreen;

	gD3D11Interface->m_DXGIFactory->CreateSwapChain(gD3D11Interface->m_D3D11Device, &scDesc, &m_pSwapChain);

	// get the address of the back buffer
	ID3D11Texture2D *pBackBuffer;
	m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

	// create render target
	m_RenderTarget = new D3D11RenderTarget(pBackBuffer);
}

D3D11Viewport::~D3D11Viewport()
{
	SAFE_DELETE(m_RenderTarget);
	SAFE_RELEASE(m_pSwapChain);
}

void D3D11Viewport::Present()
{
	m_pSwapChain->Present(0, 0);
}

RALRenderTarget* D3D11Viewport::GetRenderTarget() const
{
	return m_RenderTarget;
}