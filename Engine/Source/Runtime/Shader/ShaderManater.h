#pragma once

#include "Utility\Singleton.h"

class ShaderManager : public Singleton<ShaderManager>
{
public:
	ShaderManager();
	~ShaderManager();
};