#ifndef CARBON_D3D11INTERFACE
#define CARBON_D3D11INTERFACE

#include "Renderer\Common\RALInterface.h"
#include <d3d11.h>

#define SAFE_RELEASE(p) {if(p) {(p)->Release(); (p)=NULL;}}

class D3D11Interface : public RALInterface
{
public:
	D3D11Interface();
	virtual ~D3D11Interface();

#define RAL_METHOD(ReturnType,FuncName,FuncParaDecl,FuncPara) virtual ReturnType FuncName FuncParaDecl;
#include "Renderer/Common/RALMethods.h"
#undef RAL_METHOD

private:
	IDXGIFactory*			m_DXGIFactory;
	ID3D11Device*			m_D3D11Device;
	D3D_FEATURE_LEVEL		m_FeatureLevel;
	ID3D11DeviceContext*	m_D3D11DeviceContext;

	// initialize direct3d 11 device
	bool _initDevice();
	// release device
	void _releaseDevice();

	friend class D3D11Viewport;
};

#endif