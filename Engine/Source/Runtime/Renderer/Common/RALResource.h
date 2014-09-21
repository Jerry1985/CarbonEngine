#ifndef	RAL_RESOURCE
#define	RAL_RESOURCE

class RALResource
{
public:
	RALResource(){}
	virtual ~RALResource(){}

	// initialize the resource
	virtual void Init() {}
	// release the resource
	virtual void Release() {}
};

#endif