#ifndef BASEWINDOW_H
#define BASEWINDOW_H

#include <QtWidgets/QMainWindow>
#include "ui_basewindow.h"

class BaseWindow : public QMainWindow
{
	Q_OBJECT

public:
	BaseWindow(QWidget *parent = 0);
	~BaseWindow();

	void resizeEvent(QResizeEvent *e);
	void paintEvent(QPaintEvent *e);

private:
	Ui::BaseWindowClass ui;
};

#endif // BASEWINDOW_H
