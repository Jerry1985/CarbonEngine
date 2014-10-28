#include "D3D11Interface.h"
#include "D3D11RenderTarget.h"
#include "D3D11Shader.h"
#include "D3D11VertexLayout.h"
#include "Renderer\Common\RAL.h"

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
	// create dxgi factory
	CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&m_DXGIFactory);

	IDXGIAdapter*adapter = 0;
	if (m_DXGIFactory->EnumAdapters(0, &adapter) != DXGI_ERROR_NOT_FOUND)
	{
		DXGI_ADAPTER_DESC AdapterDesc;
		if( adapter->GetDesc(&AdapterDesc) == S_OK )
		{
			// adapter information

		}
	}

	D3D_FEATURE_LEVEL RequestedFeatureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
	};

	HRESULT hr = D3D11CreateDevice(	adapter,						// Default adapter
									D3D_DRIVER_TYPE_UNKNOWN,		// hardware driver
									NULL,
									0,								// No flag yet
									RequestedFeatureLevels,			// deseried feature level
									1,								// number of feature levels
									D3D11_SDK_VERSION,
									&m_D3D11Device,					// d3d11 device
									&m_FeatureLevel,				// the feature level of the device
									&m_D3D11DeviceContext			// device context for d3d11
									);

	// RAL interface is initialize
	gRALInitialized = true;

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

void D3D11Interface::_setVertexLayout(const RALVertexLayout* vl)
{
	const D3D11VertexLayout* d3d11_layout = dynamic_cast<const D3D11VertexLayout*>(vl);
	gD3D11Interface->m_D3D11DeviceContext->IASetInputLayout(d3d11_layout->m_inputLayout);
}

void D3D11Interface::_setVertexShader(const RALShader* vs)
{
	const D3D11VertexShader* shader = dynamic_cast<const D3D11VertexShader*>(vs);
	if (shader)
		m_D3D11DeviceContext->VSSetShader(shader->m_shader, 0, 0);
}

void D3D11Interface::_setPixelShader(const RALShader* ps)
{
	const D3D11PixelShader* shader = dynamic_cast<const D3D11PixelShader*>(ps);
	if (shader)
		m_D3D11DeviceContext->PSSetShader(shader->m_shader, 0, 0);
}