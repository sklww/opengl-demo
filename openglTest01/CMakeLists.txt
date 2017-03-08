cmake_minimum_required(VERSION 3.4)
project(openglTest01)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
include_directories(/usr/local/include)

set(SOURCE_FILES main.cpp)
link_libraries("/usr/local/lib/libgltools.a")
link_libraries("/usr/local/Cellar/glew/2.0.0/lib/libGLEW.a")

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIR})

set(CMAKE_CXX_FLAGS "-g -Wall")
add_executable(openglTest01 ${SOURCE_FILES})
target_link_libraries(openglTest01 ${GLUT_LIBRARY} ${OPENGL_LIBRARY})



