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
RALViewport(windowHandle, width, height, bIsFullscreen, format)
{
	m_swapChain = 0;
	m_renderTarget = 0;
}

D3D11Viewport::~D3D11Viewport()
{
	Release();
}

void D3D11Viewport::Present()
{
	m_swapChain->Present(0, 0);
}

RALRenderTarget* D3D11Viewport::GetRenderTarget() const
{
	return m_renderTarget;
}

void D3D11Viewport::Resize(unsigned w, unsigned h)
{
	// release resource first
	Release();

	DXGI_SWAP_CHAIN_DESC scDesc;
	memset(&scDesc, 0, sizeof(scDesc));
	scDesc.BufferDesc.Format = DXGIFORMAT_FROM_RALFORMAT(m_format);
	scDesc.BufferDesc.Width = w;
	scDesc.BufferDesc.Height = h;
	scDesc.BufferCount = 1;
	scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scDesc.OutputWindow = (HWND)m_wnd;
	scDesc.SampleDesc.Count = 1;
	scDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	scDesc.Windowed = !m_isFullScreen;

	gD3D11Interface->m_DXGIFactory->CreateSwapChain(gD3D11Interface->m_D3D11Device, &scDesc, &m_swapChain);

	// get the address of the back buffer
	ID3D11Texture2D *pBackBuffer;
	m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

	// create render target
	m_renderTarget = new D3D11RenderTarget(pBackBuffer);
}

// Release resources
void D3D11Viewport::Release()
{
	SAFE_DELETE(m_renderTarget);
	SAFE_RELEASE(m_swapChain);
}