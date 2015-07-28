TEMPLATE = subdirs
SUBDIRS = src tests

CONFIG += mer-qdoc-template
MER_QDOC.project = nemo-qml-plugin-configuration
MER_QDOC.config = doc/nemo-qml-plugin-configuration.qdocconf
MER_QDOC.style = offline
MER_QDOC.path = /usr/share/doc/nemo-qml-plugin-configuration

OTHER_FILES = \
    rpm/nemo-qml-plugin-configuration-qt5.spec \
    doc/src/index.qdoc
