#ifndef CARBON_PLATFORMFILE
#define CARBON_PLATFORMFILE

#include "Platform\Platform.h"

#ifdef CARBON_IN_WINDOWS
#include "Windows\WinFile.h"
#endif

typedef	WinFile PlatformFile;

#endif // !CARBON_PLATFORMSTRING
