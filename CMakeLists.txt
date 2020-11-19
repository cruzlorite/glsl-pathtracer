#    Copyright(C) 2020 José María Cruz Lorite
#
#    This file is part of pathtracer.
#
#    pathtracer is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    pathtracer is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with pathtracer.  If not, see <https://www.gnu.org/licenses/>.

# Set the minimum version of CMake that can be used
cmake_minimum_required(VERSION 3.5)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif(NOT CMAKE_BUILD_TYPE)

# c++ standard
set(CMAKE_CXX_STANDARD 17)

# Realease
#set(CMAKE_BUILD_TYPE Release)
#set(CMAKE_CXX_FLAGS_DEBUG "-g")
#set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# Executable and project names
set(TARGET pathtracer)
project(pathtracer)

# Set link libraries depending on OS
if(WIN32)
  set(BUILD_OS    WIN32)
  set(GL_NAMES    opengl32)
  set(GLFW_NAMES  glfw3)

elseif(UNIX AND APPLE)
  set(BUILD_OS    macOS)
  message(FATAL "not supported build for MacOS")

elseif(UNIX AND NOT APPLE)
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
  set(BUILD_OS    GNU-Linux)
  set(GL_NAMES    GL)
  set(GLFW_NAMES  glfw)
endif()

# checkOpenGLError
# https://stackoverflow.com/questions/8487986/file-macro-shows-full-path
string(LENGTH "${CMAKE_SOURCE_DIR}/" SOURCE_PATH_SIZE)
add_definitions("-DSOURCE_PATH_SIZE=${SOURCE_PATH_SIZE}")

# Shader dest folder
set(SHADER_DEST ${CMAKE_CURRENT_BINARY_DIR}/shaders)

# Include external headers
include_directories(include)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/shaders) # Modified shaders will be here

# Import third party libraries
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(third-party/glfw-3.3.2)
add_subdirectory(third-party/glad-0.1.33)
add_subdirectory(third-party/imgui-1.50)

# Source files
file(GLOB SOURCES
  "src/*"
  "src/opengl/*"
  "src/scene/*"
  "src/util/*"
  "src/pathtracer/*")

# Shader sources
file(GLOB SHADERS
  "src/pathtracer/shaders/*")

# Preprocess all shaders
add_custom_target(PREPROCESS_SHADERS ALL
    DEPENDS ${SHADERS}
)

# Copy every shader
foreach(SHADER ${SHADERS})
  get_filename_component(SHADER_NAME ${SHADER} NAME)
  configure_file(${SHADER} ${SHADER_DEST}/${SHADER_NAME} COPYONLY)
  
  # Replace in file
  add_custom_command(TARGET PREPROCESS_SHADERS
    COMMAND rm -f ${SHADER_DEST}/${SHADER_NAME}
    COMMAND /bin/cp -rf ${SHADER} ${SHADER_DEST}/${SHADER_NAME}
    COMMAND sed -i -e "/#include/ i \\)\\\"" -e "/#include/ a R\\\"\\(" -e "1 i R\\\"\\(" ${SHADER_DEST}/${SHADER_NAME}
    COMMAND echo "\\)\\\"" >> ${SHADER_DEST}/${SHADER_NAME}
    #COMMAND sed -i -e "/#include/ i \\)\\\"" -e "/#include/ a R\\\"\\(" -e "s/GLSL_BEGIN/R\\\"\\(/g" -e "s/GLSL_END/\\)\\\"/g" ${SHADER_DEST}/${SHADER_NAME}
  )
endforeach()

# Output binary on /bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Add an executable with the above sources
add_executable(${TARGET} ${SOURCES})
add_dependencies(${TARGET} PREPROCESS_SHADERS)

# Link libraries
target_link_libraries(${TARGET}
  glfw ${GLFW_LIBRARIES} glad imgui)



