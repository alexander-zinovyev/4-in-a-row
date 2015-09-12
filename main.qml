import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.2
import TestTask 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Four in a row")

    GameScene {
        id: gameScene
        state: "hidden"
    }

    MenuScene {
        id: menuScene
        state: "shown"
    }

    //end game dialog
    Dialog {
        id: endGameDialog
        title: "Game ended"

        standardButtons: StandardButton.Ok

        Text {
            id: endGameText
            color: "navy"
            anchors.centerIn: parent
        }

        onAccepted: {
            gameScene.state = "hidden"
            menuScene.state = "shown"
        }
    }

    Connections {
        target: game
        onGameEnded: {
            if (winner == Coin.None)
                endGameText.text = qsTr("No one won. Draw!")
            else
                endGameText.text = qsTr("Player " + ((winner == Coin.FirstPlayer) ? "1" : "2") + " won!")
            endGameDialog.open()
        }
    }
}
