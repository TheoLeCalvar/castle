#include "mainwindows.hpp"
#include <iostream>
#include "light.hpp"

MainWindow::MainWindow(const QString & path):light(NULL),material(NULL),objet(NULL)
{
/* ************************************** */
//          Central  Widget               //
/* ************************************** */
    QGLFormat f;
    f.setVersion(3, 2);
    f.setProfile(QGLFormat::CoreProfile);
    widget = new MyOpenGLWidget(f,this, path);
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

        ajoutpieceAct = new QAction(tr("&Piece"),this);
            connect(ajoutpieceAct,SIGNAL(triggered()),this , SLOT(ajoutpiece()));

     //aide
     racourcitAct = new QAction(tr("&Racourcit"), this);
         connect(racourcitAct, SIGNAL(triggered()), this, SLOT(Racourcit()));
//fin menubar

}

void MainWindow::createMenus()
{

    Fichier = menuBar()->addMenu(tr("&Fichier"));
        Fichier->addAction(nouveauAct);
            nouveauAct->setShortcut(QKeySequence("Ctrl+N"));
        Fichier->addAction(ouvrirAct);
            ouvrirAct->setShortcut(QKeySequence("Ctrl+O"));
        Fichier->addAction(enregistrerAct);
            enregistrerAct->setIcon(QIcon("icones/save.png"));
            enregistrerAct->setShortcut(QKeySequence("Ctrl+S"));
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

/* ************************************** */
//              ajout elements            //
/* ************************************** */

            //ajout lumiere declaration des element
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
                spinambajoutmaterialx->setDecimals(4);
            spinambajoutmaterialy = new QDoubleSpinBox;
                spinambajoutmaterialy->setRange(0 , 1);
                spinambajoutmaterialy->setSingleStep(0.01);
                spinambajoutmaterialy->setDecimals(4);
            spinambajoutmaterialz = new QDoubleSpinBox;
                spinambajoutmaterialz->setRange(0 , 1);
                spinambajoutmaterialz->setSingleStep(0.01);
                spinambajoutmaterialz->setDecimals(4);

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
                spindifajoutmaterialx->setDecimals(4);
            spindifajoutmaterialy = new QDoubleSpinBox;
                 spindifajoutmaterialy->setRange(0 , 1);
                 spindifajoutmaterialy->setSingleStep(0.01);
                 spindifajoutmaterialy->setDecimals(4);
            spindifajoutmaterialz = new QDoubleSpinBox;
                 spindifajoutmaterialz->setRange(0 , 1);
                 spindifajoutmaterialz->setSingleStep(0.01);
                 spindifajoutmaterialz->setDecimals(4);

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
                spinspeajoutmaterialx->setDecimals(4);
             spinspeajoutmaterialy = new QDoubleSpinBox;
                spinspeajoutmaterialy->setRange(0 , 1);
                spinspeajoutmaterialy->setSingleStep(0.01);
                spinspeajoutmaterialy->setDecimals(4);
             spinspeajoutmaterialz = new QDoubleSpinBox;
                spinspeajoutmaterialz->setRange(0 , 1);
                spinspeajoutmaterialz->setSingleStep(0.01);
                spinspeajoutmaterialz->setDecimals(4);
             spinspeajoutmateriala = new QDoubleSpinBox;
                   spinspeajoutmateriala->setRange(0 , 128);
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

                //ajout widget au dock
                dockajoutmateriaux->setWidget(widgetajoutmaterial);

                //ajout piece
                ajoutelement->addAction(ajoutpieceAct);

                widgetajoutpiece = new QWidget;

                //nom
                labelnomajoutpiece = new QLabel();
                    labelnomajoutpiece->setText("Nom:");
                lineeditajoutpiece = new QLineEdit();

                //materiaux
                modelemateriaupiece = new QStandardItemModel;

                labelcomboajoutpiece = new QLabel();
                    labelcomboajoutpiece->setText("Materiaux: ");
                comboajoutpiece = new QComboBox();
                    comboajoutpiece->setMaximumWidth(200);

                //dimention
                labeldimajoutpiece = new QLabel();
                    labeldimajoutpiece->setText("Dimention: ");

                ajoutpiecedimx = new QSpinBox();
                    ajoutpiecedimx->setPrefix("X= ");
                    ajoutpiecedimx->setRange(0,1000);
                ajoutpiecedimy = new QSpinBox();
                    ajoutpiecedimy->setPrefix("Y= ");
                    ajoutpiecedimy->setRange(0,1000);
                ajoutpiecedimz = new QSpinBox();
                    ajoutpiecedimz->setPrefix("Z= ");
                    ajoutpiecedimz->setRange(0,1000);

                //shader
                labelajoutpieceshader = new QLabel();
                    labelajoutpieceshader->setText("Shader:");
                comboajoutpieceshader = new QComboBox();
                    comboajoutpieceshader->setMaximumWidth(200);
                 modelepieceshader = new QStandardItemModel();

                //bouton
                boutonajoutpiece = new QPushButton("ajouter");
                connect(boutonajoutpiece,SIGNAL(clicked()), this ,SLOT(validajoutpiece()));

                //murs
                labelmurajoutpiece = new QLabel();
                    labelmurajoutpiece->setText("Liste des murs: ");

                    //label des mur
                    labelmur1 = new QLabel();
                        labelmur1->setText("bas:");
                    labelmur2 = new QLabel();
                        labelmur2->setText("haut:");
                    labelmur3 = new QLabel();
                        labelmur3->setText("arriere:");
                    labelmur4 = new QLabel();
                        labelmur4->setText("avant:");
                    labelmur5 = new QLabel();
                        labelmur5->setText("gauche:");
                    labelmur6 = new QLabel();
                        labelmur6->setText("droite:");
                    //checkbox mur
                    checkmur1 = new QCheckBox();
                    checkmur2 = new QCheckBox();
                    checkmur3 = new QCheckBox();
                    checkmur4 = new QCheckBox();
                    checkmur5 = new QCheckBox();
                    checkmur6 = new QCheckBox();

                //positionement
                mainlayoutajoutpiece = new QVBoxLayout();
                    ajoutpiecelayoutdim = new QHBoxLayout();
                        ajoutpiecelayoutdim->addWidget(labeldimajoutpiece);
                        ajoutpiecelayoutdim->addWidget(ajoutpiecedimx);
                        ajoutpiecelayoutdim->addWidget(ajoutpiecedimy);
                        ajoutpiecelayoutdim->addWidget(ajoutpiecedimz);
                    ajoutpiecelayoutnom = new QHBoxLayout();
                        ajoutpiecelayoutnom->addWidget(labelnomajoutpiece);
                        ajoutpiecelayoutnom->addWidget(lineeditajoutpiece);
                    ajoutpiecelayoutcombo = new QHBoxLayout();
                        ajoutpiecelayoutcombo->addWidget(labelcomboajoutpiece);
                        ajoutpiecelayoutcombo->addWidget(comboajoutpiece);
                    ajoutpiecelabelmure  = new QHBoxLayout();
                        ajoutpiecelabelmure->addWidget(labelmurajoutpiece);
                    ajoutpiecepiecer1  = new QHBoxLayout();
                        ajoutpiecepiecer1->addWidget(labelmur1);
                        ajoutpiecepiecer1->addWidget(checkmur1);
                        ajoutpiecepiecer1->addWidget(labelmur2);
                        ajoutpiecepiecer1->addWidget(checkmur2);
                    ajoutpiecepiecer2  = new QHBoxLayout();
                        ajoutpiecepiecer2->addWidget(labelmur3);
                        ajoutpiecepiecer2->addWidget(checkmur3);
                        ajoutpiecepiecer2->addWidget(labelmur4);
                        ajoutpiecepiecer2->addWidget(checkmur4);
                    ajoutpiecepiecer3  = new QHBoxLayout();
                        ajoutpiecepiecer3->addWidget(labelmur5);
                        ajoutpiecepiecer3->addWidget(checkmur5);
                        ajoutpiecepiecer3->addWidget(labelmur6);
                        ajoutpiecepiecer3->addWidget(checkmur6);
                    ajoutpieceshaderlayout = new QHBoxLayout();
                        ajoutpieceshaderlayout->addWidget(labelajoutpieceshader);
                        ajoutpieceshaderlayout->addWidget(comboajoutpieceshader);

                mainlayoutajoutpiece->addLayout(ajoutpiecelayoutnom);
                mainlayoutajoutpiece->addLayout(ajoutpiecelayoutcombo);
                mainlayoutajoutpiece->addLayout(ajoutpiecelayoutdim);
                mainlayoutajoutpiece->addLayout( ajoutpieceshaderlayout);
                mainlayoutajoutpiece->addLayout(ajoutpiecelabelmure);
                mainlayoutajoutpiece->addLayout(ajoutpiecepiecer1);
                mainlayoutajoutpiece->addLayout(ajoutpiecepiecer2);
                mainlayoutajoutpiece->addLayout(ajoutpiecepiecer3);
                mainlayoutajoutpiece->addWidget(boutonajoutpiece);

                widgetajoutpiece->setLayout(mainlayoutajoutpiece);

                //ajout widget au dock
                dockajoutpiece->setWidget(widgetajoutpiece);


    //aide
    Aide = menuBar()->addMenu(tr("&Aide"));
        Aide->addAction(racourcitAct);
}

