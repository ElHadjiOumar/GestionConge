QT       += core gui

QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    adminui.cpp \
    authentification.cpp \
    conge.cpp \
    congemodel.cpp \
    dbaccess.cpp \
    drhui.cpp \
    employeui.cpp \
    flowcontroller.cpp \
    main.cpp \
    managerui.cpp \
    profilui.cpp \
    user.cpp \
    usermodel.cpp

HEADERS += \
    adminui.h \
    authentification.h \
    conge.h \
    congemodel.h \
    dbaccess.h \
    drhui.h \
    employeui.h \
    flowcontroller.h \
    managerui.h \
    profilui.h \
    user.h \
    usermodel.h

FORMS += \
    adminui.ui \
    authentification.ui \
    drhui.ui \
    employeui.ui \
    managerui.ui \
    profilui.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
