#ifndef CARBON_RALINTERFACE
#define CARBON_RALINTERFACE

#include "utility/Singleton.h"

// Rendering Abstraction Layer Interface
class RALInterface : public Singleton<RALInterface>
{
public:
	~RALInterface(){}

protected:
	// the interface should be a singleton
	RALInterface(){}

	friend class Singleton<RALInterface>;
};

// some use full global functions
RALInterface*	GGetRALInterfacePtr()
{
	return RALInterface::GetSingletonPtr();
}
RALInterface&	GGetRALInterfaceRef()
{
	return RALInterface::GetSingleton();
}

#endif