cmake_minimum_required(VERSION 2.8)
project(povis)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    src/Game.cpp
    src/Game.h
    src/GameState.h
    src/GameStateTest.cpp
    src/GameStateTest.h
    src/Logger.h
    src/povis.cpp
    src/render/resource_managers/TextureManager.cpp
    src/render/resource_managers/TextureManager.h
    src/render/resources/TextureObject.cpp
    src/render/resources/TextureObject.h
    src/render/resource_managers/ShaderManager.cpp
    src/render/resource_managers/ShaderManager.h
    src/render/resources/ShaderObject.cpp
    src/render/resources/ShaderObject.h
    src/render/RenderManager.cpp
    src/render/RenderManager.h
    src/render/WindowManager.cpp
    src/render/WindowManager.h
    src/render/resources/Mesh.cpp
    src/render/resources/Mesh.h
    src/render/resources/Material.cpp
    src/render/resources/Material.h
    src/render/scene/Scene.cpp
    src/render/scene/Scene.h
    src/render/resources/Vertex.h
    src/render/resources/ModelObject.cpp
    src/render/resources/ModelObject.h
    src/render/scene/SceneNodeObject.cpp
    src/render/scene/SceneNodeObject.h
    src/render/scene/Camera.h
    src/render/scene/Camera.cpp
    src/render/resource_managers/ModelManager.cpp
    src/render/resource_managers/ModelManager.h
    src/render/scene/SceneManager.cpp
    src/render/scene/SceneManager.h
    src/render/resources/ObjLoader.cpp
    src/render/resources/ObjLoader.h
    src/render/ResourceManager.h)

add_executable(povis ${SOURCE_FILES})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${povis_SOURCE_DIR}/cmake)

set(SDL2_PATH "C:\\MinGW")

find_library(glm REQUIRED)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

include_directories(${SDL2_INCLUDE_DIR}
        "./src/")

target_link_libraries(povis ${SDL2_LIBRARY}
                      ${SDL2_IMAGE_LIBRARIES}
                      ${OPENGL_LIBRARIES}
                      ${GLEW_LIBRARIES})