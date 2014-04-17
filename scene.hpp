#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include <map>

#include "helper.hpp"
#include "camera.hpp"
#include "light.hpp"
#include "material.hpp"

#include "objet.hpp"

#include <QOpenGLFunctions_3_2_Core>
#include <QOpenGLShaderProgram>
#include <QDebug>
#include <QFile>
#include <QString>
#include <QDomDocument>
#include <QDomElement>
#include <QDomNode>
#include <QDomNodeList>



class Scene: protected QOpenGLFunctions_3_2_Core
{
private:
	QDomDocument 								_xml;

	std::map<const QString, Objet *>			_objets;
	std::map<const QString, Light *> 			_lights;
	std::map<const QString, Material *>			_materials;
	std::map<const QString, GLuint> 			_shaders;


public:
	Camera *									_camera;


public:
	Scene();
	Scene(const QString & fileName);
	
	~Scene();

	void draw();

	Objet * 	getObjet(const QString & name);
	Light * 	getLight(const QString & name);
	Material *	getMaterial(const QString & name);
	GLuint 		getShader(const QString & name);


	void 		addObjet(const QString & name, Objet * o);
	void 		addLight(const QString & name, Light * l);
	void 		addMaterial(const QString & name, Material * m);
	void 		addShader(const QString & name, GLuint s);

	void 		saveAsXML(const QString & fileName);


private:
	void 		loadLights(const QDomElement &);
	void 		loadMaterials(const QDomElement &);
	void 		loadPieces(const QDomElement &);
	void 		loadShaders(const QDomElement &);
	
};

#endif