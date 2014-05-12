#include "MyOpenGLWidget.hpp"

#include <QRectF>
#include <vector>

MyOpenGLWidget::MyOpenGLWidget(const QGLFormat & format, QWidget * parent, const QGLWidget * shareWidget, Qt::WindowFlags f):
	QGLWidget(format, parent, shareWidget, f), _captureMouse(false)
{
    //refresh tout les 1/60eme de seconde
     _timer = new QTimer(this);
     connect(_timer, SIGNAL(timeout()), this, SLOT(updateGL()));
     _timer->start(0);


     setFocusPolicy(Qt::StrongFocus);
     setMouseTracking(true);

}

MyOpenGLWidget::~MyOpenGLWidget()
{
    if (_scene)
    {
        delete _scene;
    }

    delete _timer;
}

QSize MyOpenGLWidget::minimumSizeHint() const
{
	return QSize(600, 600);
}

QSize MyOpenGLWidget::sizeHint() const
{
	return QSize(600, 600);
}

Scene * MyOpenGLWidget::getScene()
{
    return _scene;
}

void    MyOpenGLWidget::setScene(Scene * scene)
{
    if (_scene)
    {
        delete _scene;
    }

    _scene = scene;
}

void	MyOpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    qDebug("Vendor : %s\nRenderer : %s\nVersion : %s", glGetString( GL_VENDOR), glGetString(GL_RENDERER), glGetString(GL_VERSION));
    qDebug() << "Current context : " << format(); 
    qDebug() << QDir::current().entryList();


    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);



    glClearColor(0.3, 0.3, 0.3, 1.0);
   

    _scene = new Scene("scene.xml");



}


void	MyOpenGLWidget::paintGL()
{
    QElapsedTimer timer;
    timer.start();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    _scene->draw();

    openGL_check_error();

    setWindowTitle(QString("Castle | %1 fps | %2 ms").arg(1 / (timer.elapsed() / 1000.0)).arg(timer.elapsed()));

}

void	MyOpenGLWidget::resizeGL(int width, int height)
{

    glViewport(0,0, width, height);

    setProjectionMatrix(projectionMatrix(70.0, width/(float)height, 0.1f, 100.0f));

}

void    MyOpenGLWidget::keyPressEvent(QKeyEvent * event)
{

    if (event->modifiers() == (Qt::AltModifier | Qt::ShiftModifier))
    {
        _captureMouse = false;
        setCursor(Qt::ArrowCursor);
    }


    switch (event->key())
    {

        case Qt::Key_Up:
        case Qt::Key_Z:
            _scene->_camera->_avant_presse = true;
            goto action;

        case Qt::Key_Down:
        case Qt::Key_S:
            _scene->_camera->_arriere_presse = true;
            goto action;

        case Qt::Key_Right:
        case Qt::Key_D:
            _scene->_camera->_droite_presse = true;
            goto action;

        case Qt::Key_Left:
        case Qt::Key_Q:
            _scene->_camera->_gauche_presse = true;
            goto action;

        case Qt::Key_PageUp:
        case Qt::Key_A:
            _scene->_camera->_haut_presse = true;
            goto action;

        case Qt::Key_PageDown:
        case Qt::Key_W:
            _scene->_camera->_bas_presse = true;
            goto action;


        case Qt::Key_F3:
            qDebug() << _scene->getMaterialsNames();
            goto action;
    }


    QWidget::keyPressEvent(event);

action:
    return;

}

void    MyOpenGLWidget::keyReleaseEvent(QKeyEvent * event)
{
    switch (event->key())
    {
        case Qt::Key_Up:
        case Qt::Key_Z:
            _scene->_camera->_avant_presse = false;
            goto action;

        case Qt::Key_Down:
        case Qt::Key_S:
            _scene->_camera->_arriere_presse = false;
            goto action;

        case Qt::Key_Right:
        case Qt::Key_D:
            _scene->_camera->_droite_presse = false;
            goto action;

        case Qt::Key_Left:
        case Qt::Key_Q:
            _scene->_camera->_gauche_presse = false;
            goto action;

        case Qt::Key_PageUp:
        case Qt::Key_A:
            _scene->_camera->_haut_presse = false;
            goto action;

        case Qt::Key_PageDown:
        case Qt::Key_W:
            _scene->_camera->_bas_presse = false;
            goto action;
    }

    QWidget::keyReleaseEvent(event);

action:
    return;
}

void    MyOpenGLWidget::mouseMoveEvent(QMouseEvent * event)
{
    if (_captureMouse)
    {
        _scene->_camera->mouseMoveEvent(event->x(), event->y(), width(), height());

        QPoint glob = mapToGlobal(QPoint(width()/2,height()/2));
        QCursor::setPos(glob);
    }


    QWidget::mouseMoveEvent(event);
}

void    MyOpenGLWidget::mousePressEvent(QMouseEvent *)
{
    if(!_captureMouse){
        _captureMouse = true;


        setCursor(Qt::BlankCursor);
    }
}
