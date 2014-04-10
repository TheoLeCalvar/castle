#ifndef SCENE_H
#define SCENE_H


#include <GL/glew.h>

#include <iostream>
#include <stdio.h>
#include <cmath>

#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>


class Scene
{
private:
	QDomDocument 								_xml;

	std::map<const std::string, Object *>		_objects;
	std::map<const std::string, Light *> 		_lights;
	std::map<const std::string, Material *>		_materials;
	std::map<const std::string, GLuint> 		_shaders;

public:
	Camera *									_camera;


public:
	Scene();
	Scene(const std::string & fileName);
	
	~Scene();

	void draw();

	Object * 	getObject(const std::string & name);
	Light * 	getLight(const std::string & name);
	Material *	getMaterial(const std::string & name);
	GLuint		getShader(const std::string & name);

	void 		addObject(const std::string & name, Object * o);
	void 		addLight(const std::string & name, Light * l);
	void 		addMaterial(const std::string & name, Material * m);
	void 		addShader(const std::string & name, GLuint * s);

	void 		saveAsXML(const std::string & fileName);


private:
	void 		loadLights(const QDomNode &);
	void 		loadMaterials(const QDomNode &);
	void 		loadPieces(const QDomNode &);
	
};

#endif