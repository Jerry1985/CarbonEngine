#include "RALView.h"

RALView::RALView(void* WindowHandle, unsigned width, unsigned height, bool bIsFullscreen, RAL_FORMAT format) :
m_wnd(WindowHandle), m_width(width), m_height(height), m_isFullScreen(bIsFullscreen), m_format(format)
{
}

RALView::~RALView()
{
}