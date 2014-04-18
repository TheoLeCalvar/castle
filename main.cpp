#include <QApplication>
#include <QGLFormat>
#include "MyOpenGLWidget.hpp"


int main(int argc, char **argv)
{
	QApplication app(argc, argv);	
	QGLFormat f;

    f.setVersion(4, 1);
	f.setProfile(QGLFormat::CoreProfile);

	MyOpenGLWidget w(f);

	w.show();

	return app.exec();
}
