#include "MyOpenGLWidget.hpp"

MyOpenGLWidget::MyOpenGLWidget(const QGLFormat & format, QWidget * parent = 0, const QGLWidget * shareWidget = 0, Qt::WindowFlags f = 0):
	QGLWidget(format, parent, shareWidget, f), QGLFunctions(context())
{

}

MyOpenGLWidget::~MyOpenGLWidget()
{

}

QSize MyOpenGLWidget::minimumSizeHint() const
{
	return QSize(400, 400);
}

QSize MyOpenGLWidget::sizeHint() const
{
	return QSize(400, 400);
}


virtual void	MyOpenGLWidget::initializeGL()
{
    float points[] = 
    {
        -0.5f, -0.5f, 0.5f,     0.5f, -0.5f, 0.5f,      0.5f, 0.5f, 0.5f,       
        -0.5f, -0.5f, 0.5f,     0.5f, 0.5f, 0.5f,       -0.5f, 0.5f, 0.5f, 

        0.5f, -0.5f, 0.5f,      0.5f, -0.5f, -0.5f,     0.5f, 0.5f, -0.5f,
        0.5f, -0.5f, 0.5f,      0.5f, 0.5f, -0.5f,      0.5f, 0.5f, 0.5f,

        0.5f, -0.5f, -0.5f,     -0.5f, -0.5f, -0.5f,    -0.5f, 0.5f, -0.5f, 
        0.5f, -0.5f, -0.5f,     -0.5f, 0.5f, -0.5f,     0.5f, 0.5f, -0.5f,

        -0.5f, -0.5f, -0.5f,    -0.5f, -0.5f, 0.5f,     -0.5f, 0.5f, 0.5f,
        -0.5f, -0.5f, -0.5f,    -0.5f, 0.5f, 0.5f,      -0.5f, 0.5f, -0.5f,

        -0.5f, 0.5f, 0.5f,      0.5f, 0.5f, 0.5f,       0.5f, 0.5f, -0.5f,
        -0.5f, 0.5f, 0.5f,      0.5f, 0.5f, -0.5f,      -0.5f, 0.5f, -0.5f,

        -0.5f, -0.5f, 0.5f,     -0.5f, -0.5f, -0.5f,    0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, 0.5f,     0.5f, -0.5f, -0.5f,      0.5f, -0.5f, 0.5f
    };

    float normals[] = 
    {
        0.0f,  0.0f, 1.0f,     0.0f,  0.0f, 1.0f,      0.0f,  0.0f, 1.0f,       
        0.0f,  0.0f, 1.0f,     0.0f,  0.0f, 1.0f,      0.0f,  0.0f, 1.0f, 

        1.0f,  0.0f, 00.0f,     1.0f,  0.0f, 00.0f,      1.0f,  0.0f, 00.0f,       
        1.0f,  0.0f, 00.0f,     1.0f,  0.0f, 00.0f,      1.0f,  0.0f, 00.0f,

        0.0f,  0.0f, -1.0f,     0.0f,  0.0f, 1.0f,      0.0f,  0.0f, 1.0f,       
        0.0f,  0.0f, -1.0f,     0.0f,  0.0f, 1.0f,      0.0f,  0.0f, 1.0f,

        -1.0f,  0.0f, 0.0f,     -1.0f,  0.0f, 0.0f,      -1.0f,  0.0f, 0.0f,       
        -1.0f,  0.0f, 0.0f,     -1.0f,  0.0f, 0.0f,      -1.0f,  0.0f, 0.0f,

        0.0f,  1.0f, 0.0f,     0.0f,  1.0f, 0.0f,      0.0f,  1.0f, 0.0f,       
        0.0f,  1.0f, 0.0f,     0.0f,  1.0f, 0.0f,      0.0f,  1.0f, 0.0f,

        0.0f,  -1.0f, 0.0f,     0.0f,  -1.0f, 0.0f,      0.0f,  -1.0f, 0.0f,       
        0.0f,  -1.0f, 0.0f,     0.0f,  -1.0f, 0.0f,      0.0f,  -1.0f, 0.0f,
    };

    unsigned int vbo_point = 0;
    glGenBuffers (1, &vbo_point);
    glBindBuffer (GL_ARRAY_BUFFER, vbo_point);
    glBufferData (GL_ARRAY_BUFFER, 6* 6*3 * sizeof (float), points, GL_STATIC_DRAW);

    unsigned int vbo_normals = 0;
    glGenBuffers (1, &vbo_normals);
    glBindBuffer (GL_ARRAY_BUFFER, vbo_normals);
    glBufferData (GL_ARRAY_BUFFER, 6* 6*3 * sizeof (float), points, GL_STATIC_DRAW);

    glGenVertexArrays (1, &_vao);
    glBindVertexArray (_vao);
    glEnableVertexAttribArray (0);
    glBindBuffer (GL_ARRAY_BUFFER, vbo_point);
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    glEnableVertexAttribArray (1);
    glBindBuffer (GL_ARRAY_BUFFER, vbo_normals);
    glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 0, NULL);


    GLuint vs = Shader::loadVertexShader("test.vert");
    GLuint fs = Shader::loadFragmentShader("test.frag");

    shader_programme = glCreateProgram();
    glAttachShader (shader_programme, fs);
    glAttachShader (shader_programme, vs);
    glLinkProgram (shader_programme);

    glUseProgram (shader_programme);

	model_loc = glGetUniformLocation(shader_programme, "model");
    view_location = glGetUniformLocation(shader_programme, "view");
    projection_loc = glGetUniformLocation(shader_programme, "projection");

}


virtual void	MyOpenGLWidget::paintGL()
{
	static float angle = 0;

	mat4 rotation = YrotationMatrix(angle);
	mat4 transUp = translationMatrix(0.0f, 1.0f, 0.0f);
	mat4 transUpTotal(1);


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	cam->display();


	for (int i = 0; i < 8; ++i)
	{
	    mat4 model = translationMatrix(1.5f, 0.0f, 0.0f);
	    model = Yrotate(model, i * 45 * (M_PI)/180.0f);         

	    model = rotation * transUpTotal * model;

	    transUpTotal *= transUp;
	    

	    glUniformMatrix4fv(model_loc, 1, GL_FALSE, model.m);

	    glBindVertexArray (vao);
	    // draw points 0-3 from the currently bound VAO with current in-use shader
	    glDrawArrays (GL_TRIANGLES, 0, 6*6);

	    glBindVertexArray(0);
	    
	}


	swapBuffers();

	angle += 0.01;
}

virtual void	MyOpenGLWidget::resizeGL(int width, int height)
{
    mat4 projection = projectionMatrix(70.0, width/(float)height, 0.1f, 100.0f);
    glUniformMatrix4fv(projection_loc, 1, GL_FALSE, projection.m);

    cam->setProjection(view_location);
}
