#-------------------------------------------------
#
# Project created by QtCreator 2013-10-20T14:59:57
#
#-------------------------------------------------

QT       += core gui xmlpatterns xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Tinu
TEMPLATE = app

CONFIG += c++11

LIBS += /usr/lib/libobjc.A.dylib

SOURCES += main.cpp\
        maindlg.cpp \
    localappscanner.cpp \
    xmlparser.cpp \
    tabentry.cpp \
    md5.cpp \
    titlebar.cpp \
    myqapplication.cpp \
    msgdlg.cpp \
    downloadqueuehandler.cpp \
    downloadfilehandler.cpp \
    filetools.cpp \
    stringdictionnary.cpp \
    catalog.cpp \
    stemedtooltip.cpp \
    scrolltext.cpp

HEADERS  += maindlg.h \
    localappscanner.h \
    xmlparser.h \
    unzip.h \
    md5.h \
    titlebar.h \
    myqapplication.h \
    msgdlg.h \
    downloadqueuehandler.h \
    downloadfilehandler.h \
    softwareentry.h \
    filetools.h \
    stringdictionnary.h \
    catalog.h \
    tabentry.h \
    stemedtooltip.h \
    scrolltext.h

FORMS    += maindlg.ui \
    tabentry.ui \
    titlebar.ui \
    msgdlg.ui \
    stemedtooltip.ui

RESOURCES += \
    rsc.qrc

#QMAKE_INFO_PLIST = MyInfo.plist

OTHER_FILES += \
    MyInfo.plist

ICON = rsc/appicon.icns


