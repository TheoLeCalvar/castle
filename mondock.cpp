#include<mondock.hpp>

Mondock::Mondock(const QString & title, QWidget * parent, Qt::WindowFlags flags):
    QDockWidget(title,parent,flags)
{


}

Mondock:: ~Mondock(){

}
//___slots___________________________________________________//


     void Mondock::selectionlight()
     {
         //selection et verification du parent de l'element selectioner
         selection = dockvue->selectionModel();
         indexElementSelectionne = selection->currentIndex();
         elementSelectionneParent = dockmodele->data(indexElementSelectionne.parent(), Qt::DisplayRole);

         //si parent = light
         if (elementSelectionneParent.toString()=="Light")
                     {
                       traitementlumiere();
                     }
     }

    void Mondock::amblightfuncx(int x)
            {
            _light->set(GL_AMBIENT, vec3(x/25.5,_light->_ambient[1],_light->_ambient[2]));

            QString tmp = QString::number((double)x);

            labelambx->setText(" X = " + tmp);
            }

    void Mondock::amblightfuncy(int x)
            {
            _light->set(GL_AMBIENT, vec3(_light->_ambient[0],x/25.5,_light->_ambient[2]));

            QString tmp = QString::number((double)x);

            labelamby->setText(" Y = " + tmp);
            }

    void Mondock::amblightfuncz(int x)
            {
            _light->set(GL_AMBIENT, vec3(_light->_ambient[0],_light->_ambient[1],x/25.5));

            QString tmp = QString::number((double)x);

            labelambz->setText(" Z = " + tmp);
            }

    void Mondock::diflightfuncx(int x)
            {
            _light->set(GL_DIFFUSE, vec3(x/25.5,_light->_diffuse[1],_light->_diffuse[2]));

            QString tmp = QString::number((double)x);

            labeldifx->setText(" X = " + tmp);
            }

    void Mondock::diflightfuncy(int x)
            {
            _light->set(GL_DIFFUSE, vec3(_light->_diffuse[0],x/25.5,_light->_diffuse[2]));

            QString tmp = QString::number((double)x);

            labeldify->setText(" Y = " + tmp);
            }

    void Mondock::diflightfuncz(int x)
            {
            _light->set(GL_DIFFUSE, vec3(_light->_diffuse[0],_light->_diffuse[1],x/25.5));

            QString tmp = QString::number((double)x);

            labeldifz->setText(" Z = " + tmp);
            }

    void Mondock::spelightfuncx(int x)
            {
            _light->set(GL_SPECULAR, vec3(x/25.5,_light->_specular[1],_light->_specular[2]));

            QString tmp = QString::number((double)x);

            labelspex->setText(" X = " + tmp);
            }

    void Mondock::spelightfuncy(int x)
            {
            _light->set(GL_SPECULAR, vec3(_light->_specular[0],x/25.5,_light->_specular[2]));

            QString tmp = QString::number((double)x);

            labelspey->setText(" Y = " + tmp);
            }

    void Mondock::spelightfuncz(int x)
            {
             _light->set(GL_SPECULAR, vec3(_light->_specular[0],_light->_specular[1],x/25.5));

             QString tmp = QString::number((double)x);

             labelspez->setText(" Z = " + tmp);

            }

    void Mondock::poslightfuncx(double x)
            {
            _light->set(GL_POSITION,vec3(x,_light->_position[1],_light->_position[2]));
            }

    void Mondock::poslightfuncy(double x)
            {
            _light->set(GL_POSITION,vec3(_light->_position[0],x,_light->_position[2]));
            }

    void Mondock::poslightfuncz(double x)
            {
            _light->set(GL_POSITION,vec3(_light->_position[0],_light->_position[1],x));
            }
//_____slots_________________________//


