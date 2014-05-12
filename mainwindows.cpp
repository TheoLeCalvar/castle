#include "mainwindows.hpp"
#include <iostream>
#include "light.hpp"

MainWindow::MainWindow()
{
/* ************************************** */
//          Central  Widget               //
/* ************************************** */
    QGLFormat f;
    f.setVersion(3, 2);
    f.setProfile(QGLFormat::CoreProfile);
    widget = new MyOpenGLWidget(f,this);
    setCentralWidget(widget);
//fin central Widget

    createActions();
    createMenus();
    createListeDockwidget();
    createToolBar();
}

MainWindow::~MainWindow()
{
}

void MainWindow::createActions()
{
/* ************************************** */
//               Menubar                  //
/* ************************************** */
     //fichier
     nouveauAct = new QAction(tr("&Nouveau"), this);
         connect( nouveauAct, SIGNAL(triggered()), this, SLOT(Nouveau()));

     ouvrirAct = new QAction(tr("&Ouvrir"), this);
        connect( ouvrirAct, SIGNAL(triggered()), this, SLOT(Ouvrir()));

     enregistrerAct = new QAction(tr("&Enregistrer"), this);
        connect( enregistrerAct, SIGNAL(triggered()), this, SLOT(Enregistrer()));

     kiterAct = new QAction(tr("&Quitter"), this);
        connect( kiterAct, SIGNAL(triggered()), qApp, SLOT(quit()));

     //edition
    annulerAct = new QAction(tr("&Annuler"),this);
        connect(annulerAct , SIGNAL(triggered()), this,SLOT(Annuler()));

   retablirAct = new QAction(tr("&Retablir"),this);
        connect(retablirAct , SIGNAL(triggered()), this,SLOT(Retablir()));

     //affichage
     grilleAct = new QAction(tr("&Grille"), this);
         connect( grilleAct, SIGNAL(triggered()), this, SLOT(Grille()));
         grilleAct->setCheckable(true);

     apercutAct = new QAction(tr("&fullscreen"), this);
         connect(apercutAct, SIGNAL(triggered()), this, SLOT(Apercut()));
         apercutAct->setCheckable(true);

     culfaceAct = new QAction(tr("&Culface"), this);
         connect(culfaceAct, SIGNAL(triggered()), this, SLOT(Culface()));
         culfaceAct->setCheckable(true);

     //outil
     importation3DAct = new QAction(tr("&Liste elements"), this);
         connect( importation3DAct, SIGNAL(triggered()), this, SLOT(Importation3D()));
         importation3DAct->setCheckable(true);

     //aide
     racourcitAct = new QAction(tr("&Racourcit"), this);
         connect(racourcitAct, SIGNAL(triggered()), this, SLOT(Racourcit()));
//fin menubar

}

void MainWindow::createMenus()
{

    Fichier = menuBar()->addMenu(tr("&Fichier"));
        Fichier->addAction(nouveauAct);
        Fichier->addAction(ouvrirAct);
        Fichier->addAction(enregistrerAct);
        Fichier->addSeparator();
        Fichier->addAction(kiterAct);
            kiterAct->setIcon(QIcon("icones/exit.png"));

    Edition = menuBar()->addMenu(tr("&Edition"));
        Edition->addAction(annulerAct);
            annulerAct->setIcon(QIcon("icones/undo.png"));
        Edition->addAction(retablirAct);
            retablirAct->setIcon(QIcon("icones/redo.jpeg"));

    Affichage = menuBar()->addMenu(tr("&Affichage"));
        Affichage->addAction(culfaceAct);
            culfaceAct->setShortcut(QKeySequence(Qt::Key_F2));
        Affichage->addAction(grilleAct);
            grilleAct->setIcon(QIcon("icones/grid-rectangular.png"));
            grilleAct->setShortcut(QKeySequence(Qt::Key_F1));
        Affichage->addSeparator();
        Affichage->addAction(apercutAct);
            apercutAct->setIcon(QIcon("icones/fullscreen.png"));
            apercutAct->setShortcut(QKeySequence(Qt::Key_F3));

    Outil = menuBar()->addMenu(tr("&Outil"));
        Outil->addAction(importation3DAct);
            importation3DAct->setIcon(QIcon("icones/value_list.png"));

    Aide = menuBar()->addMenu(tr("&Aide"));
        Aide->addAction(racourcitAct);
}

void MainWindow::createListeDockwidget()
{
    dock_list_elements = new QDockWidget(tr("liste elements"), this);
    dock_list_elements->setAllowedAreas(Qt::LeftDockWidgetArea);
    addDockWidget(Qt::LeftDockWidgetArea, dock_list_elements);
    dock_list_elements->hide();

    dock_light = new Mondock(tr("vide"),this);
    dock_light->setAllowedAreas(Qt::LeftDockWidgetArea);
    addDockWidget(Qt::LeftDockWidgetArea, dock_light);
    dock_light->hide();
}

