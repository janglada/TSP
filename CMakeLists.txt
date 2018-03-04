cmake_minimum_required(VERSION 3.6)
project(tsp)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        Ant.cpp
        Ant.h
        ga.cpp
        ga.h
        Map.cpp
        Map.h
        nn.cpp
        nn.h
        Sa.cpp
        Sa.h
        tour.cpp
        tour.h
        tsp.cpp)

add_executable(tsp ${SOURCE_FILES})

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

target_link_libraries(tsp ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )