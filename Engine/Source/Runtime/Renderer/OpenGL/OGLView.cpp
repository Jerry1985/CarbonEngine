#include "OGLView.h"
#include "OGLInterface.h"
#include "PlatformOGL\PlatformOGL.h"

extern OGLInterface gOGLInterface;

// create viewport
RALView* OGLInterface::CreateView(void* WindowHandle, unsigned width, unsigned height, bool bIsFullscreen, RAL_FORMAT format)
{
	return new OGLView(m_OglDevice, WindowHandle, width, height, bIsFullscreen, format);
}

OGLView::OGLView(const PlatformOGLDevice* parent, void* windowHandle, unsigned width, unsigned height, bool bIsFullscreen, RAL_FORMAT format) :
RALView(windowHandle, width, height, bIsFullscreen, format)
{
	m_OglDevice = CreatePlatformOGLDevice(parent, windowHandle);
}

OGLView::~OGLView()
{
}

RALRenderTarget* OGLView::GetRenderTarget() const
{
	return 0;
}

void OGLView::Resize(unsigned w, unsigned h)
{
}

// Release resources
void OGLView::Release()
{
}