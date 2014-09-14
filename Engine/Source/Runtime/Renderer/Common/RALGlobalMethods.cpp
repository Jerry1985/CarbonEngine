#include "RALGlobalMethods.h"
#include "Renderer\D3D11\D3D11Interface.h"

RALInterface*	gRALInterface = 0;

void RALCreateInterface(RAL_TYPE raltype)
{
	if (gRALInterface != 0)
		return;

	switch (raltype)
	{
	case RAL_D3D11:
		gRALInterface = new D3D11Interface();
		break;
	case RAL_OPENGL:
		break;
	}
}

#define RAL_METHOD(ReturnType,FuncName,FuncParaDecl,FuncPara) ReturnType RAL##FuncName FuncParaDecl \
{\
	return gRALInterface->FuncName FuncPara; \
}

#include "RALMethods.h"

#undef RAL_METHOD