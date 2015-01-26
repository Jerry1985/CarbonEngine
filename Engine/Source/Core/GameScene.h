#pragma once

#include "ViewScene.h"

// temporary
#include "Core\PipelineBoundState.h"

class GameScene : public ViewScene
{
public:
	~GameScene(){}

	void Init();
	void Release();

	void toDeleteRender();

// temporary data
private:
	RALVertexBuffer*		vb = 0;
	RALIndexBuffer*			ib = 0;
	RALVertexLayout*		vl = 0;

	PipelineBoundState		shaderstate;
};