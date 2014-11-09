#pragma once

#include "Renderer\Common\RALView.h"

class RALRenderTarget;
class D3D11Interface;
class D3D11RenderTarget;
struct IDXGISwapChain;
enum RAL_FORMAT;

class D3D11View : public RALView
{
public:
	D3D11View(void* WindowHandle, unsigned width, unsigned height, bool bIsFullscreen, RAL_FORMAT format);
	~D3D11View();

	// Resize viewport
	void	Resize(unsigned w, unsigned h);
	// Release resources
	void	Release();

	// Get Render Target
	RALRenderTarget* GetRenderTarget() const;

private:
	IDXGISwapChain*			m_swapChain;
	D3D11RenderTarget*		m_renderTarget;

	friend class D3D11Interface;
};