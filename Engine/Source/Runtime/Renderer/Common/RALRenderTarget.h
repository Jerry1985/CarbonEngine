#ifndef CARBON_RALRENDERTARGET
#define	CARBON_RALRENDERTARGET

class RALRenderTarget
{
public:
	RALRenderTarget();

	virtual void Release() = 0;

protected:
	unsigned	m_width;
	unsigned	m_height;
};

#endif