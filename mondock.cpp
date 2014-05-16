#include<mondock.hpp>
#include<iostream>
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
         //si parent = material
         if (elementSelectionneParent.toString()=="Material")
                     {
                       traitementmaterial();
                     }
        //si grand parent = Objet
         indexgparent= indexElementSelectionne.parent();
         elementSelectionneGParent= dockmodele->data(indexgparent.parent(), Qt::DisplayRole);

         if( (elementSelectionneGParent)=="Objet")
                    {
                    traitementobjet();
                    }
     }

    void Mondock::amblightfuncx(int x)
            {
            _light->get(GL_AMBIENT)[0]=x/255.0;

            QString tmp = QString::number((double)x);

            labelambx->setText(" X = " + tmp);
            }

    void Mondock::amblightfuncy(int x)
            {

            _light->get(GL_AMBIENT)[1]=x/255.0;

            QString tmp = QString::number((double)x);

            labelamby->setText(" Y = " + tmp);
            }

    void Mondock::amblightfuncz(int x)
            {
            _light->get(GL_AMBIENT)[2]=x/255.0;

            QString tmp = QString::number((double)x);

            labelambz->setText(" Z = " + tmp);
            }

    void Mondock::diflightfuncx(int x)
            {

            _light->get(GL_DIFFUSE)[0]=x/255.0;

            QString tmp = QString::number((double)x);

            labeldifx->setText(" X = " + tmp);
            }

    void Mondock::diflightfuncy(int x)
            {
            _light->get(GL_DIFFUSE)[1]=x/255.0;

            QString tmp = QString::number((double)x);

            labeldify->setText(" Y = " + tmp);
            }

    void Mondock::diflightfuncz(int x)
            {
            _light->get(GL_DIFFUSE)[2]=x/255.0;

            QString tmp = QString::number((double)x);

            labeldifz->setText(" Z = " + tmp);
            }

    void Mondock::spelightfuncx(int x)
            {
            _light->get(GL_SPECULAR)[0]=x/255.0;

            QString tmp = QString::number((double)x);

            labelspex->setText(" X = " + tmp);
            }

    void Mondock::spelightfuncy(int x)
            {
            _light->get(GL_SPECULAR)[1]=x/255.0;

            QString tmp = QString::number((double)x);

            labelspey->setText(" Y = " + tmp);
            }

    void Mondock::spelightfuncz(int x)
            {
            _light->get(GL_SPECULAR)[2]=x/255.0;

             QString tmp = QString::number((double)x);

             labelspez->setText(" Z = " + tmp);

            }

    void Mondock::poslightfuncx(double x)
            {
            _light->get(GL_POSITION)[0]=x;
            }

    void Mondock::poslightfuncy(double x)
            {
            _light->get(GL_POSITION)[1]=x;
            }

    void Mondock::poslightfuncz(double x)
            {
            _light->get(GL_POSITION)[2]=x;
            }

    //materiaux
        void Mondock::emimaterialfuncx(int x)
            {
            }

        void Mondock::emimaterialfuncy(int x)
            {
            }

        void Mondock::emimaterialfuncz(int x)
            {
            }

        void Mondock::ambmaterialfuncx(int x)
            {
            _materiaux->get(GL_AMBIENT)[0]=x/255.0;
            }

        void Mondock::ambmaterialfuncy(int x)
            {
            _materiaux->get(GL_AMBIENT)[1]=x/255.0;
            }

        void Mondock::ambmaterialfuncz(int x)
            {
            _materiaux->get(GL_AMBIENT)[2]=x/255.0;
            }

        void Mondock::difmaterialfuncx(int x)
            {
            _materiaux->get(GL_DIFFUSE)[0]=x/255.0;
            }

        void Mondock::difmaterialfuncy(int x)
            {
            _materiaux->get(GL_DIFFUSE)[1]=x/255.0;
            }

        void Mondock::difmaterialfuncz(int x)
            {
             _materiaux->get(GL_DIFFUSE)[2]=x/255.0;
            }

        void Mondock::spematerialfuncx(int x)
            {
            _materiaux->get(GL_SPECULAR)[0]=x/255.0;
            }

        void Mondock::spematerialfuncy(int x)
            {
            _materiaux->get(GL_SPECULAR)[1]=x/255.0;
            }

        void Mondock::spematerialfuncz(int x)
            {
            _materiaux->get(GL_SPECULAR)[2]=x/255.0;
            }

        void Mondock::spematerialtfunca(int x)
            {
            _materiaux->set((double)x);
            }


        //objet
        void Mondock::rotobjectx(double x)
            {
            vec3 vectmp =_objet->rotation();
            _objet->rotation(vec3(x,vectmp[1],vectmp[2]));
            }

        void Mondock::rotobjecty(double x)
            {
            vec3 vectmp =_objet->rotation();
            _objet->rotation(vec3(vectmp[0],x,vectmp[2]));
            }

        void Mondock::rotobjectz(double x)
            {
            vec3 vectmp =_objet->rotation();
            _objet->rotation(vec3(vectmp[0],vectmp[1],x));
            }
