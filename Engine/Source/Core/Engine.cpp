#include "Engine.h"
#include "Common\Log\Log.h"
#include <QtWidgets/QApplication>
#include "../UI/Base/basewindow.h"
#include "Shader\GlobalShaders.h"
#include "Renderer\Common\RALGlobalMethods.h"
#include "ViewRenderer.h"
#include "GameScene.h"

extern Engine gEngine;
extern RAL_RENDERER	gRendererType;

Engine&	GetEngine()
{
	return gEngine;
}

Engine::Engine()
{
}

Engine::~Engine()
{
}

// Initialize Engine
void	Engine::Init()
{
	// Enable Log system, release build will ignore logging
	EnableLog();
	AddPlatformLogContext();
	AddFileLogContext(S("carbon.log"));

	// create D3D11RAL
	gRendererType = RAL_RENDERER_OPENGL;
	RALCreateInterface(gRendererType);

	// Load global shaders
	LoadGlobalShaders();

	m_ViewScenes.Add(new GameScene());
	m_ViewScenes[0]->Init();
	m_Renderers.Add(new ViewRenderer());
	m_Renderers[0]->SetupScene(m_ViewScenes[0]);
}

// Run the game engine
void	Engine::Run()
{
	// No need to pass the real parameter to QT
	int argc = 0;
	char argv[] = "";
	QApplication a(argc, (char**)&argv);

	BaseWindow p;
	p.show();
	p.setupViewRenderer(m_Renderers[0]);

	a.exec();
}

// Destroy Game Engine
void	Engine::Destroy()
{
	// release scene resources
	CArrayIterator<ViewRenderer*>	vrIT(m_Renderers);
	while (!vrIT.IsEnd())
	{
		SAFE_DELETE(*vrIT);
		++vrIT;
	}
	m_Renderers.Release();

	// release view renderer
	CArrayIterator<ViewScene*>	vsIT(m_ViewScenes);
	while (!vsIT.IsEnd())
	{
		SAFE_RELEASE(*vsIT);
		++vsIT;
	}
	m_ViewScenes.Release();

	LogManager::DeleteSingleton();
}