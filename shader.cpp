#include "shader.hpp"
#include <string.h>

GLuint Shader::loadVertexShader(const std::string & fileName)
{
	return loadFile(fileName, GL_VERTEX_SHADER);
}

GLuint Shader::loadFragmentShader(const std::string & fileName)
{
	return loadFile(fileName, GL_FRAGMENT_SHADER);
}

GLuint Shader::loadFile(const std::string & fileName, GLenum shaderType)
{
	GLuint shaderId;
	char * shaderSource = readFile(fileName);
	char * errorMessage = NULL;
	int shaderCompiled = 0;
	int errorLength = 0;

    shaderId = glCreateShader (shaderType);

    glShaderSource (shaderId, 1, (const GLchar **) &shaderSource, NULL);
    glCompileShader (shaderId);
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &shaderCompiled);


    if (shaderCompiled != GL_TRUE)
    {
    	glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &errorLength);

    	errorMessage  = new char[errorLength];

    	glGetShaderInfoLog(shaderId, errorLength, &errorLength, errorMessage);

    	std::cout << '"' << fileName << "\" : " << errorMessage << std::endl;

    	delete[] errorMessage;

    	shaderId = 0;
    }

	delete[] shaderSource;
	return shaderId;
}
char * Shader::readFile(const std::string & fileName)
{
	std::ifstream inFile(fileName);
	std::string ligne;
	std::ostringstream os;
	char * ret;

	while(std::getline(inFile, ligne))
	{
		os << ligne << '\n';
	}

	ret = new char[os.str().length() +1];
	strncpy(ret, os.str().c_str(), os.str().length() + 1);


	return ret;
}

void debug()
{
	Shader::loadFragmentShader("test.frag");
}