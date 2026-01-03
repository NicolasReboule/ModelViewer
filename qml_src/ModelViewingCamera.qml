import QtQuick
import QtQuick3D
import QtQuick.Controls
import QtQuick3D.Helpers

Node {
    property alias camera: pCamera
    property alias cameraOrigin: cameraOrigin
    Node {
        id: cameraOrigin
        PerspectiveCamera {
            id: pCamera
            position: Qt.vector3d(0, 200, 300)
            eulerRotation.x: -30
        }
    }
}