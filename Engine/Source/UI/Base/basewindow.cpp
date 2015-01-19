#include "basewindow.h"
#include <qtimer.h>
#include <qevent.h>

#include "Renderer\Common\RALGlobalMethods.h"
#include "Renderer\Common\RALView.h"
#include "Renderer\Common\RALViewport.h"
#include "Renderer\Common\RALRenderTarget.h"
#include "Renderer\Common\RALVertexBuffer.h"
#include "Renderer\Common\RALIndexBuffer.h"
#include "Renderer\Common\RALShader.h"
#include "Renderer\Common\RALVertexLayout.h"
#include "Common\Container\CArray.h"
#include "Platform\PlatformFile.h"
#include "Platform\PlatformString.h"
#include "Container\CString.h"
#include "Log\Log.h"
#include "Shader\FlipViewShader.h"
#include "Container\CBitArray.h"
#include "Shader\GlobalShaders.h"

#define TWO_VIEWS 0
#define D3D11_RAL 1

RALRenderTarget* m_rt;

RALVertexBuffer*		vb = 0;
RALIndexBuffer*			ib = 0;
RALVertexLayout*		vl = 0;

RALView*				pView;

ShaderBoundState		shaderstate;

extern RAL_RENDERER	gRendererType;

BaseWindow::BaseWindow(QWidget *parent)
: QMainWindow(parent)
{
	ui.setupUi(this);

	setAttribute(Qt::WA_PaintOnScreen, true);
	setAttribute(Qt::WA_NativeWindow, true);

	QTimer* timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(update()));
	timer->start(20);

	// create D3D11RAL
	gRendererType = RAL_RENDERER_OPENGL;	 
	RALCreateInterface(gRendererType);

	// Load global shaders
	LoadGlobalShaders();

	pView = RALCreateView((void*)winId(), size().width(), size().height(), false, RAL_FORMAT_R8G8B8A8_UNORM);

#if TWO_VIEWS
	frame1 = new MyFrame("Carbon Engine", wxPoint(690, 50), wxSize(640, 720));
	frame1->Show(true);
#endif

	//	m_rt = RALCreateRenderTarget(size().width(), size().height(), RAL_FORMAT_R16G16_UNORM);

	float vertices[] =
	{
		0.0f, 0.5f, 0.5f,
		0.5f, -0.5f, 0.5f,
		-0.5f, -0.5f, 0.5f,
		0.0f, -1.5f, 0.5f,
	};
	vb = RALCreateVertexBuffer(sizeof(vertices), sizeof(float)* 3, RAL_USAGE_DYNAMIC);
	if (vb)
	{
		RALBufferDesc desc = vb->Map();
		if (desc.pData)
			memcpy(desc.pData, vertices, sizeof(vertices));
		vb->Unmap();
	}

	unsigned indices[] =
	{
		0, 1, 2,
		1, 3, 2,
	};
	ib = RALCreateIndexBuffer(sizeof(indices), sizeof(unsigned), RAL_USAGE_DYNAMIC);
	if (ib)
	{
		RALBufferDesc desc = ib->Map();
		if (desc.pData)
			memcpy(desc.pData, indices, sizeof(indices));
		ib->Unmap();
	}

	RALVertexElementDesc layoutDesc;
	layoutDesc.attributeIndex = 0;
	layoutDesc.offset = 0;
	layoutDesc.streamIndex = 0;
	layoutDesc.type = RAL_VERTEXELEMENTTYPE_FLOAT3;
	layoutDesc.useInstanceIndex = false;

	CArray<RALVertexElementDesc> layoutDescs;
	layoutDescs.Add(layoutDesc);

	FlipViewVertexShader* vs = new FlipViewVertexShader();
	FlipViewPixelShader* ps = new FlipViewPixelShader();
	vl = RALCreateVertexLayout(layoutDescs, vs->m_ShaderMetaData.m_CompiledShader);
	shaderstate.SetupGraphics(vl, vs, ps);

	// Setup the viewport
	RALViewport vp(size().width(), size().height());
	RALSetViewport(vp);
}

BaseWindow::~BaseWindow()
{

}

void BaseWindow::resizeEvent(QResizeEvent *e)
{
	if (pView)
	{
		pView->Resize(e->size().width(), e->size().height());

		RALViewport vp(size().width(), size().height());
		RALSetViewport(vp);
	}
}

void BaseWindow::paintEvent(QPaintEvent *e)
{
	RALBeginRender(pView);
	RALClear(1, Color::BLACK, 1.0f);

	shaderstate.Bind();

	RALSetPrimitiveType(RAL_PRIMITIVE_TRIANGLELIST);
	RALSetVertexBuffers(0, 1, vb);
	RALSetIndexBuffer(ib);

	RALDrawIndexed(6);

	RALEndRender(pView);

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
}