#ifndef CARBON_D3D11VIEWPORT
#define CARBON_D3D11VIEWPORT

#include "Renderer\Common\RALViewport.h"

class D3D11Interface;
struct IDXGISwapChain;
struct ID3D11DeviceContext;

class D3D11Viewport : public RALViewport
{
public:
	D3D11Viewport(void* WindowHandle, unsigned width, unsigned height, bool bIsFullscreen);
	~D3D11Viewport();

	void Present();
private:

	D3D11Interface*			m_pD3D11Interface;

	ID3D11DeviceContext*	m_D3D11DeviceContext;
	IDXGISwapChain*			m_pSwapChain;
};

#endif