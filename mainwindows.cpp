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

    createActions();
    createMenus();

/* ************************************** */
//            Status bars                 //
/* ************************************** */
    QString message = tr("d'eventuel variable  comme la position truc comme ca quoi");
    statusBar()->showMessage(message);
//fin statut bar





/* ************************************** */
//              Dock widgets              //
/* ************************************** */

    modele = new QDirModel;
    vue = new QTreeView;
    vue->setModel(modele);
    vue->setRootIndex(modele->index("modeles"));


    dock = new QDockWidget(tr("modeles 3D"), this);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea);
    dock->setWidget(vue);
    addDockWidget(Qt::LeftDockWidgetArea, dock);
    dock->hide();

    dock1 = new QDockWidget(tr("lumiere"), this);
    dock1->setAllowedAreas(Qt::BottomDockWidgetArea);
    addDockWidget(Qt::BottomDockWidgetArea, dock1);
    dock1->hide();
//fin dock widget




/* ************************************** */
//               Toolbars                 //
/* ************************************** */

   fileToolBar=new QToolBar( tr("menubar"), this );
   fileToolBar->setAllowedAreas(Qt::TopToolBarArea);
   fileToolBar-> setMovable(false);
   addToolBar(Qt::TopToolBarArea, fileToolBar);

   fileToolBar->addAction(kiterAct);

   fileToolBar->addSeparator();

   fileToolBar->addAction(apercutAct);
   //apercutAct->setIcon(QIcon("icones/fullscreen.jpg"));

   fileToolBar->addSeparator();

   fileToolBar->addAction(importation3DAct);
   importation3DAct->setIcon(QIcon("icones/3d.jpeg"));
   fileToolBar->addAction(lumiereAct);
   lumiereAct->setIcon(QIcon("icones/ampoule.png"));

   fileToolBar->addSeparator();
 //fin toolbar
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

     //affichage
     editionAct = new QAction(tr("&Edition"), this);
     connect( editionAct, SIGNAL(triggered()), this, SLOT(Edition()));

     grilleAct = new QAction(tr("&Grille"), this);
     connect( grilleAct, SIGNAL(triggered()), this, SLOT(Grille()));

     apercutAct = new QAction(tr("&fullscreen"), this);
     connect(apercutAct, SIGNAL(triggered()), this, SLOT(Apercut()));
     apercutAct->setCheckable(true);

     //outil
     lumiereAct = new QAction(tr("&Lumiere"), this);
     connect( lumiereAct, SIGNAL(triggered()), this, SLOT(Lumiere()));
     lumiereAct->setCheckable(true);

     importation3DAct = new QAction(tr("&Importation"), this);
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

    Affichage = menuBar()->addMenu(tr("&Affichage"));
    Affichage->addAction(editionAct);
    Affichage->addAction(grilleAct);
    Affichage->addSeparator();
    Affichage->addAction(apercutAct);

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
    void MainWindow::Grille(){}

    //outil
    void MainWindow::Lumiere()
    {
         if (!(lumiereAct ->isChecked()))
         {
          dock1->hide();
         }
         else
         {
          dock1->show();
         }
    }

    void MainWindow::Importation3D(){

           if (!(importation3DAct->isChecked()))
           {
            dock->hide();
           }
           else
           {
            dock->show();
           }


    }

    //aide
    void MainWindow::Racourcit(){}
//fin Menubars
