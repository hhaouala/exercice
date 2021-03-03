cmake_minimum_required(VERSION 3.12..3.20)

project (glue CXX)

add_subdirectory(Config)
add_subdirectory(Server)
add_subdirectory(Main)



# DOXYGEN ---------------------------------------------------------------------
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

find_package(Doxygen REQUIRED)

set(DOXYGEN_INPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(DOXYGEN_OUTPUT_DIR ${CMAKE_INSTALL_PREFIX}/docs/glue)
set(DOXYGEN_INDEX_FILE ${DOXYGEN_OUTPUT_DIR}/html/index.html)

#Replace variables inside @@ with the current values
set(DOXYFILE_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
set(DOXYFILE_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
configure_file(${DOXYFILE_IN} ${DOXYFILE_OUT} @ONLY)

file(MAKE_DIRECTORY ${DOXYGEN_OUTPUT_DIR})
file(GLOB_RECURSE CAT_CUTIFIER_PUBLIC_HEADERS ${DOXYGEN_INPUT_DIR}/*.hpp)
add_custom_command(OUTPUT ${DOXYGEN_INDEX_FILE}
                   DEPENDS ${CAT_CUTIFIER_PUBLIC_HEADERS}
                   COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE_OUT}
                   MAIN_DEPENDENCY ${DOXYFILE_OUT} ${DOXYFILE_IN}
                   COMMENT "Generating docs")

add_custom_target(Doxygen ALL DEPENDS ${DOXYGEN_INDEX_FILE})
