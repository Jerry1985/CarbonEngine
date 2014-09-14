#ifndef CARBON_RALINTERFACE
#define CARBON_RALINTERFACE

class RALViewport;

// Rendering Abstraction Layer Interface
class RALInterface
{
public:
	RALInterface(){}
	virtual ~RALInterface(){}

#define RAL_METHOD(ReturnType,FuncName,FuncParaDecl,FuncPara) virtual ReturnType FuncName FuncParaDecl = 0;
	#include "RALMethods.h"
#undef RAL_METHOD
};

#endif