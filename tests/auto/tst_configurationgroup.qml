import QtTest 1.0
import QtQuick 2.0
import org.nemomobile.configuration 1.0

Item {
    ConfigurationGroup {
        id: settings1

        path: "/opt/tests/org/nemomobile/configuration/group"

        ConfigurationGroup {
            id: child1

            path: "child1"

            property int integerProperty: 4
            property real realProperty: 12.5
            property bool booleanProperty: false
            property string stringProperty: "default"
            property variant stringListProperty: [ "one", "two", "three" ]
            property variant integerListProperty: [ 1, 2, 3 ]
        }
    }

    ConfigurationGroup {
        id: settings2

        path: settings1.path

        ConfigurationGroup {
            id: child2

            path: "child2"

            property int integerProperty
            property real realProperty
            property bool booleanProperty: true
            property string stringProperty
            property variant stringListProperty
            property variant integerListProperty
        }

    }

    resources: TestCase {
        name: "ConfigurationGroup"

        function initTestCase() {
            child2.integerProperty = 4
            child2.realProperty = 12.5
            child2.booleanProperty = false
            child2.stringProperty = "default"
            child2.stringListProperty = [ "one", "two", "three" ]
            child2.integerListProperty = [ 1, 2, 3 ]
        }

        function cleanup() {
            child1.path = "child1"
            child2.path = "child2"
        }

        function cleanupTestCase() {
            settings1.clear()
        }

        function test_groupProperties_data() {
            return [
                { tag: "integer", property: "integerProperty", value1: 64, value2: 4 },
                { tag: "real", property: "realProperty", value1: 0.5, value2: 12.5 },
                { tag: "boolean", property: "booleanProperty", value1: true, value2: false },
                { tag: "string", property: "stringProperty", value1: "changed", value2: "default" },
                { tag: "list<string>", property: "stringListProperty",
                  value1: [ "a", "B", "c", "d" ], value2: [ "one", "two", "three" ] },
                { tag: "list<integer>", property: "integerListProperty",
                  value1: [ 8, 7, 5 ], value2: [ 1, 2, 3 ] }
            ]
        }

        function test_groupProperties(data) {
            child1[data.property] = data.value1

            tryCompare(child1, data.property, data.value1)
            tryCompare(child2, data.property, data.value2)

            child2.path = "child1"
            tryCompare(child2, data.property, data.value1)

            child1[data.property] = data.value2
            tryCompare(child2, data.property, data.value2)
        }
    }
}
