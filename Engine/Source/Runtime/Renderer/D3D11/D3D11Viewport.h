#ifndef CARBON_D3D11VIEWPORT
#define CARBON_D3D11VIEWPORT

#include "Renderer\Common\RALViewport.h"

class D3D11Interface;
struct IDXGISwapChain;
struct ID3D11DeviceContext;
struct ID3D11RenderTargetView;

class D3D11Viewport : public RALViewport
{
public:
	D3D11Viewport(void* WindowHandle, unsigned width, unsigned height, bool bIsFullscreen);
	~D3D11Viewport();

	void	BeginRender();
	void	Present();

private:
	IDXGISwapChain*			m_pSwapChain;
	ID3D11RenderTargetView*	m_pRenderTargetView;
};

#endif