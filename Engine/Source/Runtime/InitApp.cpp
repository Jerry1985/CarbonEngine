#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

// The main frame for rendering
class MyFrame : public wxFrame
{
	// Public method
public:
	// Constructor
	MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
		: wxFrame(NULL, wxID_ANY, title, pos, size){}
};

// The app
class MyApp : public wxApp
{
public:
	virtual bool OnInit();
};

wxIMPLEMENT_APP_NO_THEMES(MyApp);

// Initialization
bool MyApp::OnInit()
{
	MyFrame *frame = new MyFrame("Carbon Engine", wxPoint(50, 50), wxSize(450, 340));
	frame->Show(true);
	return true;
}