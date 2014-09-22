#include "D3D11Interface.h"
#include "Common\Math\Color.h"
#include "D3D11RenderTarget.h"
#include "D3D11Define.h"

// clear render target
void D3D11Interface::Clear( unsigned index , Color color , float depth )
{
	_flushRT();

	if (m_validRTNum == 0)
		return;

	index = min(m_validRTNum-1, index);

	ID3D11RenderTargetView* rtView = (m_currentRT[index]) ? ((ID3D11RenderTargetView*)((D3D11RenderTarget*)m_currentRT[index])->GetRenderTargetView()) : 0;
	m_D3D11DeviceContext->ClearRenderTargetView(rtView, (float*)&color);
}

// set primitive type
void D3D11Interface::SetPrimitiveType(RAL_PRIMITIVE type)
{
	m_D3D11DeviceContext->IASetPrimitiveTopology(D3DPRIMITIVETOPOLOGY_FROM_RALPRIMITIVE(type));
}