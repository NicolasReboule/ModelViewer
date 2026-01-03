

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

    ModelEditor {}
    ModelView {}
}