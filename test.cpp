#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <stdio.h>
#include <cmath>

#include "camera.hpp"
#include "shader.hpp"

GLFWwindow* window = NULL;
Camera * cam = NULL;


void keyboard_handler(GLFWwindow *, int key, int, int action, int);

int main () {
//*
      // start GL context and O/S window using the GLFW helper library
      if (!glfwInit ()) {
        fprintf (stderr, "ERROR: could not start GLFW3\n");
        return 1;
      } 

    // uncomment these lines if on Apple OS X
    #ifdef __APPLE__
        glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #endif

    window = glfwCreateWindow (640, 480, "Hello Triangle", NULL, NULL);
    if (!window) {
        fprintf (stderr, "ERROR: could not open window with GLFW3\n");
        glfwTerminate();
        return 1;
    }


    glfwMakeContextCurrent (window);
                              
    glfwSetKeyCallback(window, keyboard_handler);
    glfwSetCursorPosCallback(window, Camera::mouse_event);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    glfwSetCursorPos (window, 400, 300);

    // start GLEW extension handler
    glewExperimental = GL_TRUE;
    glewInit ();

    // get version info
    const GLubyte* renderer = glGetString (GL_RENDERER); // get renderer string
    const GLubyte* version = glGetString (GL_VERSION); // version as a string
    printf ("Renderer: %s\n", renderer);
    printf ("OpenGL version supported %s\n", version);

    // tell GL to only draw onto a pixel if the shape is closer to the viewer
    glEnable (GL_DEPTH_TEST); // enable depth-testing
    glDepthFunc (GL_LESS); // depth-testing interprets a smaller value as "closer"

    cam = new Camera(0.0f, 1.0f, 0.0f);



    // float points[] = {
    //     -0.5f, -0.5f, 0.5f,
    //     0.5f, -0.5f, 0.5f,
    //     0.0, 0.0f, 0.0f,

    //     0.5f, -0.5f, 0.5f,
    //     0.0f, -0.5f, -0.5f,
    //     0.0, 0.0f, 0.0f,

    //     0.5f, -0.5f, 0.5f,
    //     -0.5f, -0.5f, 0.5f,
    //     0.0, 0.0f, 0.0f
    // };



    // float points[] =
    // {
    //     -0.5f, -0.5f, 0.5f,
    //     0.5f, -0.5f, 0.5f, 
    //     0.5f, 0.5f, 0.5f, 
    //     -0.5f, 0.5f, 0.5f, 

    //     -0.5f, -0.5f, -0.5f,
    //     0.5f, -0.5f, -0.5f, 
    //     0.5f, 0.5f, -0.5f, 
    //     -0.5f, 0.5f, -0.5f
    // };

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

    unsigned int vbo = 0;
    glGenBuffers (1, &vbo);
    glBindBuffer (GL_ARRAY_BUFFER, vbo);
    glBufferData (GL_ARRAY_BUFFER, 6* 6*3 * sizeof (float), points, GL_STATIC_DRAW);

    unsigned int vao = 0;
    glGenVertexArrays (1, &vao);
    glBindVertexArray (vao);
    glEnableVertexAttribArray (0);
    glBindBuffer (GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, NULL);



    GLuint vs = Shader::loadVertexShader("test.vert");
    GLuint fs = Shader::loadFragmentShader("test.frag");

    unsigned int shader_programme = glCreateProgram ();
    glAttachShader (shader_programme, fs);
    glAttachShader (shader_programme, vs);
    glLinkProgram (shader_programme);

    glUseProgram (shader_programme);

    GLuint resolution_loc = glGetUniformLocation(shader_programme, "resolution");
    glUniform2f(resolution_loc, 640, 480);
    
    mat4 projection = projectionMatrix(70.0, 640.0f/480.0f, 0.1f, 100.0f);

    GLuint projection_loc = glGetUniformLocation(shader_programme, "projection");
    glUniformMatrix4fv(projection_loc, 1, GL_FALSE, projection.m);

    GLuint model_loc = glGetUniformLocation(shader_programme, "model");


    glBindFragDataLocation(shader_programme, 0, "color_out");

    GLuint view_location = glGetUniformLocation(shader_programme, "view");
    cam->setProjection(view_location);



    while (!glfwWindowShouldClose (window)) 
    {
        static float angle = 0;

        mat4 rotation = YrotationMatrix(angle);


        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        cam->display();

        glUniformMatrix4fv(model_loc, 1, GL_FALSE, rotation.m);


        glBindVertexArray (vao);
        // draw points 0-3 from the currently bound VAO with current in-use shader
        glDrawArrays (GL_TRIANGLES, 0, 6*6);

        glBindVertexArray(0);

        // // update other events like input handling 
        glfwPollEvents ();
        // put the stuff we've been drawing onto the display
        glfwSwapBuffers (window);

        angle += 0.01;
    }


    // close GL context and any other GLFW resources
    glfwTerminate();
    return 0;
//*/
}


void keyboard_handler(GLFWwindow *, int key, int, int action, int)
{
    switch (key) 
    {
        case GLFW_KEY_ESCAPE: 
            glfwSetWindowShouldClose(window, GL_TRUE);                 
        break; 

        case GLFW_KEY_LEFT:
        case GLFW_KEY_A:
            cam->_gauche_presse = (action == GLFW_PRESS) || (action == GLFW_REPEAT);
        break;

        case GLFW_KEY_UP:
        case GLFW_KEY_W:
            cam->_avant_presse = (action == GLFW_PRESS) || (action == GLFW_REPEAT);
        break;

        case GLFW_KEY_RIGHT:
        case GLFW_KEY_D:
            cam->_droite_presse = (action == GLFW_PRESS) || (action == GLFW_REPEAT);
        break;

        case GLFW_KEY_DOWN:
        case GLFW_KEY_S:
            cam->_arriere_presse = (action == GLFW_PRESS) || (action == GLFW_REPEAT);
        break;

        case GLFW_KEY_PAGE_UP:
        case GLFW_KEY_Q:
            cam->_haut_presse  = (action == GLFW_PRESS) || (action == GLFW_REPEAT);
        break;

        case GLFW_KEY_PAGE_DOWN:
        case GLFW_KEY_Z:
            cam->_bas_presse = (action == GLFW_PRESS) || (action == GLFW_REPEAT);
        break;
    }
}

