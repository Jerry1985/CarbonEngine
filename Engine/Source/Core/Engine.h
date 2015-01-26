#pragma once

#include "Container\CArray.h"

class ViewRenderer;
class ViewScene;

class Engine
{
public:
	Engine();
	~Engine();

	// Initialize Engine
	void	Init();

	// Run the game engine
	void	Run();

	// Destroy Game Engine
	void	Destroy();

private:
	// View renderers
	CArray<ViewRenderer*>	m_Renderers;
	// The scenes
	CArray<ViewScene*>		m_ViewScenes;
};

Engine&	GetEngine();