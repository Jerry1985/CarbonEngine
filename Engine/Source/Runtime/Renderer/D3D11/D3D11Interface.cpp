#include "D3D11Interface.h"
#include "D3D11Viewport.h"

D3D11Interface*	D3D11Interface::m_D3D11Interface = 0;

D3D11Interface::D3D11Interface()
{
	m_D3D11Interface = this;

	_initDevice();
}

D3D11Interface::~D3D11Interface()
{
	_releaseDevice();
}

// initialize direct3d 11 device
bool D3D11Interface::_initDevice()
{
	D3D_FEATURE_LEVEL RequestedFeatureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
	};

	HRESULT hr = D3D11CreateDevice(	NULL,							// Default adapter
									D3D_DRIVER_TYPE_HARDWARE,		// hardware driver
									NULL,
									NULL,							// No flag yet
									RequestedFeatureLevels,			// deseried feature level
									1,								// number of feature levels
									D3D11_SDK_VERSION,
									&m_D3D11Device,					// d3d11 device
									&m_FeatureLevel,				// the feature level of the device
									&m_D3D11DeviceContext			// device context for d3d11
									);

	IDXGIDevice* DXGIDevice;
	HRESULT Hr = m_D3D11Device->QueryInterface(__uuidof(IDXGIDevice), (void**)&DXGIDevice);

	IDXGIAdapter* DXGIAdapter;
	Hr = DXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void **)&DXGIAdapter);

	DXGIAdapter->GetParent(__uuidof(IDXGIFactory), (void **)&m_DXGIFactory);

	return hr == S_OK;
}

// release device
void D3D11Interface::_releaseDevice()
{
	SAFE_RELEASE(m_D3D11DeviceContext);
	SAFE_RELEASE(m_D3D11Device);
}

// create viewport
RALViewport* D3D11Interface::CreateViewport(void* WindowHandle, unsigned width, unsigned height, bool bIsFullscreen)
{
	return new D3D11Viewport( WindowHandle, width, height, bIsFullscreen );
}