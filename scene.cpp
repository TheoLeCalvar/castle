#include "scene.hpp"

Scene::Scene()
{
	initializeOpenGLFunctions();
	_camera = new Camera();
}

Scene::Scene(const QString & fileName):
	_xml("scene")
{
	initializeOpenGLFunctions();
	QFile file;
	file.setFileName(fileName);

	QDomElement root; 

	if (!file.open(QIODevice::ReadOnly))
	{
		qFatal("Impossible d'ouvrir le fichier \"%s\"", fileName.toStdString().c_str());
	}


	_xml.setContent(&file);

	file.close();


	root = _xml.documentElement();

	QDomElement materiaux, lumieres, camera, pieces;

	camera = root.firstChildElement("camera");
	materiaux = root.firstChildElement("materiaux");
	lumieres = root.firstChildElement("lumieres");
	pieces = root.firstChildElement("pieces");

	QDomElement camera_position = camera.firstChild().toElement();


	_camera = new Camera(
		camera_position.attribute("x").toFloat(),
		camera_position.attribute("y").toFloat(),
		camera_position.attribute("z").toFloat()
		);
	qDebug() << "Camera chargee avec succes";


	loadMaterials(materiaux);
	qDebug() << "Materiaux charges avec succes";

	loadLights(lumieres);
	qDebug() << "Lumieres chargées avec succes";

	// loadPieces(pieces);
	// qDebug() << "Pièces chargées avec succès";

}

Scene::~Scene()
{

}

void 	Scene::addMaterial(const QString & name, Material * v)
{
	std::pair<const QString, Material *> p(name, v->clone());
	std::pair<std::map<const QString, Material *>::iterator , bool> res = _materials.insert(p);

	if (!res.second)
	{
		qWarning() << "Materiaux deja present";
	}
}

void 	Scene::addLight(const QString & name, Light * v)
{
	std::pair<const QString, Light *> p(name, v->clone());
	std::pair<std::map<const QString, Light *>::iterator , bool> res = _lights.insert(p);

	if (!res.second)
	{
		qWarning() << "Lumiere deja presente";
	}
}

// void 	Scene::addObject(const QString & name, Object * v)
// {
// 	std::pair<const QString, Object *> p(name, v->clone());
// 	std::pair<std::map<const QString, Object *>::iterator , bool> res = _objects.insert(p);

// 	if (!res.second)
// 	{
// 		qWarning() << "Objet deja present";
// 	}
// }

void 	Scene::addShader(const QString & name, GLuint v)
{
	std::pair<const QString, GLuint> p(name, v);
	std::pair<std::map<const QString, GLuint>::iterator , bool> res = _shaders.insert(p);

	if (!res.second)
	{
		qWarning() << "Shader deja present";
	}
}

void 	Scene::loadMaterials(const QDomElement & dom)
{
	QDomElement material = dom.firstChildElement("material");

	while(!material.isNull())
	{
		qDebug() << material.attribute("nom");
		QString nom = material.attribute("nom");
		Material tmp;

			QDomNode var = material.firstChild();


			while(!var.isNull())
			{
				float r, b, g, a, s;
				QString path;
				if (var.isElement())
				{	
					QDomElement var2 = var.toElement();

					if (var2.tagName() == "ambient")
					{
						r = var2.attribute("r", "0").toFloat();
						g = var2.attribute("g", "0").toFloat();
						b = var2.attribute("b", "0").toFloat();
						a = var2.attribute("a", "0").toFloat();

						tmp.set(GL_AMBIENT, vec4(r,g,b,a));

						qDebug() << "Ambient";
					}
					else if (var2.tagName() == "diffuse")
					{
						r = var2.attribute("r", "0").toFloat();
						g = var2.attribute("g", "0").toFloat();
						b = var2.attribute("b", "0").toFloat();
						a = var2.attribute("a", "0").toFloat();

						tmp.set(GL_DIFFUSE, vec4(r,g,b,a));

						qDebug() << "Diffuse";
					}
					else if (var2.tagName() == "specular")
					{
						r = var2.attribute("r", "0").toFloat();
						g = var2.attribute("g", "0").toFloat();
						b = var2.attribute("b", "0").toFloat();
						a = var2.attribute("a", "0").toFloat();
						s = var2.attribute("s", "0").toFloat();

						tmp.set(GL_SPECULAR, vec4(r,g,b,a));
						tmp.set(s);

						qDebug() << "Specular";
					}
					else if (var2.tagName() == "emissive")
					{
						r = var2.attribute("r", "0").toFloat();
						g = var2.attribute("g", "0").toFloat();
						b = var2.attribute("b", "0").toFloat();
						a = var2.attribute("a", "0").toFloat();

						tmp.set(GL_EMISSION, vec4(r,g,b,a));

						qDebug() << "Emissive";
					}
					else if (var2.tagName() == "texture")
					{
						path = var2.attribute("src", "");



						qDebug() << "Texture" << "TODO !";
					}
				}
				

				var = var.nextSibling();
			}

		addMaterial(nom, &tmp);

		material = material.nextSiblingElement("material");
	}
}

void 	Scene::loadLights(const QDomElement & dom)
{
	QDomElement light = dom.firstChildElement("lumiere");

	while(!light.isNull())
	{
		Light tmp;
		QString nom = light.attribute("nom"), mat = light.attribute("mat");
		std::map<const QString, Material *>::const_iterator res = _materials.find(mat);
		
		qDebug() << light.attribute("nom");

		if (res != _materials.end())
		{
			tmp.set(GL_AMBIENT, res->second->get(GL_AMBIENT));
			tmp.set(GL_DIFFUSE, res->second->get(GL_DIFFUSE));
			tmp.set(GL_SPECULAR, res->second->get(GL_SPECULAR));
		}


			QDomNode var = light.firstChild();


			while(!var.isNull())
			{
				float x, y, z;
				QString repere, path;

				if (var.isElement())
				{	
					QDomElement var2 = var.toElement();

					if (var2.tagName() == "position")
					{
						x = var2.attribute("x", "0").toFloat();
						y = var2.attribute("y", "0").toFloat();
						z = var2.attribute("z", "0").toFloat();
						repere = var2.attribute("repere", "world");

						qDebug() << "Repere a gerer";

						tmp.set(GL_POSITION, vec3(x, y, z));

						qDebug() << "Position";

						break;
					}
				}
				var = var.nextSibling();
			}

		addLight(nom, &tmp);

		light = light.nextSiblingElement("lumiere");
	}
}

void Scene::saveAsXML(const QString & fileName)
{
	QFile  file;
	file.setFileName(fileName);


}
