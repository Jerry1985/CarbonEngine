#pragma once

#include "Renderer\Common\RALInterface.h"
#include <d3d11.h>

#include "Utility\UtilityMacro.h"

class D3D11Interface : public RALInterface
{
public:
	D3D11Interface();
	virtual ~D3D11Interface();

#define RAL_METHOD(ReturnType,FuncName,FuncParaDecl,FuncParaDef,FuncPara) virtual ReturnType FuncName FuncParaDecl;
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

	// flush render target if neccessary
	void _flushRT();

	void _setVertexLayout(const RALVertexLayout* vl);
	void _setVertexShader(const RALShader* vs);
	void _setPixelShader(const RALShader* ps);

	friend class D3D11View;
	friend class D3D11RenderTarget;
	friend class D3D11VertexBuffer;
	friend class D3D11IndexBuffer;
	friend class D3D11VertexShader;
	friend class D3D11PixelShader;
	friend class D3D11HullShader;
	friend class D3D11DomainShader;
	friend class D3D11GeometryShader;
	friend class D3D11ComputeShader;
	friend class D3D11VertexLayout;
};