#include "OGLVertexLayout.h"
#include "OGLInterface.h"
#include "OGLDefine.h"

extern OGLInterface* gOGLInterface;

RALVertexLayout* OGLInterface::CreateVertexLayout(unsigned elementCount, const RALVertexElementDesc* descs, const void* bcode, unsigned bcodelen)
{
	return new OGLVertexLayout(elementCount, descs, bcode, bcodelen);
}

OGLVertexLayout::OGLVertexLayout(unsigned count, const RALVertexElementDesc* layouts, const void* bcode, unsigned bcodelen) :m_elements(0), m_elementCount(0)
{
	if (count <= 0 || count >= MAX_VERTEX_ELEMENT_COUNT)
		return;

	m_elementCount = count;
	m_elements = new OGLVertexElementLayout[m_elementCount];
	
	for (unsigned i = 0; i < m_elementCount; ++i)
	{
		m_elements[i].m_index = layouts[i].attributeIndex;
		m_elements[i].m_size = OGLVERTEXELEMENTTYPECOUNT_FROM_VERTEXELEMENTTYPE(layouts[i].type);
		m_elements[i].m_type = OGLVERTEXELEMENTTYPE_FROM_VERTEXELEMENTTYPE(layouts[i].type);
	}
}

OGLVertexLayout::~OGLVertexLayout()
{
	Release();
}

void OGLVertexLayout::Release()
{
	delete[] m_elements;
}