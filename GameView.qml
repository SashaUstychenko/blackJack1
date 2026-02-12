import QtQuick
import QtQuick.Controls
import blackJack 1.0

Rectangle
{
    width: 900
    height: 600

    ControlerBlackJack
    {
        id: controller
    }

    Image
    {
        id: table
        width: parent.width
        height: parent.height
        source: "qrc:/image/table.jpg"
        Rectangle
        {
            width: parent.width
            height: 90
            anchors.bottom: parent.bottom
            gradient: Gradient 
                      {
                         GradientStop { position: 0.0; color: "#777c85" }
                         GradientStop { position: 1.0; color: "#4a4d52" }
                      }

            Row
            {
                spacing: 15
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 40


            Text
            {
                id: cashT
                text: "Cach $"+controller.playerMoney
                font.bold: true;
                font.pixelSize: 30
                color: "#f5f7f5"
            }

            Text
            {
                id: betT
                text: "Bet $"+controller.playerBet
                font.bold: true;
                font.pixelSize: 30
                color: "#f5f7f5"
            }
            }
        }
            //menu bet

            Popup
            {
                id: betPopup
                modal: true
                focus: true
                dim: true
                closePolicy: Popup.NoAutoClose
                x: parent.width / 2 - width / 2
                y: parent.height / 2 - height / 2
                width: 400
                height: 120
                background: Rectangle {
                        color: "#000000"
                        opacity: 0.45
                        radius: 12
                    }


                Rectangle {
                    anchors.fill: parent
                    color: "#208a84"
                    radius: 12

                    Column {
                        anchors.centerIn: parent
                        spacing: 15

                        Text {
                            text: "Choose your bet"
                            color: "#145c58"
                            font.bold: true
                            font.pixelSize: 20

                            anchors.horizontalCenter: parent.horizontalCenter
                        }

                        Row {
                            anchors.horizontalCenter: parent.horizontalCenter
                            spacing: 15
                            Repeater {
                                model: [25, 50, 100, 200]

                                Rectangle
                                {
                                    id: btnBet
                                    width: 50
                                    height: 50
                                    radius: width/2
                                    Text {
                                        id: textBet
                                        text: "$" + modelData
                                        font.bold: true
                                        anchors.centerIn: parent
                                        color: "#2db5ae"
                                    }
                                    MouseArea
                                    {
                                        anchors.fill: parent
                                        onClicked:
                                        {
                                            controller.placeBet(modelData)

                                            betPopup.close()

                                        }
                                        cursorShape: Qt.PointingHandCursor
                                    }
                                }

                            }
                            Rectangle {
                                id:btnPerfect
                                width: 120
                                height: 44
                                radius: 22

                                color: controller.canPlacePerfectPairBet() ? "#8e44ad" : "#555"
                                opacity: controller.canPlacePerfectPairBet() ? 1 : 0.4

                                Text {
                                    anchors.centerIn: parent
                                    text: "PERFECT PAIR"
                                    color: "white"
                                    font.bold: true
                                }

                                MouseArea {
                                    anchors.fill: parent
                                    enabled: controller.canPlacePerfectPairBet()
                                    cursorShape: Qt.PointingHandCursor
                                    onClicked: perfectPairPopup.open()
                                }
                            }
                        }
                    }
                }

                Component.onCompleted: open()
            }
            //menu result
            Popup {
                id: resultPopup
                modal: true
                focus: true
                dim: true
                closePolicy: Popup.NoAutoClose

                width: 360
                height: 220

                x: parent.width / 2 - width / 2
                y: parent.height / 2 - height / 2

                background: Rectangle {
                    color: "#000000"
                    opacity: 0.5
                    radius: 12
                }

                Rectangle {
                    anchors.fill: parent
                    radius: 16
                    color: "#208a84"

                    Column {
                        anchors.centerIn: parent
                        spacing: 24

                        Text {
                            text: {
                                switch (controller.roundResult) {
                                case ControlerBlackJack.PlayerWin:   return "YOU WIN"
                                case ControlerBlackJack.DealerWin:   return "DEALER WINS"
                                case ControlerBlackJack.PlayerBust:  return "BUST!"
                                case ControlerBlackJack.DealerBust:  return "DEALER BUST"
                                case ControlerBlackJack.BlackJack:   return "BLACKJACK!"
                                case ControlerBlackJack.Push:        return "PUSH"
                                default: return ""
                                }
                            }
                            font.pixelSize: 36
                            font.bold: true
                            color: "white"
                            horizontalAlignment: Text.AlignHCenter
                        }

                        Rectangle {
                            width: 180
                            height: 56
                            radius: 28
                            color: "#49b8b8"

                            Text {
                                text: "NEXT ROUND"
                                anchors.centerIn: parent
                                font.bold: true
                                color: "white"
                            }

                            MouseArea
                            {
                                anchors.fill: parent
                                cursorShape: Qt.PointingHandCursor
                                onClicked: {
                                    resultPopup.close()
                                    controller.newRound()
                                    betPopup.open()
                                }
                            }
                        }
                    }
                }
            }
            Connections {
                target: controller
                function onRoundResultChanged() {
                    if (controller.roundResult !== ControlerBlackJack.None) {
                        resultPopup.open()
                    }
                }
            }


        Rectangle
        {
          width: 70
          height: 50
          topRightRadius: 50
          bottomRightRadius: 50
          color: "#e6e6e6"
          opacity: 0.7
          anchors.left: parent.left
          anchors.bottom: parent.bottom
          anchors.bottomMargin: 65

          Rectangle
          {
            width: 40
            height: 40
            radius: width / 2
            clip: true
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right;
            anchors.rightMargin: 5
            Image {
                anchors.fill: parent
                source: "qrc:/icon/menu.png"
                fillMode: Image.PreserveAspectCrop
                }
            }
        }

        Popup {
            id: perfectPairPopup
            modal: true
            focus: true
            dim: true
            closePolicy: Popup.CloseOnPressOutside

            width: 360
            height: 140

            x: parent.width / 2 - width / 2
            y: parent.height / 2 - height / 2

            Rectangle {
                anchors.fill: parent
                radius: 14
                color: "#5e3370"

                Column {
                    anchors.centerIn: parent
                    spacing: 16

                    Text {
                        text: "Perfect Pair Bet"
                        font.pixelSize: 20
                        font.bold: true
                        color: "white"
                    }
                    Row {
                        spacing: 14
                        anchors.horizontalCenter: parent.horizontalCenter

                        Repeater {
                            model: [5, 10, 25, 50]

                            Rectangle {
                                width: 48
                                height: 48
                                radius: 24
                                color: "#9b59b6"

                                Text {
                                    anchors.centerIn: parent
                                    text: "$" + modelData
                                    font.bold: true
                                    color: "white"
                                }

                                MouseArea {
                                    anchors.fill: parent
                                    cursorShape: Qt.PointingHandCursor
                                    enabled: controller.perfectPairEnabled
                                    onClicked: {
                                        controller.placePerfectPairBet(modelData)
                                        perfectPairPopup.close()
                                    }
                                }

                            }
                        }
                    }
                }
            }
        }

        HandView
        {
            id: playerHand

            anchors.bottom: parent.bottom
            anchors.bottomMargin: 100
            anchors.horizontalCenter: parent.horizontalCenter

            cardCount: controller.playerCardCount
            cardSource: function(index) { return controller.playerCardImage(index) }
            deckAnchor: deckAnchor

        }
        HandView
        {
            id: dealerHand

            anchors.top: parent.top
            anchors.topMargin: 40
            anchors.horizontalCenter: parent.horizontalCenter

            cardCount: controller.dealerCardCount
            cardSource: function(index) { return controller.dealerCardImage(index) }
            deckAnchor: deckAnchor
        }
        Rectangle
        {
            id: deckAnchor
            width: 100
            height: 150
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.topMargin: 40
            anchors.rightMargin: 40
            clip: true
            radius: 10

            Image
            {
                id: name
                anchors.fill: parent
                fillMode: Image.PreserveAspectCrop
                source: "qrc:/image/back_black.png"
            }
        }

        Rectangle
        {
            id: btnHit
            width: 80
            height: 80
            radius: width/2
            color: "#49b8b8"
            border.color: "black"
            border.width: 5
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.rightMargin: 20
            anchors.bottomMargin: 120
            Text
            {
                id: hitTxt
                text: qsTr("HIT")
                font.bold: true
                font.pixelSize: 20
                color: "#fafcfc"
                anchors.centerIn: parent
            }

            MouseArea
            {
                anchors.fill: parent
                onClicked:
                {
                    controller.playerHit()
                }
            }

        }
        Rectangle
        {
            id: btnStand
            width: 80
            height: 80
            radius: width/2
            color: "#49b8b8"
            border.color: "black"
            border.width: 5
            anchors.right: parent.right
            anchors.bottom: btnHit.top
            anchors.rightMargin: 20
            anchors.bottomMargin: 10
            Text
            {
                id: standTxt
                text: qsTr("STAND")
                font.bold: true
                font.pixelSize: 20
                color: "#fafcfc"
                anchors.centerIn: parent
            }

            MouseArea
            {
                anchors.fill: parent
                onClicked:
                {
                    controller.playerStand()
                }
            }

        }
        Rectangle
        {
            id: doubleDownButton
            width: 80
            height: 80
            radius: width/2
            color: "#49b8b8"
            border.color: "black"
            border.width: 5
            anchors.right: parent.right
            anchors.bottom: btnStand.top
            anchors.rightMargin: 20
            anchors.bottomMargin: 10
            Text
            {
                text: qsTr("Double\nDown")
                font.bold: true
                font.pixelSize: 15
                color: "#fafcfc"
                anchors.centerIn: parent
            }

            MouseArea
            {
                anchors.fill: parent
                enabled: controller.canDoubleDown()   // автоматично включається/виключається
                onClicked: {
                    controller.doubleDown()           // подвоюємо ставку і одразу додаємо карту
                }
            }

        }




    }
}

