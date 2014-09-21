#include "D3D11Interface.h"
#include "D3D11Viewport.h"
#include "D3D11RenderTarget.h"

D3D11Interface* gD3D11Interface = 0;

D3D11Interface::D3D11Interface()
{
	gD3D11Interface = this;

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

// flush render target if neccessary
void D3D11Interface::_flushRT()
{
	if (m_rtChanged)
	{
		ID3D11RenderTargetView* rt[MAX_RT_COUNT];

		m_validRTNum = 0;
		for (int i = 0; i < MAX_RT_COUNT; ++i)
		{
			if (m_pendingRT[i] != 0)
				m_validRTNum = i + 1;

			D3D11RenderTarget* d11rt = (D3D11RenderTarget*)(m_pendingRT[i]);
			rt[i] = (d11rt) ? d11rt->m_RTV : 0;
		}
		m_D3D11DeviceContext->OMSetRenderTargets(m_validRTNum, rt, 0);

		for (int i = 0; i < MAX_RT_COUNT; ++i)
			m_currentRT[i] = m_pendingRT[i];
	}
}