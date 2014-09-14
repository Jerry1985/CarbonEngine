#ifndef CARBON_RALVIEWPORT
#define CARBON_RALVIEWPORT

class RALViewport
{
public:
	RALViewport(void* WindowHandle, unsigned width, unsigned height, bool bIsFullscreen);
	virtual ~RALViewport();

	virtual void	Present() = 0;

protected:
	void*		m_wnd;
	unsigned	m_width;
	unsigned	m_height;
	bool		m_isFullScreen;
};

#endif