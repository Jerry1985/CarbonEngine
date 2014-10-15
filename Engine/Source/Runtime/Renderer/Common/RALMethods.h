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
	(unsigned index, const RALRenderTarget* rt),
	(unsigned index, const RALRenderTarget* rt),
	(index, rt)
)

RAL_METHOD(
	void,
	SetVertexBuffers,
	(unsigned startSlot, unsigned numBuffurs, const RALVertexBuffer* vbs),
	(unsigned startSlot, unsigned numBuffurs, const RALVertexBuffer* vbs),
	(startSlot, numBuffurs, vbs)
)

RAL_METHOD(
	void,
	SetIndexBuffer,
	(const RALIndexBuffer* ibs),
	(const RALIndexBuffer* ibs),
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

RAL_METHOD(
	RALShader*,
	CreateVertexShader,
	(),
	(),
	()
)

RAL_METHOD(
	RALShader*,
	CreatePixelShader,
	(),
	(),
	()
)

RAL_METHOD(
	void,
	SetVertexShader,
	(const RALShader* vs),
	(const RALShader* vs),
	(vs)
)

RAL_METHOD(
	void,
	SetPixelShader,
	(const RALShader* ps),
	(const RALShader* ps),
	(ps)
)

RAL_METHOD(
	RALVertexLayout*,
	CreateVertexLayout,
	(unsigned elementCount, const RALVertexElementDesc* descs, const void* bcode, unsigned bcodelen),
	(unsigned elementCount, const RALVertexElementDesc* descs, const void* bcode, unsigned bcodelen),
	(elementCount, descs, bcode, bcodelen)
)

RAL_METHOD(
	void,
	SetVertexLayout,
	(const RALVertexLayout* layout),
	(const RALVertexLayout* layout),
	(layout)
)

RAL_METHOD(
	void,
	BeginRender,
	(const RALView* view),
	(const RALView* view),
	(view)
)

RAL_METHOD(
	void,
	EndRender,
	(const RALView* view),
	(const RALView* view),
	(view)
)