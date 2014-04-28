#include "mainwindows.hpp"



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

/* ************************************** */
//            Status bars                 //
/* ************************************** */
    QString message = tr("d'eventuel variable  comme la position truc comme ca quoi");
    statusBar()->showMessage(message);
//fin statut bar

/* ************************************** */
//              Dock widgets              //
/* ************************************** */
    QDockWidget* dock = new QDockWidget(tr("Dock Widget"), this);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea);
   //dock->setWidget(le widget);
    addDockWidget(Qt::LeftDockWidgetArea, dock);
//fin dock widget


    createActions();
    createMenus();
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
     connect( kiterAct, SIGNAL(triggered()), this, SLOT(Kiter()));

     //affichage
     editionAct = new QAction(tr("&Edition"), this);
     connect( editionAct, SIGNAL(triggered()), this, SLOT(Edition()));

     apercutAct = new QAction(tr("&Apercut"), this);
     connect(apercutAct, SIGNAL(triggered()), this, SLOT(Apercut()));

     grilleAct = new QAction(tr("&Grille"), this);
     connect( grilleAct, SIGNAL(triggered()), this, SLOT(Grille()));

     //outil
     lumiereAct = new QAction(tr("&Lumiere"), this);
     connect( lumiereAct, SIGNAL(triggered()), this, SLOT(Lumiere()));

     importation3DAct = new QAction(tr("&Importation3D"), this);
     connect( importation3DAct, SIGNAL(triggered()), this, SLOT(Importation3D()));

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


    Affichage = menuBar()->addMenu(tr("&Affichage"));
    Affichage->addAction(editionAct);
    Affichage->addAction(apercutAct);
    Affichage->addAction(grilleAct);


    Outil = menuBar()->addMenu(tr("&Outil"));
    Outil->addAction(lumiereAct);
    Outil->addAction(importation3DAct);

    Aide = menuBar()->addMenu(tr("&Aide"));
    Aide->addAction(racourcitAct);
}

/* ************************************** */
//               Menubars                 //
/* ************************************** */
    //fichier
    void MainWindow::Nouveau(){}
    void MainWindow::Ouvrir(){}
    void MainWindow::Enregistrer(){}
    void MainWindow::Kiter(){}

    //affichage
    void MainWindow::Edition(){}
    void MainWindow::Apercut(){}
    void MainWindow::Grille(){}

    //outil
    void MainWindow::Lumiere(){}
    void MainWindow::Importation3D(){}

    //aide
    void MainWindow::Racourcit(){}
//fin Menubars
