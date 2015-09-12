import QtQuick 2.0
import QtQuick.Layouts 1.1

Item {
    id: gameScene
    anchors.fill: parent

    states: [
        State {
            name: "hidden"
            PropertyChanges {
                target: gameScene
                visible: false
            }
        },
        State {
            name: "shown"
            PropertyChanges {
                target: gameScene
                visible: true
            }
        }

    ]

    RowLayout {
        id: rowLayout
        anchors.fill: parent
        spacing: 0

        Rectangle {
            Layout.fillHeight: true
            Layout.fillWidth: true

            gradient: Gradient {
                GradientStop { position: 0; color: "#ccc" }
                GradientStop { position: 1; color: "#aaa" }
            }

            Grid {
                id: coinsGrid
                columns: 7

                spacing: 10

                anchors.centerIn: parent
                Repeater {
                    model: game.coins
                    Coin { }
                }
            }
        }

        // Panel
        Rectangle {
            color: "black"
            opacity: 0.5

            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.minimumWidth: parent.width / 4
            Layout.maximumWidth: parent.width / 4

            Rectangle {
                id: colorTurn
                color: game.firstPlayerTurn ? "yellow" : "red"

                width: parent.width; height: 25
                anchors.top: parent.top
            }

            Text {
                id: textTurn
                text: qsTr("Player " + (game.firstPlayerTurn ? "1" : "2") + " Turn");
                font.pointSize: 12
                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
    }
}
