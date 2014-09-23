RAL_METHOD(
	void,
	Clear,
	(unsigned index, Color cColor, float depth),
	(unsigned index, Color cColor, float depth),
	(index, cColor, depth)
)

RAL_METHOD(
	RALView*,
	CreateView,
	(void* WindowHandle, unsigned width, unsigned height, bool bIsFullscreen, RAL_FORMAT format),
	(void* WindowHandle, unsigned width, unsigned height, bool bIsFullscreen, RAL_FORMAT format),
	(WindowHandle, width, height, bIsFullscreen, format)
)

RAL_METHOD(
	RALRenderTarget*,
	CreateRenderTarget,
	(unsigned w, unsigned h, RAL_FORMAT format),
	(unsigned w, unsigned h, RAL_FORMAT format),
	(w, h, format)
)

RAL_METHOD(
	RALVertexBuffer*,
	CreateVertexBuffer,
	(unsigned size, unsigned stride, RAL_USAGE usage, void* data = 0),
	(unsigned size, unsigned stride, RAL_USAGE usage, void* data),
	(size, stride, usage, data)
)

RAL_METHOD(
	RALIndexBuffer*,
	CreateIndexBuffer,
	(unsigned size, unsigned stride, RAL_USAGE usage, void* data = 0),
	(unsigned size, unsigned stride, RAL_USAGE usage, void* data),
	(size, stride, usage, data)
)

RAL_METHOD(
	void,
	SetRenderTarget,
	(unsigned index, RALRenderTarget* rt),
	(unsigned index, RALRenderTarget* rt),
	(index, rt)
)

RAL_METHOD(
	void,
	SetVertexBuffers,
	(unsigned startSlot, unsigned numBuffurs, RALVertexBuffer* vbs),
	(unsigned startSlot, unsigned numBuffurs, RALVertexBuffer* vbs),
	(startSlot, numBuffurs, vbs)
)

RAL_METHOD(
	void,
	SetIndexBuffer,
	(RALIndexBuffer* ibs),
	(RALIndexBuffer* ibs),
	(ibs)
)

RAL_METHOD(
	void,
	SetPrimitiveType,
	(RAL_PRIMITIVE type),
	(RAL_PRIMITIVE type),
	(type)
)

RAL_METHOD(
	void,
	Draw,
	(unsigned vertNum, unsigned baseVertLoc = 0),
	(unsigned vertNum, unsigned baseVertLoc),
	(vertNum, baseVertLoc)
)

RAL_METHOD(
	void,
	DrawIndexed,
	(unsigned indexCount, unsigned startIndexLoc=0, unsigned baseVertLoc=0),
	(unsigned indexCount, unsigned startIndexLoc, unsigned baseVertLoc),
	(indexCount,startIndexLoc,baseVertLoc)
)

RAL_METHOD(
	void,
	SetViewport,
	(unsigned vpCount, RALViewport* vps),
	(unsigned vpCount, RALViewport* vps),
	(vpCount,vps)
)