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
        src/render/managers/TextureManager.cpp
        src/render/managers/TextureManager.h
        src/render/resources/TextureObject.cpp
        src/render/resources/TextureObject.h
        src/render/managers/ShaderManager.cpp
        src/render/managers/ShaderManager.h
        src/render/resources/ShaderObject.cpp
        src/render/resources/ShaderObject.h
        src/render/managers/RenderManager.cpp
        src/render/managers/RenderManager.h
        src/render/managers/WindowManager.cpp
        src/render/managers/WindowManager.h
        src/render/resources/Mesh.cpp
        src/render/resources/Mesh.h
        src/render/resources/Material.cpp
        src/render/resources/Material.h
        src/render/scene/Scene.cpp
        src/render/scene/Scene.h
        src/render/resources/Vertex.h src/render/resources/ModelObject.cpp src/render/resources/ModelObject.h src/render/scene/SceneNodeObject.cpp src/render/scene/SceneNodeObject.h src/render/scene/Camera.h src/render/scene/Camera.cpp src/render/managers/ModelManager.cpp src/render/managers/ModelManager.h src/render/managers/SceneManager.cpp src/render/managers/SceneManager.h)

add_executable(timepovis ${SOURCE_FILES})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${timepovis_SOURCE_DIR}/cmake)

set(SDL2_PATH "C:\\MinGW")

find_library(glm REQUIRED)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

include_directories(${SDL2_INCLUDE_DIR}
        "./src/")

target_link_libraries(timepovis ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARIES}
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES})