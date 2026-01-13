# https://cmake.org/cmake/help/latest/module/CPack.html
include(InstallRequiredSystemLibraries) # include any runtime libraries that are needed by the project for the current platform

# Set some basic information about the project
set(CPACK_PACKAGE_NAME "ModelViewer")
set(CPACK_PACKAGE_CONTACT "Nicolas Reboule")
set(CPACK_PACKAGE_VENDOR "Nicolas Reboule")
set(CPACK_PACKAGE_DESCRIPTION "ModelViewer is an application to visualize 3D models, developed with Qt.")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "ModelViewer is an application to visualize 3D models, developed with Qt.")
set(CPACK_PACKAGE_HOMEPAGE_URL "${PROJECT_HOMEPAGE_URL}")

# Set the version information
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

# Set some resource files
set(CPACK_RESOURCE_FILE_WELCOME "${CMAKE_SOURCE_DIR}/README.md")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")
set(CPACK_RESOURCE_FILE_README "${CMAKE_SOURCE_DIR}/README.md")

set(CPACK_PACKAGE_INSTALL_DIRECTORY "${CPACK_PACKAGE_NAME}") # Installation directory on the target system
#set(CPACK_PACKAGE_ICON "${CMAKE_SOURCE_DIR}/assets/ModelViewer/icons/logo.ico") # Location of an icon to display during the installation process
set(CPACK_PACKAGE_CHECKSUM "SHA256") # Create a checksum for the package
set(CPACK_MONOLITHIC_INSTALL ON) # Install all components in one package, can be useful to force the installation of all components

# Set the executables name
set(CPACK_PACKAGE_EXECUTABLES
        "ModelViewer" "Model Viewer"
)

# Source package generator
set(CPACK_SOURCE_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${PROJECT_VERSION}-src")
set(CPACK_SOURCE_GENERATOR "7Z;DEB;IFW;NSIS;NSIS64;NUGET;STGZ:TGZ;TXZ;ZIP")
set(CPACK_SOURCE_IGNORE_FILES ".git;build;out;dist;cmake-*;include;lib")

#include(${CMAKE_SOURCE_DIR}/cmake/cpack/CPackDEB.cmake) # DEB
#include(${CMAKE_SOURCE_DIR}/cmake/cpack/CPackNSIS.cmake) # NSIS
#include(${CMAKE_SOURCE_DIR}/cmake/cpack/CPackRPM.cmake) # RPM

include(CPack)