#include "D3D11Interface.h"
#include "Common\Math\Color.h"

// clear render target
void D3D11Interface::Clear( Color color , float depth )
{
	_flushRT();

	ID3D11RenderTargetView* rtView;
	m_D3D11DeviceContext->OMGetRenderTargets(1, &rtView, 0);
	m_D3D11DeviceContext->ClearRenderTargetView(rtView, (float*)&color);
}