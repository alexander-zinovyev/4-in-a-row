import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2

Item {
    id: menuScene
    anchors.fill: parent

    states: [
        State {
            name: "hidden"
            PropertyChanges {
                target: menuScene
                visible: false
            }
        },
        State {
            name: "shown"
            PropertyChanges {
                target: menuScene
                visible: true
            }
        }

    ]

    Text {
        id: gameName
        text: qsTr("Four in a row")
        font.pointSize: 16
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 20
    }

    Button {
        id: startGame
        text: qsTr("Start game")
        style: MenuButtonStyle { }
        anchors.right: parent.horizontalCenter
        anchors.rightMargin: 5
        anchors.verticalCenter: parent.verticalCenter

        onClicked: {
            game.newGame()
            menuScene.state = "hidden"
            gameScene.state = "shown"
        }
    }

    Button {
        id: quitGame
        text: qsTr("Quit")
        style: MenuButtonStyle { }
        anchors.left: startGame.right
        anchors.leftMargin: 5
        anchors.verticalCenter: parent.verticalCenter

        onClicked: Qt.quit()
    }
}
