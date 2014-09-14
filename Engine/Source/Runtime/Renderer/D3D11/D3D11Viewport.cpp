#include "D3D11Viewport.h"
#include "D3D11Interface.h"

D3D11Viewport::D3D11Viewport(void* windowHandle, unsigned width, unsigned height, bool bIsFullscreen) :
RALViewport(windowHandle, width, height, bIsFullscreen), m_D3D11DeviceContext(D3D11Interface::GetD3D11DeviceContext())
{
	DXGI_SWAP_CHAIN_DESC scDesc;
	memset(&scDesc, 0, sizeof(scDesc));
	scDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scDesc.BufferDesc.Width = width;
	scDesc.BufferDesc.Height = height;
	scDesc.BufferCount = 1;
	scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scDesc.OutputWindow = (HWND)m_wnd;
	scDesc.SampleDesc.Count = 1;
	scDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	scDesc.Windowed = !bIsFullscreen;

	IDXGIFactory*	DXGIFactory = D3D11Interface::GetDXGIFactory();
	HRESULT hr = DXGIFactory->CreateSwapChain(D3D11Interface::GetD3D11Device(), &scDesc, &m_pSwapChain);

	// get the address of the back buffer
	ID3D11Texture2D *pBackBuffer;
	m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

	ID3D11RenderTargetView *backbuffer;
	// use the back buffer address to create the render target
	D3D11Interface::GetD3D11Device()->CreateRenderTargetView(pBackBuffer, NULL, &backbuffer);
	pBackBuffer->Release();

	// set the render target as the back buffer
	m_D3D11DeviceContext->OMSetRenderTargets(1, &backbuffer, NULL);
}

D3D11Viewport::~D3D11Viewport()
{
	SAFE_RELEASE(m_pSwapChain);
}

void D3D11Viewport::Present()
{
	m_pSwapChain->Present(0, 0);
}