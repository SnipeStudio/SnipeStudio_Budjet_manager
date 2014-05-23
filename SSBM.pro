#-------------------------------------------------
#
# Project created by QtCreator 2014-03-11T23:52:09
#
#-------------------------------------------------

QT       += core

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ssbm
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    settings.cpp

HEADERS  += widget.h \
    datamanager/datamanager.h \
    settings.h

FORMS    += widget.ui

RESOURCES += icons.qrc
RC_FILE = icon.rc

TRANSLATIONS = spreadsheet_de.ts \
               spreadsheet_en.ts \
               spreadsheet_ru.ts
