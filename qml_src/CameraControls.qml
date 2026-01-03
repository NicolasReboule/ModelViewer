import QtQuick
import QtQuick3D
import QtQuick.Controls
import QtQuick3D.Helpers

Item {
    property Node cameraOrigin: null
    property PerspectiveCamera pCamera: null
    OrbitCameraController {
        enabled: ModelManager ? ModelManager.ready : false
        anchors.fill: parent
        origin: cameraOrigin
        camera: pCamera
    }

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