

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
            position: Qt.vector3d(0, -200, 0)
            source: "assets/meshes/teapot.mesh"
            scale: Qt.vector3d(20, 20, 20)
            materials: [
                PrincipledMaterial {
                    baseColor: "red"
                }
            ]
        }
        //! [objects]
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
            selectedNameFilter.index: 1
            nameFilters: ["OBJ files (*.obj)"]
            currentFolder: StandardPaths.standardLocations(StandardPaths.DownloadLocation)[0]
            fileMode: FileDialog.OpenFile
            onAccepted: {
                console.log("Selected file:", selectedFile)
            }
            onRejected: console.log("Dialog cancelled")
        }
    }
}