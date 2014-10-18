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
#include "../ThirdParty/Regal/Include/Regal.h"
#include "shader.hpp"

RALViewport* viewport = 0;

#define TWO_VIEWS 0
#define D3D11_RAL 0

// The main frame for rendering
class MyFrame : public wxFrame
{
	// Public method
public:
	// Constructor
	MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
	void OnSize(wxSizeEvent& evt)
	{
		if (view)
			view->Resize(evt.GetSize().x, evt.GetSize().y);
	}

	void OnCloseWindow(wxCloseEvent& evt)
	{
		wxFrame::OnCloseWindow(evt);
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
	MyFrame* frame1;

	RALRenderTarget* m_rt;

	RALVertexBuffer*		vb = 0;
	RALIndexBuffer*			ib = 0;
	RALVertexLayout*		vl = 0;

	RALShader*				pVS;
	RALShader*				pPS;

	GLuint		programID;
};

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
	EVT_SIZE(MyFrame::OnSize)
	EVT_CLOSE(MyFrame::OnCloseWindow)
END_EVENT_TABLE()

wxIMPLEMENT_APP_NO_THEMES(MyApp);

// Initialization
bool MyApp::OnInit()
{
	// create D3D11RAL
#if D3D11_RAL
	RALCreateInterface(RAL_RENDERER_D3D11);
#else
	RALCreateInterface(RAL_RENDERER_OPENGL);
#endif

	frame0 = new MyFrame("Carbon Engine", wxPoint(50, 50), wxSize(1280, 720));
	frame0->Show(true);

#if TWO_VIEWS
	frame1 = new MyFrame("Carbon Engine", wxPoint(690, 50), wxSize(640, 720));
	frame1->Show(true);
#endif

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
	ib = RALCreateIndexBuffer(sizeof(indices), sizeof(unsigned), RAL_USAGE_IMMUTABLE, indices);
	/*if (ib)
	{
		RALBufferDesc desc = ib->Map();
		if (desc.pData)
			memcpy(desc.pData, indices, sizeof(indices));
		ib->Unmap();
	}*/

	RALVertexElementDesc layoutDesc;
	layoutDesc.attributeIndex = 0;
	layoutDesc.offset = 0;
	layoutDesc.streamIndex = 0;
	layoutDesc.type = RAL_VERTEXELEMENTTYPE_FLOAT3;
	layoutDesc.useInstanceIndex = false;

	vl = RALCreateVertexLayout(1, &layoutDesc, (void*)g_vs, sizeof(g_vs));

	pVS = RALCreateVertexShader();
	pPS = RALCreatePixelShader();

	if (pVS)
		pVS->CreateShader((void*)g_vs, sizeof(g_vs));
	if (pPS)
		pPS->CreateShader((void*)g_ps, sizeof(g_ps));

	// Setup the viewport
	RALViewport vp(frame0->GetSize().x, frame0->GetSize().y);
	RALSetViewport(vp);

	// Create and compile our GLSL program from the shaders
#if D3D11_RAL == 0
	 programID = LoadShaders("E:\\CarbonEngine\\Engine\\Source\\Temp\\SimpleVertexShader.vertexshader", "E:\\CarbonEngine\\Engine\\Source\\Temp\\SimpleFragmentShader.fragmentshader");
#endif

	return true;
}

void MyApp::onIdle(wxIdleEvent& evt)
{
#if D3D11_RAL == 0
	glUseProgram(programID);
#endif

	RALBeginRender(frame0->view);
	
	RALClear(1,Color::BLACK,1.0f);
	
	// Set the input layout
	RALSetVertexLayout(vl);

	RALSetPrimitiveType(RAL_PRIMITIVE_TRIANGLELIST);
	RALSetVertexBuffers(0, 1, vb);
	RALSetIndexBuffer(ib);

	RALSetVertexShader(pVS);
	RALSetPixelShader(pPS);
	RALDrawIndexed(6);

	RALEndRender(frame0->view);

#if TWO_VIEWS
	RALBeginRender(frame1->view);

	RALClear(1, Color::RED, 1.0f);

	// Set the input layout
	RALSetVertexLayout(vl);

	RALSetPrimitiveType(RAL_PRIMITIVE_TRIANGLELIST);
	RALSetVertexBuffers(0, 1, vb);
	RALSetIndexBuffer(ib);

	RALSetVertexShader(pVS);
	RALSetPixelShader(pPS);
	RALDrawIndexed(6);

	RALEndRender(frame1->view);
#endif

	evt.RequestMore();
}

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
: wxFrame(NULL, wxID_ANY, title, pos, size)
{
	// Create viewport for this frame
	view = RALCreateView((void*)GetHWND(), GetSize().x, GetSize().y, false, RAL_FORMAT_R8G8B8A8_UNORM);
}