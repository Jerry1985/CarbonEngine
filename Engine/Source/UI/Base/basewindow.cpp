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
	"color = vec4(1.0 , 1.0 , 1.0 , 1.0);\n"
	"}"
};

RALRenderTarget* m_rt;

RALVertexBuffer*		vb = 0;
RALIndexBuffer*			ib = 0;
RALVertexLayout*		vl = 0;

RALView*				pView;

ShaderBoundState		shaderstate;

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
#if D3D11_RAL
	RALCreateInterface(RAL_RENDERER_D3D11);
#else
	RALCreateInterface(RAL_RENDERER_OPENGL);
#endif

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

	PlatformFileHandle* handle = PlatformFile::OpenFile(CString("E:\\CarbonEngine\\Engine\\Shader\\vs.shader"));
	uint32	data_size = handle->Size();
	char* data = new char[data_size+1];
	data[data_size] = 0;
	bool flag = handle->Read((uint8*)data, data_size);
	delete handle;

	CBitArray vs_bytecode;
	RALCompileShader(data, data_size, RAL_SHADERTYPE_VERTEXSHADER, vs_bytecode);

	delete[] data;

	handle = PlatformFile::OpenFile(CString("E:\\CarbonEngine\\Engine\\Shader\\ps.shader"));
	data_size = handle->Size();
	data = new char[data_size + 1];
	data[data_size] = 0;
	flag = handle->Read((uint8*)data, data_size);
	delete handle;

	CBitArray ps_bytecode;
	RALCompileShader(data, data_size, RAL_SHADERTYPE_PIXELSHADER, ps_bytecode);

	delete[] data;

#if !D3D11_RAL
	FlipViewVertexShader::m_ShaderMetaData.CreateShaderFromHL((uint8*)data, data_size);
	FlipViewPixelShader::m_ShaderMetaData.CreateShaderFromHL((uint8*)g_ogl_fs, sizeof(g_ogl_fs));
#else
	FlipViewVertexShader::m_ShaderMetaData.CreateShader(vs_bytecode);
	FlipViewPixelShader::m_ShaderMetaData.CreateShader(ps_bytecode);
#endif

	vl = RALCreateVertexLayout(layoutDescs, vs_bytecode);

	shaderstate.SetupGraphics(vl, new FlipViewVertexShader(), new FlipViewPixelShader());

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