import QtQuick
import QtQuick3D
import QtQuick.Controls
import QtQuick3D.Helpers

View3D {
    id: modelView
    anchors.right: parent.right
    width: parent.width * 0.7
    height: parent.height

    //! [environment]
    environment: SceneEnvironment {
        clearColor: "skyblue"
        backgroundMode: SceneEnvironment.Color
    }
    //! [environment]

    //! [light]
    DirectionalLight {
        eulerRotation.x: -30
        eulerRotation.y: -70
    }
    //! [light]

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

    //! [camera]
    camera: mvc.camera
    ModelViewingCamera {
        id: mvc
    }
    CameraControls {
        id: cc
        cameraOrigin: mvc.cameraOrigin
        pCamera: mvc.camera
        anchors.fill: parent
    }
    //! [camera]

    //! [objects]
    CustomModel {}
    //! [objects]


    //! [loader]
    BusyIndicator {
        running: ModelManager ? ModelManager.loading : false
        height: parent.height / 10
        width: parent.width / 10
        anchors.centerIn: parent
    }
    //! [loader]
}