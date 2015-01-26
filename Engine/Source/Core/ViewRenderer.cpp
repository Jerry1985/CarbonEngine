#include "ViewRenderer.h"
#include "ViewScene.h"

#include "Renderer\Common\RALGlobalMethods.h"
#include "Renderer\Common\RALView.h"

void ViewRenderer::Render(RALView* view)
{
	RALBeginRender(view);

	if (m_Scene)
		m_Scene->toDeleteRender();

	RALEndRender(view);
}