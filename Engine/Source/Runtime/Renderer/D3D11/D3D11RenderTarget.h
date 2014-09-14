#ifndef CARBON_D3D11RENDERTARGET
#define CARBON_D3D11RENDERTARGET

#include "Renderer\Common\RALRenderTarget.h"

class D3D11RenderTarget : public RALRenderTarget
{
public:
	D3D11RenderTarget(unsigned width, unsigned height);
	~D3D11RenderTarget();

private:

};

#endif