#include "basewindow.h"
#include <qtimer.h>
#include <qevent.h>

#include "Renderer\Common\RALGlobalMethods.h"
#include "Renderer\Common\RALView.h"
#include "Renderer\Common\RALViewport.h"
#include "Common\Utility\UtilityMacro.h"

BaseWindow::BaseWindow(QWidget *parent)
: QMainWindow(parent)
{
	ui.setupUi(this);

	setAttribute(Qt::WA_PaintOnScreen, true);
	setAttribute(Qt::WA_NativeWindow, true);

	QTimer* timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(update()));
	timer->start(20);

	// Create View
	m_View = RALCreateView((void*)winId(), size().width(), size().height(), false, RAL_FORMAT_R8G8B8A8_UNORM);
}

BaseWindow::~BaseWindow()
{
	SAFE_DELETE(m_View);
}

// setup view renderer
void BaseWindow::setupViewRenderer(ViewRenderer* vr)
{
	m_ViewRenderer = vr;
}

void BaseWindow::resizeEvent(QResizeEvent *e)
{
	if (m_View)
	{
		m_View->Resize(e->size().width(), e->size().height());

		RALViewport vp(size().width(), size().height());
		RALSetViewport(vp);
	}
}

void BaseWindow::paintEvent(QPaintEvent *e)
{
	if (m_ViewRenderer)
		m_ViewRenderer->Render(m_View);
}