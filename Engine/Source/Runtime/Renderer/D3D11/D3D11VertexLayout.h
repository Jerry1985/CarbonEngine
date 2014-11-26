#pragma once

#include "Renderer\Common\RALVertexLayout.h"

template<class T>
class CArray;
class CBitArray;

struct RALVertexElementLayout;
struct ID3D11InputLayout;

class D3D11VertexLayout : public RALVertexLayout
{
public:
	D3D11VertexLayout(const CArray<RALVertexElementDesc>& descs, const CBitArray& bytecode);
	~D3D11VertexLayout();

	void Release();

private:
	ID3D11InputLayout*	m_inputLayout;

	friend class D3D11Interface;
};