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

    QStandardItemModel *dockmodele;
    QTreeView *dockvue;

private:

             QItemSelectionModel *selection;
             QModelIndex indexElementSelectionne;
             QVariant elementSelectionneParent;
             QModelIndex indexlightSelectionne;
             QVariant lightselectioner;

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

                void traitementlumiere();

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
};
#endif
