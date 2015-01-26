#ifndef BASEWINDOW_H
#define BASEWINDOW_H

#include <QtWidgets/QMainWindow>
#include "ui_basewindow.h"
#include "Core\ViewRenderer.h"

class BaseWindow : public QMainWindow
{
	Q_OBJECT

public:
	BaseWindow(QWidget *parent = 0);
	~BaseWindow();

	void resizeEvent(QResizeEvent *e);
	void paintEvent(QPaintEvent *e);
	
	virtual QPaintEngine* paintEngine() const { return NULL; }

	// setup view renderer
	void setupViewRenderer(ViewRenderer* vr);

private:
	Ui::BaseWindowClass ui;

	ViewRenderer*	m_ViewRenderer = 0;

	RALView*		m_View = 0;
};

#endif // BASEWINDOW_H
