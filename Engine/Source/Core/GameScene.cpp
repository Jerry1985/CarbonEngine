#include "GameScene.h"

// temporary data
#include "Renderer\Common\RALGlobalMethods.h"
#include "Renderer\Common\RALVertexBuffer.h"
#include "Renderer\Common\RALIndexBuffer.h"
#include "Shader\FlipViewShader.h"
#include "Shader\GlobalShaders.h"
#include "Core\PipelineBoundState.h"

void GameScene::Init()
{
	float vertices[] =
	{
		0.0f, 0.5f, 0.5f,
		0.5f, -0.5f, 0.5f,
		-0.5f, -0.5f, 0.5f,
		0.0f, -1.5f, 0.5f,
	};
	vb = RALCreateVertexBuffer(sizeof(vertices), sizeof(float)* 3, RAL_USAGE_DYNAMIC);
	if (vb)
	{
		RALBufferDesc desc = vb->Map();
		if (desc.pData)
			memcpy(desc.pData, vertices, sizeof(vertices));
		vb->Unmap();
	}

	unsigned indices[] =
	{
		0, 1, 2,
		1, 3, 2,
	};
	ib = RALCreateIndexBuffer(sizeof(indices), sizeof(unsigned), RAL_USAGE_DYNAMIC);
	if (ib)
	{
		RALBufferDesc desc = ib->Map();
		if (desc.pData)
			memcpy(desc.pData, indices, sizeof(indices));
		ib->Unmap();
	}

	FlipViewVertexShader& vs = GetGlobalShader<FlipViewVertexShader>();
	FlipViewPixelShader& ps = GetGlobalShader<FlipViewPixelShader>();

	PipelineBoundStateDesc pbsDesc;
	pbsDesc.m_VertexShader = &GetGlobalShader<FlipViewVertexShader>();
	pbsDesc.m_PixelShader = &GetGlobalShader<FlipViewPixelShader>();
	pbsDesc.m_VertexLayout = pbsDesc.m_VertexShader->GetRALVertexLayout();

	shaderstate.Init(pbsDesc);
}

void GameScene::Release()
{
	SAFE_DELETE(ib);
	SAFE_DELETE(vb);
}

// temporary data
void GameScene::toDeleteRender()
{
	RALClear(1, Color::BLACK, 1.0f);

	shaderstate.Bind();

	RALSetVertexBuffers(0, 1, vb);
	RALSetIndexBuffer(ib);

	RALDrawIndexed(6);
}