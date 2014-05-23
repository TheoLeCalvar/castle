#include "scene.hpp"
#include "mesh.hpp"
#include "node.hpp"
#include "camera.hpp"

Scene::Scene()
{
	initializeOpenGLFunctions();
	_camera = new Camera(this);
}

Scene::Scene(const QString & fileName)
{
	initializeOpenGLFunctions();
	QFile file;
	QDomDocument xml;
	file.setFileName(fileName);

	QDomElement root; 

	if (!file.open(QIODevice::ReadOnly))
	{
		qFatal("Impossible d'ouvrir le fichier \"%s\"", fileName.toStdString().c_str());
	}


	xml.setContent(&file);

	file.close();


	root = xml.documentElement();

	QDomElement materiaux, lumieres, camera, pieces, shaders;

	camera 		= root.firstChildElement("camera");
	materiaux 	= root.firstChildElement("materiaux");
	lumieres 	= root.firstChildElement("lumieres");
	pieces 		= root.firstChildElement("pieces");
	shaders 	= root.firstChildElement("shaders");

	QDomElement camera_position = camera.firstChild().toElement();


	_camera = new Camera(
		this,
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

	for(auto i : _loadedShaders)
		delete i;

	Material::clear();
}


void 	Scene::draw()
{
	orderLights();

	int size = _orderedLights.size();



	_camera->display();
	

	for(auto i : _pieces)
	{
		i->draw();
		openGL_check_error();
	}

	for(auto i: _shaders)
	{
		char cpt = 0;

		setActiveShader(i->programId());

		openGL_check_error();


		for(auto j = _orderedLights.begin(); j != _orderedLights.begin() + (size >= MAX_LIGHT ? MAX_LIGHT : size); ++j)
		{
			j.value()->update(cpt++);
			openGL_check_error();
		}
	}

}

Piece * 	Scene::getPiece(const QString & name) const
{
	return _pieces.value(name);
}

Light * 	Scene::getLight(const QString & name) const
{
	return _lights.value(name);
}

Material *	Scene::getMaterial(const QString & name) const
{
	return _materials.value(name);
}

GLuint 		Scene::getShader(const QString & name) const
{
	auto shader = _shaders.value(name);
	return (shader ? shader->programId() : 0);
}

QString 	Scene::getShaderNameByID(GLuint id) const
{
	for(auto i = _shaders.begin(); i != _shaders.end(); ++i)
	{
		if (i.value()->programId() == id)
		{
			return i.key();
		}
	}

	return "not found";
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

QString 	Scene::getMaterialName(Material * m) const
{
	return _materials.key(m, "");
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

	addMaterial("neutre", new Material());
}

void 	Scene::loadLights(const QDomElement & dom)
{
	QDomElement light = dom.firstChildElement("lumiere");

	while(!light.isNull())
	{
		Light * tmp = new Light;
		QString nom = light.attribute("nom"), mat = light.attribute("mat");

		
		qDebug() << light.attribute("nom");

		if (mat != "")
		{
			Material * res = _materials.value(mat);

			if(res)
			{
				tmp->set(GL_AMBIENT, res->get(GL_AMBIENT));
				tmp->set(GL_DIFFUSE, res->get(GL_DIFFUSE));
				tmp->set(GL_SPECULAR, res->get(GL_SPECULAR));
			}
		}
		else
		{
			QDomElement ambient = light.firstChildElement("ambient");
			QDomElement diffuse = light.firstChildElement("diffuse");
			QDomElement specular = light.firstChildElement("specular");

			vec3 vAmbient(	
				ambient.attribute("r", "0").toFloat(),
				ambient.attribute("g", "0").toFloat(),
				ambient.attribute("b", "0").toFloat());

			vec3 vDiffuse(
				diffuse.attribute("r", "0").toFloat(),
				diffuse.attribute("g", "0").toFloat(),
				diffuse.attribute("b", "0").toFloat());

			vec3 vSpecular(
				specular.attribute("r", "0").toFloat(),
				specular.attribute("g", "0").toFloat(),
				specular.attribute("b", "0").toFloat());

			tmp->set(GL_DIFFUSE, vDiffuse);
			tmp->set(GL_SPECULAR, vSpecular);
			tmp->set(GL_AMBIENT, vAmbient);

		}

		float x, y, z;
		QDomElement position = light.firstChildElement("position");

		x = position.attribute("x", "0").toFloat();
		y = position.attribute("y", "0").toFloat();
		z = position.attribute("z", "0").toFloat();


		tmp->set(GL_POSITION, vec3(x, y, z));


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
		QString fragName = shader.attribute("fragment");
		QString vertName = shader.attribute("vertex");

		QOpenGLShader * frag = _loadedShaders.value(fragName);
		QOpenGLShader * vert = _loadedShaders.value(vertName);

		if(!frag)
		{
			frag = new QOpenGLShader(QOpenGLShader::Fragment);
			if(!frag->compileSourceFile(fragName))
			{
				qDebug() << "Erreur de chargement du shader " << fragName;
				qDebug() << "Log : " << frag->log();

				qFatal("Erreur de chargement de shader");
			}
			
			_loadedShaders.insert(fragName, frag);	
		}

		if(!vert)
		{
			vert = new QOpenGLShader(QOpenGLShader::Vertex);
			if(!vert->compileSourceFile(vertName))
			{
				qDebug() << "Erreur de chargement du shader " << vertName;
				qDebug() << "Log : " << vert->log();

				qFatal("Erreur de chargement de shader");
			}
			
			_loadedShaders.insert(vertName, vert);	
		}

		prog->addShader(frag);
		prog->addShader(vert);

		if (!prog->link())
		{
			qDebug() << "Erreur de chargement du shader " << nom;
			qDebug() << "Log : " << prog->log();

			qFatal("Erreur de chargement de shader");
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
		vec3 position;
		vec3 scale(1.0f, 1.0f, 1.0f);

		QDomElement dim = piece.firstChildElement("dimension");
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


		position = readPosition(piece.firstChildElement("position"));
		qDebug() << "Position : " << position;

		scale = readScale(piece.firstChildElement("scale"));
		qDebug() << "Scale : " << scale;


		pieceTmp = new Piece(vec3(width, height, length), vec3(), position, NULL);
		pieceTmp->shaderId(shaderId);
		pieceTmp->material(getMaterial(materialPiece));
		pieceTmp->name(nom);
		pieceTmp->scale(scale);

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
				vec3 scale = readScale(objet.firstChildElement("scale"));
				QString modeleObjet = objet.attribute("modele");
				QString nomObjet = objet.attribute("nom", nom + "_" + modeleObjet);
				QString matObjet = objet.attribute("mat", "");
				QString shaderObjet = objet.attribute("shader", "");


				Node * node = Node::loadModel(modeleObjet, this);

				if (!node)
				{
					qFatal("Stop, erreur de chargement");
				}

				node->parent(pieceTmp);
				node->rotation(vec3(xRot, yRot, zRot));
				node->scale(scale);

				if (matObjet != "")
				{
					node->material(getMaterial(matObjet));
				}

				node->shaderId(getShader(shaderObjet));
				node->name(nomObjet);
				



				vec3 position = readPosition(objet.firstChildElement("position"));


				node->position(position);


				pieceTmp->addChild(nomObjet ,node);

				objet = objet.nextSiblingElement("objet");
			}
		}




		addPiece(nom, pieceTmp);

		piece = piece.nextSiblingElement("piece");
	}
}

bool Scene::saveAsXML(const QString & fileName)
{
	QDomDocument doc(fileName);

	QDomElement scene = doc.createElement("scene");

	doc.appendChild(scene);

	QDomElement camera = doc.createElement("camera");
	QDomElement camPos = doc.createElement("position");
	vec3 pos = _camera->position();

	camPos.setAttribute("x", pos[0]);
	camPos.setAttribute("y", pos[1]);
	camPos.setAttribute("z", pos[2]);

	camera.appendChild(camPos);
	scene.appendChild(camera);

	saveMaterials(scene, doc);
	saveLights(scene, doc);
	saveShaders(scene, doc);
	savePieces(scene, doc);

	QFile file(fileName);

	if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		qDebug() << "Ouverture du fichier de sauvegarde impossible";

		return false;
	}

	QTextStream stream( &file );
	stream << doc.toString();
  
	file.close();

	return true;
}

