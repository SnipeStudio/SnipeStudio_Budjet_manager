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
    sqlman/sqlman.cpp \
    datamanager/datamanager.cpp \
    settings/settings.cpp \
    logger/logger.cpp \
    editentry/editentry.cpp \
    addentry/addentry.cpp \
    export/export.cpp \
    import/import.cpp \
    commandline/commandline.cpp

HEADERS  += widget.h \
    datamanager/datamanager.h \
    sqlman/sqlman.h \
    app_info.h \
    settings/settings.h \
    logger/logger.h \
    editentry/editentry.h \
    addentry/addentry.h \
    export/export.h \
    import/import.h \
    commandline/commandline.h \
    res.rc

FORMS    += widget.ui \
    settings/settings.ui \
    auth/auth.ui \
    editentry/editentry.ui \
    addentry/addentry.ui \
    export/export.ui \
    import/import.ui

RESOURCES += res.qrc
RC_FILE = res.rc
win32: RC_ICONS = ico.ico


TRANSLATIONS = translations/ssbm_de.ts \
               translations/ssbm_en.ts \
               translations/ssbm_ru.ts \
               translations/ssbm_nl.ts \
               translations/ssbm_fr.ts \

OTHER_FILES += \
    readme.md

DISTFILES += \
    ico.ico \
    .gitlab-ci.yml \
    BudgetManager.iss \
    CHANGELOG.md \
    build.sh \
    .build \
    prepareSource.sh