void MainWindow::createListeDockwidget()
{
    dock_list_elements = new QDockWidget(tr("liste elements"), this);
        dock_list_elements->setAllowedAreas(Qt::LeftDockWidgetArea);
        addDockWidget(Qt::LeftDockWidgetArea, dock_list_elements);
        dock_list_elements->hide();

    dock_perso = new Mondock(tr("vide"),this);
        dock_perso->setAllowedAreas(Qt::LeftDockWidgetArea);
        addDockWidget(Qt::LeftDockWidgetArea, dock_perso);
        dock_perso->hide();


    dockajoutlumiere =new QDockWidget(tr("Ajout d'une lumiere"), this);
        dockajoutlumiere->setAllowedAreas(Qt::LeftDockWidgetArea);
        addDockWidget(Qt::LeftDockWidgetArea, dockajoutlumiere);
        dockajoutlumiere->hide();

    dockajoutmateriaux =new QDockWidget(tr("Ajout d'un materiau"), this);
        dockajoutmateriaux->setAllowedAreas(Qt::LeftDockWidgetArea);
        addDockWidget(Qt::LeftDockWidgetArea, dockajoutmateriaux);
        dockajoutmateriaux->hide();

        dockajoutpiece =new QDockWidget(tr("Ajout d'une piece"), this);
            dockajoutmateriaux->setAllowedAreas(Qt::LeftDockWidgetArea);
            addDockWidget(Qt::LeftDockWidgetArea,  dockajoutpiece);
            dockajoutpiece->hide();
}

