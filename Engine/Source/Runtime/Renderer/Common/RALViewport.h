#ifndef CARBON_RALVIEWPORT
#define CARBON_RALVIEWPORT

#include "RALResource.h"

class	RALRenderTarget;
enum	RAL_FORMAT;

class RALViewport : public RALResource
{
public:
	RALViewport(void* WindowHandle, unsigned width, unsigned height, bool bIsFullscreen, RAL_FORMAT format);
	virtual ~RALViewport();

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