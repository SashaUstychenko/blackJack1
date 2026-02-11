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
            gradient:
                Gradient {
                    GradientStop { position: 0.0; color: "#777c85" }
                    GradientStop { position: 1.0; color: "#4a4d52" }
                }
        }


            Popup {
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
                        }
                    }
                }

                Component.onCompleted: open()
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
        Rectangle
        {
          width: 70
          height: 50
          topLeftRadius: 50
          bottomLeftRadius: 50
          color: "#e6e6e6"
          opacity: 0.7
          anchors.right: parent.right
          anchors.bottom: parent.bottom
          anchors.bottomMargin: 65

          Rectangle
          {
            width: 40
            height: 40
            radius: width / 2
            clip: true
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left;
            anchors.leftMargin: 5
            Image {
                anchors.fill: parent
                source: "qrc:/icon/home.png"
                fillMode: Image.PreserveAspectCrop
                }
            }
        }
        HandView
        {
            id: playerHand

            anchors.bottom: parent.bottom
            anchors.bottomMargin: 40
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
            width: 80
            height: 80
            radius: width/2
            color: "#49b8b8"
            border.color: "black"
            border.width: 5
            Text
            {
                id: hitTxt
                text: qsTr("HIT")
                font.bold: true
                font.pixelSize: 20
                color: "#fafcfc"
                anchors.centerIn: parent
            }


        }


    }
}