void MainWindow::createToolBar()
{
    fileToolBar=new QToolBar( tr("menubar"), this );
    fileToolBar->setAllowedAreas(Qt::TopToolBarArea);
    fileToolBar-> setMovable(false);
    addToolBar(Qt::TopToolBarArea, fileToolBar);

            fileToolBar->addAction(kiterAct);

            fileToolBar->addSeparator();

            fileToolBar->addAction(enregistrerAct);

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

void MainWindow::affichagerecnoderestant(Node *a ,QStandardItem *b )
        {
        QStringList *listeelement = new QStringList(a->getChildrenNames());

        for (int i = 0;i<listeelement->size();i++)
            {
            QStandardItem * itemtmp= new QStandardItem(listeelement->at(i));
            b->appendRow(itemtmp);
            Node *nodetmp = a->getChild(listeelement->at(i));
            affichagerecnoderestant(nodetmp, itemtmp);
            }

        }



//__slots_________________________________//

/* ************************************** */
//               Menubars                 //
/* ************************************** */
    //fichier
    void MainWindow::Nouveau()
    {
            delete widget;

            QGLFormat f;
            f.setVersion(3, 2);
            f.setProfile(QGLFormat::CoreProfile);
            widget = new MyOpenGLWidget(f,this);
            setCentralWidget(widget);

    }

    void MainWindow::Ouvrir(){

           QString fileName = QFileDialog::getOpenFileName(this,
                tr("Open Scene"), "",
                tr("XML files (*.xml)"));
     if (fileName!=NULL){

        widget->close();
        delete widget;

        QGLFormat f;
        f.setVersion(3, 2);
        f.setProfile(QGLFormat::CoreProfile);
        widget = new MyOpenGLWidget(f,this, fileName);
        setCentralWidget(widget);

     }
    }

    void MainWindow::Enregistrer(){
        QString fileName = QFileDialog::getSaveFileName(this,
            tr("Save Scene"), "",
            tr("XML files (*.xml)"));
    if (fileName!=NULL){
                if(fileName.endsWith(".xml",Qt::CaseSensitive) )
                 {
                 widget->getScene()->saveAsXML(fileName);
                 }
                else widget->getScene()->saveAsXML(fileName + ".xml");
        }
    }

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
            dock_perso->hide();
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
                    dock_perso->_itemmaterial=material;

                    //objet
                    objet = new QStandardItem("Objet");
                    modele->appendRow(objet);

                        for (int i = 0; i < listtempobjet.size(); ++i)
                                {
                                  Piece * objtemp = scenetemp->getPiece(listtempobjet.at(i));
                                  QStringList listobjfils = objtemp->getChildren();

                                  item =  new QStandardItem(listtempobjet.at(i));
                                  objet->appendRow(item);

                                  for(int j=0 ; j < listobjfils.size();j++)
                                          {
                                           Objet * objetfils = objtemp->getChild(listobjfils.at(j));

                                           QStandardItem * itemfils =  new QStandardItem(listobjfils.at(j));
                                           item->appendRow(itemfils); ;


                                           //recherche des item petits fils
                                           Node* nodepetitfils;
                                           if ( (nodepetitfils = dynamic_cast<Node*> (objetfils)))
                                           {
                                              QStringList listobjpetitfils = nodepetitfils->getChildrenNames();

                                                    for(int k=0 ; k<listobjpetitfils.size();k++)
                                                        {
                                                        QStandardItem * itempetitfils =  new QStandardItem(listobjpetitfils.at(k));
                                                        itemfils->appendRow(itempetitfils);

                                                            //traitement item encore plus jeune que petit fils
                                                            affichagerecnoderestant((nodepetitfils->getChild(listobjpetitfils.at(k))),itempetitfils);
                                                            //fin traitement item encore plus jeune que petit fils

                                                        }//fin for petit fils
                                          }//fin if

                                }//fin for fils
                             }//fin for pere

                     dock_perso->_itempiece = objet;//afection de la liste des objet dans le dock d'edition

                     //shader
                    shader = new QStandardItem("Shader");
                    modele->appendRow(shader);

                        for (int i = 0; i < listtemshader.size(); ++i)
                                {
                                   shader->appendRow(new QStandardItem(listtemshader.at(i)));
                                }

            vue = new QTreeView;
            //vue->setModel(modele);
            vue->header()->hide();
            vue->setEditTriggers(QTreeView::NoEditTriggers);
            vue->setModel(modele);
            vue->sortByColumn(1,Qt::AscendingOrder);
            //creation widget a fixer dans le dockwidget

            boutonlisteelement = new QPushButton("Editer");
            boutonlisteelementdelete = new QPushButton("Suprimer");

            layoutlistescene = new QVBoxLayout();
                layoutlistescene->addWidget(vue);
                layoutlistescene->addWidget(boutonlisteelement);
                layoutlistescene->addWidget(boutonlisteelementdelete);

            widgetdocklistscene = new QWidget() ;
                widgetdocklistscene->setLayout(layoutlistescene);

            //afectation de la vus dans le dockwidget
            dock_list_elements->setWidget(widgetdocklistscene);

            //afichage du dockwidget
            dock_list_elements->show();

            //conect les element de la vus au fonction d'afichage et donne vue+ model au docklight
            dock_perso->dockmodele= modele;
            dock_perso->dockvue = vue;
            dock_perso->dockscene= scenetemp;
            connect(boutonlisteelement, SIGNAL(clicked()), dock_perso, SLOT(selectionlight()));
            connect(boutonlisteelementdelete, SIGNAL(clicked()), this, SLOT(supresionelement()));

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
                            )
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
                if(dock_perso->modelmaterial){
                  dock_perso->modelmaterial->appendRow(new QStandardItem(lineeditnomajoutmaterial->text()));
                }
            }//fin else
        }

    void MainWindow::ajoutpiece()
        {
            //creation model materiaux
            QStringList listtmp = widget->getScene()->getMaterialsNames();

            modelemateriaupiece = new QStandardItemModel();

            for (int ligne=0 ; ligne < listtmp.size(); ligne++)
            {
            QStandardItem *itemtmp =new QStandardItem(listtmp.at(ligne));
            modelemateriaupiece->setItem(ligne,itemtmp);
            }

            comboajoutpiece->setModel(modelemateriaupiece);

            //creation model shader
            listtmp = widget->getScene()->getShadersNames();

            modelepieceshader = new QStandardItemModel();

            for (int ligne=0 ; ligne < listtmp.size(); ligne++)
            {
            QStandardItem *itemtmp =new QStandardItem(listtmp.at(ligne));
            modelepieceshader->setItem(ligne,itemtmp);
            }

            comboajoutpieceshader->setModel(modelepieceshader);


            //show
            dockajoutpiece->show();
        }

    void MainWindow::validajoutpiece()
        {
        Scene * scenetemp = widget->getScene();

        if (lineeditajoutpiece->text()==NULL)
        {
            QMessageBox msgBox;
            msgBox.setText("le champ nom , ne peut etre vide");
            msgBox.exec();
         dockajoutpiece->close();
        }
        else{
            Piece* piecetmp = new Piece (
                        vec3(//dimention
                             ajoutpiecedimx->value(),
                             ajoutpiecedimy->value(),
                             ajoutpiecedimz->value()),
                        vec3(),//rotation
                        vec3(),//position
                        scenetemp->getMaterial(comboajoutpiece->currentText()));

             piecetmp->shaderId(scenetemp->getShader(comboajoutpieceshader->currentText()));

             scenetemp->addPiece( lineeditajoutpiece->text(), piecetmp);

                //ajout des murs
                if (checkmur1->isChecked())
                {

                    Plan* plantmp = new Plan(
                                ajoutpiecedimx->value(),//width
                                ajoutpiecedimz->value(),//height
                                20,//widthDivision
                                20,//heightDivision
                                QList<QRectF>(),
                                scenetemp->getMaterial(comboajoutpiece->currentText()),//material
                                vec3(-90,0,0),
                                vec3(0,0,ajoutpiecedimz->value())
                                 );
                    plantmp->parent(piecetmp);

                    scenetemp->getPiece(lineeditajoutpiece->text())->addChild(lineeditajoutpiece->text()+"_bas" ,plantmp);
                }
               if (checkmur2->isChecked())
               {
                   Plan* plantmp = new Plan(
                               ajoutpiecedimx->value(),//width
                               ajoutpiecedimz->value(),//height
                               20,//widthDivision
                               20,//heightDivision
                               QList<QRectF>(),
                               scenetemp->getMaterial(comboajoutpiece->currentText()),//material
                               vec3(90,0,0),
                               vec3(0,ajoutpiecedimy->value(),0)
                                );
                   plantmp->parent(piecetmp);

                   scenetemp->getPiece(lineeditajoutpiece->text())->addChild(lineeditajoutpiece->text()+"_haut" ,plantmp);
               }

                if (checkmur3->isChecked())
                {
                    Plan* plantmp = new Plan(
                                ajoutpiecedimx->value(),//width
                                ajoutpiecedimy->value(),//height
                                20,//widthDivision
                                20,//heightDivision
                                QList<QRectF>(),
                                scenetemp->getMaterial(comboajoutpiece->currentText())//material
                                 );
                    plantmp->parent(piecetmp);

                    scenetemp->getPiece(lineeditajoutpiece->text())->addChild(lineeditajoutpiece->text()+"_arriere" ,plantmp);
                }
                if (checkmur4->isChecked())
                {
                    Plan* plantmp = new Plan(
                                ajoutpiecedimx->value(),//width
                                ajoutpiecedimy->value(),//height
                                20,//widthDivision
                                20,//heightDivision
                                QList<QRectF>(),
                                scenetemp->getMaterial(comboajoutpiece->currentText()),//material
                                vec3(0,180,0),
                                vec3(ajoutpiecedimx->value(),0,ajoutpiecedimz->value())
                                 );
                    plantmp->parent(piecetmp);

                    scenetemp->getPiece(lineeditajoutpiece->text())->addChild(lineeditajoutpiece->text()+"_avant" ,plantmp);
                }
                if (checkmur5->isChecked())
                {
                    Plan* plantmp = new Plan(
                                ajoutpiecedimz->value(),//width
                                ajoutpiecedimy->value(),//height
                                20,//widthDivision
                                20,//heightDivision
                                QList<QRectF>(),
                                scenetemp->getMaterial(comboajoutpiece->currentText()),//material
                                vec3(0,-90,0),
                                vec3(ajoutpiecedimx->value(),0,0)
                                 );
                    plantmp->parent(piecetmp);

                    scenetemp->getPiece(lineeditajoutpiece->text())->addChild(lineeditajoutpiece->text()+"_gauche" ,plantmp);
                }
               if (checkmur6->isChecked())
               {
                   Plan* plantmp = new Plan(
                               ajoutpiecedimz->value(),//width
                               ajoutpiecedimy->value(),//height
                               20,//widthDivision
                               20,//heightDivision
                               QList<QRectF>(),
                               scenetemp->getMaterial(comboajoutpiece->currentText()),//material
                               vec3(0,90,0),
                               vec3(0,0,ajoutpiecedimz->value())
                                );
                   plantmp->parent(piecetmp);

                   scenetemp->getPiece(lineeditajoutpiece->text())->addChild(lineeditajoutpiece->text()+"_droite" ,plantmp);
               }

                //fin de l'ajout
                dockajoutpiece->close();

                //ajout au model qui liste les objets
                if(objet){
                        objet->appendRow(new QStandardItem(lineeditajoutpiece->text()));

                            for (int i = 0 ;i<objet->rowCount(); i++)
                            {

                                if ((objet->child(i)->text())== (lineeditajoutpiece->text()) )
                                {
                                    if (checkmur1->isChecked()) {objet->child(i)->appendRow(new QStandardItem(lineeditajoutpiece->text()+"_bas"));}
                                    if (checkmur2->isChecked()) {objet->child(i)->appendRow(new QStandardItem(lineeditajoutpiece->text()+"_haut"));}
                                    if (checkmur3->isChecked()) {objet->child(i)->appendRow(new QStandardItem(lineeditajoutpiece->text()+"_arriere"));}
                                    if (checkmur4->isChecked()) {objet->child(i)->appendRow(new QStandardItem(lineeditajoutpiece->text()+"_avant"));}
                                    if (checkmur5->isChecked()) {objet->child(i)->appendRow(new QStandardItem(lineeditajoutpiece->text()+"_gauche"));}
                                    if (checkmur6->isChecked()) {objet->child(i)->appendRow(new QStandardItem(lineeditajoutpiece->text()+"_droite"));}

                                }
                            }
                        }
            }
        }

    //aide
    void MainWindow::Racourcit()
    {
    }


    //supression
    void MainWindow::supresionelement()
    {

        //supression lumiere
        if( modele->data ( (vue->selectionModel()->currentIndex().parent()), Qt::DisplayRole)=="Light")
            {
            widget->getScene()->removeLight(vue->selectionModel()->currentIndex().data().toString());
            light->removeRow(vue->selectionModel()->currentIndex().row());
            }
        //supresion piece
        if( modele->data ( (vue->selectionModel()->currentIndex().parent()), Qt::DisplayRole)=="Objet")
            {
            widget->getScene()->removePiece(vue->selectionModel()->currentIndex().data().toString());
            objet->removeRow(vue->selectionModel()->currentIndex().row());
            }
        //supression objet
        if( modele->data ( (vue->selectionModel()->currentIndex().parent().parent()), Qt::DisplayRole)=="Objet")
            {
            widget->getScene()->getPiece(vue->selectionModel()->currentIndex().parent().data().toString())->removeChild(vue->selectionModel()->currentIndex().data().toString());

            objet->child(vue->selectionModel()->currentIndex().parent().row())->removeRow(vue->selectionModel()->currentIndex().row());
                        std::cout<< vue->selectionModel()->currentIndex().parent().data().toString().toStdString() << std::endl;
                        std::cout<<vue->selectionModel()->currentIndex().data().toString().toStdString() <<std::endl;
            }
    }

//fin Menubars

//__fin_slots____________________________//
