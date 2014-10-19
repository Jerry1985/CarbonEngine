#ifndef QTPROJECT_H
#define QTPROJECT_H

#include <QtGui/QMainWindow>
#include "ui_qtproject.h"

class QTProject : public QMainWindow
{
	Q_OBJECT

public:
	QTProject(QWidget *parent = 0, Qt::WFlags flags = 0);
	~QTProject();


	virtual QPaintEngine* paintEngine() const { return NULL; }

protected:
	virtual void resizeEvent(QResizeEvent *e);
	virtual void paintEvent(QPaintEvent *e);

private:
	Ui::QTProjectClass ui;
};

#endif // QTPROJECT_H
