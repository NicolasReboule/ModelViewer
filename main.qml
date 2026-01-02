

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


    //! [debug]
    Connections {
        target: ModelManager
        // function onMaterialChanged() {
        //     console.log("Material changed")
        // }
        //
        // function onGeometryChanged() {
        //     console.log("Geometry changed")
        // }
    }
    //! [debug]

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
            scale: Qt.vector3d(10, 10, 10)
            materials: [
                PrincipledMaterial {
                    id: pMaterial

                    baseColor: ModelManager.material.diffuseColor

                    roughness: ModelManager.material.roughness
                    metalness: ModelManager.material.metalness
                    normalStrength: ModelManager.material.bumpStrength
                    opacity: ModelManager.material.opacity
                    lighting: ModelManager.material.illumination
                    indexOfRefraction: ModelManager.material.indexOfRefraction

                    /*emissiveFactor: ModelManager.material.emissiveFactor
                    specularTint: ModelManager.material.specularTint
                    transmissionFactor: ModelManager.material.transmissionFactor*/

                    Loader {
                        id: baseColorLoader
                        active: ModelManager.material.diffuseMap.toString() !== ""
                        sourceComponent: Component {
                            Texture { source: ModelManager.material.diffuseMap }
                        }
                        onLoaded: {
                            pMaterial.baseColorMap = item
                        }
                    }


                    Loader {
                        id: normalLoader
                        active: ModelManager.material.bumpMap.toString() !== ""
                        sourceComponent: Component {
                            Texture { source: ModelManager.material.bumpMap }
                        }
                        onLoaded: {
                            pMaterial.normalMap = item
                        }
                    }

                    Loader {
                        id: specularReflectionlLoader
                        active: ModelManager.material.specularReflectionMap.toString() !== ""
                        sourceComponent: Component {
                            Texture { source: ModelManager.material.specularReflectionMap }
                        }
                        onLoaded: {
                            pMaterial.specularReflectionMap = item
                        }
                    }

                    Loader {
                        id: emissiveLoader
                        active: ModelManager.material.emissiveMap.toString() !== ""
                        sourceComponent: Component {
                            Texture { source: ModelManager.material.emissiveMap }
                        }
                        onLoaded: {
                            pMaterial.emissiveMap = item
                        }
                    }

                    /*Inverse specularMap
                    Loader {
                        id: roughnessLoader
                        active: ModelManager.material.roughnessMap.toString() !== ""
                        sourceComponent: Component {
                            Texture { source: ModelManager.material.roughnessMap }
                        }
                        onLoaded: {
                            pMaterial.roughnessMap = item
                        }
                    }*/

                    Loader {
                        id: opacityLoader
                        active: ModelManager.material.dissolveMap.toString() !== ""
                        sourceComponent: Component {
                            Texture { source: ModelManager.material.dissolveMap }
                        }
                        onLoaded: {
                            pMaterial.opacityMap = item
                        }
                    }
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