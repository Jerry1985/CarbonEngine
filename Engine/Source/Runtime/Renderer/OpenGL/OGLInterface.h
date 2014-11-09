#pragma once

#include "Renderer\Common\RALInterface.h"
#include "../ThirdParty/Regal/Include/Regal.h"

struct PlatformOGLDevice;

class OGLInterface : public RALInterface
{
public:
	OGLInterface();
	virtual ~OGLInterface();

#define RAL_METHOD(ReturnType,FuncName,FuncParaDecl,FuncParaDef,FuncPara) virtual ReturnType FuncName FuncParaDecl;
#include "Renderer/Common/RALMethods.h"
#undef RAL_METHOD

private:
	// Primitive type
	GLuint		m_primitiveType;
	// Element array buffer type
	GLuint		m_elementArrayType;

	// Parent Opengl device
	PlatformOGLDevice*	m_OglDevice;

	// flush render target if neccessary
	virtual void _flushRT();

	void _setVertexLayout(const RALVertexLayout* vl);
};