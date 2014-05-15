#include "objet.hpp"

Objet::Objet(const QString & name, Material * mat, vec3 rotation, vec3 position, Objet * parent)
		:_parent(parent), _mat(mat), _name(name), _rotation(rotation), _position(position), _model(1), _shaderId(0)
{
	initializeOpenGLFunctions(); 
	updateModel();
}

Objet::Objet(const Objet & o)
		:_parent(o._parent), _mat(o._mat), _name(o._name), _rotation(o._rotation), _position(o._position), _model(o._model), _shaderId(o._shaderId)
{
	initializeOpenGLFunctions(); 
}

void 	Objet::draw()
{

	activateShader();


	applyMaterial();

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


void 	Objet::applyMaterial()
{
	if (_mat)
	{
		_mat->update();
	}
	else if(_parent)
	{
		_parent->applyMaterial();
	}
}

void 	Objet::activateShader()
{
	if (_shaderId)
	{
		setActiveShader(_shaderId);
	}
	else if (_parent)
	{
		_parent->activateShader();
	}
	else
	{
		qDebug() << "Pas de shader à charger, résultat random";
	}
}

void 	Objet::updateModel()
{
	_model = XrotationMatrix(_rotation[0]);
	_model = Yrotate(_model, _rotation[1]);
	_model = Zrotate(_model, _rotation[2]);

	_model = translate(_model, _position);
}