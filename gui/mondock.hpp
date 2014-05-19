#ifndef mon_dock
#define mon_dock

#include "scene.hpp"
#include <helper.hpp>

#include <QDockWidget>
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
#include <QHBoxLayout>
#include <QStandardItemModel>
#include <QPushButton>
#include <QTabWidget>
#include <QSlider>
#include <QDoubleSpinBox>
#include<QLabel>
#include<QString>
#include <QComboBox>

class Mondock:public QDockWidget
{
Q_OBJECT
public:
    Mondock(const QString & title, QWidget * parent = 0, Qt::WindowFlags flags = 0);
    ~Mondock();

public://a metre private plus tard (donc geter/seter a faire)

    Scene *dockscene;
    Light * _light;
    Material * _materiaux;
    Objet * _objet;
    Piece * _piece;

    QStandardItemModel *dockmodele;
    QTreeView *dockvue;

    QStandardItem *_itemmaterial;//liste des materiaux
    QStandardItem *_itempiece;//liste des piece

private:

             QItemSelectionModel *selection;
             QModelIndex indexElementSelectionne;
             QVariant elementSelectionneParent;

             QModelIndex indexlightSelectionne;
             QVariant lightselectioner;

             QModelIndex indexmaterialSelectionne;
             QVariant materialselectioner;

             QModelIndex indexpieceSelectionne;
             QVariant pieceselectioner;

             QModelIndex indexgparent;
             QVariant elementSelectionneGParent;

             QModelIndex indexobjetlSelectionne;
             QVariant objetselectioner;
public:
             QStandardItemModel * modelmaterial;//(model de la liste des materiaux)
private:
             QStandardItemModel * modelpiece;//(model de la liste des piece)

/* ******************************************************** */
             //lumiere
/* ******************************************************** */

             //contien les 4 widget ( pos , amb , spe, dif)
             QTabWidget * tablight;

            //position
             QWidget * tablightpos;
             QHBoxLayout *tablightposlayout;
                QDoubleSpinBox *lightdoublespinboxx;
                QDoubleSpinBox *lightdoublespinboxy;
                QDoubleSpinBox *lightdoublespinboxz;
             //difuse
                QWidget * tablightdif;
                QVBoxLayout  *tabdiflayout;

                    QHBoxLayout *lightdiflayout;
                       QSlider *sliderdifx;
                       QSlider *sliderdify;
                       QSlider *sliderdifz;

                    QHBoxLayout *labeldiflayout;
                       QLabel *labeldifx;
                       QLabel *labeldify;
                       QLabel *labeldifz;
            //speculaire
                QWidget * tablightspe;
                QVBoxLayout  *tabspelayout;

                    QHBoxLayout *lightspelayout;
                       QSlider *sliderspex;
                       QSlider *sliderspey;
                       QSlider *sliderspez;

                    QHBoxLayout *labelspelayout;
                       QLabel *labelspex;
                       QLabel *labelspey;
                       QLabel *labelspez;
             //ambiant
             QWidget * tablightamb;
             QVBoxLayout  *tabamblayout;

                 QHBoxLayout *lightamblayout;
                    QSlider *sliderambx;
                    QSlider *slideramby;
                    QSlider *sliderambz;

                 QHBoxLayout *labelamblayout;
                    QLabel *labelambx;
                    QLabel *labelamby;
                    QLabel *labelambz;
/* ******************************************************** */
                      //materiaux
/* ******************************************************** */

                    //contien les 4 widget ( emisive , ambiante , spe, dif)
                    QTabWidget * tabmaterial;

                    //ambiante
                    QWidget * tabmaterialamb;
                    QHBoxLayout *tabmaterialamblayout;
                       QSpinBox *materialspinboxambx;
                       QSpinBox *materialspinboxamby;
                       QSpinBox *materialspinboxambz;

                    //difuse
                    QWidget * tabmaterialdif;
                    QHBoxLayout *tabmaterialdiflayout;
                       QSpinBox *materialspinboxdifx;
                       QSpinBox *materialspinboxdify;
                       QSpinBox *materialspinboxdifz;

