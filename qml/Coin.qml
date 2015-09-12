import TestTask 1.0
import QtQuick 2.0

Rectangle {
    id: circle
    width: 50; height: 50
    color: modelData.owner == Coin.None ? "white" : (modelData.owner == Coin.FirstPlayer ? "yellow" : "red")

    radius: 25
    border.width: 1
    border.color: "#777"

    MouseArea {
        anchors.fill: parent
        enabled: !modelData.hasOwner
        onClicked: {
            game.drop(index)
        }
    }
}
