#pragma once

#include "RALInterface.h"
#include "RALDefine.h"

void RALCreateInterface(RAL_RENDERER raltype);

#define RAL_METHOD(ReturnType,FuncName,FuncParaDecl,FuncParaDef,FuncPara) ReturnType RAL##FuncName FuncParaDecl;
#include "RALMethods.h"
#undef RAL_METHOD