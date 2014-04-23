#include "objet.hpp"

Objet::Objet(Material * mat, vec3 rotation, vec3 position, Objet * parent)
		:_parent(parent), _mat(mat), _rotation(rotation), _position(position), _model(1), _model_location(0)
{
	initializeOpenGLFunctions(); 
	updateModel();
}

void 	Objet::draw()
{
	GLint activeProgram = 0;
	glGetIntegerv(GL_CURRENT_PROGRAM, &activeProgram);

	if ((GLuint)activeProgram != _shaderId)
	{
		qDebug() << "Changement de shader, update des location pour projection et view à faire";
		glUseProgram(_shaderId);
	}

	if (!_model_location){
		_model_location = glGetUniformLocation(_shaderId, "model");
	}
	

	if (_mat)
		_mat->update();
	else if(_parent && _parent->_mat)
		_parent->_mat->update();
}

void	Objet::position(vec3 p)
{
	_position = p;
	updateModel();
}

void	Objet::rotation(vec3 r)
{
	_rotation = r;
	updateModel();
}

void 	Objet::updateModel()
{
	_model = XrotationMatrix(_rotation[0]);
	_model = Yrotate(_model, _rotation[1]);
	_model = Zrotate(_model, _rotation[2]);

	_model = translate(_model, _position);
}