#include "scene.hpp"
#include "mesh.hpp"
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
	qDebug() << "Camera chargée avec succes";


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
	for(auto i : _pieces)
		delete i;

	for(auto i : _lights)
		delete i;

	for(auto i : _materials)
		delete i;

	for(auto i : _shaders)
		delete i;
}


void 	Scene::draw()
{

	_camera->display();
	

	for(auto i : _pieces)
	{
		i->draw();
		openGL_check_error();
	}

	for(auto i: _shaders)
	{
		setActiveShader(i->programId());

		openGL_check_error();

		for(auto j : _lights)
		{
			j->update();
			openGL_check_error();
		}
	}

}

Piece * 	Scene::getPiece(const QString & name)
{
	return _pieces.value(name);
}

Light * 	Scene::getLight(const QString & name)
{
	return _lights.value(name);
}

Material *	Scene::getMaterial(const QString & name)
{
	return _materials.value(name);
}

GLuint 		Scene::getShader(const QString & name)
{
	auto shader = _shaders.value(name);
	return (shader ? shader->programId() : 0);
}

QStringList Scene::getPiecesName() const
{
	return _pieces.keys();
}


QStringList Scene::getLightsNames() const
{
	return _lights.keys();
}

QStringList Scene::getMaterialsNames() const
{
	return _materials.keys();
}

QStringList Scene::getShadersNames() const
{
	return _shaders.keys();
}

void 	Scene::addMaterial(const QString & name, Material * v)
{
	if (_materials.contains(name))
	{
		qWarning() << "Materiaux deja present";
	}
	else
	{
		_materials[name] = v;
	}
}

void 	Scene::addLight(const QString & name, Light * v)
{
	if (_lights.contains(name))
	{
		qWarning() << "Lumiere deja presente";
	}
	else
	{
		_lights[name] = v;
	}
}

void 	Scene::addPiece(const QString & name, Piece * v)
{
	if (_pieces.contains(name))
	{
		qWarning() << "Piece deja present";
	}
	else
	{
		_pieces[name] = v;
	}
}

