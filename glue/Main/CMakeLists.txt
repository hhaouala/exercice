# Requirements to the cmake ----------------------------------------------------
cmake_minimum_required(VERSION 3.12..3.20)

# Project Declaration ----------------------------------------------------------
project(awesome_server
    VERSION         0.0.1
    DESCRIPTION    "Http server that configurable using YAML"
    LANGUAGES       CXX
)

# Includes ---------------------------------------------------------------------
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# Target Declaration -----------------------------------------------------------
add_executable(${PROJECT_NAME})

# Dependency resolving ---------------------------------------------------------
foreach(package ConfigManager
                HttpLibServer
)
  if(NOT TARGET ${package}::${package})
    find_package(${package} REQUIRED)
  endif()

  target_include_directories(${PROJECT_NAME}
    PRIVATE
      $<TARGET_PROPERTY:${package}::${package},INTERFACE_INCLUDE_DIRECTORIES>
  )
  
  target_link_libraries(${PROJECT_NAME} ${package}::${package} )
  
endforeach()

find_package(FileWatch REQUIRED)
target_include_directories(${PROJECT_NAME}
    PRIVATE
      $<TARGET_PROPERTY:FileWatch,INTERFACE_INCLUDE_DIRECTORIES>
  )

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
     ${CMAKE_CURRENT_SOURCE_DIR}/Main.cpp
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../interfaces>
    PUBLIC
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
      $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
      $<INSTALL_INTERFACE:${PACKAGE_INSTALL_INCLUDE_DIR}>
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
    PUBLIC_HEADER   DESTINATION ${PACKAGE_INSTALL_INCLUDE_DIR}
)

## CMake's configurations
install(EXPORT ${PROJECT_NAME}Targets
    NAMESPACE   ${PROJECT_NAME}::
    DESTINATION ${PACKAGE_INSTALL_CMAKE_DIR}
)