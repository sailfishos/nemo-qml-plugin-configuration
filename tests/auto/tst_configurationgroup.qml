import QtTest 1.0
import QtQuick 2.0
import org.nemomobile.configuration 1.0

Item {
    width: 500; height: 500

    ConfigurationGroup {
        id: settings1

        path: "/opt/tests/org/nemomobile/gconf"

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

        path: "/opt/tests/org/nemomobile/gconf"

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

        function test_integerProperty() {
            child1.integerProperty = 65
            compare(child1.integerProperty, 65)
            compare(child2.integerProperty, 4)

            child2.path = "child1"
            compare(child2.integerProperty, 65)

            child1.integerProperty = 4
            tryCompare(child2, "integerProperty", 4)
        }

        function test_realProperty() {
            child1.realProperty = 0.5
            compare(child1.realProperty, 0.5)
            compare(child2.realProperty, 12.5)

            child2.path = "child1"
            compare(child2.realProperty, 0.5)

            child1.realProperty = 12.5
            tryCompare(child2, "realProperty", 12.5)
        }

        function test_booleanProperty() {
            child1.booleanProperty = true
            compare(child1.booleanProperty, true)
            compare(child2.booleanProperty, false)

            child2.path = "child1"
            compare(child2.booleanProperty, true)

            child1.booleanProperty = false
            tryCompare(child2, "booleanProperty", false)
        }

        function test_stringProperty() {
            child1.stringProperty = "changed"
            compare(child1.stringProperty, "changed")
            compare(child2.stringProperty, "default")

            child2.path = "child1"
            compare(child2.stringProperty, "changed")

            child1.stringProperty = "default"
            tryCompare(child2, "stringProperty", "default")
        }

        function test_stringListProperty() {
            child1.stringListProperty = [ "a", "B", "c", "d" ]
            compare(child1.stringListProperty, [ "a", "B", "c", "d" ])
            compare(child2.stringListProperty, [ "one", "two", "three" ])

            child2.path = "child1"
            compare(child2.stringListProperty, [ "a", "B", "c", "d" ])

            child1.stringListProperty = [ "one", "two", "three" ]
            tryCompare(child2, "stringListProperty", [ "one", "two", "three" ])
        }

        function test_integerListProperty() {
            child1.integerListProperty = [ 8, 7, 5 ]
            compare(child1.integerListProperty, [ 8, 7, 5 ])
            compare(child2.integerListProperty, [ 1, 2, 3 ])

            child2.path = "child1"
            compare(child2.integerListProperty, [ 8, 7, 5 ])

            child1.integerListProperty = [ 1, 2, 3 ]
            tryCompare(child2, "integerListProperty", [ 1, 2, 3 ])
        }
    }
}
