#include "MyOpenGLWidget.hpp"

#include <QRectF>
#include <vector>

MyOpenGLWidget::MyOpenGLWidget(const QGLFormat & format, QWidget * parent, const QString & path, const QGLWidget * shareWidget, Qt::WindowFlags f):
	QGLWidget(format, parent, shareWidget, f), _captureMouse(false), _path(path), _vao_quad(0), _framebuffer(0), _texture(0), _renderbuffer(0), _activeProgram(0)
{
    //refresh tout les 1/60eme de seconde
     _timer = new QTimer(this);
     connect(_timer, SIGNAL(timeout()), this, SLOT(updateGL()));
     _timer->start(60.0/1000.0);


     setFocusPolicy(Qt::StrongFocus);
     setMouseTracking(true);



}

MyOpenGLWidget::~MyOpenGLWidget()
{
    makeCurrent();

    if (_scene)
    {
        delete _scene;
    }

    delete _timer;

    glDeleteTextures(1, &_texture);
    glDeleteRenderbuffers(1, &_renderbuffer);
    glDeleteFramebuffers(1, &_framebuffer);

    for(auto * i : _postProcessPrograms)
        delete i;

    for(auto * i : _loadedShaders)
        delete i;
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
    makeCurrent();
    initializeOpenGLFunctions();


    qDebug("Vendor : %s\nRenderer : %s\nVersion : %s", glGetString( GL_VENDOR), glGetString(GL_RENDERER), glGetString(GL_VERSION));
    qDebug() << "Current context : " << format(); 
    qDebug() << context() << context()->isValid();
    qDebug() << QDir::current().entryList();


    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);



    glClearColor(0.3, 0.3, 0.3, 1.0);
   
    if(_path == "")
        _scene= new Scene(this);
    else
        _scene = new Scene(this, _path);


    float quad_point[] = {
      -1.0, -1.0,
       1.0, -1.0,
       1.0,  1.0,
       1.0,  1.0,
      -1.0,  1.0,
      -1.0, -1.0
    };
    float quad_tex[] = {
      0.0, 0.0,
      1.0, 0.0,
      1.0, 1.0,
      1.0, 1.0,
      0.0, 1.0,
      0.0, 0.0
    };

    unsigned int vbo_point = 0;
    glGenBuffers (1, &vbo_point);
    glBindBuffer (GL_ARRAY_BUFFER, vbo_point);
    glBufferData (GL_ARRAY_BUFFER, 6*2 * sizeof (float), quad_point, GL_STATIC_DRAW);

    unsigned int vbo_tex = 0;
    glGenBuffers (1, &vbo_tex);
    glBindBuffer (GL_ARRAY_BUFFER, vbo_tex);
    glBufferData (GL_ARRAY_BUFFER, 6*2 * sizeof (float), quad_tex, GL_STATIC_DRAW);

    glGenVertexArrays (1, &_vao_quad);
    glBindVertexArray (_vao_quad);
    glEnableVertexAttribArray (0);
    glBindBuffer (GL_ARRAY_BUFFER, vbo_point);
    glVertexAttribPointer (0, 2, GL_FLOAT, GL_FALSE, 0, NULL);

    glEnableVertexAttribArray (1);
    glBindBuffer (GL_ARRAY_BUFFER, vbo_tex);
    glVertexAttribPointer (1, 2, GL_FLOAT, GL_FALSE, 0, NULL);

    glBindVertexArray(0);


    // useShader("");

}


void	MyOpenGLWidget::paintGL()
{
    QElapsedTimer timer;
    timer.start();

    if(_activeProgram)
        glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer);


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    _scene->draw();

    openGL_check_error();

    if(_activeProgram)
    {


        glBindFramebuffer(GL_FRAMEBUFFER, 0);  
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(_activeProgram->programId());


        int pixel_location = glGetUniformLocation(_activeProgram->programId(), "pixel_scale");

        if(pixel_location >= 0)
            glUniform2fv( pixel_location, 1, _pixel_scale.v);


        glBindVertexArray(_vao_quad);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, _texture);

        glDrawArrays(GL_TRIANGLES, 0, 6);

        glBindVertexArray(0);
    }
    setActiveShader(0);

    openGL_check_error();

    qint64 time = timer.nsecsElapsed();

    setWindowTitle(QString("Castle | %1 fps | %2 ns").arg(1 / (time / 1000000000.0)).arg(time));

}

