cmake_minimum_required(VERSION 2.8)
project(povis)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")

set(SOURCE_FILES
        src/Game.cpp
        src/Game.h
        src/GameState.h
        src/Logger.h
        src/povis.cpp
        src/render/resource_managers/TextureManager.cpp
        src/render/resource_managers/TextureManager.h
        src/render/resources/Texture.cpp
        src/render/resources/Texture.h
        src/render/resource_managers/ShaderManager.cpp
        src/render/resource_managers/ShaderManager.h
        src/render/resources/Shader.cpp
        src/render/resources/Shader.h
        src/render/RenderManager.h
        src/render/RenderManager.cpp
        src/render/WindowManager.cpp
        src/render/WindowManager.h
        src/render/Framebuffer.cpp
        src/render/Framebuffer.h
        src/render/Vertex.h
        src/render/Camera.h
        src/render/Camera.cpp
        src/render/ResourceManager.h
        src/render/Sprite.cpp
        src/render/Sprite.h
        src/Interpolation/Back.cpp
        src/Interpolation/Back.h
        src/Interpolation/Back.cpp
        src/Interpolation/Back.h
        src/Interpolation/Bounce.cpp
        src/Interpolation/Bounce.h
        src/Interpolation/Circ.cpp
        src/Interpolation/Circ.h
        src/Interpolation/Cubic.cpp
        src/Interpolation/Cubic.h
        src/Interpolation/Elastic.cpp
        src/Interpolation/Elastic.h
        src/Interpolation/Expo.cpp
        src/Interpolation/Expo.h
        src/Interpolation/Linear.cpp
        src/Interpolation/Linear.h
        src/Interpolation/Quad.cpp
        src/Interpolation/Quad.h
        src/Interpolation/Quart.cpp
        src/Interpolation/Quart.h
        src/Interpolation/Quint.cpp
        src/Interpolation/Quint.h
        src/Interpolation/Sine.cpp
        src/Interpolation/Sine.h
        src/utils/to_string.h
        src/Interpolation/Interpolator.h
        src/Interpolation/Interpolator.cpp
        src/Interpolation/InterpolatorQueue.h
        src/Timer.cpp
        src/Timer.h
        src/game/dev/GameStateStartScreen.cpp
        src/game/dev/GameStateStartScreen.h
        src/render/BatchSprite.cpp src/render/BatchSprite.h src/render/BatchPrimitives.cpp src/render/BatchPrimitives.h)

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