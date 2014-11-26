#pragma once

#include "Renderer\Common\RALVertexLayout.h"

template<class T>
class CArray;
class CBitArray;

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
	OGLVertexLayout(const CArray<RALVertexElementDesc>& layouts, const CBitArray& bytecode);
	~OGLVertexLayout();

	void Release();

private:
	OGLVertexElementLayout*	m_elements;
	int						m_elementCount;

	friend class OGLInterface;
};