void Scene::saveMaterials(QDomElement & root, QDomDocument & doc) const
{	
	QDomElement materiaux = doc.createElement("materiaux");


	for(auto i = _materials.begin(); i != _materials.end(); ++i)
	{
		QDomElement material = doc.createElement("material");

		material.setAttribute("nom", i.key());

		vec3 ambient = i.value()->get(GL_AMBIENT);
		vec3 diffuse = i.value()->get(GL_DIFFUSE);
		vec3 specular = i.value()->get(GL_SPECULAR);
		float shininess = i.value()->shininess();

		QDomElement ambientE = doc.createElement("ambient");

		ambientE.setAttribute("r", ambient[0]);
		ambientE.setAttribute("g", ambient[1]);
		ambientE.setAttribute("b", ambient[2]);


		QDomElement diffuseE = doc.createElement("diffuse");

		diffuseE.setAttribute("r", diffuse[0]);
		diffuseE.setAttribute("g", diffuse[1]);
		diffuseE.setAttribute("b", diffuse[2]);


		QDomElement specularE = doc.createElement("specular");

		specularE.setAttribute("r", specular[0]);
		specularE.setAttribute("g", specular[1]);
		specularE.setAttribute("b", specular[2]);
		specularE.setAttribute("a", shininess);


		material.appendChild(ambientE);
		material.appendChild(diffuseE);	
		material.appendChild(specularE);


		if(i.value()->hasDiffuseTexture())
		{
			QDomElement diffuseT = doc.createElement("texture");

			diffuseT.setAttribute("src", i.value()->getDiffuseTextureName());
			diffuseT.setAttribute("location", 0);

			material.appendChild(diffuseT);

		}

		if(i.value()->hasSpecularTexture())
		{
			QDomElement specularT = doc.createElement("texture");

			specularT.setAttribute("src", i.value()->getSpecularTextureName());
			specularT.setAttribute("location", 2);

			material.appendChild(specularT);
		}

		if(i.value()->hasNormalTexture())
		{
			QDomElement normalT = doc.createElement("texture");

			normalT.setAttribute("src", i.value()->getNormalTextureName());
			normalT.setAttribute("location", 1);

			material.appendChild(normalT);
		}

		materiaux.appendChild(material);

	}

	root.appendChild(materiaux);
}

