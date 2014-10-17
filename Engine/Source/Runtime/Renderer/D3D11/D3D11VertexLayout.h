#ifndef CARBON_D3D11VERTEXLAYOUT
#define CARBON_D3D11VERTEXLAYOUT

#include "Renderer\Common\RALVertexLayout.h"

struct RALVertexElementLayout;
struct ID3D11InputLayout;

class D3D11VertexLayout : public RALVertexLayout
{
public:
	D3D11VertexLayout(unsigned count, const RALVertexElementDesc* layouts, const void* bcode, unsigned bcodelen);
	~D3D11VertexLayout();

	void Release();

private:
	ID3D11InputLayout*	m_inputLayout;

	friend class D3D11Interface;
};

#endif