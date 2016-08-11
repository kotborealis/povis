cmake_minimum_required(VERSION 2.8)
project(timepovis)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        src/Game.cpp
        src/Game.h
        src/GameState.h
        src/GameStateTest.cpp
        src/GameStateTest.h
        src/Logger.h
        src/povis.cpp
        src/render/TextureManager.cpp
        src/render/TextureManager.h
        src/render/TextureObject.cpp
        src/render/TextureObject.h
        src/render/ShaderManager.cpp
        src/render/ShaderManager.h
        src/render/ShaderObject.cpp
        src/render/ShaderObject.h
        src/render/RenderManager.cpp
        src/render/RenderManager.h
        src/render/WindowManager.cpp
        src/render/WindowManager.h
        src/render/Mesh.cpp
        src/render/Mesh.h
        src/render/Material.cpp
        src/render/Material.h
        src/render/Scene.cpp
        src/render/Scene.h
        src/render/Vertex.h)

add_executable(timepovis ${SOURCE_FILES})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${timepovis_SOURCE_DIR}/cmake)

set(SDL2_PATH "C:\\MinGW")

find_library(glm REQUIRED)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLU REQUIRED)

include_directories(${SDL2_INCLUDE_DIR}
        "./src/")

target_link_libraries(timepovis ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARIES}
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${GLU_LIBRARIES})