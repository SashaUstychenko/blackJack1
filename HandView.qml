import QtQuick

Item {
    id: root

    property int cardCount: 0
    property var cardSource
    property int overlap: 30
    property Item deckAnchor

    width: cardCount * overlap + 100
    height: 150

    Repeater {
        model: root.cardCount



        Image {
            width: 100
            height: 150
            source: cardSource(index)
            z: index

            readonly property real targetX: index * root.overlap
            readonly property real targetY: 0

            x: appeared || !root.deckAnchor
               ? targetX
               : mapFromItem(root.deckAnchor, 0, 0).x

            y: appeared || !root.deckAnchor
               ? targetY
               : mapFromItem(root.deckAnchor, 0, 0).y

            opacity: appeared ? 1 : 0

            Behavior on x {
                NumberAnimation { duration: 400; easing.type: Easing.OutCubic }
            }
            Behavior on y {
                NumberAnimation { duration: 400; easing.type: Easing.OutCubic }
            }
            Behavior on opacity {
                NumberAnimation { duration: 200 }
            }

            property bool appeared: false
            Component.onCompleted: Qt.callLater(() => appeared = true)
        }
    }
}
