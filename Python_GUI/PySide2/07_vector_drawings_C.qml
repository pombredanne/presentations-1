import QtQuick 2.0

Rectangle {
    id: main
    width: 320
    height: 240
    color: "lightgray"

    Image {
        id: left_image
        source: "editors/vim.svg"
        fillMode: Image.PreserveAspectFit
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.right: center_image.left
    }

    Image {
        id: center_image
        source: "editors/emacs.svg"
        width: 100
        height: 100
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
    }

    Image {
        id: right_image
        source: "editors/atom.svg"
        fillMode: Image.PreserveAspectFit
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.left: center_image.right
    }
}
