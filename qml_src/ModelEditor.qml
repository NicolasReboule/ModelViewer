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
        text: "Choose OBJ file"
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