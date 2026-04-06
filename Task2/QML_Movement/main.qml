import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.5

Window {
    id: root
    width: 300
    height: 600
    visible: true
    title: "Game"

    Timer {
        id: spawnTimer
        interval: Math.floor(Math.random() * (1000 - 100 + 1) + 100)
        repeat: true
        running: true
        onTriggered: {
            var btn = buttonComponent.createObject(root)
            btn.x = Math.random() * root.width
            btn.y = Math.random() * 100
            interval = Math.floor(Math.random() * (1000 - 100 + 1) + 100)
        }
    }

    Timer {
        id: animTimer
        interval: 60
        repeat: true
        running: true
        onTriggered: {
            for(let i = 0; i < contentItem.children.length; i++) {
                var btn = contentItem.children[i]
                if(btn.hasOwnProperty("isGameButton")) {
                    btn.y += btn.hovered ? btn.velocity * 1.5 : btn.velocity
                    if(btn.y + btn.height > root.height) {
                        root.color = "red"
                        root.title = qsTr("You LOOSE!")
                        btn.destroy()
                    }
                }
            }
        }
    }

    Component {
        id: buttonComponent
        Button {
            property int velocity: Math.floor(Math.random() * (8 - 2 + 1) + 2)
            property bool isGameButton: true
            text: "*"
            width: 20
            height: 20
            onClicked: destroy()
        }
    }
}