void Scene::saveLights(QDomElement & root, QDomDocument & doc) const
{
	QDomElement lumieres = doc.createElement("lumieres");


	for(auto i = _lights.begin(); i != _lights.end(); ++i)
	{
		QDomElement lumiere = doc.createElement("lumiere");

		lumiere.setAttribute("nom", i.key());

		vec3 ambient = i.value()->get(GL_AMBIENT);
		vec3 diffuse = i.value()->get(GL_DIFFUSE);
		vec3 specular = i.value()->get(GL_SPECULAR);
		vec3 position = i.value()->get(GL_POSITION);

		QDomElement ambientE = doc.createElement("ambient");

		ambientE.setAttribute("r", ambient[0]);
		ambientE.setAttribute("g", ambient[1]);
		ambientE.setAttribute("b", ambient[2]);


		QDomElement diffuseE = doc.createElement("diffuse");

		diffuseE.setAttribute("r", diffuse[0]);
		diffuseE.setAttribute("g", diffuse[1]);
		diffuseE.setAttribute("b", diffuse[2]);


		QDomElement specularE = doc.createElement("specular");

		specularE.setAttribute("r", specular[0]);
		specularE.setAttribute("g", specular[1]);
		specularE.setAttribute("b", specular[2]);

		QDomElement positionE = doc.createElement("position");

		positionE.setAttribute("x", position[0]);
		positionE.setAttribute("y", position[1]);
		positionE.setAttribute("z", position[2]);

		lumiere.appendChild(positionE);
		lumiere.appendChild(ambientE);
		lumiere.appendChild(diffuseE);	
		lumiere.appendChild(specularE);


		lumieres.appendChild(lumiere);

	}

	root.appendChild(lumieres);
}


void Scene::saveShaders(QDomElement & root, QDomDocument & doc) const
{
	QDomElement shaders = doc.createElement("shaders");

	for(auto i = _shaders.begin(); i != _shaders.end(); ++i)
	{
		QDomElement shader = doc.createElement("shader");
		QList<QOpenGLShader *> shaderList = i.value()->shaders(); 

		shader.setAttribute("nom", i.key());
		
		for(QOpenGLShader * j : shaderList)
		{
			switch(j->shaderType())
			{
				case QOpenGLShader::Vertex :
					shader.setAttribute("vertex", _loadedShaders.key(j));
					break;

				case QOpenGLShader::Fragment :
					shader.setAttribute("fragment", _loadedShaders.key(j));
					break; 
			}
		}

		shaders.appendChild(shader);
	}

	root.appendChild(shaders);
}

