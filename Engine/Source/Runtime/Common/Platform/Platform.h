#pragma once

#include "DataType.h"

#if defined(_WIN32) || defined(_WIN64)
	#include "Windows/WinPlatform.h"
#elif defined(__linux__)
#elif defined(__APPLE__)
#endif