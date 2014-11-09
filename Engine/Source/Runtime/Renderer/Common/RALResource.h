#pragma once

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