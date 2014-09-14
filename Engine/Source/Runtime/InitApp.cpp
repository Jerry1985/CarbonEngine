#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "Renderer\Common\RALGlobalMethods.h"
#include "Renderer\Common\\RALViewport.h"

RALViewport* viewport = 0;

// The main frame for rendering
class MyFrame : public wxFrame
{
	// Public method
public:
	// Constructor
	MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
};

// The app
class MyApp : public wxApp
{
public:
	virtual bool OnInit();
	void onIdle(wxIdleEvent& evt);
};

wxIMPLEMENT_APP_NO_THEMES(MyApp);

// Initialization
bool MyApp::OnInit()
{
	// create D3D11RAL
	RALCreateInterface(RAL_D3D11);

	MyFrame *frame = new MyFrame("Carbon Engine", wxPoint(50, 50), wxSize(1280, 720));
	frame->Show(true);
	
	Connect(wxID_ANY, wxEVT_IDLE, wxIdleEventHandler(MyApp::onIdle));

	return true;
}

void MyApp::onIdle(wxIdleEvent& evt)
{
	RALClear(1.0f);

	viewport->Present();

	evt.RequestMore();
}

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
: wxFrame(NULL, wxID_ANY, title, pos, size)
{
	// Create viewport for this frame
	viewport = RALCreateViewport((void*)GetHWND(), GetSize().x, GetSize().y, false);
}