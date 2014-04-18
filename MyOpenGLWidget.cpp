#include "MyOpenGLWidget.hpp"

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

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);


	_cam = new Camera();
    cube = new Cube();

    qDebug() << QDir::current().entryList();

    GLuint vs = Shader::loadVertexShader("test.vert");
    GLuint fs = Shader::loadFragmentShader("test.frag");

    shader_programme = glCreateProgram();
    glAttachShader (shader_programme, fs);
    glAttachShader (shader_programme, vs);
    glLinkProgram (shader_programme);

    glUseProgram (shader_programme);

	model_loc =        glGetUniformLocation(shader_programme, "model");
    view_loc =         glGetUniformLocation(shader_programme, "view");
    projection_loc =   glGetUniformLocation(shader_programme, "projection");

    _cam->setProjection(view_loc);
    cube->modelLocation(model_loc);

}


void	MyOpenGLWidget::paintGL()
{
	static float angle = 0;


	mat4 rotation = YrotationMatrix(angle);
	mat4 transUp = translationMatrix(0.0f, 1.0f, 0.0f);
	mat4 transUpTotal(1);


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_cam->display();


	for (int i = 0; i < 8; ++i)
	{
	    mat4 model = translationMatrix(1.5f, 0.0f, 0.0f);
	    model = Yrotate(model, i * 45 * (M_PI)/180.0f);         

	    model = rotation * transUpTotal * model;

	    transUpTotal *= transUp;


        pushMatrix(model);
        
            cube->draw();    

        popMatrix();   
	    
	}


	// swapBuffers();
	angle += 0.01;
}

void	MyOpenGLWidget::resizeGL(int width, int height)
{
    mat4 projection = projectionMatrix(70.0, width/(float)height, 0.1f, 100.0f);
    glUniformMatrix4fv(projection_loc, 1, GL_FALSE, projection.m);
}

void    MyOpenGLWidget::keyPressEvent(QKeyEvent * event)
{

    if (event->modifiers() & (Qt::AltModifier | Qt::ShiftModifier))
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
            _cam->_avant_presse = true;
            goto action;

        case Qt::Key_Down:
        case Qt::Key_S:
            _cam->_arriere_presse = true;
            goto action;

        case Qt::Key_Right:
        case Qt::Key_D:
            _cam->_droite_presse = true;
            goto action;

        case Qt::Key_Left:
        case Qt::Key_Q:
            _cam->_gauche_presse = true;
            goto action;

        case Qt::Key_PageUp:
        case Qt::Key_A:
            _cam->_haut_presse = true;
            goto action;

        case Qt::Key_PageDown:
        case Qt::Key_W:
            _cam->_bas_presse = true;
            goto action;
    }

noAction:
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
            _cam->_avant_presse = false;
            goto action;

        case Qt::Key_Down:
        case Qt::Key_S:
            _cam->_arriere_presse = false;
            goto action;

        case Qt::Key_Right:
        case Qt::Key_D:
            _cam->_droite_presse = false;
            goto action;

        case Qt::Key_Left:
        case Qt::Key_Q:
            _cam->_gauche_presse = false;
            goto action;

        case Qt::Key_PageUp:
        case Qt::Key_A:
            _cam->_haut_presse = false;
            goto action;

        case Qt::Key_PageDown:
        case Qt::Key_W:
            _cam->_bas_presse = false;
            goto action;
    }

noAction:
    QWidget::keyReleaseEvent(event);

action:
    return;
}

void    MyOpenGLWidget::mouseMoveEvent(QMouseEvent * event)
{
    if (_captureMouse)
    {
        _cam->mouseMoveEvent(event->x(), event->y(), width(), height());

        QPoint glob = mapToGlobal(QPoint(width()/2,height()/2));
        QCursor::setPos(glob);
    }


    QWidget::mouseMoveEvent(event);
}

void    MyOpenGLWidget::mousePressEvent(QMouseEvent *)
{
    if(!_captureMouse){
        _captureMouse = true;

        qDebug() << "Blank cursor";

        setCursor(Qt::BlankCursor);
    }
}
