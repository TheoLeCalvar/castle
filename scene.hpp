#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include <map>

#include "math.hpp"
#include "camera.hpp"
#include "light.hpp"
#include "material.hpp"

#include <QOpenGLFunctions_3_2_Core>
#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QtCore/QString>
#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>
#include <QtXml/QDomNode>
#include <QtXml/QDomNodeList>


class Object;

class Scene: protected QOpenGLFunctions_3_2_Core
{
private:
	QDomDocument 								_xml;

	std::map<const QString, Object *>		_objects;
	std::map<const QString, Light *> 		_lights;
	std::map<const QString, Material *>		_materials;
	std::map<const QString, GLuint> 		_shaders;

	mat4 										_projectionMatrix;

public:
	Camera *									_camera;


public:
	Scene();
	Scene(const QString & fileName);
	
	~Scene();

	void draw();

	Object * 	getObject(const QString & name);
	Light * 	getLight(const QString & name);
	Material *	getMaterial(const QString & name);
	GLuint		getShader(const QString & name);

	void 		setProjectionMatrix(mat4 m);

	void 		addObject(const QString & name, Object * o);
	void 		addLight(const QString & name, Light * l);
	void 		addMaterial(const QString & name, Material * m);
	void 		addShader(const QString & name, GLuint s);

	void 		saveAsXML(const QString & fileName);


private:
	void 		loadLights(const QDomElement &);
	void 		loadMaterials(const QDomElement &);
	void 		loadPieces(const QDomElement &);
	
};

#endif