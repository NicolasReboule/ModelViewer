

//! [import]
import QtCore
import QtQuick
import QtQuick3D
import QtQuick.Controls
import QtQuick.Dialogs
import QtQuick3D.Helpers
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
        camera: pCamera
        Node {
            id: cameraOrigin
            PerspectiveCamera {
                id: pCamera
                position: Qt.vector3d(0, 200, 300)
                eulerRotation.x: -30
            }
        }
        OrbitCameraController {
            enabled: ModelManager ? ModelManager.ready : false
            anchors.fill: parent
            origin: cameraOrigin
            camera: pCamera
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
            visible: ModelManager ? ModelManager.ready : false
            geometry: ModelManager ? ModelManager.geometry : null
            scale: Qt.vector3d(20, 20, 20)
            materials: [
                PrincipledMaterial {
                    baseColor: "red"
                }
            ]
        }
        //! [objects]


        //! [loader]
        BusyIndicator {
            running: ModelManager ? ModelManager.loading : false
            height: parent.height / 10
            width: parent.width / 10
            anchors.centerIn: parent
        }
        //! [loader]

        MouseArea {
            enabled: ModelManager ? ModelManager.ready : false
            anchors.fill: parent
            acceptedButtons: Qt.RightButton

            property real sensitivity: 0.5
            property real lastX: 0
            property real lastY: 0

            onPressed: (mouse) => {
                lastX = mouse.x
                lastY = mouse.y
            }

            onPositionChanged: (mouse) => {
                const dx = (mouse.x - lastX) * sensitivity
                const dy = (mouse.y - lastY) * sensitivity

                lastX = mouse.x
                lastY = mouse.y

                pCamera.position = Qt.vector3d(
                    pCamera.position.x - dx,
                    pCamera.position.y + dy,
                    pCamera.position.z
                )
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