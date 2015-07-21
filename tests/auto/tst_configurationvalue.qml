import QtTest 1.0
import QtQuick 2.0
import org.nemomobile.configuration 1.0

Item {
    ConfigurationValue {
        id: setting1

        key: "/opt/tests/org/nemomobile/configuration/value"
    }

    ConfigurationValue {
        id: setting2

        key: setting1.key
        defaultValue: "DEFAULT"
    }

    SignalSpy {
        id: setting1Spy

        target: setting1
        signalName: "valueChanged"
    }

    SignalSpy {
        id: setting2Spy

        target: setting2
        signalName: "valueChanged"
    }

    resources: TestCase {
        name: "ConfigurationValue"

        function initTestCase() {
            setting1.value = undefined
        }

        function cleanupTestCase() {
            setting1.value = undefined
        }

        function init() {
            setting1Spy.clear()
            setting2Spy.clear()
        }

        function test_defaultValue() {
            verify(setting1.value === undefined)
            compare(setting2.value, setting2.defaultValue)

            setting1.value = "VALUE"
            compare(setting1Spy.count, 1)
            tryCompare(setting2Spy, "count", 1)

            compare(setting1.value, "VALUE")
            compare(setting1.value, "VALUE")
            verify(setting2.value !== setting2.defaultValue)

            setting1.value = undefined
            compare(setting1Spy.count, 2)
            tryCompare(setting2Spy, "count", 2)

            verify(setting1.value === undefined)
            compare(setting2.value, setting2.defaultValue)
        }

        function test_valueTypes_data() {
            return [
                { tag: "double", value: 3.14, string: "3.14" },
                { tag: "integer", value: 2, string: "2" },
                { tag: "boolean", value: true, string: "1" },
                { tag: "string", value: "text" },
                { tag: "list<string>", value: [ "text1", "text2" ] },
                { tag: "list<variant>", value: [ 1, 2, 3 ] }
            ]
        }

        function test_valueTypes(data) {
            setting1.value = data.value
            tryCompare(setting2Spy, "count", 1)

            if (typeof setting2.value === "object") {
                compare(setting2.value.length, data.value.length)
                for (var i = 0; i < setting2.value.length; ++i)
                    compare(setting2.value[i], data.value[i])
            } else {
                verify(setting2.value === data.value)
                if (data.string) {
                    verify(setting2.value !== data.string)
                    verify(setting2.value == data.string)
                }
            }
        }
    }
}

