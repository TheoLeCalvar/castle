#include <QApplication>
#include <QDir>
#include <QGLFormat>

#include "mainwindows.hpp"

#include <QString>
#include <QDebug>


int main(int argc, char **argv)
{
	QApplication app(argc, argv);	
	QDir dir(QApplication::applicationDirPath());


	#ifdef Q_OS_OSX
		dir.cdUp();
		dir.cd("Resources");
	#endif

	QDir::setCurrent(dir.absolutePath());


	if(argc < 2)
	{
		QGLFormat f;

		f.setVersion(3, 2);
		f.setProfile(QGLFormat::CoreProfile);
	


		MyOpenGLWidget * w = new MyOpenGLWidget(f, NULL, "scene.xml");
		w->show();



		return app.exec();
	}
	else
	{
		MainWindow w(argv[1]);
		w.show();

		return app.exec();
	}
}
