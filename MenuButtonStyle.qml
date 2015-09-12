import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2

ButtonStyle {
    background: Rectangle {
        implicitWidth: 200
        implicitHeight: 50
        border.width: control.activeFocus ? 2 : 1
        border.color: "#888"
        radius: 10
        gradient: Gradient {
            GradientStop { position: 0 ; color: control.pressed ? "#ccc" : "#eee" }
            GradientStop { position: 1 ; color: control.pressed ? "#aaa" : "#ccc" }
        }
    }
}
