#include <QApplication>
#include <QDir>
#include <QGLFormat>
#include <QSurface>
#include "MyOpenGLWidget.hpp"


int main(int argc, char **argv)
{
	QApplication app(argc, argv);	
	QDir dir(QApplication::applicationDirPath());

	#ifdef Q_OS_OSX
		dir.cdUp();
		dir.cd("Resources");
	#endif

	QDir::setCurrent(dir.absolutePath());

	QGLFormat f;

    f.setVersion(3, 2);
	f.setProfile(QGLFormat::CoreProfile);

	MyOpenGLWidget w(f);

	w.show();

	return app.exec();
}