                    //speculaire
                       QWidget * tabmaterialspe;
                       QHBoxLayout *tabmaterialspelayout;
                          QSpinBox *materialspinboxspex;
                          QSpinBox *materialspinboxspey;
                          QSpinBox *materialspinboxspez;
                          QSpinBox *materialspinboxspea;

                    //emisive
                          QWidget * tabmaterialemi;
                          QHBoxLayout *tabmaterialemilayout;
                             QSpinBox *materialspinboxemix;
                             QSpinBox *materialspinboxemiy;
                             QSpinBox *materialspinboxemiz;

/* ******************************************************** */
                   //objet
/* ******************************************************** */

//contien les 4 widget ( propriété ,rotation , trans, scale )
                QTabWidget * tabobjet;

                //propriete
                QWidget * tabobjetpropr;
                    QVBoxLayout *layouttabobjetpropr ;
                        QHBoxLayout *layouttabobjetproprlabel;
                        QHBoxLayout *layouttabobjetproprcombo;

                    QComboBox *combomaterial;
                    QComboBox *comboparent;

                    QLabel *labelobjetproprmaterial;
                    QLabel *labelobjetproprparent;
                //rotation
                QWidget * tabobjetrotation;
                    QHBoxLayout * layouttabobjetrotation;

                    QDoubleSpinBox * boxobjetrotationx;
                    QDoubleSpinBox * boxobjetrotationy;
                    QDoubleSpinBox * boxobjetrotationz;

                //translation
                QWidget * tabobjettrans;
                    QHBoxLayout * layouttabobjettrans;

                    QDoubleSpinBox * boxobjettransx;
                    QDoubleSpinBox * boxobjettransy;
                    QDoubleSpinBox * boxobjettransz;
                //scale
                QWidget * tabobjetscale;
                    QHBoxLayout * layouttabobjetscale;

                    QDoubleSpinBox * boxobjetscalex;
                    QDoubleSpinBox * boxobjetscaley;
                    QDoubleSpinBox * boxobjetscalez;

/* ******************************************************** */
                    //piece
/* ******************************************************** */
                QTabWidget * tabpiece;

                    QWidget * widgetpiecedim;
                    QHBoxLayout *piecedimlayout;

                    QSpinBox* dimentionpiecex;
                    QSpinBox* dimentionpiecey;
                    QSpinBox* dimentionpiecez;


                    QWidget * widgetpieceposi;
                    QHBoxLayout *pieceposilayout;

                    QSpinBox* positionpiecex;
                    QSpinBox* positionpiecey;
                    QSpinBox* positionpiecez;


                void traitementlumiere();
                void traitementmaterial();
                void traitementobjet();
                void traitementpiece();

private slots:
    void selectionlight();

    void poslightfuncx(double x);
    void poslightfuncy(double x);
    void poslightfuncz(double x);

    void amblightfuncx(int x);
    void amblightfuncy(int x);
    void amblightfuncz(int x);

    void diflightfuncx(int x);
    void diflightfuncy(int x);
    void diflightfuncz(int x);

    void spelightfuncx(int x);
    void spelightfuncy(int x);
    void spelightfuncz(int x);

//materiaux
//    void emimaterialfuncx(int x);
//    void emimaterialfuncy(int x);
//    void emimaterialfuncz(int x);

    void ambmaterialfuncx(int x);
    void ambmaterialfuncy(int x);
    void ambmaterialfuncz(int x);

    void difmaterialfuncx(int x);
    void difmaterialfuncy(int x);
    void difmaterialfuncz(int x);

    void spematerialfuncx(int x);
    void spematerialfuncy(int x);
    void spematerialfuncz(int x);
    void spematerialtfunca(int x);

//objet
    void matobjet(const QString & text );
    void pereobjet(const QString & text );

    void rotobjectx(double x);
    void rotobjecty(double x);
    void rotobjectz(double x);

    void transobjectx(double x);
    void transobjecty(double x);
    void transobjectz(double x);

    void scaleobjectx(double x);
    void scaleobjecty(double x);
    void scaleobjectz(double x);

//piece
    void slotpositionpiecex(int x);
    void slotpositionpiecey(int x);
    void slotpositionpiecez(int x);

//    void slotdimentionpiecex(double);
//    void slotdimentionpiecey(double);
//    void slotdimentionpiecez(double);
};
#endif
