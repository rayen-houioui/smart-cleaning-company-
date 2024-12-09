#-------------------------------------------------
#
# Project created by QtCreator 2018-10-26T21:45:23
#
#-------------------------------------------------

QT += core gui sql
QT += widgets sql printsupport
QT += core gui network
QT += charts
QT += core gui serialport
QT += serialport
QT += multimedia
QT += core gui
QT += multimedia charts
QT += core gui charts
QT += core gui widgets printsupport





greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gestionCommandes
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    arduino.cpp \
    commande.cpp \
    main.cpp \
    mainwindow.cpp \
    connection.cpp \
    produit.cpp \
    client.cpp \
    service.cpp \
    e_mail.cpp \
    employe.cpp \
    facture.cpp \
    historique.cpp\
    maintenance.cpp

HEADERS += \
    arduino.h \
    commande.h \
    mainwindow.h \
    connection.h \
    produit.h \
    client.h \
    service.h \
    e_mail.h \
    employe.h \
    facture.h \
    historique.h\
    maintenance.h

FORMS += \
    commande.ui



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
