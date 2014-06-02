######################################################################
# Automatically generated by qmake (3.0) lun. avr. 14 16:02:11 2014
######################################################################

TEMPLATE = app
TARGET = castle
INCLUDEPATH += . scene/ objets/ gui/
QT += opengl xml gui concurrent
CONFIG += c++11 
QMAKE_CXXFLAGS += -g
OBJECTS_DIR = build
MOC_DIR = build


#QMAKE_CXXFLAGS += -DDEBUG

macx
{
  LIBS += -L/usr/local/lib
  INCLUDEPATH += /usr/local/include/
}

LIBS += -lassimp


# Input
HEADERS += camera.hpp \
           helper.hpp \
           gui/mainwindows.hpp \
           gui/mondock.hpp \
           gui/MyOpenGLWidget.hpp \
           objets/mesh.hpp \
           objets/node.hpp \
           objets/plan.hpp \
           objets/objet.hpp \
           scene/light.hpp \
           scene/material.hpp \
           scene/piece.hpp \
           scene/scene.hpp 


           
SOURCES += camera.cpp \
           helper.cpp \
           gui/mainwindows.cpp \
           gui/mondock.cpp \
           gui/MyOpenGLWidget.cpp \
           objets/mesh.cpp \
           objets/node.cpp \
           objets/objet.cpp \
           objets/plan.cpp \
           scene/light.cpp \
           scene/material.cpp \
           scene/piece.cpp \
           scene/scene.cpp \
           main.cpp 

