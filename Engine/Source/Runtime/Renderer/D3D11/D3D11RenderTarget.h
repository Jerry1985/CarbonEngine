#ifndef CARBON_D3D11RENDERTARGET
#define CARBON_D3D11RENDERTARGET

#include "Renderer\Common\RALRenderTarget.h"

struct ID3D11Texture2D;
struct ID3D11RenderTargetView;
enum RAL_FORMAT;

class D3D11RenderTarget : public RALRenderTarget
{
public:
	D3D11RenderTarget(unsigned width, unsigned height, RAL_FORMAT format);
	~D3D11RenderTarget();

	// Release resource
	void Release();

	// get render target view
	ID3D11RenderTargetView*	GetRenderTargetView() const;

private:
	ID3D11Texture2D*			m_RTTexture;
	ID3D11RenderTargetView*		m_RTV;

	D3D11RenderTarget(ID3D11Texture2D* tex);

	friend class D3D11Viewport;
	friend class D3D11Interface;
};

#endif