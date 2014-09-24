#ifndef CARBON_RALSHADER
#define	CARBON_RALSHADER

#include "RALResource.h"

class RALShader : public RALResource
{
public:
	RALShader();
	virtual ~RALShader();

	// create shader from byte code
	virtual bool CreateShader(void* data, unsigned length) = 0;
};

#endif