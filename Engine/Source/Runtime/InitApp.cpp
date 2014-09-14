#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "Renderer\Common\RALGlobalMethods.h"
#include "Renderer\Common\RALViewport.h"
#include "Common\Math\Color.h"

RALViewport* viewport = 0;

// The main frame for rendering
class MyFrame : public wxFrame
{
	// Public method
public:
	// Constructor
	MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size, MyFrame** ppFrame);

	RALViewport*	vp;
	MyFrame**		ppFrame;
};

// The app
class MyApp : public wxApp
{
public:
	virtual bool OnInit();
	void onIdle(wxIdleEvent& evt);

private:
	MyFrame* frame0;
	MyFrame* frame1;
};

wxIMPLEMENT_APP_NO_THEMES(MyApp);

// Initialization
bool MyApp::OnInit()
{
	// create D3D11RAL
	RALCreateInterface(RAL_D3D11);

	frame0 = new MyFrame("Carbon Engine", wxPoint(50, 50), wxSize(1280, 720), &frame0);
	frame0->Show(true);

	Connect(wxID_ANY, wxEVT_IDLE, wxIdleEventHandler(MyApp::onIdle));

	return true;
}

void MyApp::onIdle(wxIdleEvent& evt)
{
	frame0->vp->BeginRender();
	RALClear(Color::YELLOW,1.0f);
	frame0->vp->Present();

	evt.RequestMore();
}

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size, MyFrame** _ppFrame)
: wxFrame(NULL, wxID_ANY, title, pos, size)
{
	// Create viewport for this frame
	vp = RALCreateViewport((void*)GetHWND(), GetSize().x, GetSize().y, false);

	ppFrame = _ppFrame;
}