////
        void Mondock::transobjectx(double x)
            {
            vec3 vectmp =_objet->position();
            _objet->position(vec3(x,vectmp[1],vectmp[2]));
            }

        void Mondock::transobjecty(double x)
            {
            vec3 vectmp =_objet->position();
            _objet->position(vec3(vectmp[0],x,vectmp[2]));
            }

        void Mondock::transobjectz(double x)
            {
            vec3 vectmp =_objet->position();
            _objet->position(vec3(vectmp[0],vectmp[1],x));
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

        this->setWindowTitle("Edition :  " + lightselectioner.toString());

        this->_light= dockscene->getLight(lightselectioner.toString());
        //creation qtabwidget
        tablight = new QTabWidget();

        //creation des 4 widget du Qtab

        //widget1
        tablightpos = new QWidget();
            lightdoublespinboxx = new QDoubleSpinBox(this);
                lightdoublespinboxx->setPrefix("X = ");
                lightdoublespinboxx->setRange(-1000,1000);
                lightdoublespinboxx->setValue(this->_light->get(GL_POSITION)[0]);
            connect(lightdoublespinboxx, SIGNAL(valueChanged(double)),this, SLOT(poslightfuncx(double)));

            lightdoublespinboxy = new QDoubleSpinBox(this);
                lightdoublespinboxy->setPrefix("Y = ");
                lightdoublespinboxy->setRange(-1000,1000);
                lightdoublespinboxy->setValue(this->_light->get(GL_POSITION)[1]);
            connect(lightdoublespinboxy, SIGNAL(valueChanged(double)),this, SLOT(poslightfuncy(double)));

            lightdoublespinboxz = new QDoubleSpinBox(this);
                lightdoublespinboxz->setPrefix("Z = ");
                lightdoublespinboxz->setRange(-1000,1000);
                lightdoublespinboxz->setValue(this->_light->get(GL_POSITION)[2]);
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
                    sliderdifx->setValue((int)((this->_light->get(GL_DIFFUSE)[0])*255));
             connect(sliderdifx, SIGNAL(valueChanged ( int )), this, SLOT(diflightfuncx(int)));

             sliderdify = new QSlider(Qt::Horizontal);
                     sliderdify->setMinimum(0);
                     sliderdify->setMaximum(255);
                     sliderdify->setValue((int)((this->_light->get(GL_DIFFUSE)[1])*255));
             connect(sliderdify, SIGNAL(valueChanged ( int )), this, SLOT(diflightfuncy(int)));

             sliderdifz = new QSlider(Qt::Horizontal);
                     sliderdifz->setMinimum(0);
                     sliderdifz->setMaximum(255);
                     sliderdifz->setValue((int)((this->_light->get(GL_DIFFUSE)[2])*255));
             connect(sliderdifz, SIGNAL(valueChanged ( int )), this, SLOT(diflightfuncz(int)));

             //partie label
                 labeldifx = new QLabel();
                 labeldify = new QLabel();
                 labeldifz = new QLabel();

                 xtmp = ((this->_light->get(GL_DIFFUSE)[0])*255);
                 ytmp = ((this->_light->get(GL_DIFFUSE)[1])*255);
                 ztmp = ((this->_light->get(GL_DIFFUSE)[2])*255);

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
                    sliderspex->setValue((int)((this->_light->get(GL_SPECULAR)[0])*255));
              connect(sliderspex, SIGNAL(valueChanged ( int )), this, SLOT(spelightfuncx(int)));


             sliderspey = new QSlider(Qt::Horizontal);
                     sliderspey->setMinimum(0);
                     sliderspey->setMaximum(255);
                     sliderspey->setValue((int)((this->_light->get(GL_SPECULAR)[1])*255));
              connect(sliderspey, SIGNAL(valueChanged ( int )), this, SLOT(spelightfuncy(int)));

             sliderspez = new QSlider(Qt::Horizontal);
                     sliderspez->setMinimum(0);
                     sliderspez->setMaximum(255);
                     sliderspez->setValue((int)((this->_light->get(GL_SPECULAR)[2])*255));
              connect(sliderspez, SIGNAL(valueChanged ( int )), this, SLOT(spelightfuncz(int)));

              //partie label
                  labelspex = new QLabel();
                  labelspey = new QLabel();
                  labelspez = new QLabel();

                  xtmp = ((this->_light->get(GL_SPECULAR)[0])*255);
                  ytmp = ((this->_light->get(GL_SPECULAR)[1])*255);
                  ztmp = ((this->_light->get(GL_SPECULAR)[2])*255);

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
                    sliderambx->setValue((int)((this->_light->get(GL_AMBIENT)[0])*255));
              connect(sliderambx, SIGNAL(valueChanged ( int )), this, SLOT(amblightfuncx(int)));

             slideramby = new QSlider(Qt::Horizontal);
                     slideramby->setMinimum(0);
                     slideramby->setMaximum(255);
                     slideramby->setValue((int)((this->_light->get(GL_AMBIENT)[1])*255));
              connect(slideramby, SIGNAL(valueChanged ( int )), this, SLOT(amblightfuncy(int)));

             sliderambz = new QSlider(Qt::Horizontal);
                     sliderambz->setMinimum(0);
                     sliderambz->setMaximum(255);
                     sliderambz->setValue((int)((this->_light->get(GL_AMBIENT)[2])*255));
              connect(sliderambz, SIGNAL(valueChanged ( int )), this, SLOT(amblightfuncz(int)));
              //partie label
                  labelambx = new QLabel();
                  labelamby = new QLabel();
                  labelambz = new QLabel();

                  xtmp = ((this->_light->get(GL_AMBIENT)[0])*255);
                  ytmp = ((this->_light->get(GL_AMBIENT)[1])*255);
                  ztmp = ((this->_light->get(GL_AMBIENT)[2])*255);

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
/* ************************************ */
//             material                 //
/* ************************************ */

        void Mondock::traitementmaterial()
            {

            indexmaterialSelectionne = selection->currentIndex();
            materialselectioner = dockmodele->data(indexmaterialSelectionne, Qt::DisplayRole);

            //renome le dockwidget

            this->setWindowTitle("Edition :  " + materialselectioner.toString());

            this->_materiaux= dockscene->getMaterial(materialselectioner.toString());

            //creation qtabwidget
            tabmaterial = new QTabWidget();

            //creation 4 widget

            //widget1
            tabmaterialemi = new QWidget();
                materialspinboxemix = new QSpinBox(this);
                materialspinboxemix->setPrefix("X = ");
                materialspinboxemix->setRange(0,255);
                connect(materialspinboxemix, SIGNAL(valueChanged(int)),this, SLOT(emimaterialfuncx(int)));

                materialspinboxemiy = new QSpinBox(this);
                materialspinboxemiy->setPrefix("Y = ");
                materialspinboxemiy->setRange(0,255);
                connect(materialspinboxemiy, SIGNAL(valueChanged(int)),this, SLOT(emimaterialfuncy(int)));

                materialspinboxemiz = new QSpinBox(this);
                materialspinboxemiz->setPrefix("Z = ");
                materialspinboxemiz->setRange(0,255);
                connect(materialspinboxemiz, SIGNAL(valueChanged(int)),this, SLOT(emimaterialfuncz(int)));

                //partie layout
                tabmaterialemilayout = new QHBoxLayout();
                    tabmaterialemilayout->addWidget(materialspinboxemix);
                    tabmaterialemilayout->addWidget(materialspinboxemiy);
                    tabmaterialemilayout->addWidget(materialspinboxemiz);

              tabmaterialemi->setLayout(tabmaterialemilayout);

              //widget2
              tabmaterialdif = new QWidget();
                  materialspinboxdifx = new QSpinBox(this);
                  materialspinboxdifx->setPrefix("X = ");
                  materialspinboxdifx->setRange(0,255);
                  materialspinboxdifx->setValue(this->_materiaux->get(GL_DIFFUSE)[0]*255);
                  connect(materialspinboxdifx, SIGNAL(valueChanged(int)),this, SLOT(difmaterialfuncx(int)));

                  materialspinboxdify = new QSpinBox(this);
                  materialspinboxdify->setPrefix("Y = ");
                  materialspinboxdify->setRange(0,255);
                  materialspinboxdify->setValue(this->_materiaux->get(GL_DIFFUSE)[1]*255);
                  connect(materialspinboxdify, SIGNAL(valueChanged(int)),this, SLOT(difmaterialfuncy(int)));

                  materialspinboxdifz = new QSpinBox(this);
                  materialspinboxdifz->setPrefix("Z = ");
                  materialspinboxdifz->setRange(0,255);
                  materialspinboxdifz->setValue(this->_materiaux->get(GL_DIFFUSE)[3]*255);
                  connect(materialspinboxdifz, SIGNAL(valueChanged(int)),this, SLOT(difmaterialfuncz(int)));

                  //partie layout
                  tabmaterialdiflayout = new QHBoxLayout();
                      tabmaterialdiflayout->addWidget(materialspinboxdifx);
                      tabmaterialdiflayout->addWidget(materialspinboxdify);
                      tabmaterialdiflayout->addWidget(materialspinboxdifz);

                tabmaterialdif->setLayout(tabmaterialdiflayout);

                //widget3
                tabmaterialamb = new QWidget();
                    materialspinboxambx = new QSpinBox(this);
                    materialspinboxambx->setPrefix("X = ");
                    materialspinboxambx->setRange(0,255);
                    materialspinboxambx->setValue(this->_materiaux->get(GL_AMBIENT)[0]*255);
                    connect(materialspinboxambx, SIGNAL(valueChanged(int)),this, SLOT(ambmaterialfuncx(int)));

                    materialspinboxamby = new QSpinBox(this);
                    materialspinboxamby->setPrefix("Y = ");
                    materialspinboxamby->setRange(0,255);
                    materialspinboxamby->setValue(this->_materiaux->get(GL_AMBIENT)[1]*255);
                    connect(materialspinboxamby, SIGNAL(valueChanged(int)),this, SLOT(ambmaterialfuncy(int)));

                    materialspinboxambz = new QSpinBox(this);
                    materialspinboxambz->setPrefix("Z = ");
                    materialspinboxambz->setRange(0,255);
                    materialspinboxambz->setValue(this->_materiaux->get(GL_AMBIENT)[2]*255);
                    connect(materialspinboxambz, SIGNAL(valueChanged(int)),this, SLOT(ambmaterialfuncz(int)));

                    //partie layout
                    tabmaterialamblayout = new QHBoxLayout();
                        tabmaterialamblayout->addWidget(materialspinboxambx);
                        tabmaterialamblayout->addWidget(materialspinboxamby);
                        tabmaterialamblayout->addWidget(materialspinboxambz);

                  tabmaterialamb->setLayout(tabmaterialamblayout);

                  //widget4
                  tabmaterialspe = new QWidget();
                      materialspinboxspex = new QSpinBox(this);
                      materialspinboxspex->setPrefix("X = ");
                      materialspinboxspex->setRange(0,255);
                      materialspinboxspex->setValue(this->_materiaux->get(GL_SPECULAR)[0]*255);
                      connect(materialspinboxspex, SIGNAL(valueChanged(int)),this, SLOT(spematerialfuncx(int)));

                      materialspinboxspey = new QSpinBox(this);
                      materialspinboxspey->setPrefix("Y = ");
                      materialspinboxspey->setRange(0,255);
                      materialspinboxspey->setValue(this->_materiaux->get(GL_SPECULAR)[1]*255);
                      connect(materialspinboxspey, SIGNAL(valueChanged(int)),this, SLOT(spematerialfuncy(int)));

                      materialspinboxspez = new QSpinBox(this);
                      materialspinboxspez->setPrefix("Z = ");
                      materialspinboxspez->setRange(0,255);
                      materialspinboxspez->setValue(this->_materiaux->get(GL_SPECULAR)[2]*255);
                      connect(materialspinboxspez, SIGNAL(valueChanged(int)),this, SLOT(spematerialfuncz(int)));

                      materialspinboxspea = new QSpinBox(this);
                      materialspinboxspea->setPrefix("a = ");
                      materialspinboxspea->setRange(0,255);
                      materialspinboxspea->setValue(this->_materiaux->shininess());
                      connect(materialspinboxspea, SIGNAL(valueChanged(int)),this, SLOT(spematerialtfunca(int)));

                      //partie layout
                      tabmaterialspelayout = new QHBoxLayout();
                          tabmaterialspelayout->addWidget(materialspinboxspex);
                          tabmaterialspelayout->addWidget(materialspinboxspey);
                          tabmaterialspelayout->addWidget(materialspinboxspez);
                          tabmaterialspelayout->addWidget(materialspinboxspea);

                    tabmaterialspe->setLayout(tabmaterialspelayout);

            //assosiation des 4widget au tab
            tabmaterial->addTab(tabmaterialemi , "Emissive");
            tabmaterial->addTab(tabmaterialdif , "Difuse");
            tabmaterial->addTab(tabmaterialamb , "Ambiante");
            tabmaterial->addTab(tabmaterialspe , "Speculaire");

            //fixe de widget et afiche le dockwidget
            this->setWidget(tabmaterial);
            this->show();
            }
/* ************************************ */
//             objet                    //
/* ************************************ */
        void Mondock::traitementobjet()
        {

            indexobjetlSelectionne = selection->currentIndex();
            objetselectioner = dockmodele->data(indexobjetlSelectionne, Qt::DisplayRole);

            //renome le dockwidget
            this->setWindowTitle("Edition :  " + objetselectioner.toString());

            //recuperatin de l'objet dans dans le dockwidget

            QVariant elementgpvariant = dockmodele->data(indexgparent, Qt::DisplayRole);

            Piece * piecetmp = dockscene->getPiece(elementgpvariant.toString());

            this->_objet= piecetmp->getChild(objetselectioner.toString());

            //creation qtabwidget
            tabobjet = new QTabWidget();

            //widget1
            tabobjetpropr = new QWidget();

                //les layout du widget
                layouttabobjetpropr = new QVBoxLayout();
                    layouttabobjetproprlabel= new QHBoxLayout();
                    layouttabobjetproprcombo= new QHBoxLayout();

                //partie combobox
                    //creation du model des materiaux
                    modelmaterial=new QStandardItemModel();

                    int nblignetmp =_itemmaterial->rowCount();

                    for (int i=0 ; i<nblignetmp ;i++)
                           {
                           modelmaterial->insertRow( i,(_itemmaterial->child(i)->clone()) );
                           }

                    //creation du model des parent

                    modelpiece=new QStandardItemModel();

                    nblignetmp =_itempiece->rowCount();

                    for (int i=0 ; i<nblignetmp ;i++)
                           {
                           modelpiece->insertRow( i,(_itempiece->child(i)->clone()));
                           }

                    //creation des combo
                    combomaterial = new QComboBox();
                        combomaterial->setModel( modelmaterial);

                    comboparent= new QComboBox();
                        comboparent->setModel(modelpiece);

                //ligne des label
                labelobjetproprmaterial=new QLabel();
                    labelobjetproprmaterial->setText("Materiaux:");
                labelobjetproprparent=new QLabel();;
                    labelobjetproprparent->setText("Parents:");

                //possitionement+ajout au widget du layout principal
                layouttabobjetproprlabel->addWidget(labelobjetproprmaterial);
                layouttabobjetproprlabel->addWidget(labelobjetproprparent);

                layouttabobjetproprcombo->addWidget(combomaterial);
                layouttabobjetproprcombo->addWidget(comboparent);

                layouttabobjetpropr->addLayout(layouttabobjetproprlabel);
                layouttabobjetpropr->addLayout(layouttabobjetproprcombo);

                tabobjetpropr->setLayout(layouttabobjetpropr);

            //widget2
            tabobjetrotation = new QWidget();

                //spinbox
            vec3 rotationtmp = _objet->rotation();

                boxobjetrotationx = new QDoubleSpinBox();
                    boxobjetrotationx->setPrefix("X = ");
                    boxobjetrotationx->setSuffix("°");
                    boxobjetrotationx->setRange(0,360);
                    boxobjetrotationx->setValue(rotationtmp[3]);
                    connect(boxobjetrotationx, SIGNAL(valueChanged(double)),this, SLOT(rotobjectx(double)));

                boxobjetrotationy = new QDoubleSpinBox();
                    boxobjetrotationy->setPrefix("Y = ");
                    boxobjetrotationy->setSuffix("°");
                    boxobjetrotationy->setRange(0,360);
                    boxobjetrotationy->setValue(rotationtmp[1]);
                    connect(boxobjetrotationy, SIGNAL(valueChanged(double)),this, SLOT(rotobjecty(double)));

                boxobjetrotationz = new QDoubleSpinBox();
                    boxobjetrotationz->setPrefix("Z = ");
                    boxobjetrotationz->setSuffix("°");
                    boxobjetrotationz->setRange(0,360);
                    boxobjetrotationx->setValue(rotationtmp[0]);
                    connect(boxobjetrotationz, SIGNAL(valueChanged(double)),this, SLOT(rotobjectz(double)));

                //layout + layout au  widget
                    layouttabobjetrotation =new QHBoxLayout();
                        layouttabobjetrotation->addWidget(boxobjetrotationx);
                        layouttabobjetrotation->addWidget(boxobjetrotationy);
                        layouttabobjetrotation->addWidget(boxobjetrotationz);
                tabobjetrotation->setLayout(layouttabobjetrotation);

            //widget3
            tabobjettrans = new QWidget();

            //spinbox
        vec3 transtmp = _objet->position() ;

            boxobjettransx = new QDoubleSpinBox();
                boxobjettransx->setPrefix("X = ");
                boxobjettransx->setRange(-1000,1000);
                boxobjettransx->setValue(transtmp[3]);
                connect(boxobjettransx, SIGNAL(valueChanged(double)),this, SLOT(transobjectx(double)));

            boxobjettransy = new QDoubleSpinBox();
                boxobjettransy->setPrefix("Y = ");
                boxobjettransy->setRange(-1000,1000);
                boxobjettransy->setValue(transtmp[1]);
                connect(boxobjettransy, SIGNAL(valueChanged(double)),this, SLOT(transobjecty(double)));

            boxobjettransz = new QDoubleSpinBox();
                boxobjettransz->setPrefix("Z = ");
                boxobjettransz->setRange(-1000,1000);
                boxobjettransx->setValue(transtmp[0]);
                connect(boxobjettransz, SIGNAL(valueChanged(double)),this, SLOT(transobjectz(double)));

            //layout + layout au  widget
                layouttabobjettrans =new QHBoxLayout();
                    layouttabobjettrans->addWidget(boxobjettransx);
                    layouttabobjettrans->addWidget(boxobjettransy);
                    layouttabobjettrans->addWidget(boxobjettransz);
            tabobjettrans->setLayout(layouttabobjettrans);


            //widget4
            tabobjetscale = new QWidget();


            //assosiation des 4widget au tab
            tabobjet->addTab(tabobjetpropr , "Propriete");
            tabobjet->addTab(tabobjetrotation , "Rotation");
            tabobjet->addTab(tabobjettrans , "Translation");
            tabobjet->addTab(tabobjetscale , "Scale");

            //fixe de widget et afiche le dockwidget
            this->setWidget(tabobjet);
            this->show();
        }
