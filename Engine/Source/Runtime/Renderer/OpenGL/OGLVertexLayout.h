#ifndef CARBON_OGLVERTEXLAYOUT
#define CARBON_OGLVERTEXLAYOUT

#include "Renderer\Common\RALVertexLayout.h"
#include "Renderer\Common\RALDefine.h"

struct RALVertexElementLayout;

struct OGLVertexElementLayout
{
	unsigned	m_index;		// index of the element
	unsigned	m_size;			// size of the element
	unsigned	m_type;			// type of the element
	unsigned	m_stride;		// stride between elements
	unsigned	m_offset;		// array buffer offset
};

class OGLVertexLayout : public RALVertexLayout
{
public:
	OGLVertexLayout(unsigned count, const RALVertexElementDesc* layouts, const void* bcode, unsigned bcodelen);
	~OGLVertexLayout();

	void Release();

private:
	OGLVertexElementLayout*	m_elements;
	unsigned				m_elementCount;

	friend class OGLInterface;
};

#endif
