#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "mondock.hpp"
#include "node.hpp"
#include "MyOpenGLWidget.hpp"

#include <QCheckBox>
#include <QMainWindow>
#include <QAction>
#include <QMenuBar>
#include <QDir>
#include <QGLFormat>
#include <QSurface>
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
#include <QLineEdit>

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
        void ajoutlumiere();
        void validajoutlumiere();
        void ajoutmaterial();
        void validajoutmaterial();
        void ajoutpiece();
        void validajoutpiece();


        //aide
        void Racourcit();
//fin slots menu bar


//__fin___slots___________________________//


    private:
        void createActions();
        void createMenus();
        void createListeDockwidget();
        void createToolBar();

        //fichage node
        void affichagerecnoderestant(Node *a , QStandardItem *b );

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

        QMenu *ajoutelement ;
            QAction *ajoutlumierAct;
            QAction *ajoutmaterialAct;
            QAction *ajoutpieceAct;
        //ajout lumiere
        QDockWidget * dockajoutlumiere;

            //contenu dock ajout lumiere
            QWidget * widgetajoutlumiere;

            QPushButton * boutonajoutlumiere;

            QLineEdit *lineeditnomajoutlumiere;
            QLabel *nomajoutlumiere;

            QDoubleSpinBox *spinpositionajoutlumierex;
            QDoubleSpinBox *spinpositionajoutlumierey;
            QDoubleSpinBox *spinpositionajoutlumierez;
            QLabel *positionajoutlumiere;

            QDoubleSpinBox *spindifajoutlumierex;
            QDoubleSpinBox *spindifajoutlumierey;
            QDoubleSpinBox *spindifajoutlumierez;
            QLabel *difajoutlumiere;

            QDoubleSpinBox *spinspeajoutlumierex;
            QDoubleSpinBox *spinspeajoutlumierey;
            QDoubleSpinBox *spinspeajoutlumierez;
            QLabel *speajoutlumiere;


            QHBoxLayout * layoutnomajoutlumiere;
            QHBoxLayout * layoutposajoutlumiere;
            QHBoxLayout * layoutdifajoutlumiere;
            QHBoxLayout * layoutspeajoutlumiere;

            QVBoxLayout * layoutajoutlumiere;

        //ajout materiaux
        QDockWidget * dockajoutmateriaux;

            //contenu dockajoutlumiere materiau
            QWidget * widgetajoutmaterial;

            QPushButton * boutonajoutmaterial;

            QLineEdit *lineeditnomajoutmaterial;
            QLabel *nomajoutmaterial;

            QDoubleSpinBox *spinambajoutmaterialx;
            QDoubleSpinBox *spinambajoutmaterialy;
            QDoubleSpinBox *spinambajoutmaterialz;
            QLabel *ambajoutmaterial;

            QDoubleSpinBox *spindifajoutmaterialx;
            QDoubleSpinBox *spindifajoutmaterialy;
            QDoubleSpinBox *spindifajoutmaterialz;
            QLabel *difajoutmaterial;

            QDoubleSpinBox *spinspeajoutmaterialx;
            QDoubleSpinBox *spinspeajoutmaterialy;
            QDoubleSpinBox *spinspeajoutmaterialz;
            QDoubleSpinBox *spinspeajoutmateriala;
            QLabel *speajoutmaterial;


            QHBoxLayout * layoutnomajoutmaterial;
            QHBoxLayout * layoutambajoutmaterial;
            QHBoxLayout * layoutdifajoutmaterial;
            QHBoxLayout * layoutspeajoutmaterial;


            QVBoxLayout * layoutajoutmaterial;

        //ajout piece
        QDockWidget * dockajoutpiece;

            //contenu ajout piece
            QWidget * widgetajoutpiece;

            QPushButton * boutonajoutpiece;

            QSpinBox * ajoutpiecedimx;
            QSpinBox * ajoutpiecedimy;
            QSpinBox * ajoutpiecedimz;

            QComboBox * comboajoutpiece;
            QStandardItemModel * modelemateriaupiece;

            QComboBox * comboajoutpieceshader;
            QStandardItemModel * modelepieceshader;

            QLabel * labelcomboajoutpiece;
            QLabel * labeldimajoutpiece;
            QLabel * labelnomajoutpiece;
            QLabel * labelmurajoutpiece;
            QLabel * labelajoutpieceshader;

            //label des mur
            QLabel * labelmur1;
            QLabel * labelmur2;
            QLabel * labelmur3;
            QLabel * labelmur4;
            QLabel * labelmur5;
            QLabel * labelmur6;
            //checkbox mur
            QCheckBox * checkmur1;
            QCheckBox * checkmur2;
            QCheckBox * checkmur3;
            QCheckBox * checkmur4;
            QCheckBox * checkmur5;
            QCheckBox * checkmur6;

            QLineEdit * lineeditajoutpiece;

            //layout ajout piece
            QVBoxLayout * mainlayoutajoutpiece;
                QHBoxLayout * ajoutpiecelayoutdim;
                QHBoxLayout * ajoutpiecelayoutnom;
                QHBoxLayout * ajoutpiecelayoutcombo;
                QHBoxLayout * ajoutpiecelabelmure;
                QHBoxLayout * ajoutpiecepiecer1;
                QHBoxLayout * ajoutpiecepiecer2;
                QHBoxLayout * ajoutpiecepiecer3;
                QHBoxLayout * ajoutpieceshaderlayout;

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
       Mondock *dock_perso;
       //fin element selectioner

//fin dock widgets

/* ************************************** */
//          Central  Widget               //
/* ************************************** */
        MyOpenGLWidget *widget;
//fin central Widget
};

#endif // MAINWINDOW_HPP
