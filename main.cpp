#include <QApplication>
#include <QDir>
#include <QGLFormat>
#include <QSurface>
#include "mainwindows.hpp"


int main(int argc, char **argv)
{
	QApplication app(argc, argv);	
	QDir dir(QApplication::applicationDirPath());

	#ifdef Q_OS_OSX
		dir.cdUp();
		dir.cd("Resources");
	#endif


        MainWindow window;
        window.show();
        return app.exec();


	return app.exec();
}
