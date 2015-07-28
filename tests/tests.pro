TEMPLATE = aux

target.files = \
    auto/tst_configurationgroup.qml \
    auto/tst_configurationvalue.qml
target.path = /opt/tests/nemo-qml-plugins/configuration/auto

definition.files = tests.xml
definition.path = /opt/tests/nemo-qml-plugins/configuration/test-definition

INSTALLS += target definition
