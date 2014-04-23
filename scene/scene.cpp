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

	QDomElement materiaux, lumieres, camera, pieces, shaders;

	camera 		= root.firstChildElement("camera");
	materiaux 	= root.firstChildElement("materiaux");
	lumieres 	= root.firstChildElement("lumieres");
	pieces 		= root.firstChildElement("pieces");
	shaders 	= root.firstChildElement("shaders");

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

	loadShaders(shaders);
	qDebug() << "Shaders chargés avec succès";

	loadPieces(pieces);
	qDebug() << "Pièces chargées avec succès";
}

Scene::~Scene()
{
	for(auto i : _objets)
		delete i.second;

	for(auto i : _lights)
		delete i.second;

	for(auto i : _materials)
		delete i.second;

	for(auto i : _shaders)
		delete i.second;
}


void 	Scene::draw()
{
	GLint active_shader;
	GLuint projection_location, view_location;
	glGetIntegerv(GL_CURRENT_PROGRAM, &active_shader);

	projection_location = glGetUniformLocation(active_shader, "projection");
	view_location = glGetUniformLocation(active_shader, "view");

	_camera->setProjection(view_location);
	glUniformMatrix4fv(projection_location, 1, GL_FALSE, _projectionMatrix.m);



	std::map<const QString, Objet *>::iterator i;


	_camera->display();

	for (i = _objets.begin(); i != _objets.end(); ++i)
	{
		i->second->draw();
		openGL_check_error();
	}
}

void 		Scene::setProjectionMatrix(const mat4 & m)
{
	_projectionMatrix = m;
}

Objet * 	Scene::getObjet(const QString & name)
{
	auto res = _objets.find(name);


	return (res != _objets.end()) ? res->second : NULL;
}

Light * 	Scene::getLight(const QString & name)
{
	auto res = _lights.find(name);

	return (res != _lights.end()) ? res->second : NULL;

}

Material *	Scene::getMaterial(const QString & name)
{
	auto res = _materials.find(name);

	return (res != _materials.end()) ? res->second : NULL;
}

GLuint 		Scene::getShader(const QString & name)
{
	auto res = _shaders.find(name);

	return (res != _shaders.end()) ? res->second->programId() : 0;
}

void 	Scene::addMaterial(const QString & name, Material * v)
{
	std::pair<const QString, Material *> p(name, v);
	std::pair<std::map<const QString, Material *>::iterator , bool> res = _materials.insert(p);

	if (!res.second)
	{
		qWarning() << "Materiaux deja present";
	}
}

void 	Scene::addLight(const QString & name, Light * v)
{
	std::pair<const QString, Light *> p(name, v);
	std::pair<std::map<const QString, Light *>::iterator , bool> res = _lights.insert(p);

	if (!res.second)
	{
		qWarning() << "Lumiere deja presente";
	}
}

void 	Scene::addObjet(const QString & name, Objet * v)
{
	std::pair<const QString, Objet *> p(name, v);
	std::pair<std::map<const QString, Objet *>::iterator , bool> res = _objets.insert(p);

	if (!res.second)
	{
		qWarning() << "Objet deja present";
	}
}

void 	Scene::addShader(const QString & name, QOpenGLShaderProgram * v)
{
	std::pair<const QString, QOpenGLShaderProgram *> p(name, v);
	std::pair<std::map<const QString, QOpenGLShaderProgram *>::iterator , bool> res = _shaders.insert(p);

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
		Material * tmp = new Material;

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

						tmp->set(GL_AMBIENT, vec4(r,g,b,a));

						qDebug() << "Ambient";
					}
					else if (var2.tagName() == "diffuse")
					{
						r = var2.attribute("r", "0").toFloat();
						g = var2.attribute("g", "0").toFloat();
						b = var2.attribute("b", "0").toFloat();
						a = var2.attribute("a", "0").toFloat();

						tmp->set(GL_DIFFUSE, vec4(r,g,b,a));

						qDebug() << "Diffuse";
					}
					else if (var2.tagName() == "specular")
					{
						r = var2.attribute("r", "0").toFloat();
						g = var2.attribute("g", "0").toFloat();
						b = var2.attribute("b", "0").toFloat();
						a = var2.attribute("a", "0").toFloat();
						s = var2.attribute("s", "0").toFloat();

						tmp->set(GL_SPECULAR, vec4(r,g,b,a));
						tmp->set(s);

						qDebug() << "Specular";
					}
					else if (var2.tagName() == "emissive")
					{
						r = var2.attribute("r", "0").toFloat();
						g = var2.attribute("g", "0").toFloat();
						b = var2.attribute("b", "0").toFloat();
						a = var2.attribute("a", "0").toFloat();

						tmp->set(GL_EMISSION, vec4(r,g,b,a));

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

		addMaterial(nom, tmp);

		material = material.nextSiblingElement("material");
	}
}

void 	Scene::loadLights(const QDomElement & dom)
{
	QDomElement light = dom.firstChildElement("lumiere");

	while(!light.isNull())
	{
		Light * tmp = new Light;
		QString nom = light.attribute("nom"), mat = light.attribute("mat");
		std::map<const QString, Material *>::const_iterator res = _materials.find(mat);

		
		qDebug() << light.attribute("nom");

		if (res != _materials.end())
		{
			tmp->set(GL_AMBIENT, res->second->get(GL_AMBIENT));
			tmp->set(GL_DIFFUSE, res->second->get(GL_DIFFUSE));
			tmp->set(GL_SPECULAR, res->second->get(GL_SPECULAR));
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

						tmp->set(GL_POSITION, vec3(x, y, z));

						qDebug() << "Position";

						break;
					}
				}
				var = var.nextSibling();
			}

		addLight(nom, tmp);

		light = light.nextSiblingElement("lumiere");
	}
}

