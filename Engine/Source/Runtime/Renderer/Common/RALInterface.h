#ifndef CARBON_RALINTERFACE
#define CARBON_RALINTERFACE

#include "Common\Math\Color.h"
#include "RALDefine.h"

class RALViewport;
class RALRenderTarget;

#define	MAX_RT_COUNT	8

// Rendering Abstraction Layer Interface
class RALInterface
{
public:
	RALInterface();
	virtual ~RALInterface(){}

#define RAL_METHOD(ReturnType,FuncName,FuncParaDecl,FuncPara) virtual ReturnType FuncName FuncParaDecl = 0;
	#include "RALMethods.h"
#undef RAL_METHOD

protected:
	// Pending Render target
	RALRenderTarget*	m_PendingRT[MAX_RT_COUNT];
	// Current Render target
	RALRenderTarget*	m_CurrentRT[MAX_RT_COUNT];
	// If the render target is changed
	bool				m_RTChanged;

	// flush render target if neccessary
	virtual void _flushRT() = 0;
	// check if the RT is changed
	void _checkRTChanged();
};

#endif