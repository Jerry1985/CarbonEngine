#ifndef CARBON_OGLDEFINE
#define CARBON_OGLDEFINE

#include "Renderer\Common\RALDefine.h"
#include "../ThirdParty/Regal/Include/Regal.h"

GLuint OGLPRIMITIVE_FROM_RALPRIMITIVE(RAL_PRIMITIVE type);
GLuint OGLUSAGE_FROM_RALUSAGE(RAL_USAGE ral_usage);

#endif