#-------------------------------------------------
#
# Project created by QtCreator 2014-03-11T23:52:09
#
#-------------------------------------------------

QT       += core
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ssbm
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    settings.cpp \
    sqlman/sqlman.cpp \
    datamanager/datamanager.cpp \
    logApi/logapi.cpp

HEADERS  += widget.h \
    datamanager/datamanager.h \
    settings.h \
    sqlman/sqlman.h \
    app_info.h \
    logApi/logapi.h

FORMS    += widget.ui

RESOURCES += res.qrc
RC_FILE = res.rc

TRANSLATIONS = translations\ssbm_de.ts \
               translations\ssbm_de.ts \
               translations\ssbm_ru.ts \
               translations\ssbm_nl.ts \

OTHER_FILES += \
    readme.md


