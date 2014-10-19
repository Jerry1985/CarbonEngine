#include "qtproject.h"
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

#include "../Temp/vs.h"
#include "../Temp/ps.h"

#define TWO_VIEWS 0
#define D3D11_RAL 1

const char g_ogl_vs[] = {
	"#version 330 core\n"
	"layout(location = 0) in vec3 vertexPosition_modelspace;\n"
	"void main(){\n"
	"gl_Position.xyz = vertexPosition_modelspace;\n"
	"gl_Position.y *= -1.0;\n"
	"gl_Position.w = 1.0;\n"
	"}"
};

const char g_ogl_fs[] = {
	"#version 330 core\n"
	"out vec4 color;\n"
	"void main()\n"
	"{\n"
	"color = vec4(1.0 , 1.0 , 0.0 , 1.0);\n"
	"}"
};

RALRenderTarget* m_rt;

RALVertexBuffer*		vb = 0;
RALIndexBuffer*			ib = 0;
RALVertexLayout*		vl = 0;

RALShader*				pVS;
RALShader*				pPS;
RALShaderBoundState*	pShaders;
RALView*				pView;

QTProject::QTProject(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	setAttribute(Qt::WA_PaintOnScreen, true);
	setAttribute(Qt::WA_NativeWindow, true);

	QTimer* timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(update()));

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
	vb = RALCreateVertexBuffer(sizeof(vertices), sizeof(float)* 3, RAL_USAGE_IMMUTABLE, vertices);

	unsigned indices[] =
	{
		0, 1, 2,
		1, 3, 2,
	};
	ib = RALCreateIndexBuffer(sizeof(indices), sizeof(unsigned), RAL_USAGE_IMMUTABLE, indices);
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

	vl = RALCreateVertexLayout(1, &layoutDesc, (void*)g_vs, sizeof(g_vs));

	pVS = RALCreateVertexShader();
	pPS = RALCreatePixelShader();

#if D3D11_RAL
	if (pVS)
		pVS->CreateShader((void*)g_vs, sizeof(g_vs));
	if (pPS)
		pPS->CreateShader((void*)g_ps, sizeof(g_ps));
#else
	if (pVS)
		pVS->CreateShader((void*)g_ogl_vs, sizeof(g_ogl_vs));
	if (pPS)
		pPS->CreateShader((void*)g_ogl_fs, sizeof(g_ogl_fs));
#endif

	pShaders = RALCreateShaderBoundState(vl, pVS, pPS);

	// Setup the viewport
	RALViewport vp(size().width(), size().height());
	RALSetViewport(vp);
}

QTProject::~QTProject()
{

}

void QTProject::resizeEvent(QResizeEvent *e)
{
	if (pView)
		pView->Resize(e->size().width(),e->size().height());
}

void QTProject::paintEvent(QPaintEvent *e)
{
	RALBeginRender(pView);

	static float a = 0.0f;
	if (a > 1.0f)
		a = 0.0f;
	a += 0.1f;
	Color c(a, a, a);
	RALClear(1, c, 1.0f);
	
	RALSetShaderBoundState(pShaders);

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