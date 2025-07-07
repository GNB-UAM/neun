cmake_minimum_required(VERSION 3.5)

project(Neun VERSION 0.4.0 LANGUAGES CXX)

export(PACKAGE Neun)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS_DEBUG   "-Wall -O0 -g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

# Add subdirectories
add_subdirectory(include)
add_subdirectory(integrators)
add_subdirectory(archetypes)
add_subdirectory(concepts)
add_subdirectory(examples)
add_subdirectory(models)
add_subdirectory(wrappers)

# Packaging
include(CPack)
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "An efficient library to simulate neural networks in C++.")
set(CPACK_PACKAGE_VENDOR "Grupo de Neurocomputación Biológica")
set(CPACK_PACKAGE_CONTACT "angel.lareo@uam.es")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/Description")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/Copyright")
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_PACKAGE_INSTALL_DIRECTORY "CMake ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}")
set(CPACK_DEBIAN_PACKAGE_SECTION "devel")
set(CPACK_GENERATOR "DEB")

configure_file(neun.pc.in neun.pc @ONLY)
install(FILES neun.pc DESTINATION pkgconfig)
