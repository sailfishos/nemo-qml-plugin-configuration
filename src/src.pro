TARGET = nemoconfiguration
PLUGIN_IMPORT_PATH = Nemo/Configuration

TEMPLATE = lib
CONFIG = qt plugin hide_symbols
QT = core qml

target.path = $$[QT_INSTALL_QML]/$$PLUGIN_IMPORT_PATH
INSTALLS += target

qmldir.files += \
        qmldir \
        plugins.qmltypes
qmldir.path +=  $$target.path
INSTALLS += qmldir

qmltypes.commands = qmlplugindump -nonrelocatable Nemo.Configuration 1.0 > $$PWD/plugins.qmltypes
QMAKE_EXTRA_TARGETS += qmltypes

SOURCES += plugin.cpp \
           configurationgroup.cpp \
           configurationvalue.cpp

HEADERS += configurationgroup.h \
           configurationvalue.h

CONFIG += link_pkgconfig
PKGCONFIG += mlite5
