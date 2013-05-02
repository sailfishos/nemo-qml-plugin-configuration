TARGET = nemoconfiguration
PLUGIN_IMPORT_PATH = org/nemomobile/configuration

TEMPLATE = lib
CONFIG += qt plugin hide_symbols
equals(QT_MAJOR_VERSION, 4): QT += declarative
equals(QT_MAJOR_VERSION, 5): QT += qml
QT -= gui

equals(QT_MAJOR_VERSION, 4): target.path = $$[QT_INSTALL_IMPORTS]/$$PLUGIN_IMPORT_PATH
equals(QT_MAJOR_VERSION, 5): target.path = $$[QT_INSTALL_QML]/$$PLUGIN_IMPORT_PATH
INSTALLS += target

qmldir.files += $$_PRO_FILE_PWD_/qmldir
qmldir.path +=  $$target.path
INSTALLS += qmldir

SOURCES += plugin.cpp \
           configurationvalue.cpp

HEADERS += configurationvalue.h

CONFIG += link_pkgconfig
equals(QT_MAJOR_VERSION, 4): PKGCONFIG += mlite
equals(QT_MAJOR_VERSION, 5): PKGCONFIG += mlite5