/* ************************************ */
//             lumiere                  //
/* ************************************ */

    void Mondock::traitementlumiere()
        {
        //variable
        int xtmp;
        int ytmp;
        int ztmp;

         QString sxtmp ;
         QString sytmp ;
         QString sztmp ;

        //fin variable

        indexlightSelectionne = selection->currentIndex();
        lightselectioner = dockmodele->data(indexlightSelectionne, Qt::DisplayRole);

        //renome le dockwidget

        this->setWindowTitle(lightselectioner.toString());

        this->_light= dockscene->getLight(lightselectioner.toString());
        //creation qtabwidget
        tablight = new QTabWidget();

        //creation des 4 widget du Qtab

        //widget1
        tablightpos = new QWidget();
            lightdoublespinboxx = new QDoubleSpinBox(this);
                lightdoublespinboxx->setPrefix("X = ");
                lightdoublespinboxx->setRange(-1000,1000);
                lightdoublespinboxx->setValue(this->_light->_position[0]);
            connect(lightdoublespinboxx, SIGNAL(valueChanged(double)),this, SLOT(poslightfuncx(double)));

            lightdoublespinboxy = new QDoubleSpinBox(this);
                lightdoublespinboxy->setPrefix("Y = ");
                lightdoublespinboxy->setRange(-1000,1000);
                lightdoublespinboxy->setValue(this->_light->_position[1]);
            connect(lightdoublespinboxy, SIGNAL(valueChanged(double)),this, SLOT(poslightfuncy(double)));

            lightdoublespinboxz = new QDoubleSpinBox(this);
                lightdoublespinboxz->setPrefix("Z = ");
                lightdoublespinboxz->setRange(-1000,1000);
                lightdoublespinboxz->setValue(this->_light->_position[2]);
            connect(lightdoublespinboxz, SIGNAL(valueChanged(double)),this, SLOT(poslightfuncz(double)));

            //partie layout
            tablightposlayout = new QHBoxLayout();
                tablightposlayout->addWidget(lightdoublespinboxx);
                tablightposlayout->addWidget(lightdoublespinboxy);
                tablightposlayout ->addWidget(lightdoublespinboxz);



          tablightpos->setLayout(tablightposlayout);

        //widget2
        tablightdif = new QWidget();
             sliderdifx = new QSlider(Qt::Horizontal);
                    sliderdifx->setMinimum(0);
                    sliderdifx->setMaximum(255);
                    sliderdifx->setValue((int)((this->_light->_diffuse[0])*25.5));
             connect(sliderdifx, SIGNAL(valueChanged ( int )), this, SLOT(diflightfuncx(int)));

             sliderdify = new QSlider(Qt::Horizontal);
                     sliderdify->setMinimum(0);
                     sliderdify->setMaximum(255);
                     sliderdify->setValue((int)((this->_light->_diffuse[1])*25.5));
             connect(sliderdify, SIGNAL(valueChanged ( int )), this, SLOT(diflightfuncy(int)));

             sliderdifz = new QSlider(Qt::Horizontal);
                     sliderdifz->setMinimum(0);
                     sliderdifz->setMaximum(255);
                     sliderdifz->setValue((int)((this->_light->_diffuse[2])*25.5));
             connect(sliderdifz, SIGNAL(valueChanged ( int )), this, SLOT(diflightfuncz(int)));

             //partie label
                 labeldifx = new QLabel();
                 labeldify = new QLabel();
                 labeldifz = new QLabel();

                 xtmp = ((this->_light->_diffuse[0])*25.5);
                 ytmp = ((this->_light->_diffuse[1])*25.5);
                 ztmp = ((this->_light->_diffuse[2])*25.5);

                 sxtmp = QString::number(xtmp);
                 sytmp = QString::number(ytmp);
                 sztmp = QString::number(ztmp);



                 labeldifx->setText(" X = " + sxtmp);
                 labeldify->setText(" Y = " + sytmp);
                 labeldifz->setText(" Z = " + sztmp);

             //partie layout
                 tabdiflayout= new QVBoxLayout();

                    labeldiflayout = new QHBoxLayout();
                    lightdiflayout = new QHBoxLayout();

                       labeldiflayout->addWidget(labeldifx);
                       lightdiflayout->addWidget(sliderdifx);

                       labeldiflayout->addWidget(labeldify);
                       lightdiflayout->addWidget(sliderdify);

                       labeldiflayout->addWidget(labeldifz);
                       lightdiflayout->addWidget(sliderdifz);

                 tabdiflayout->addLayout(labeldiflayout);
                 tabdiflayout->addLayout(lightdiflayout);

               tablightdif->setLayout(tabdiflayout);

        //widget3
        tablightspe = new QWidget();
             sliderspex = new QSlider(Qt::Horizontal);
                    sliderspex->setMinimum(0);
                    sliderspex->setMaximum(255);
                    sliderspex->setValue((int)((this->_light->_specular[0])*25.5));
              connect(sliderspex, SIGNAL(valueChanged ( int )), this, SLOT(spelightfuncx(int)));


             sliderspey = new QSlider(Qt::Horizontal);
                     sliderspey->setMinimum(0);
                     sliderspey->setMaximum(255);
                     sliderspey->setValue((int)((this->_light->_specular[1])*25.5));
              connect(sliderspey, SIGNAL(valueChanged ( int )), this, SLOT(spelightfuncy(int)));

             sliderspez = new QSlider(Qt::Horizontal);
                     sliderspez->setMinimum(0);
                     sliderspez->setMaximum(255);
                     sliderspez->setValue((int)((this->_light->_specular[2])*25.5));
              connect(sliderspez, SIGNAL(valueChanged ( int )), this, SLOT(spelightfuncz(int)));

              //partie label
                  labelspex = new QLabel();
                  labelspey = new QLabel();
                  labelspez = new QLabel();

                  xtmp = ((this->_light->_specular[0])*25.5);
                  ytmp = ((this->_light->_specular[1])*25.5);
                  ztmp = ((this->_light->_specular[2])*25.5);

                  sxtmp = QString::number(xtmp);
                  sytmp = QString::number(ytmp);
                  sztmp = QString::number(ztmp);


                  labelspex->setText(" X = " + sxtmp);
                  labelspey->setText(" Y = " + sytmp);
                  labelspez->setText(" Z = " + sztmp);

              //partie layout
                  tabspelayout= new QVBoxLayout();

                     labelspelayout = new QHBoxLayout();
                     lightspelayout = new QHBoxLayout();

                        labelspelayout->addWidget(labelspex);
                        lightspelayout->addWidget(sliderspex);

                        labelspelayout->addWidget(labelspey);
                        lightspelayout->addWidget(sliderspey);

                        labelspelayout->addWidget(labelspez);
                        lightspelayout->addWidget(sliderspez);

                  tabspelayout->addLayout(labelspelayout);
                  tabspelayout->addLayout(lightspelayout);

                tablightspe->setLayout(tabspelayout);

        //widget4
        tablightamb = new QWidget();
             sliderambx = new QSlider(Qt::Horizontal);
                    sliderambx->setMinimum(0);
                    sliderambx->setMaximum(255);
                    sliderambx->setValue((int)((this->_light->_ambient[0])*25.5));
              connect(sliderambx, SIGNAL(valueChanged ( int )), this, SLOT(amblightfuncx(int)));

             slideramby = new QSlider(Qt::Horizontal);
                     slideramby->setMinimum(0);
                     slideramby->setMaximum(255);
                     slideramby->setValue((int)((this->_light->_ambient[1])*25.5));
              connect(slideramby, SIGNAL(valueChanged ( int )), this, SLOT(amblightfuncy(int)));

             sliderambz = new QSlider(Qt::Horizontal);
                     sliderambz->setMinimum(0);
                     sliderambz->setMaximum(255);
                     sliderambz->setValue((int)((this->_light->_ambient[2])*25.5));
              connect(sliderambz, SIGNAL(valueChanged ( int )), this, SLOT(amblightfuncz(int)));
              //partie label
                  labelambx = new QLabel();
                  labelamby = new QLabel();
                  labelambz = new QLabel();

                  xtmp = ((this->_light->_ambient[0])*25.5);
                  ytmp = ((this->_light->_ambient[1])*25.5);
                  ztmp = ((this->_light->_ambient[2])*25.5);

                  sxtmp = QString::number(xtmp);
                  sytmp = QString::number(ytmp);
                  sztmp = QString::number(ztmp);



                  labelambx->setText(" X = " + sxtmp);
                  labelamby->setText(" Y = " + sytmp);
                  labelambz->setText(" Z = " + sztmp);

              //partie layout
              tabamblayout= new QVBoxLayout();

                 labelamblayout = new QHBoxLayout();
                 lightamblayout = new QHBoxLayout();

                    labelamblayout->addWidget(labelambx);
                    lightamblayout->addWidget(sliderambx);

                    labelamblayout->addWidget(labelamby);
                    lightamblayout->addWidget(slideramby);

                    labelamblayout->addWidget(labelambz);
                    lightamblayout->addWidget(sliderambz);

              tabamblayout->addLayout(labelamblayout);
              tabamblayout->addLayout(lightamblayout);

            tablightamb->setLayout(tabamblayout);

        //assosiation des 4widget au tab
        tablight->addTab(tablightpos , "Position");
        tablight->addTab(tablightdif, "Difuse" );
        tablight->addTab(tablightspe, "Speculaire");
        tablight->addTab(tablightamb, "Ambiante" );

        //fixe de widget et afiche le dockwidget
        this->setWidget(tablight);
        this->show();
        }
