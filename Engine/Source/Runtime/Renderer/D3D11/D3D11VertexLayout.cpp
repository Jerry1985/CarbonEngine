#include "D3D11VertexLayout.h"
#include "D3D11Interface.h"
#include "D3D11Define.h"
#include "Common\Container\CArray.h"
#include "Container\CBitArray.h"

extern D3D11Interface* gD3D11Interface;

RALVertexLayout* D3D11Interface::CreateVertexLayout(const CArray<RALVertexElementDesc>& descs, const CBitArray& bytecode)
{
	return new D3D11VertexLayout(descs, bytecode);
}

D3D11VertexLayout::D3D11VertexLayout(const CArray<RALVertexElementDesc>& layouts, const CBitArray& bytecode) : m_inputLayout(0)
{
	int count = layouts.GetCount();
	if (count == 0 || count >= MAX_VERTEX_ELEMENT_COUNT)
		return;

	D3D11_INPUT_ELEMENT_DESC* descs = new D3D11_INPUT_ELEMENT_DESC[count];
	for (int i = 0; i < count; ++i){
		descs[i].SemanticName = "ATTRIBUTE";
		descs[i].SemanticIndex = i;
		descs[i].InputSlot = layouts[i].streamIndex;
		descs[i].AlignedByteOffset = layouts[i].offset;
		descs[i].Format = DXGIFORMAT_FROM_RAL_VERTEXELEMENTTYPE(layouts[i].type);
		descs[i].InputSlotClass = layouts[i].useInstanceIndex ? D3D11_INPUT_PER_INSTANCE_DATA : D3D11_INPUT_PER_VERTEX_DATA;
		descs[i].InstanceDataStepRate = 0;
	}

	gD3D11Interface->m_D3D11Device->CreateInputLayout(descs, count, bytecode.GetData(), bytecode.GetSize(), &m_inputLayout);

	delete descs;
}

D3D11VertexLayout::~D3D11VertexLayout()
{
	Release();
}

void D3D11VertexLayout::Release()
{
	SAFE_RELEASE(m_inputLayout);
}