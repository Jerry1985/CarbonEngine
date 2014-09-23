#include "RALGlobalMethods.h"
#include "Renderer\D3D11\D3D11Interface.h"

RALInterface*	gRALInterface = 0;

void RALCreateInterface(RAL_RENDERER raltype)
{
	if (gRALInterface != 0)
		return;

	switch (raltype)
	{
	case RAL_RENDERER_D3D11:
		gRALInterface = new D3D11Interface();
		break;
	case RAL_RENDERER_OPENGL:
		break;
	}
}

#define RAL_METHOD(ReturnType,FuncName,FuncParaDecl,FuncParaDef,FuncPara) ReturnType RAL##FuncName FuncParaDef \
{\
	return gRALInterface->FuncName FuncPara; \
}

#include "RALMethods.h"

#undef RAL_METHOD