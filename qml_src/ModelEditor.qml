import QtCore
import QtQuick
import QtQuick3D
import QtQuick.Controls
import QtQuick.Dialogs

Rectangle {
    id: modelEditor
    anchors.left: parent.left
    width: parent.width * 0.3
    height: parent.height
    color: "black"

    Button {
        icon.name: "folder-open"
        text: "Choose OBJ file"
        anchors.centerIn: parent
        width: parent.width * 0.8
        height: 60
        font.pixelSize: 20
        onClicked: fileDialog.open()
    }

    FileDialog {
        id: fileDialog
        title: "Open Obj"
        selectedNameFilter.index: 1
        nameFilters: ["OBJ files (*.obj)"]
        currentFolder: StandardPaths.standardLocations(StandardPaths.DownloadLocation)[0]
        fileMode: FileDialog.OpenFile
        onAccepted: {
            ModelManager.loadModel(selectedFile)
        }
    }
}