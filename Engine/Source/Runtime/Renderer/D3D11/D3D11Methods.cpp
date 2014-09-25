#include "D3D11Interface.h"
#include "Common\Math\Color.h"
#include "Renderer\Common\RALViewport.h"
#include "D3D11RenderTarget.h"
#include "D3D11Define.h"
#include "D3D11View.h"

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

// present the buffer
void D3D11Interface::Present(const RALView* view)
{
	const D3D11View* d3d11view = dynamic_cast<const D3D11View*>(view);
	d3d11view->m_swapChain->Present(0, 0);
}

// set view port
void D3D11Interface::SetViewport(unsigned vpCount, RALViewport* vps)
{
	D3D11_VIEWPORT viewports[MAX_VP_COUNT];

	vpCount = min(vpCount, MAX_VP_COUNT);

	for (unsigned i = 0; i < vpCount; ++i)
	{
		viewports[i].Width = vps[i].w;
		viewports[i].Height = vps[i].h;
		viewports[i].MinDepth = vps[i].minZ;
		viewports[i].MaxDepth = vps[i].maxZ;
		viewports[i].TopLeftX = vps[i].x;
		viewports[i].TopLeftY = vps[i].y;
	}
	
	m_D3D11DeviceContext->RSSetViewports(vpCount, viewports);
}

// set primitive type
void D3D11Interface::SetPrimitiveType(RAL_PRIMITIVE type)
{
	m_D3D11DeviceContext->IASetPrimitiveTopology(D3DPRIMITIVETOPOLOGY_FROM_RALPRIMITIVE(type));
}

// draw primitives without index buffer
void D3D11Interface::Draw(unsigned vertNum, unsigned baseVertLoc)
{
	m_D3D11DeviceContext->Draw(vertNum, baseVertLoc);
}

// draw primitives with index buffer
void D3D11Interface::DrawIndexed(unsigned indexCount, unsigned startIndexLoc, unsigned baseVertLoc)
{
	m_D3D11DeviceContext->DrawIndexed(indexCount, startIndexLoc, baseVertLoc);
}