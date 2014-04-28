#include "MyOpenGLWidget.hpp"

#include <QRectF>
#include <vector>

MyOpenGLWidget::MyOpenGLWidget(const QGLFormat & format, QWidget * parent, const QGLWidget * shareWidget, Qt::WindowFlags f):
	QGLWidget(format, parent, shareWidget, f), _captureMouse(false)
{
    //refresh tout les 1/60eme de seconde
     QTimer *timer = new QTimer(this);
     connect(timer, SIGNAL(timeout()), this, SLOT(updateGL()));
     timer->start(1000/60);


     setFocusPolicy(Qt::StrongFocus);
     setMouseTracking(true);
}

MyOpenGLWidget::~MyOpenGLWidget()
{
}

QSize MyOpenGLWidget::minimumSizeHint() const
{
	return QSize(600, 600);
}

QSize MyOpenGLWidget::sizeHint() const
{
	return QSize(600, 600);
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
   

    scene = new Scene("scene.xml");


}


void	MyOpenGLWidget::paintGL()
{
    QElapsedTimer timer;
    timer.start();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    scene->draw();

    openGL_check_error();


    if (timer.elapsed() > 1000/16)
    {
        qDebug() << "Moins de 60 fps !";
        qDebug() << "Elapsed time : " << timer.nsecsElapsed();
    }
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
        case Qt::Key_Escape:
            close();
            goto action;

        case Qt::Key_Up:
        case Qt::Key_Z:
            scene->_camera->_avant_presse = true;
            goto action;

        case Qt::Key_Down:
        case Qt::Key_S:
            scene->_camera->_arriere_presse = true;
            goto action;

        case Qt::Key_Right:
        case Qt::Key_D:
            scene->_camera->_droite_presse = true;
            goto action;

        case Qt::Key_Left:
        case Qt::Key_Q:
            scene->_camera->_gauche_presse = true;
            goto action;

        case Qt::Key_PageUp:
        case Qt::Key_A:
            scene->_camera->_haut_presse = true;
            goto action;

        case Qt::Key_PageDown:
        case Qt::Key_W:
            scene->_camera->_bas_presse = true;
            goto action;

        case Qt::Key_F1:
        {
            static bool wire = true;

            glPolygonMode(GL_FRONT_AND_BACK, wire ? GL_LINE : GL_FILL);

            wire = !wire;

            goto action;
        }

        case Qt::Key_F2:
        {
            static bool cullface = false;

            if (cullface)  
            {
                glEnable(GL_CULL_FACE);
            }
            else
            {
                glDisable(GL_CULL_FACE);
            }

            cullface = !cullface;

            goto action;
        }

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
            scene->_camera->_avant_presse = false;
            goto action;

        case Qt::Key_Down:
        case Qt::Key_S:
            scene->_camera->_arriere_presse = false;
            goto action;

        case Qt::Key_Right:
        case Qt::Key_D:
            scene->_camera->_droite_presse = false;
            goto action;

        case Qt::Key_Left:
        case Qt::Key_Q:
            scene->_camera->_gauche_presse = false;
            goto action;

        case Qt::Key_PageUp:
        case Qt::Key_A:
            scene->_camera->_haut_presse = false;
            goto action;

        case Qt::Key_PageDown:
        case Qt::Key_W:
            scene->_camera->_bas_presse = false;
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
        scene->_camera->mouseMoveEvent(event->x(), event->y(), width(), height());

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
