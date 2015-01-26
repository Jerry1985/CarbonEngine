#pragma once

class ViewScene
{
public:
	virtual ~ViewScene(){}

	virtual void Init(){}
	virtual void Release(){}

	// temporary data
	virtual void	toDeleteRender(){}
};