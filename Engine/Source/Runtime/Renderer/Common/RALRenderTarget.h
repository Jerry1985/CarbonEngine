#ifndef CARBON_RALRENDERTARGET
#define	CARBON_RALRENDERTARGET

class RALRenderTarget
{
public:
	RALRenderTarget( unsigned width , unsigned height );

protected:
	unsigned	m_width;
	unsigned	m_height;
};

#endif