RAL_METHOD(
	void ,
	Clear,
	( Color cColor , float depth ),
	( cColor , depth )
)

RAL_METHOD(
	RALViewport*,
	CreateViewport,
	(void* WindowHandle, unsigned width, unsigned height, bool bIsFullscreen, RAL_FORMAT format),
	(WindowHandle, width, height, bIsFullscreen, format)
)

RAL_METHOD(
	RALRenderTarget*,
	CreateRenderTarget,
	(unsigned w, unsigned h, RAL_FORMAT format),
	(w, h, format)
)

RAL_METHOD(
	void,
	SetRenderTarget,
	(unsigned index, RALRenderTarget* rt),
	(index,rt)
)