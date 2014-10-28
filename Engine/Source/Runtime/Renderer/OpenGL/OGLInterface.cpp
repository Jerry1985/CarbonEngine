#include "OGLInterface.h"
#include "OGLView.h"
#include "PlatformOGL\PlatformOGL.h"
#include "OGLVertexLayout.h"
#include "Renderer\Common\RAL.h"

OGLInterface* gOGLInterface = 0;

OGLInterface::OGLInterface()
{
	gOGLInterface = this;

	m_OglDevice = CreatePlatformOGLDevice();

	// RAL interface is initialize
	gRALInitialized = true;
}

OGLInterface::~OGLInterface()
{
}

// flush render target if neccessary
void OGLInterface::_flushRT()
{
}

// to be deleted
void OGLInterface::Clear(unsigned index, Color color, float depth)
{
	glClearColor(color.r, color.g, color.b, color.a);
	glClear(GL_COLOR_BUFFER_BIT);
}

RALRenderTarget* OGLInterface::CreateRenderTarget(unsigned int, unsigned int, RAL_FORMAT)
{
	return 0;
}

void OGLInterface::SetRenderTarget(unsigned int, RALRenderTarget const *)
{
}

void OGLInterface::_setVertexLayout(const RALVertexLayout* vl)
{
	const OGLVertexLayout* ogl_layout = dynamic_cast<const OGLVertexLayout*>(vl);

	int i = 0;
	for (; i < ogl_layout->m_elementCount; ++i)
	{
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(
			ogl_layout->m_elements[i].m_index,          // attribute 0. No particular reason for 0, but must match the layout in the shader.
			ogl_layout->m_elements[i].m_size,           // size
			ogl_layout->m_elements[i].m_type,           // type
			GL_FALSE,									// normalized?
			0,											// stride
			(void*)0									// array buffer offset
			);
	}
	while (i < MAX_VERTEX_ELEMENT_COUNT)
	{
		glDisableVertexAttribArray(i);
		++i;
	}
}