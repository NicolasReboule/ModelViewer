import QtQuick
import QtQuick3D

Node {
    id: node

    // Resources
    PrincipledMaterial {
        id: defaultMaterial_material
        objectName: "DefaultMaterial"
        baseColor: "#ff999999"
        roughness: 1
        indexOfRefraction: 1
    }

    // Nodes:
    Node {
        id: teapot_obj
        objectName: "teapot.obj"
        Model {
            id: defaultobject
            objectName: "teapot"
            source: "meshes/teapot.mesh"
            materials: [
                defaultMaterial_material
            ]
        }
    }

    // Animations:
}
