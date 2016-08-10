cmake_minimum_required(VERSION 2.8)
project(timepovis)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        src/AABB.h
        src/Area.cpp
        src/Area.h
        src/Entity.h
        src/Game.cpp
        src/Game.h
        src/GameState.h
        src/GameStateTest.cpp
        src/GameStateTest.h
        src/Graphics.cpp
        src/Graphics.h
        src/Logger.h
        src/povis.cpp
        src/v2.h
        src/World.cpp
        src/World.h
        src/Zone.h)

add_executable(timepovis ${SOURCE_FILES})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${timepovis_SOURCE_DIR}/cmake)

set(SDL2_PATH "C:\\MinGW")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLU REQUIRED)

include_directories(${SDL2_INCLUDE_DIR}
        "./include/")

target_link_libraries(timepovis ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARIES}
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${GLU_LIBRARIES})