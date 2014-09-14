RAL_METHOD(
	void ,
	Clear,
	( Color cColor , float depth ),
	( cColor , depth )
)

RAL_METHOD(
	RALViewport*,
	CreateViewport,
	(void* WindowHandle, unsigned width, unsigned height, bool bIsFullscreen),
	(WindowHandle, width, height, bIsFullscreen )
)

RAL_METHOD(
	void,
	SetRenderTarget,
	(unsigned index, RALRenderTarget* rt),
	(index,rt)
)