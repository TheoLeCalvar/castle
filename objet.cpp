#include "objet.hpp"

Objet::Objet(Material * mat, vec3 rotation, vec3 position)
		:_mat(mat), _rotation(rotation), _position(position), _model(1)
{
	initializeOpenGLFunctions(); 
	updateModel();
}

void 	Objet::draw()
{
	GLint activeProgram = 0;
	glGetIntegerv(GL_CURRENT_PROGRAM, &activeProgram);

	if (activeProgram != _shaderId)
		glUseProgram(_shaderId);
	

	if (_mat)
		_mat->update();
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