void MainWindow::createToolBar()
{
    fileToolBar=new QToolBar( tr("menubar"), this );
    fileToolBar->setAllowedAreas(Qt::TopToolBarArea);
    fileToolBar-> setMovable(false);
    addToolBar(Qt::TopToolBarArea, fileToolBar);

            fileToolBar->addAction(kiterAct);

            fileToolBar->addSeparator();

            fileToolBar->addAction(annulerAct);

            fileToolBar->addAction(retablirAct);

            fileToolBar->addSeparator();

            fileToolBar->addAction(apercutAct);

            fileToolBar->addAction(grilleAct);

            fileToolBar->addSeparator();

            fileToolBar->addAction(importation3DAct);

            fileToolBar->addSeparator();
}


//__slots_________________________________//

/* ************************************** */
//               Menubars                 //
/* ************************************** */
    //fichier
    void MainWindow::Nouveau(){}

    void MainWindow::Ouvrir(){}

    void MainWindow::Enregistrer(){}

    void MainWindow::Kiter(){}

    //edition
    void MainWindow::Annuler(){}

    void MainWindow::Retablir(){}

    //affichage
    void MainWindow::Culface()
    {
        static bool cullface = false;

        if (cullface)
        {
            glEnable(GL_CULL_FACE);
        }
        else
        {
            glDisable(GL_CULL_FACE);
        }

        cullface = !cullface;
    }

    void MainWindow::Apercut()
    {
            if ( !QWidget::isFullScreen ())
            {
                 QWidget::showFullScreen();
            }
            else
            {
               QWidget::showNormal () ;
            }
     }

    void MainWindow::Grille(){
        static bool wire = true;

        glPolygonMode(GL_FRONT_AND_BACK, wire ? GL_LINE : GL_FILL);

        wire = !wire;

    }

    //outil
    void MainWindow::Importation3D(){

           if (!(importation3DAct->isChecked()))
           {
            dock_list_elements->hide();
            dock_light->hide();
           }
           else
           {

          //recupèration des element a aficher
           scenetemp = widget->getScene();

           listtempobjet = scenetemp->getObjetsNames();
           listtemplight = scenetemp->getLightsNames();
           listtempmaterial = scenetemp->getMaterialsNames();
           listtemshader = scenetemp->getShadersNames();

           //créeation du model et de la vus
           modele = new QStandardItemModel;
                    //lumiere
                    light = new QStandardItem("Light");
                    modele->appendRow(light);

                         for (int i = 0; i < listtemplight.size(); ++i)
                                 {
                                    light->appendRow(new QStandardItem(listtemplight.at(i)));
                                 }
                    //materiaux
                    material = new QStandardItem("Material");
                    modele->appendRow(material);

                        for (int i = 0; i < listtemplight.size(); ++i)
                                {
                                   material->appendRow(new QStandardItem(listtempmaterial.at(i)));
                                }
                    //objet
                    objet = new QStandardItem("Objet");
                    modele->appendRow(objet);

                        for (int i = 0; i < listtemplight.size(); ++i)
                                {
                                   objet->appendRow(new QStandardItem(listtempobjet.at(i)));
                                }
                    //shader
                    shader = new QStandardItem("Shader");
                    modele->appendRow(shader);

                        for (int i = 0; i < listtemplight.size(); ++i)
                                {
                                   shader->appendRow(new QStandardItem(listtemshader.at(i)));
                                }

            vue = new QTreeView;
            vue->setModel(modele);
            vue->header()->hide();


            //creation widget a fixer dans le dockwidget

            boutonlisteelement = new QPushButton("Editer");

            layoutlistescene = new QVBoxLayout();
                layoutlistescene->addWidget(vue);
                layoutlistescene->addWidget(boutonlisteelement);

            widgetdocklistscene = new QWidget() ;
                widgetdocklistscene->setLayout(layoutlistescene);

            //afectation de la vus dans le dockwidget
            dock_list_elements->setWidget(widgetdocklistscene);

            //afichage du dockwidget
            dock_list_elements->show();

            //conect les element de la vus au fonction d'afichage et donne vue+ model au docklight
            dock_light->dockmodele= modele;
            dock_light->dockvue = vue;
            dock_light->dockscene= scenetemp;
            connect(boutonlisteelement, SIGNAL(clicked()), dock_light, SLOT(selectionlight()));

           }//fin else
    }

    //aide
    void MainWindow::Racourcit(){
    }

//fin Menubars

//__fin_slots____________________________//
