QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

QMAKE_LFLAGS +=  -fopenmp
QMAKE_CXXFLAGS+=  -fopenmp

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Ball.cpp \
    HitRecord.cpp \
    LightSource.cpp \
    Materia.cpp \
    Ray.cpp \
    Scene.cpp \
    Surface.cpp \
    camera.cpp \
    main.cpp \
    mainwindow.cpp \
    point3.cpp \
    vec3.cpp

HEADERS += \
    Ball.h \
    Camera.h \
    HitRecord.h \
    LightSource.h \
    Materia.h \
    Ray.h \
    Scene.h \
    Surface.h \
    mainwindow.h \
    point3.h \
    vec3.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
