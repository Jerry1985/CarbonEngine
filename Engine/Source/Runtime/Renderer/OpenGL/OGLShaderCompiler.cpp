#include "OGLInterface.h"
#include "Container\CBitArray.h"

// Since OpenGL binary shader cache is hardware dependent, we do use naive shader code as shader cache. Just like the way Unreal Engine3 works.
bool OGLInterface::CompileShader(const uint8* source, uint32 len, uint8 shaderType, CBitArray& bytecode)
{
	bytecode.Allocate(len);
	bytecode.Copy((uint8*)source, len);

	return true;
}