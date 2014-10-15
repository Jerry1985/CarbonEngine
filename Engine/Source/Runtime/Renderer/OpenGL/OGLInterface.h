#ifndef CARBON_OGLINTERFACE
#define CARBON_OGLINTERFACE

#include "Renderer\Common\RALInterface.h"

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
	// Opengl Platform information
	PlatformOGLDevice*	m_PlatformOGLDevice;

	// flush render target if neccessary
	virtual void _flushRT();
};

#endif