#pragma once

class RALView;
class ViewScene;

class ViewRenderer
{
public:
	virtual ~ViewRenderer(){}

	// Setup scene
	void SetupScene(ViewScene* scene){
		m_Scene = scene;
	}

	// Render the view
	virtual void Render(RALView* view);

protected:
	ViewScene*	m_Scene;
};