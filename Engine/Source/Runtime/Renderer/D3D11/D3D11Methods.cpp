#include "D3D11Interface.h"

#include <math.h>

// clear render target
void	D3D11Interface::Clear( float depth )
{
	ID3D11DeviceContext*	d3d11DeviceContext = D3D11Interface::GetD3D11DeviceContext();
	ID3D11RenderTargetView* rtView;
	d3d11DeviceContext->OMGetRenderTargets(1, &rtView,0);
	float color[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
	static float red = 1.0f;
	color[0] = sin(red);
	red += 0.001f;
	d3d11DeviceContext->ClearRenderTargetView(rtView, color);
}