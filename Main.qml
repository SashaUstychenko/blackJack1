import QtQuick
import QtQuick.Controls

ApplicationWindow {
    width: 900
    height: 600
    visible: true
    title: qsTr("Blackjack Game")


    StackView
    {
        id: stack
        anchors.fill: parent
        initialItem: GameView{}
    }


}
