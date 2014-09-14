#ifndef CARBON_RALGLOBALMETHODS
#define CARBON_RALGLOBELMETHODS

#include "RALInterface.h"
#include "Common\Math\Color.h"

enum RAL_TYPE
{
	RAL_D3D11 = 0,
	RAL_OPENGL = 1,

	RAL_COUNT
};
void RALCreateInterface(RAL_TYPE raltype);

#define RAL_METHOD(ReturnType,FuncName,FuncParaDecl,FuncPara) ReturnType RAL##FuncName FuncParaDecl;
#include "RALMethods.h"
#undef RAL_METHOD

#endif