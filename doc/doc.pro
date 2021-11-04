TEMPLATE=aux

CONFIG += sailfish-qdoc-template
SAILFISH_QDOC.project = nemo-qml-plugin-configuration
SAILFISH_QDOC.config = nemo-qml-plugin-configuration.qdocconf
SAILFISH_QDOC.style = offline
SAILFISH_QDOC.path = /usr/share/doc/nemo-qml-plugin-configuration

OTHER_FILES = \
    src/index.qdoc
