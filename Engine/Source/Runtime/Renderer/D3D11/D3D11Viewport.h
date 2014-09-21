#ifndef CARBON_D3D11VIEWPORT
#define CARBON_D3D11VIEWPORT

#include "Renderer\Common\RALViewport.h"

class RALRenderTarget;
class D3D11Interface;
class D3D11RenderTarget;
struct IDXGISwapChain;
enum RAL_FORMAT;

class D3D11Viewport : public RALViewport
{
public:
	D3D11Viewport(void* WindowHandle, unsigned width, unsigned height, bool bIsFullscreen, RAL_FORMAT format);
	~D3D11Viewport();

	// Resize viewport
	void	Resize(unsigned w, unsigned h);
	// Present
	void	Present();
	// Release resources
	void	Release();

	// Get Render Target
	RALRenderTarget* GetRenderTarget() const;

private:
	IDXGISwapChain*			m_swapChain;
	D3D11RenderTarget*		m_renderTarget;
};

#endif