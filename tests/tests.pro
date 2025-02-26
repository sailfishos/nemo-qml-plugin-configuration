TEMPLATE = aux

target.files = \
    auto/tst_configurationgroup.qml \
    auto/tst_configurationvalue.qml
target.path = /opt/tests/nemo-qml-plugin-configuration-qt5/auto

definition.files = tests.xml
definition.path = /opt/tests/nemo-qml-plugin-configuration-qt5/test-definition

INSTALLS += target definition
