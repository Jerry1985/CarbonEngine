#include "Common\Platform.h"
#include "../ThirdParty/Regal/Include/Regal.h"

class RALView;

struct PlatformOGLDevice;

// create opengl platform device
PlatformOGLDevice*	CreatePlatformOGLDevice( void* hwnd );

// make OGL context current
void MakeOGLCurrent(PlatformOGLDevice* device);

// swap OGL buffer
void SwapBuffer(PlatformOGLDevice* device);