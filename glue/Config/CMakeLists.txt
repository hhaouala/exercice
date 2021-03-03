# Requirements to the cmake ----------------------------------------------------
cmake_minimum_required(VERSION 3.12..3.20)

# Project Declaration ----------------------------------------------------------
project(ConfigManager
    VERSION         0.0.1
    DESCRIPTION    "handle config file : using yaml to json"
    LANGUAGES       CXX
)

# Includes ---------------------------------------------------------------------
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# Target Declaration -----------------------------------------------------------
add_library(${PROJECT_NAME} SHARED)
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

# Dependency resolving ---------------------------------------------------------

if(NOT TARGET nlohmann_json)
find_package(nlohmann_json REQUIRED)
endif()
target_include_directories(${PROJECT_NAME}
  PRIVATE
    $<TARGET_PROPERTY:nlohmann_json::nlohmann_json,INTERFACE_INCLUDE_DIRECTORIES> )

foreach(package yaml-cpp
                FileWatch
                toJSON
                rapidxml
)
    if(NOT TARGET ${package})
        find_package(${package} REQUIRED)
    endif()

    target_include_directories(${PROJECT_NAME}
      PRIVATE
        $<TARGET_PROPERTY:${package},INTERFACE_INCLUDE_DIRECTORIES> )

endforeach()


# Pacakage setting -------------------------------------------------------------
set(PACKAGE_INSTALL_CMAKE_DIR   ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})
set(PACKAGE_INSTALL_INCLUDE_DIR ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})
set(PACKAGE_INSTALL_LIBRARY_DIR ${CMAKE_INSTALL_LIBDIR})
set(PACKAGE_INSTALL_ARCHIVE_DIR ${CMAKE_INSTALL_LIBDIR})
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Target Definition ------------------------------------------------------------

target_sources(${PROJECT_NAME} 
    PRIVATE 
     ${CMAKE_CURRENT_SOURCE_DIR}/src/YAMLtoJsonConfigManager.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/src/FileWatcher.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/src/CoreConfigManager.cpp
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../interfaces>
    PUBLIC
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
      $<INSTALL_INTERFACE:${PACKAGE_INSTALL_INCLUDE_DIR}>
)

set(${PROJECT_NAME}_PUBLIC_HEADER
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/YAMLtoJsonConfigManager.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/CoreConfigManager.hpp
)

target_link_libraries(${PROJECT_NAME}
    yaml-cpp
)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
        PUBLIC_HEADER         "${${PROJECT_NAME}_PUBLIC_HEADER}"
        CXX_STANDARD          11
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS        NO
        POSITION_INDEPENDENT_CODE TRUE
)

# Installations ----------------------------------------------------------------

## Targets installation
install(TARGETS ${PROJECT_NAME}
    EXPORT          ${PROJECT_NAME}Targets
    LIBRARY         DESTINATION ${PACKAGE_INSTALL_LIBRARY_DIR}
    PUBLIC_HEADER   DESTINATION ${PACKAGE_INSTALL_INCLUDE_DIR}
    COMPONENT       library
)

## CMake's configurations
install(EXPORT ${PROJECT_NAME}Targets
    NAMESPACE   ${PROJECT_NAME}::
    DESTINATION ${PACKAGE_INSTALL_CMAKE_DIR}
)
