#ifndef CARBON_RALVIEW
#define CARBON_RALVIEW

#include "RALResource.h"

class	RALRenderTarget;
enum	RAL_FORMAT;

class RALView : public RALResource
{
public:
	RALView(void* WindowHandle, unsigned width, unsigned height, bool bIsFullscreen, RAL_FORMAT format);
	virtual ~RALView();

	virtual void	Resize(unsigned w, unsigned h) = 0;
	virtual void	Present() = 0;
	virtual RALRenderTarget* GetRenderTarget() const = 0;

protected:
	void*		m_wnd;
	unsigned	m_width;
	unsigned	m_height;
	bool		m_isFullScreen;
	RAL_FORMAT	m_format;
};

#endif