#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "Renderer\D3D11\D3D11Interface.h"
#include "Renderer\Common\RALGlobalMethods.h"
#include "Renderer\Common\RALView.h"
#include "Renderer\Common\RALViewport.h"
#include "Renderer\Common\RALRenderTarget.h"
#include "Renderer\Common\RALVertexBuffer.h"
#include "Renderer\Common\RALIndexBuffer.h"
#include "Renderer\Common\RALShader.h"

#include "../Temp/vs.h"
#include "../Temp/ps.h"

RALViewport* viewport = 0;

// temporary
extern D3D11Interface* gD3D11Interface;

// The main frame for rendering
class MyFrame : public wxFrame
{
	// Public method
public:
	// Constructor
	MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
	void OnSize(wxSizeEvent& evt)
	{
		view->Resize(evt.GetSize().x, evt.GetSize().y);
	}

	RALView*	view;

	DECLARE_EVENT_TABLE()
};

// The app
class MyApp : public wxApp
{
public:
	virtual bool OnInit();
	void onIdle(wxIdleEvent& evt);

private:
	MyFrame* frame0;
//	MyFrame* frame1;

	RALRenderTarget* m_rt;

	ID3D11InputLayout*      pVertexLayout = NULL;
	RALVertexBuffer*		vb = 0;
	RALIndexBuffer*			ib = 0;

	RALShader*				pVS;
	RALShader*				pPS;
};

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
	EVT_SIZE(MyFrame::OnSize)
END_EVENT_TABLE()

wxIMPLEMENT_APP_NO_THEMES(MyApp);

// Initialization
bool MyApp::OnInit()
{
	// create D3D11RAL
	RALCreateInterface(RAL_RENDERER_D3D11);

	frame0 = new MyFrame("Carbon Engine", wxPoint(50, 50), wxSize(1280, 720));
	frame0->Show(true);

//	frame1 = new MyFrame("Carbon Engine", wxPoint(690, 50), wxSize(640, 720));
//	frame1->Show(true);

	Connect(wxID_ANY, wxEVT_IDLE, wxIdleEventHandler(MyApp::onIdle));

	m_rt = RALCreateRenderTarget(frame0->GetSize().GetWidth(), frame0->GetSize().GetHeight(), RAL_FORMAT_R16G16_UNORM);

	float vertices[] =
	{
		0.0f, 0.5f, 0.5f,
		0.5f, -0.5f, 0.5f,
		-0.5f, -0.5f, 0.5f,
		0.0f, -1.5f, 0.5f,
	};
	vb = RALCreateVertexBuffer(sizeof(vertices), sizeof(float)* 3, RAL_USAGE_IMMUTABLE, vertices);

	unsigned indices[] =
	{
		0 , 1 , 2,
		1 , 3 , 2,
	};
	ib = RALCreateIndexBuffer(sizeof(indices), sizeof(unsigned), RAL_USAGE_DYNAMIC);
	RALBufferDesc desc = ib->Map();
	if (desc.pData)
		memcpy(desc.pData, indices, sizeof(indices));
	ib->Unmap();

	// Define the input layout
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = ARRAYSIZE(layout);

	// Create the input layout
	gD3D11Interface->m_D3D11Device->CreateInputLayout(layout, numElements, g_vs, sizeof(g_vs), &pVertexLayout);

	pVS = RALCreateVertexShader();
	pPS = RALCreatePixelShader();

	pVS->CreateShader((void*)g_vs, sizeof(g_vs));
	pPS->CreateShader((void*)g_ps, sizeof(g_ps));

	return true;
}

void MyApp::onIdle(wxIdleEvent& evt)
{
	// Setup the viewport
	RALViewport vp(frame0->GetSize().x, frame0->GetSize().y);
	RALSetViewport(1, &vp);
	/*
	RALSetRenderTarget(0, frame1->view->GetRenderTarget());
	RALClear(1,Color::RED,1.0f);

	// Set the input layout
	gD3D11Interface->m_D3D11DeviceContext->IASetInputLayout(pVertexLayout);

	RALSetPrimitiveType(RAL_PRIMITIVE_TRIANGLELIST);
	RALSetVertexBuffers(0, 1, vb);
	RALSetIndexBuffer(ib);

	gD3D11Interface->m_D3D11DeviceContext->VSSetShader(vs, NULL, 0);
	gD3D11Interface->m_D3D11DeviceContext->PSSetShader(ps, NULL, 0);
	RALDraw(3);

	frame1->view->Present();
	*/
	//frame0->vp->BeginRender();
	RALSetRenderTarget(0, frame0->view->GetRenderTarget());
	RALClear(1,Color::BLACK,1.0f);

	// Set the input layout
	gD3D11Interface->m_D3D11DeviceContext->IASetInputLayout(pVertexLayout);

	RALSetPrimitiveType(RAL_PRIMITIVE_TRIANGLELIST);
	RALSetVertexBuffers(0, 1, vb);
	RALSetIndexBuffer(ib);

	RALSetVertexShader(pVS);
	RALSetPixelShader(pPS);

	RALDrawIndexed(6);

	frame0->view->Present();

	evt.RequestMore();
}

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
: wxFrame(NULL, wxID_ANY, title, pos, size)
{
	// Create viewport for this frame
	view = RALCreateView((void*)GetHWND(), GetSize().x, GetSize().y, false, RAL_FORMAT_R8G8B8A8_UNORM);
}