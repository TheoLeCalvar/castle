#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#include <QDir>
#include <QGLWidget>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions_3_2_Core>
#include <QOpenGLShaderProgram>

#include <QTimer>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QPoint>
#include <QCursor>
#include <QDebug>
#include <QOpenGLDebugLogger>


#include "helper.hpp"
#include "camera.hpp"

#include "cube.hpp"
#include "plan.hpp"
#include "sphere.hpp"
#include "material.hpp"

#include "scene.hpp"


class MyOpenGLWidget: public QGLWidget, protected QOpenGLFunctions_4_1_Core
{
Q_OBJECT

private:
	Camera * 	_cam;
	GLuint 		shader_programme;

	GLuint 		model_loc;
	GLuint 		view_loc;
	GLuint 		projection_loc;

	bool   		_captureMouse;

	Cube * 		cube;
	Plan * 		plan;
	Plan *  	plan2;
	Sphere * 	sphere;


public:
	MyOpenGLWidget(const QGLFormat & format, QWidget * parent = 0, const QGLWidget * shareWidget = 0, Qt::WindowFlags f = 0);
	~MyOpenGLWidget();

    QSize minimumSizeHint() const;
    QSize sizeHint() const;

	virtual void	initializeGL();
	virtual void	paintGL();
	virtual void	resizeGL(int width, int height);

	virtual void	keyPressEvent(QKeyEvent * event);
	virtual void	keyReleaseEvent(QKeyEvent * event);

	virtual void 	mouseMoveEvent(QMouseEvent * event);
	virtual void 	mousePressEvent(QMouseEvent * event);
};


#endif
