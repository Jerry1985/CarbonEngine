#include "D3D11RenderTarget.h"
#include "D3D11Interface.h"

void D3D11Interface::SetRenderTarget( unsigned index , RALRenderTarget* rt )
{
	if (index >= MAX_RT_COUNT)
		return;

	m_PendingRT[index] = rt;

	// check if render target is changed
	_checkRTChanged();
}

D3D11RenderTarget::D3D11RenderTarget(unsigned width, unsigned height):
	RALRenderTarget(width,height)
{

}

D3D11RenderTarget::~D3D11RenderTarget()
{
}