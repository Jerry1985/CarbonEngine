#include "OGLInterface.h"
#include "PlatformOGL\PlatformOGL.h"
#include "OGLView.h"

extern OGLInterface* gOGLInterface;

void OGLInterface::BeginRender(RALView const * view)
{
	OGLView const * ogl_view = dynamic_cast<OGLView const *>(view);
	MakeOGLCurrent(ogl_view->m_OglDevice);

	gOGLInterface->SetRenderTarget(0, view->GetRenderTarget());
}

void OGLInterface::EndRender(RALView const * view)
{
	OGLView const * ogl_view = dynamic_cast<OGLView const *>(view);
	SwapBuffer(ogl_view->m_OglDevice);
}