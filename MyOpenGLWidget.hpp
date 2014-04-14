#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#include <QGLWidget>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions_3_2_Core>
#include <QTimer>

#include "math.hpp"
#include "camera.hpp"
#include "shader.hpp"


class MyOpenGLWidget: public QGLWidget, protected QOpenGLFunctions_3_2_Core
{
Q_OBJECT

private:
	Camera * _cam;
	GLuint _vao;
	GLuint shader_programme;

	GLuint model_loc;
	GLuint view_location;
	GLuint projection_loc;


public:
	MyOpenGLWidget(const QGLFormat & format, QWidget * parent = 0, const QGLWidget * shareWidget = 0, Qt::WindowFlags f = 0);
	~MyOpenGLWidget();

    QSize minimumSizeHint() const;
    QSize sizeHint() const;

	virtual void	initializeGL();
	virtual void	paintGL();
	virtual void	resizeGL(int width, int height);

};


#endif