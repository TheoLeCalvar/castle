#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <mondock.hpp>
#include <QMainWindow>
#include <QAction>
#include <QMenuBar>
#include <QDir>
#include <QGLFormat>
#include <QSurface>
#include "MyOpenGLWidget.hpp"
#include <QStatusBar>
#include <QDockWidget>
#include <QToolBar>
#include <QFileSystemModel>
#include <QApplication>
#include <QStringListModel>
#include <QStringList>
#include <QHeaderView>
#include <QTreeView>
#include <QVBoxLayout>
#include <QStandardItemModel>
#include <QPushButton>
#include <QTabWidget>
#include <QSlider>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

//___slots_________________________________//
private slots:

 /* ************************************** */
 //           menu bar                     //
 /* ************************************** */
        //fichier
        void Nouveau();
        void Ouvrir();
        void Enregistrer();
        void Kiter();

        //edition
        void Annuler();
        void Retablir();

        //affichage
        void Apercut();
        void Culface();
        void Grille();

        //outil
        void Importation3D();

        //aide
        void Racourcit();
//fin slots menu bar


//__fin___slots___________________________//


    private:
        void createActions();
        void createMenus();
        void createListeDockwidget();
        void createToolBar();

/* ************************************** */
//               menu bar                 //
/* ************************************** */
        QMenu *Fichier;
        QMenu *Edition;
        QMenu *Affichage;
        QMenu *Outil;
        QMenu *Aide;

        //fichier
        QAction *nouveauAct;
        QAction *ouvrirAct;
        QAction *enregistrerAct;
        QAction *kiterAct;

        //edition
        QAction *annulerAct;
        QAction *retablirAct;

        //affichage
        QAction *apercutAct;
        QAction *culfaceAct;
        QAction *grilleAct;

        //outil
        QAction *importation3DAct;

        //aide
        QAction *racourcitAct;
//fin menu bar


/* ************************************** */
//               Toolbars                 //
/* ************************************** */
       QToolBar     *fileToolBar;
//fin toolbars

/* ************************************** */
//              Dock widgets              //
/* ************************************** */

       //liste element scene
       QDockWidget* dock_list_elements;

       QPushButton* boutonlisteelement;

       Scene * scenetemp;

       QStringList listtempobjet;
       QStringList listtemplight;
       QStringList listtempmaterial;
       QStringList listtemshader;

       QStandardItemModel *modele;

       QStandardItem *light;
       QStandardItem *material;
       QStandardItem *objet;
       QStandardItem *shader;

       QTreeView *vue;

       QVBoxLayout *layoutlistescene;

       QWidget * widgetdocklistscene;
       //fin liste element scene

       //widget element selectioner
       Mondock *dock_light;
       //fin element selectioner

//fin dock widgets

/* ************************************** */
//          Central  Widget               //
/* ************************************** */
        MyOpenGLWidget *widget;
//fin central Widget
};

#endif // MAINWINDOW_HPP
