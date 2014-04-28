#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QAction>
#include <QMenuBar>
#include <QDir>
#include <QGLFormat>
#include <QSurface>
#include "MyOpenGLWidget.hpp"
#include <QStatusBar>
#include <QDockWidget>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();


    private slots:

 /* ************************************** */
 //          slots  menu bar               //
 /* ************************************** */
        //fichier
        void Nouveau();
        void Ouvrir();
        void Enregistrer();
        void Kiter();

        //affichage
        void Edition();
        void Apercut();
        void Grille();

        //outil
        void Lumiere();
        void Importation3D();

        //aide
        void Racourcit();
//fin slots menu bar

    private:
        void createActions();
        void createMenus();

/* ************************************** */
//               menu bar                 //
/* ************************************** */
        QMenu *Fichier;
        QMenu *Affichage;
        QMenu *Outil;
        QMenu *Aide;

        //fichier
        QAction *nouveauAct;
        QAction *ouvrirAct;
        QAction *enregistrerAct;
        QAction *kiterAct;

        //affichage
        QAction *editionAct;
        QAction *apercutAct;
        QAction *grilleAct;

        //outil
        QAction *lumiereAct;
        QAction *importation3DAct;

        //aide
        QAction *racourcitAct;
//fin menu bar


/* ************************************** */
//               Toolbars                 //
/* ************************************** */
//fin toolbars

/* ************************************** */
//              Dock widgets              //
/* ************************************** */
//fin dock widgets

/* ************************************** */
//          Central  Widget               //
/* ************************************** */
        MyOpenGLWidget *widget;
//fin central Widget

/* ************************************** */
//            Status bars                 //
/* ************************************** */

//fin status bars

};

#endif // MAINWINDOW_HPP
