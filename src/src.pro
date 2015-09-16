TARGET = nemoconfiguration
PLUGIN_IMPORT_PATH = org/nemomobile/configuration

TEMPLATE = lib
CONFIG = qt plugin hide_symbols
QT = core qml

target.path = $$[QT_INSTALL_QML]/$$PLUGIN_IMPORT_PATH
INSTALLS += target

qmldir.files += \
        $$_PRO_FILE_PWD_/qmldir \
        $$_PRO_FILE_PWD_/plugins.qmltypes
qmldir.path +=  $$target.path
INSTALLS += qmldir

SOURCES += plugin.cpp \
           configurationgroup.cpp \
           configurationvalue.cpp

HEADERS += configurationgroup.h \
           configurationvalue.h


CONFIG += link_pkgconfig
PKGCONFIG += mlite5

