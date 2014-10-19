#ifndef CARBON_PLATFORMOGL
#define CARBON_PLATFORMOGL

#include "Common\Platform.h"
#include "../ThirdParty/Regal/Include/Regal.h"

class RALView;

struct PlatformOGLDevice;

// create opengl platform device
PlatformOGLDevice*	CreatePlatformOGLDevice( const PlatformOGLDevice* parent = 0 , void* hwnd = 0);

// make OGL context current
void MakeOGLCurrent(PlatformOGLDevice* device);

// swap OGL buffer
void SwapBuffer(PlatformOGLDevice* device);

#endif