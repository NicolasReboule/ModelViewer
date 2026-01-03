import QtQuick
import QtQuick3D

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
            Loaders {
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