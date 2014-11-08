#include "D3D11Interface.h"
#include "Common\Math\Color.h"
#include "Common\Math\Math.h"
#include "Renderer\Common\RALViewport.h"
#include "D3D11RenderTarget.h"
#include "D3D11Define.h"
#include "D3D11View.h"

extern D3D11Interface* gD3D11Interface;

// clear render target
void D3D11Interface::Clear( unsigned index , Color color , float depth )
{
	_flushRT();

	if (m_validRTNum == 0)
		return;

	index = Math::Min(m_validRTNum-1, index);

	ID3D11RenderTargetView* rtView = (m_currentRT[index]) ? ((ID3D11RenderTargetView*)((D3D11RenderTarget*)m_currentRT[index])->GetRenderTargetView()) : 0;
	m_D3D11DeviceContext->ClearRenderTargetView(rtView, (float*)&color);
}

// begin render
void D3D11Interface::BeginRender(RALView const * view)
{
	// Set render target
	gD3D11Interface->SetRenderTarget(0, view->GetRenderTarget());
}

// present the buffer
void D3D11Interface::EndRender(const RALView* view)
{
	const D3D11View* d3d11view = dynamic_cast<const D3D11View*>(view);
	d3d11view->m_swapChain->Present(0, 0);
}

// set view port
void D3D11Interface::SetViewport(const RALViewport& vp)
{
	D3D11_VIEWPORT viewport;

	viewport.Width = vp.w;
	viewport.Height = vp.h;
	viewport.MinDepth = vp.minZ;
	viewport.MaxDepth = vp.maxZ;
	viewport.TopLeftX = vp.x;
	viewport.TopLeftY = vp.y;
	
	m_D3D11DeviceContext->RSSetViewports(1, &viewport);
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