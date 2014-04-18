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

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glClearColor(0.3, 0.3, 0.3, 1.0);


    qDebug() << QDir::current().entryList();

    QOpenGLShaderProgram program;


    if(!program.addShaderFromSourceFile(QOpenGLShader::Fragment, "test.frag"))
    {
        qFatal("Erreur de chargement du shader test.frag\nLogs : %s", program.log().toStdString().c_str());
    }

    if(!program.addShaderFromSourceFile(QOpenGLShader::Vertex, "test.vert"))
    {
        qFatal("Erreur de chargement du shader test.vert\nLogs : %s", program.log().toStdString().c_str());
    }


    shader_programme = program.programId();


    glLinkProgram (shader_programme);
    glUseProgram (shader_programme);


    // Scene s("scene.xml");
    Material *mat  = new Material();
    mat->set(shader_programme);

    _cam = new Camera();
    cube = new Cube();

    
    plan = new Plan(10, 10, 40, 20, std::vector<QRectF> {QRectF(1, 1, 1, 1), QRectF(4,2,1,2)}, mat);
    plan2 = new Plan(40, 40, 400, 200, std::vector<QRectF>(), NULL, vec3(), vec3(0, 0, 4));
    sphere = new Sphere(5, 40, 40);

	model_loc =        glGetUniformLocation(shader_programme, "model");
    view_loc =         glGetUniformLocation(shader_programme, "view");
    projection_loc =   glGetUniformLocation(shader_programme, "projection");

    _cam->setProjection(view_loc);
    cube->modelLocation(model_loc);
    cube->shaderId(shader_programme);
    plan->modelLocation(model_loc);
    plan->shaderId(shader_programme);
    plan2->modelLocation(model_loc);
    plan2->shaderId(shader_programme);
    sphere->modelLocation(model_loc);
    sphere->shaderId(shader_programme);


    Scene s("scene.xml");

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
            plan->draw(); 

        popMatrix();   
	    
	}


    plan2->draw();

    sphere->draw();





	angle += 0.01;
}

void	MyOpenGLWidget::resizeGL(int width, int height)
{
    mat4 projection = projectionMatrix(70.0, width/(float)height, 0.1f, 100.0f);
    glUniformMatrix4fv(projection_loc, 1, GL_FALSE, projection.m);

    glViewport(0,0, width, height);
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

        case Qt::Key_F1:
        {
            static bool wire = true;

            glPolygonMode(GL_FRONT_AND_BACK, wire ? GL_LINE : GL_FILL);

            wire = !wire;
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


        setCursor(Qt::BlankCursor);
    }
}