void 	Scene::addShader(const QString & name, QOpenGLShaderProgram * v)
{
	qDebug() << "Ajout shader " << name << v;
	if (_shaders.contains(name))
	{
		qWarning() << "Shader deja present";
	}
	else
	{
		_shaders[name] = v;
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
				unsigned char location;
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
					}
					else if (var2.tagName() == "diffuse")
					{
						r = var2.attribute("r", "0").toFloat();
						g = var2.attribute("g", "0").toFloat();
						b = var2.attribute("b", "0").toFloat();
						a = var2.attribute("a", "0").toFloat();

						tmp->set(GL_DIFFUSE, vec4(r,g,b,a));
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
					}
					else if (var2.tagName() == "emissive")
					{
						r = var2.attribute("r", "0").toFloat();
						g = var2.attribute("g", "0").toFloat();
						b = var2.attribute("b", "0").toFloat();
						a = var2.attribute("a", "0").toFloat();

						tmp->set(GL_EMISSION, vec4(r,g,b,a));
					}
					else if (var2.tagName() == "texture")
					{
						path = var2.attribute("src", "");
						location = var2.attribute("location", "500").toUInt();

						if (location < 3)
							tmp->addTexture(path, location);
						else
							tmp->addTexture(path, 0);
						
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
		int lightNum = light.attribute("num", "0").toInt();
		Material * res = _materials[mat];

		tmp->setNumber(lightNum);
		
		qDebug() << light.attribute("nom");

		if (res)
		{
			tmp->set(GL_AMBIENT, res->get(GL_AMBIENT));
			tmp->set(GL_DIFFUSE, res->get(GL_DIFFUSE));
			tmp->set(GL_SPECULAR, res->get(GL_SPECULAR));
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

					qDebug() << "Repere a gerer " << x << y << z;

					tmp->set(GL_POSITION, vec3(x, y, z));

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
	Piece * pieceTmp = NULL;


	while (!piece.isNull())
	{
		QString nom = piece.attribute("nom");
		QString materialPiece = piece.attribute("mat", "");
		QString shaderName = piece.attribute("shader");
		GLuint 	shaderId = getShader(shaderName);
		int width, height, length;
		int x, y, z;

		QDomElement dim = piece.firstChildElement("dimension");
		QDomElement pos = piece.firstChildElement("position");
		QDomElement murs = piece.firstChildElement("murs");
		QDomElement objets = piece.firstChildElement("objets");

		qDebug() << "Traitement de " << nom;


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

		pieceTmp = new Piece(vec3(width, height, length), vec3(), vec3(x, y, z), NULL);
		pieceTmp->shaderId(shaderId);
		pieceTmp->material(getMaterial(materialPiece));
		pieceTmp->name(nom);

		if (!murs.isNull())
		{

			QDomElement mur = murs.firstChildElement("mur");
			Plan * plan = NULL;

			while(!mur.isNull())
			{
				QString cote = mur.attribute("cote");
				QString material = mur.attribute("mat", "");
				QList<QRectF> fenetres;

				QDomElement fenetre = mur.firstChildElement("fenetre");

				while(!fenetre.isNull())
				{
					fenetres <<	QRectF(	
										fenetre.attribute("x", "1.0").toFloat(), 
										fenetre.attribute("y", "1.0").toFloat(), 
										fenetre.attribute("width", "1.0").toFloat(), 
										fenetre.attribute("height", "1.0").toFloat()
									);

					fenetre = fenetre.nextSiblingElement("fenetre");
				}

				if (cote == "avant")
				{
					plan = new Plan(width, height, 20, 20, fenetres, getMaterial(material), vec3(0.0f, 180.0f, 0.0f), vec3(width, 0.0f, length));
				}
				else if (cote == "arriere")
				{
					plan = new Plan(width, height, 20, 20, fenetres, getMaterial(material), vec3(), vec3());
				}
				else if (cote == "haut")
				{
					plan = new Plan(width, length, 20, 20, fenetres, getMaterial(material), vec3(90.0f, 0.0f, 0.0f), vec3(0.0f, height, 0.0f));
				}
				else if (cote == "bas")
				{
					plan = new Plan(width, length, 20, 20, fenetres, getMaterial(material), vec3(-90.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, length));
				}
				else if (cote == "droite")
				{
					plan = new Plan(length, height, 20, 20, fenetres, getMaterial(material), vec3(0.0f, 90.0f, 0.0f), vec3(0.0f, 0.0f, length));	
				}
				else if (cote == "gauche")
				{
					plan = new Plan(length, height, 20, 20, fenetres, getMaterial(material), vec3(0.0f, -90.0f, 0.0f), vec3(width, 0.0f, 0.0f));
				}

				if (plan)
				{
					plan->name(nom + "_" + cote);
					plan->parent(pieceTmp);
					pieceTmp->addChild(plan);

					plan = NULL;
				}

				mur = mur.nextSiblingElement("mur");
			}			
		}
		else
		{
			qDebug() << "Pas de murs trouvés, problème ?";
		}


		if (!objets.isNull())
		{
			QDomElement objet = objets.firstChildElement("objet");

			while(!objet.isNull())
			{
				float xRot, yRot, zRot;
				xRot = objet.attribute("Xrot", "0").toFloat();
				yRot = objet.attribute("Yrot", "0").toFloat();
				zRot = objet.attribute("Zrot", "0").toFloat();
				QString modeleObjet = objet.attribute("modele");
				QString nomObjet = objets.attribute("nom", nom + "_" + modeleObjet);
				QString matObjet = objet.attribute("mat", "");
				QString shaderObjet = objet.attribute("shader", "");


				QList<Mesh *> meshs = Mesh::loadMesh(modeleObjet, this);

				if (meshs.empty())
				{
					qFatal("Stop, erreur de chargement");
				}
				for(auto mesh : meshs)
				{
					mesh->parent(pieceTmp);
					mesh->rotation(vec3(xRot, yRot, zRot));
					mesh->material(getMaterial(matObjet));
					mesh->shaderId(getShader(shaderObjet));
					mesh->name(nomObjet);
				}


				QDomElement position = objet.firstChildElement("position");

				if (!position.isNull())
				{
					float x, y, z;

					x = position.attribute("x", "0").toFloat();
					y = position.attribute("y", "0").toFloat();
					z = position.attribute("z", "0").toFloat();

					for(auto mesh: meshs)
						mesh->position(vec3(x, y, z));
				}

				for(auto mesh: meshs)
					pieceTmp->addChild(mesh);

				objet = objet.nextSiblingElement("objet");
			}
		}




		addPiece(nom, pieceTmp);

		piece = piece.nextSiblingElement("piece");
	}
}

void Scene::saveAsXML(const QString & fileName)
{
	QFile  file;
	file.setFileName(fileName);
}
