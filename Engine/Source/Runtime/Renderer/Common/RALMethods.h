RAL_METHOD(
	void ,
	Clear,
	( float depth ),
	( depth )
)

RAL_METHOD(
	RALViewport*,
	CreateViewport,
	(void* WindowHandle, unsigned width, unsigned height, bool bIsFullscreen),
	(WindowHandle, width, height, bIsFullscreen )
)