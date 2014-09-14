#include "RALViewport.h"


RALViewport::RALViewport(void* WindowHandle, unsigned width, unsigned height, bool bIsFullscreen) :
m_wnd(WindowHandle), m_width(width), m_height(height), m_isFullScreen(bIsFullscreen)
{
}

RALViewport::~RALViewport()
{
}