void Scene::savePieces(QDomElement & root, QDomDocument & doc) const
{
	QDomElement pieces = doc.createElement("pieces");

	for(auto i = _pieces.begin(); i != _pieces.end(); ++i)
	{
		QDomElement piece = doc.createElement("piece");


		piece.setAttribute("nom", i.key());
		piece.setAttribute("shader", getShaderNameByID(i.value()->shaderId()));
		piece.setAttribute("mat", getMaterialName(i.value()->material()));

		QDomElement dimensionE = doc.createElement("dimension");
		vec3 	dimension = i.value()->dimensions();

		dimensionE.setAttribute("width", dimension[0]);
		dimensionE.setAttribute("height", dimension[1]);
		dimensionE.setAttribute("length", dimension[2]);

		piece.appendChild(dimensionE);

		QDomElement positionE = doc.createElement("position");
		vec3 position = i.value()->position();

		positionE.setAttribute("x", position[0]);
		positionE.setAttribute("y", position[1]);
		positionE.setAttribute("z", position[2]);

		piece.appendChild(positionE);


		QDomElement mursE = doc.createElement("murs");
		QDomElement objetsE = doc.createElement("objets");
		QStringList children = i.value()->getChildren();

		for(QString child : children)
		{

			if(child.startsWith(i.key()))
			//c'est un mur
			{
				QDomElement murE = doc.createElement("mur");
				Plan * mur = dynamic_cast<Plan *>(i.value()->getChild(child));

				if(!mur)
				{
					qWarning() << "Impossible de caster l'objet en Plan.";
					continue;
				}

				if(mur->material())
				{
					murE.setAttribute("mat", getMaterialName(mur->material()));
				}

				child.remove(i.key() + "_");


				murE.setAttribute("cote", child);

				const QList<QRectF> fenetres = mur->getFenetres();

				for(QRectF r : fenetres)
				{
					QDomElement fenetreE = doc.createElement("fenetre");

					fenetreE.setAttribute("x", r.x());
					fenetreE.setAttribute("y", r.y());
					fenetreE.setAttribute("width", r.width());
					fenetreE.setAttribute("height", r.height());

					murE.appendChild(fenetreE);
				}

				mursE.appendChild(murE);
			}
			else
			{
				QDomElement objetE = doc.createElement("objet");
				Node * node = dynamic_cast<Node *>(i.value()->getChild(child));

				if(!node)
				{
					qWarning() << "Impossible de caster l'objet en node";
					continue;
				}

				objetE.setAttribute("nom", node->name());
				objetE.setAttribute("modele", node->getModelName());

				vec3 rotation = node->rotation();

				objetE.setAttribute("xRot", rotation[0]);
				objetE.setAttribute("yRot", rotation[1]);
				objetE.setAttribute("zRot", rotation[2]);


				QDomElement positionE = doc.createElement("position");
				vec3 position = node->position();

				positionE.setAttribute("x", position[0]);
				positionE.setAttribute("y", position[1]);
				positionE.setAttribute("z", position[2]);

				objetE.appendChild(positionE);


				objetsE.appendChild(objetE);
			}


		}

		piece.appendChild(mursE);
		piece.appendChild(objetsE);


		pieces.appendChild(piece);
	}

	root.appendChild(pieces);
}

void Scene::orderLights()
{
	_orderedLights.clear();

	QList<QFuture<QPair<Light *, float> > > resultats;

	// auto res = QtConcurrent::mapped(_lights, [this](const Light * l){vec3 distance = _camera->position() - l->get(GL_POSITION); return (distance[0]*distance[0] + distance[1]*distance[1] + distance[2]*distance[2]);});

	for(Light * i : _lights)
	{
		resultats << QtConcurrent::run([this](Light * l){vec3 distance = _camera->position() - l->get(GL_POSITION); return QPair<Light *, float>(l, (distance[0]*distance[0] + distance[1]*distance[1] + distance[2]*distance[2]));}, i);
	}


	for(QFuture<QPair<Light *, float> > f : resultats)
	{
		_orderedLights.insert(f.result().second, f.result().first);
	}

}

bool Scene::collide(const Hitbox & h) const
{
	for (Piece * i : _pieces)
	{
		if(i->collide(h))
		{
			qDebug() << "Collision avec " << i->name();
			return true;
		}
	}

	return false;
}

vec3 Scene::readPosition(const QDomElement & e)
{
	vec3 position;

	position[0] = e.attribute("x", "1").toFloat();
	position[1] = e.attribute("y", "1").toFloat();
	position[2] = e.attribute("z", "1").toFloat();

	return position;
}

vec3 Scene::readScale(const QDomElement & e)
{
	vec3 scale;

	scale[0] = e.attribute("x", "1").toFloat();
	scale[1] = e.attribute("y", "1").toFloat();
	scale[2] = e.attribute("z", "1").toFloat();

	return scale;
}
