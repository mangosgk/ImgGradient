project(ImgGradient)
cmake_minimum_required(VERSION 2.8)

file(GLOB SOURCES *.cpp)
file(GLOB HEADERS *.h)

option(BUILD_DOCS "BUILD_DOCS" OFF)

# Copy image'data into data build directory.
file( GLOB_RECURSE pattern_files RELATIVE  "${CMAKE_CURRENT_SOURCE_DIR}/" "data/*.jpg" )
foreach( pattern_file ${pattern_files} )
    add_custom_command(
        OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${pattern_file}"
        COMMAND cmake -E copy
        "${CMAKE_CURRENT_SOURCE_DIR}/${pattern_file}"
        "${CMAKE_CURRENT_BINARY_DIR}/${pattern_file}"
        DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/${pattern_file}"
    )
    list( APPEND pattern_files_dest "${pattern_file}" )
endforeach( pattern_file )
add_custom_target( CopyPatterns ALL DEPENDS ${pattern_files_dest} )

# add a target to generate API documentation with Doxygen
find_package(Doxygen)
if(DOXYGEN_FOUND AND BUILD_DOCS MATCHES ON)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    add_custom_target(docs ALL
        ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen" VERBATIM
    )
endif(DOXYGEN_FOUND AND BUILD_DOCS MATCHES ON)


add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

