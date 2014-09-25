#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "Renderer\Common\RALGlobalMethods.h"
#include "Renderer\Common\RALView.h"
#include "Renderer\Common\RALViewport.h"
#include "Renderer\Common\RALRenderTarget.h"
#include "Renderer\Common\RALVertexBuffer.h"
#include "Renderer\Common\RALIndexBuffer.h"
#include "Renderer\Common\RALShader.h"
#include "Renderer\Common\RALVertexLayout.h"

#include "../Temp/vs.h"
#include "../Temp/ps.h"

RALViewport* viewport = 0;

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

	RALVertexBuffer*		vb = 0;
	RALIndexBuffer*			ib = 0;
	RALVertexLayout*		vl = 0;

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

	RALVertexElementDesc layoutDesc;
	layoutDesc.attributeIndex = 0;
	layoutDesc.offset = 0;
	layoutDesc.streamIndex = 0;
	layoutDesc.type = RAL_VERTEXELEMENTTYPE_FLOAT3;
	layoutDesc.useInstanceIndex = false;

	vl = RALCreateVertexLayout(1, &layoutDesc, (void*)g_vs, sizeof(g_vs));

	pVS = RALCreateVertexShader();
	pPS = RALCreatePixelShader();

	pVS->CreateShader((void*)g_vs, sizeof(g_vs));
	pPS->CreateShader((void*)g_ps, sizeof(g_ps));

	// Setup the viewport
	RALViewport vp(frame0->GetSize().x, frame0->GetSize().y);
	RALSetViewport(1, &vp);

	return true;
}

void MyApp::onIdle(wxIdleEvent& evt)
{
	//frame0->vp->BeginRender();
	RALSetRenderTarget(0, frame0->view->GetRenderTarget());
	RALClear(1,Color::BLACK,1.0f);

	// Set the input layout
	RALSetVertexLayout(vl);

	RALSetPrimitiveType(RAL_PRIMITIVE_TRIANGLELIST);
	RALSetVertexBuffers(0, 1, vb);
	RALSetIndexBuffer(ib);

	RALSetVertexShader(pVS);
	RALSetPixelShader(pPS);
	RALDrawIndexed(6);

	RALPresent(frame0->view);

	evt.RequestMore();
}

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
: wxFrame(NULL, wxID_ANY, title, pos, size)
{
	// Create viewport for this frame
	view = RALCreateView((void*)GetHWND(), GetSize().x, GetSize().y, false, RAL_FORMAT_R8G8B8A8_UNORM);
}