void 	Scene::loadShaders(const QDomElement & dom)
{
	QDomElement shader = dom.firstChildElement("shader");

	while(!shader.isNull())
	{
		QOpenGLShaderProgram * prog = new QOpenGLShaderProgram();
		QString nom = shader.attribute("nom");

		if(!prog->addShaderFromSourceFile(QOpenGLShader::Fragment, shader.attribute("fragment")))
		{
			qFatal("Erreur de chargement du shader %s\nLogs : %s", shader.attribute("fragment").toStdString().c_str(), prog->log().toStdString().c_str());
		}

		if(!prog->addShaderFromSourceFile(QOpenGLShader::Vertex, shader.attribute("vertex")))
		{
			qFatal("Erreur de chargement du shader %s\nLogs : %s", shader.attribute("vertex").toStdString().c_str(), prog->log().toStdString().c_str());
		}

		if (!prog->link())
		{
			qFatal("Erreur de linkage du shader %s\nLogs  : %s", nom.toStdString().c_str(), prog->log().toStdString().c_str());
		}

		addShader(nom, prog);

		shader = shader.nextSiblingElement("shader");
	}
}

void 	Scene::loadPieces(const QDomElement & dom)
{
	QDomElement piece = dom.firstChildElement("piece");
	Objet * tmp = NULL;


	while (!piece.isNull())
	{
		QString nom = piece.attribute("nom");

		qDebug() << "Traitement de " << nom;

		QString shader_name = piece.attribute("shader");
		GLuint 	shader_id = getShader(shader_name);
		int width, height, length;
		int x, y, z;

		QDomElement dim = piece.firstChildElement("dimension");
		QDomElement pos = piece.firstChildElement("position");
		QDomElement murs = piece.firstChildElement("murs");

		if (!dim.isNull())
		{
			width = dim.attribute("width").toInt();
			height = dim.attribute("height").toInt();
			length = dim.attribute("length").toInt();
			qDebug() << "Dimension : " << width << height << length;
		}
		else
		{
			width = 1;
			height = 1;
			length = 1;
			qDebug() << "Pas de dimension trouvé pour" << nom << "valeur par défaut 1x1x1";
		}

		if (!pos.isNull())
		{
			x = pos.attribute("x").toUInt();
			y = pos.attribute("y").toUInt();
			z = pos.attribute("z").toUInt();
			qDebug() << "Position : " << x << y << z;
		}
		else
		{
			x = 0;
			y = 0;
			z = 0;
			qDebug() << "Pas de position trouvée pour" << nom << "valeur par défaut (0,0,0)";
		}

		tmp = new Piece(vec3(width, height, length), vec3(), vec3(x, y, z), NULL, NULL);


		if (!murs.isNull())
		{

			QDomElement mur = murs.firstChildElement("mur");
			Plan * plan = NULL;

			while(!mur.isNull())
			{
				qDebug() << "Un mur !";

				QString cote = mur.attribute("cote");
				QString material = mur.attribute("mat");
				std::vector<QRectF> fenetres;

				QDomElement fenetre = mur.firstChildElement("fenetre");

				while(!fenetre.isNull())
				{
					fenetres.push_back(
								QRectF(	
										fenetre.attribute("x", "1.0").toFloat(), 
										fenetre.attribute("y", "1.0").toFloat(), 
										fenetre.attribute("width", "1.0").toFloat(), 
										fenetre.attribute("height", "1.0").toFloat()
									));

					fenetre = fenetre.nextSiblingElement("fenetre");
				}

				for(auto q : fenetres)
				{
					qDebug() << q;
				}

				if (cote == "avant")
				{
					plan = new Plan(width, height, 10*width, 10*height, fenetres, getMaterial(material), vec3(0.0f, 180.0f, 0.0f), vec3(width, 0.0f, length));
				}
				else if (cote == "arriere")
				{
					plan = new Plan(width, height, 10*width, 10*height, fenetres, getMaterial(material), vec3(), vec3());
				}
				else if (cote == "haut")
				{
					plan = new Plan(width, length, 10*width, 10*length, fenetres, getMaterial(material), vec3(90.0f, 0.0f, 0.0f), vec3(0.0f, height, 0.0f));
				}
				else if (cote == "bas")
				{
					plan = new Plan(width, length, 10*width, 10*length, fenetres, getMaterial(material), vec3(-90.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, length));
				}
				else if (cote == "droite")
				{
					plan = new Plan(length, height, 10*length, 10*height, fenetres, getMaterial(material), vec3(0.0f, 90.0f, 0.0f), vec3(0.0f, 0.0f, length));	
				}
				else if (cote == "gauche")
				{
					plan = new Plan(length, height, 10*length, 10*height, fenetres, getMaterial(material), vec3(0.0f, -90.0f, 0.0f), vec3(width, 0.0f, 0.0f));
				}

				if (plan)
				{

					plan->shaderId(shader_id);
					dynamic_cast<Piece *>(tmp)->addWall(plan);

					plan = NULL;
				}

				mur = mur.nextSiblingElement("mur");
			}			
		}
		else
		{
			qDebug() << "Pas de murs trouvés, problème ?";
		}


		




		addObjet(nom, tmp);

		piece = piece.nextSiblingElement("piece");
	}
}

void Scene::saveAsXML(const QString & fileName)
{
	QFile  file;
	file.setFileName(fileName);
}