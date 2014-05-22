#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#include <QDir>
#include <QGLWidget>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions_3_2_Core>
#include <QOpenGLShaderProgram>


#include <QElapsedTimer>
#include <QTimer>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QPoint>
#include <QCursor>
#include <QDebug>

#include "helper.hpp"
#include "camera.hpp"

#include "material.hpp"

#include "scene.hpp"

#include "QMessageBox"


class MyOpenGLWidget: public QGLWidget, protected QOpenGLFunctions_3_2_Core
{
Q_OBJECT

private:
	bool   		_captureMouse;
	QTimer 	*	_timer;
	QString 	_path;


	Scene * 	_scene;


public:
	MyOpenGLWidget(const QGLFormat & format, QWidget * parent = 0, const QString & path = "scene.xml", const QGLWidget * shareWidget = 0, Qt::WindowFlags f = 0);
	~MyOpenGLWidget();

    QSize minimumSizeHint() const;
    QSize sizeHint() const;

    Scene * 		getScene();
    void 			setScene(Scene * scene);

	virtual void	initializeGL();
	virtual void	paintGL();
	virtual void	resizeGL(int width, int height);

	virtual void	keyPressEvent(QKeyEvent * event);
	virtual void	keyReleaseEvent(QKeyEvent * event);

	virtual void 	mouseMoveEvent(QMouseEvent * event);
	virtual void 	mousePressEvent(QMouseEvent * event);
};


#endif
