#include "OGLInterface.h"
#include "PlatformOGL\PlatformOGL.h"
#include "OGLView.h"
#include "OGLDefine.h"
#include "Renderer\Common\RALViewport.h"

extern OGLInterface* gOGLInterface;

void OGLInterface::BeginRender(RALView const * view)
{
	OGLView const * ogl_view = dynamic_cast<OGLView const *>(view);
	MakeOGLCurrent(ogl_view->m_OglDevice);

	gOGLInterface->SetRenderTarget(0, view->GetRenderTarget());
}

void OGLInterface::EndRender(RALView const * view)
{
	OGLView const * ogl_view = dynamic_cast<OGLView const *>(view);
	SwapBuffer(ogl_view->m_OglDevice);
}

void OGLInterface::SetPrimitiveType(RAL_PRIMITIVE type)
{
	m_primitiveType = OGLPRIMITIVE_FROM_RALPRIMITIVE(type);
}

void OGLInterface::Draw(unsigned vertNum, unsigned baseVertLoc)
{
	glDrawArrays(m_primitiveType, baseVertLoc, vertNum);
}

void OGLInterface::DrawIndexed(unsigned indexCount, unsigned startIndexLoc, unsigned baseVertLoc)
{
	unsigned int dataSize = (m_elementArrayType == GL_UNSIGNED_INT) ? 4 : 2;
	glDrawElementsBaseVertex(m_primitiveType, indexCount, m_elementArrayType, (void*)(startIndexLoc*dataSize), baseVertLoc);
}

void OGLInterface::SetViewport(const RALViewport& vp)
{
	glViewport((GLint)vp.x, (GLint)vp.y, (GLsizei)vp.w, (GLsizei)vp.h);
}
