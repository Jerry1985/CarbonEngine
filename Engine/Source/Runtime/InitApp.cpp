#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "Renderer\Common\RALGlobalMethods.h"
#include "Renderer\Common\RALViewport.h"
#include "Renderer\Common\RALRenderTarget.h"
#include "Renderer\Common\RALVertexBuffer.h"
#include "Common\Math\Color.h"
#include "Renderer\Common\RALIndexBuffer.h"

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
		vp->Resize(evt.GetSize().x, evt.GetSize().y);
	}

	RALViewport*	vp;

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

	RALRenderTarget* m_rt;
};

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
	EVT_SIZE(MyFrame::OnSize)
END_EVENT_TABLE()

wxIMPLEMENT_APP_NO_THEMES(MyApp);

// Initialization
bool MyApp::OnInit()
{
	// create D3D11RAL
	RALCreateInterface(RAL_D3D11);

	frame0 = new MyFrame("Carbon Engine", wxPoint(50, 50), wxSize(1280, 720));
	frame0->Show(true);

	Connect(wxID_ANY, wxEVT_IDLE, wxIdleEventHandler(MyApp::onIdle));

	m_rt = RALCreateRenderTarget(frame0->GetSize().GetWidth(), frame0->GetSize().GetHeight(), RAL_FORMAT_R16G16_UNORM);

	RALVertexBuffer* vb = RALCreateVertexBuffer(1024, RAL_USAGE_DYNAMIC);
	vb->Map();
	vb->Unmap();

	RALIndexBuffer* ib = RALCreateIndexBuffer(1024, RAL_USAGE_DYNAMIC);
	ib->Map();
	ib->Unmap();

	return true;
}

void MyApp::onIdle(wxIdleEvent& evt)
{
	RALSetRenderTarget(0, m_rt);
	RALClear(1,Color::RED,1.0f);

	//frame0->vp->BeginRender();
	RALSetRenderTarget(0, frame0->vp->GetRenderTarget());
	RALClear(1,Color::YELLOW,1.0f);
	frame0->vp->Present();

	evt.RequestMore();
}

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
: wxFrame(NULL, wxID_ANY, title, pos, size)
{
	// Create viewport for this frame
	vp = RALCreateViewport((void*)GetHWND(), GetSize().x, GetSize().y, false, RAL_FORMAT_R8G8B8A8_UNORM );
}