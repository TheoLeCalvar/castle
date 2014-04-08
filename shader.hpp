#ifndef SHADER_H
#define SHADER_H


#include <GL/glew.h> 
#include <iostream>
#include <fstream>
#include <sstream>

class Shader
{
public:
	static GLuint loadVertexShader(const std::string & fileName);
	static GLuint loadFragmentShader(const std::string & fileName);

private:
	static GLuint loadFile(const std::string & fileName, GLenum shaderType);
	static char * readFile(const std::string & fileName);
};

void debug();

#endif