#include "OGLInterface.h"
#include "OGLView.h"
#include "PlatformOGL\PlatformOGL.h"

OGLInterface* gOGLInterface = 0;

OGLInterface::OGLInterface()
{
	gOGLInterface = this;

//	m_PlatformOGLDevice = CreatePlatformOGLDevice();
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

RALShader* OGLInterface::CreateVertexShader(void)
{
	return 0;
}

RALShader* OGLInterface::CreatePixelShader(void)
{
	return 0;
}

void OGLInterface::SetVertexShader(class RALShader const *)
{
}

void OGLInterface::SetPixelShader(class RALShader const *)
{
}