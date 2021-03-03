cmake_minimum_required(VERSION 3.12..3.20)

project (top CXX)

# Enable c++11 as the externals libs are C++ 11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/rapidxml)
  file(DOWNLOAD "https://freefr.dl.sourceforge.net/project/rapidxml/rapidxml/rapidxml%201.13/rapidxml-1.13.zip" ${CMAKE_CURRENT_SOURCE_DIR}/rapidxml-1.13.zip SHOW_PROGRESS)
  execute_process(
        COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_CURRENT_SOURCE_DIR}/rapidxml
        COMMAND ${CMAKE_COMMAND} -E tar xzf ${CMAKE_CURRENT_SOURCE_DIR}/rapidxml-1.13.zip
        WORKING_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR}
   )
   file(RENAME ${CMAKE_CURRENT_SOURCE_DIR}/rapidxml-1.13 ${CMAKE_CURRENT_SOURCE_DIR}/rapidxml)
endif()

file(GLOB files "${CMAKE_SOURCE_DIR}/patchs/*.patch")
foreach(file ${files})
  get_filename_component(filename_we ${file} NAME_WE)
  if(NOT EXISTS ${CMAKE_SOURCE_DIR}/patchs/.${filename_we}.patch.applied)
    execute_process(
          COMMAND patch -p1 
          WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/${filename_we}"
          INPUT_FILE "${CMAKE_SOURCE_DIR}/patchs/${filename_we}.patch"
          OUTPUT_VARIABLE OUTPUT
          RESULT_VARIABLE RESULT)
    if (RESULT EQUAL 0)
      message(STATUS "Patch applied: ${filename_we}.patch")
      file(TOUCH ${CMAKE_SOURCE_DIR}/patchs/.${filename_we}.patch.applied )
    else()
       message(STATUS "Failed to apply Patch ${filename_we}.patch : ${OUTPUT} (${RESULT})")
    endif()
  endif()
endforeach()



add_subdirectory(cpp-httplib)
add_subdirectory(filewatch)
add_subdirectory(yaml-cpp)
add_subdirectory(rapidxml)
add_subdirectory(toJson)
add_subdirectory(glue)
