

//! [import]
import QtCore
import QtQuick
import QtQuick3D
import QtQuick.Controls
import QtQuick.Dialogs
//! [import]

Window {
    id: window
    width: 1280
    height: 720
    visible: true


    View3D {
        id: view
        anchors.right: parent.right
        width: parent.width * 0.7
        height: parent.height

        //! [environment]
        environment: SceneEnvironment {
            clearColor: "skyblue"
            backgroundMode: SceneEnvironment.Color
        }
        //! [environment]

        //! [camera]
        PerspectiveCamera {
            id: pCamera
            position: Qt.vector3d(0, 200, 300)
            eulerRotation.x: -30
        }
        //! [camera]

        //! [light]
        DirectionalLight {
            eulerRotation.x: -30
            eulerRotation.y: -70
        }
        //! [light]

        //! [objects]
        Model {
            id: model
            visible: ModelManager ? !ModelManager.loading : false
            position: Qt.vector3d(0, -200, 0)
            geometry: ModelManager ? ModelManager.geometry : null
            scale: Qt.vector3d(20, 20, 20)
            materials: [
                PrincipledMaterial {
                    baseColor: "red"
                }
            ]
        }
        //! [objects]

        BusyIndicator {
            running: ModelManager ? ModelManager.loading : false
            height: parent.height / 10
            width: parent.width / 10
            anchors.centerIn: parent
        }

        MouseArea {
            anchors.fill: parent
            acceptedButtons: Qt.LeftButton
            onPressAndHold: (mouse) => {
                var axis = Qt.vector3d(mouseX, mouseY, 0)
                pCamera.pan(10, axis)
            }
        }
    }

    Rectangle {
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
}