void	MyOpenGLWidget::resizeGL(int width, int height)
{
    glViewport(0,0, width, height);

    setProjectionMatrix(projectionMatrix(70.0, width/(float)height, 0.1f, 100.0f));

    initFramebuffer(width, height);

    _pixel_scale = vec2(1.0f / width, 1.0f / height);

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


        case Qt::Key_F4:
            qDebug() << getShaderNames();
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

void            MyOpenGLWidget::useShader(const QString & name)
{
    _activeProgram = _postProcessPrograms.value(name);
}

void            MyOpenGLWidget::addShader(const QString & name, const QString & vertex, const QString & fragment)
{
    QOpenGLShaderProgram *p = new QOpenGLShaderProgram(this);

    if(_loadedShaders.value(vertex))
    {
    	p->addShader(_loadedShaders.value(vertex));
    }
    else
	{
		QOpenGLShader *shader = new QOpenGLShader(QOpenGLShader::Vertex);

	    if(!shader->compileSourceFile(vertex))
	    {
	        qDebug() << "Erreur de chargement du vertex" << shader->log();
	    }
	    else
	    {
	    	_loadedShaders.insert(vertex, shader);

	    	p->addShader(shader);
	    }
	}


	if(_loadedShaders.value(fragment))
    {
    	p->addShader(_loadedShaders.value(fragment));
    }
    else
	{
		QOpenGLShader *shader = new QOpenGLShader(QOpenGLShader::Fragment);

	    if(!shader->compileSourceFile(fragment))
	    {
	        qDebug() << "Erreur de chargement du fragment" << shader->log();
	    }
	    else
	    {
	    	_loadedShaders.insert(fragment, shader);

	    	p->addShader(shader);
	    }
	}

    if(!p->link())
    {
        qDebug() << "Erreur de linkage !";
    }
    else
    {
    	qDebug() << "Ajout de " << name << " dans les filtres";
        _postProcessPrograms.insert(name, p);
    }
}

QStringList     MyOpenGLWidget::getShaderNames()
{
    return _postProcessPrograms.keys();
}

void            MyOpenGLWidget::loadShaders(const QDomElement & postProcess)
{
    QDomElement shader = postProcess.firstChildElement("shader");

    while(!shader.isNull())
    {
    	QString nom, vertex, fragment;

    	nom = shader.attribute("nom");
    	vertex = shader.attribute("vertex", "shaders/base.vert");
    	fragment= shader.attribute("fragment", "shaders/base.frag");

    	addShader(nom, vertex, fragment);


        shader = shader.nextSiblingElement("shader");
    }
}

void 			MyOpenGLWidget::saveShaders(QDomElement & root, QDomDocument & doc) const
{
	QDomElement postProcess = doc.createElement("postProcess");

	for(auto i=  _postProcessPrograms.begin(); i != _postProcessPrograms.end(); ++i)
	{
		QDomElement shader = doc.createElement("shader");
		QList<QOpenGLShader *> shaderList = i.value()->shaders(); 

		shader.setAttribute("nom", i.key());

		for(QOpenGLShader * j : shaderList)
		{
			switch(j->shaderType())
			{
				case QOpenGLShader::Vertex :
					shader.setAttribute("vertex", _loadedShaders.key(j));
					break;

				case QOpenGLShader::Fragment :
					shader.setAttribute("fragment", _loadedShaders.key(j));
					break; 
			}
		}

		postProcess.appendChild(shader);
	}

	root.appendChild(postProcess);
}


void MyOpenGLWidget::initFramebuffer(int width, int height)
{

    glDeleteTextures(1, &_texture);
    glDeleteRenderbuffers(1, &_renderbuffer);
    glDeleteFramebuffers(1, &_framebuffer);

    //génération texture du framebuffer
    glGenTextures(1, &_texture);
    glBindTexture(GL_TEXTURE_2D, _texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    //génération framebuffer
    glGenFramebuffers(1, &_framebuffer);
    glBindFramebuffer (GL_FRAMEBUFFER, _framebuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _texture, 0);

    //buffer pour la profondeur
    GLuint renderBuffer = 0;

    glGenRenderbuffers(1, &renderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);

    glRenderbufferStorage (GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
    glFramebufferRenderbuffer (GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, renderBuffer);


    GLenum draw_bufs[] = { GL_COLOR_ATTACHMENT0 };
    glDrawBuffers (1, draw_bufs);

    GLenum status = glCheckFramebufferStatus (GL_FRAMEBUFFER);
    if (GL_FRAMEBUFFER_COMPLETE != status) {
      qDebug() << "Framebuffer incomplet.";
    }

    glBindFramebuffer (GL_FRAMEBUFFER, 0);
}
