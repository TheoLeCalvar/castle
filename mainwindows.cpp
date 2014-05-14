#include "mainwindows.hpp"
#include <iostream>
#include "light.hpp"

MainWindow::MainWindow():light(NULL),material(NULL)
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
    createListeDockwidget();
    createMenus();
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

     ajoutelement = new QMenu(tr("&Ajout"));
        ajoutlumierAct = new QAction(tr("&Lumiere"),this);
            connect(ajoutlumierAct,SIGNAL(triggered()),this , SLOT(ajoutlumiere()));
        ajoutmaterialAct = new QAction(tr("&Materiaux"),this);
            connect(ajoutmaterialAct,SIGNAL(triggered()),this , SLOT(ajoutmaterial()));

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
        Outil->addMenu(ajoutelement);
            //ajout lumiere
            ajoutelement->addAction(ajoutlumierAct);

            widgetajoutlumiere = new QWidget;

            //nom
            nomajoutlumiere = new QLabel("Nom:");
            lineeditnomajoutlumiere = new QLineEdit(this);
            layoutnomajoutlumiere = new QHBoxLayout();
                layoutnomajoutlumiere->addWidget(nomajoutlumiere);
                layoutnomajoutlumiere->addWidget(lineeditnomajoutlumiere);
            //position
            positionajoutlumiere = new QLabel("Position: ");
            spinpositionajoutlumierex = new QDoubleSpinBox;
                spinpositionajoutlumierex->setRange(-1000 , 1000);
            spinpositionajoutlumierey = new QDoubleSpinBox;
                spinpositionajoutlumierey->setRange(-1000 , 1000);
            spinpositionajoutlumierez = new QDoubleSpinBox;
                spinpositionajoutlumierez->setRange(-1000 , 1000);

            layoutposajoutlumiere = new QHBoxLayout();
                 layoutposajoutlumiere->addWidget(positionajoutlumiere);
                 layoutposajoutlumiere->addWidget(spinpositionajoutlumierex);
                 layoutposajoutlumiere->addWidget(spinpositionajoutlumierey);
                 layoutposajoutlumiere->addWidget(spinpositionajoutlumierez);

            //difuse
            difajoutlumiere = new QLabel("Difuse: ");
            spindifajoutlumierex = new QDoubleSpinBox;
                spindifajoutlumierex->setRange(0 , 1);
                spindifajoutlumierex->setSingleStep(0.01);
            spindifajoutlumierey = new QDoubleSpinBox;
                 spindifajoutlumierey->setRange(0 , 1);
                 spindifajoutlumierey->setSingleStep(0.01);
            spindifajoutlumierez = new QDoubleSpinBox;
                 spindifajoutlumierez->setRange(0 , 1);
                 spindifajoutlumierez->setSingleStep(0.01);

            layoutdifajoutlumiere = new QHBoxLayout();
                layoutdifajoutlumiere->addWidget(difajoutlumiere);
                layoutdifajoutlumiere->addWidget(spindifajoutlumierex);
                layoutdifajoutlumiere->addWidget(spindifajoutlumierey);
                layoutdifajoutlumiere->addWidget(spindifajoutlumierez);

             //speculaire
             speajoutlumiere = new QLabel("Speculaire: ");
             spinspeajoutlumierex = new QDoubleSpinBox;
                spinspeajoutlumierex->setRange(0 , 1);
                spinspeajoutlumierex->setSingleStep(0.01);
             spinspeajoutlumierey = new QDoubleSpinBox;
                spinspeajoutlumierey->setRange(0 , 1);
                spinspeajoutlumierey->setSingleStep(0.01);
             spinspeajoutlumierez = new QDoubleSpinBox;
                spinspeajoutlumierez->setRange(0 , 1);
                spinspeajoutlumierez->setSingleStep(0.01);

             layoutspeajoutlumiere = new QHBoxLayout();
                layoutspeajoutlumiere->addWidget(speajoutlumiere);
                layoutspeajoutlumiere->addWidget(spinspeajoutlumierex);
                layoutspeajoutlumiere->addWidget(spinspeajoutlumierey);
                layoutspeajoutlumiere->addWidget(spinspeajoutlumierez);


            //bouton
             boutonajoutlumiere = new QPushButton("ajouter");
             connect(boutonajoutlumiere,SIGNAL(clicked()), this ,SLOT(validajoutlumiere()));

             layoutajoutlumiere=new QVBoxLayout;
                layoutajoutlumiere->addLayout(layoutnomajoutlumiere);
                layoutajoutlumiere->addLayout(layoutposajoutlumiere);
                layoutajoutlumiere->addLayout(layoutdifajoutlumiere);
                layoutajoutlumiere->addLayout(layoutspeajoutlumiere);
                layoutajoutlumiere->addWidget(boutonajoutlumiere);

                widgetajoutlumiere->setLayout(layoutajoutlumiere);

                dockajoutlumiere->setWidget(widgetajoutlumiere);

            //ajout material
            ajoutelement->addAction(ajoutmaterialAct);

            widgetajoutmaterial = new QWidget;

            //nom
            nomajoutmaterial = new QLabel("Nom:");
            lineeditnomajoutmaterial = new QLineEdit(this);
            layoutnomajoutmaterial = new QHBoxLayout();
                layoutnomajoutmaterial->addWidget(nomajoutmaterial);
                layoutnomajoutmaterial->addWidget(lineeditnomajoutmaterial);

            //ambiante
            ambajoutmaterial = new QLabel("ambiante: ");
            spinambajoutmaterialx = new QDoubleSpinBox;
                spinambajoutmaterialx->setRange(0 , 1);
                spinambajoutmaterialx->setSingleStep(0.01);
            spinambajoutmaterialy = new QDoubleSpinBox;
                spinambajoutmaterialy->setRange(0 , 1);
                spinambajoutmaterialy->setSingleStep(0.01);
            spinambajoutmaterialz = new QDoubleSpinBox;
                spinambajoutmaterialz->setRange(0 , 1);
                spinambajoutmaterialz->setSingleStep(0.01);

            layoutambajoutmaterial = new QHBoxLayout();
                 layoutambajoutmaterial->addWidget(ambajoutmaterial);
                 layoutambajoutmaterial->addWidget(spinambajoutmaterialx);
                 layoutambajoutmaterial->addWidget(spinambajoutmaterialy);
                 layoutambajoutmaterial->addWidget(spinambajoutmaterialz);

            //difuse
            difajoutmaterial = new QLabel("Difuse: ");
            spindifajoutmaterialx = new QDoubleSpinBox;
                spindifajoutmaterialx->setRange(0 , 1);
                spindifajoutmaterialx->setSingleStep(0.01);
            spindifajoutmaterialy = new QDoubleSpinBox;
                 spindifajoutmaterialy->setRange(0 , 1);
                 spindifajoutmaterialy->setSingleStep(0.01);
            spindifajoutmaterialz = new QDoubleSpinBox;
                 spindifajoutmaterialz->setRange(0 , 1);
                 spindifajoutmaterialz->setSingleStep(0.01);

            layoutdifajoutmaterial = new QHBoxLayout();
                layoutdifajoutmaterial->addWidget(difajoutmaterial);
                layoutdifajoutmaterial->addWidget(spindifajoutmaterialx);
                layoutdifajoutmaterial->addWidget(spindifajoutmaterialy);
                layoutdifajoutmaterial->addWidget(spindifajoutmaterialz);

             //speculaire
             speajoutmaterial = new QLabel("Speculaire: ");
             spinspeajoutmaterialx = new QDoubleSpinBox;
                spinspeajoutmaterialx->setRange(0 , 1);
                spinspeajoutmaterialx->setSingleStep(0.01);
             spinspeajoutmaterialy = new QDoubleSpinBox;
                spinspeajoutmaterialy->setRange(0 , 1);
                spinspeajoutmaterialy->setSingleStep(0.01);
             spinspeajoutmaterialz = new QDoubleSpinBox;
                spinspeajoutmaterialz->setRange(0 , 1);
                spinspeajoutmaterialz->setSingleStep(0.01);
                spinspeajoutmateriala = new QDoubleSpinBox;
                   spinspeajoutmateriala->setRange(0 , 64);
                   spinspeajoutmateriala->setSingleStep(0.5);

             layoutspeajoutmaterial = new QHBoxLayout();
                layoutspeajoutmaterial->addWidget(speajoutmaterial);
                layoutspeajoutmaterial->addWidget(spinspeajoutmaterialx);
                layoutspeajoutmaterial->addWidget(spinspeajoutmaterialy);
                layoutspeajoutmaterial->addWidget(spinspeajoutmaterialz);
                layoutspeajoutmaterial->addWidget(spinspeajoutmateriala);

            //bouton
             boutonajoutmaterial = new QPushButton("ajouter");
             connect(boutonajoutmaterial,SIGNAL(clicked()), this ,SLOT(validajoutmaterial()));

             layoutajoutmaterial=new QVBoxLayout;
                layoutajoutmaterial->addLayout(layoutnomajoutmaterial);
                layoutajoutmaterial->addLayout(layoutambajoutmaterial);
                layoutajoutmaterial->addLayout(layoutdifajoutmaterial);
                layoutajoutmaterial->addLayout(layoutspeajoutmaterial);
                layoutajoutmaterial->addWidget(boutonajoutmaterial);

                widgetajoutmaterial->setLayout(layoutajoutmaterial);

                dockajoutmateriaux->setWidget(widgetajoutmaterial);


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

    dockajoutlumiere =new QDockWidget(tr("Ajout d'une lumiere"), this);
        dockajoutlumiere->setAllowedAreas(Qt::LeftDockWidgetArea);
        addDockWidget(Qt::LeftDockWidgetArea, dockajoutlumiere);
        dockajoutlumiere->hide();

    dockajoutmateriaux =new QDockWidget(tr("Ajout d'un materiau"), this);
        dockajoutmateriaux->setAllowedAreas(Qt::LeftDockWidgetArea);
        addDockWidget(Qt::LeftDockWidgetArea, dockajoutmateriaux);
        dockajoutmateriaux->hide();
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

           listtempobjet = scenetemp->getPiecesName();
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

                        for (int i = 0; i < listtempmaterial.size(); ++i)
                                {
                                   material->appendRow(new QStandardItem(listtempmaterial.at(i)));
                                }
                    //objet
                    objet = new QStandardItem("Objet");
                    modele->appendRow(objet);

                        for (int i = 0; i < listtempobjet.size(); ++i)
                                {
                                  Piece * objtemp = scenetemp->getPiece(listtempobjet.at(i));
                                  QStringList listobjfils = objtemp->getChildren();

                                  QStandardItem * item =  new QStandardItem(listtempobjet.at(i));
                                  objet->appendRow(item);

                                  for(int j=0 ; j < listobjfils.size();j++)
                                          {
                                           QStandardItem * itemfils =  new QStandardItem(listobjfils.at(j));
                                           item->appendRow(itemfils); ;
                                          }
                                }
                    //shader
                    shader = new QStandardItem("Shader");
                    modele->appendRow(shader);

                        for (int i = 0; i < listtemshader.size(); ++i)
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

    void MainWindow::ajoutlumiere(){
        dockajoutlumiere->show();
    }

    void MainWindow::validajoutlumiere(){
        Scene * scenetemp = widget->getScene();

        if (lineeditnomajoutlumiere->text()==NULL)
        {
            QMessageBox msgBox;
            msgBox.setText("le champ nom , ne peut etre vide");
            msgBox.exec();
         dockajoutlumiere->close();
        }
        else
        {
            scenetemp->addLight(
                lineeditnomajoutlumiere->text(),//nom

                    new Light//lumiere
                        (
                            vec3(//position
                            spinpositionajoutlumierex->value(),
                            spinpositionajoutlumierey->value(),
                            spinpositionajoutlumierez->value()
                            ),

                            vec3(//difuse
                            spindifajoutlumierex->value(),
                            spindifajoutlumierey->value(),
                            spindifajoutlumierez->value()
                            ),

                            vec3(//speculaire
                            spinspeajoutlumierex->value(),
                            spinspeajoutlumierey->value(),
                            spinspeajoutlumierez->value()
                            ),

                            2
                        )
                    );
            dockajoutlumiere->close();

             if (light)
             {
              light->appendRow(new QStandardItem(lineeditnomajoutlumiere->text()));
             }
        }//fin else
    }

    void MainWindow::ajoutmaterial(){
        dockajoutmateriaux->show();
    }

    void MainWindow::validajoutmaterial()
        {
            Scene * scenetemp = widget->getScene();

            if (lineeditnomajoutmaterial->text()==NULL)
            {
                QMessageBox msgBox;
                msgBox.setText("le champ nom , ne peut etre vide");
                msgBox.exec();
             dockajoutmateriaux->close();
            }
            else
            {
                scenetemp->addMaterial(
                    lineeditnomajoutmaterial->text(),//nom

                        new Material//lumiere
                            (
                                vec3(//ambiante
                                spinambajoutmaterialx->value(),
                                spinambajoutmaterialy->value(),
                                spinambajoutmaterialz->value()
                                ),

                                vec3(//difuse
                                spindifajoutmaterialx->value(),
                                spindifajoutmaterialy->value(),
                                spindifajoutmaterialz->value()

                                ),

                                vec3(//spe
                                spinspeajoutmaterialx->value(),
                                spinspeajoutmaterialy->value(),
                                spinspeajoutmaterialz->value()
                                ),

                                spinspeajoutmateriala->value()//shines
                            )
                        );

                dockajoutmateriaux->close();

                if(material){
                        material->appendRow(new QStandardItem(lineeditnomajoutmaterial->text()));
                }
            }//fin else
        }



    //aide
    void MainWindow::Racourcit()
    {
    }

//fin Menubars

//__fin_slots____________________________//
