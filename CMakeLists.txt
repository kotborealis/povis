cmake_minimum_required(VERSION 2.8)
project(povis)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

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
    src/render/resources/Mesh.cpp
    src/render/resources/Mesh.h
    src/render/resources/Vertex.h
    src/render/Camera.h
    src/render/Camera.cpp
    src/render/ResourceManager.h
    src/render/resources/Sprite.cpp
    src/render/resources/Sprite.h
    src/render/resource_managers/SpriteManager.cpp
    src/render/resource_managers/SpriteManager.h
    src/game/xff2/GameStateDemo.cpp
    src/game/xff2/GameStateDemo.h
    src/game/xff2/xff2_game.h
    src/game/xff2/BulletHell.cpp
    src/game/xff2/BulletHell.h
    src/game/xff2/Player.cpp
    src/game/xff2/Player.h
    src/game/xff2/Enemy.cpp
    src/game/xff2/Enemy.h
    src/game/xff2/PlayerTest.cpp
    src/game/xff2/PlayerTest.h
    src/game/xff2/Entity.cpp
    src/game/xff2/Entity.h src/game/xff2/StateInfo.h
        src/game/xff2/EnemyYukari.cpp
        src/game/xff2/EnemyYukari.h
    src/game/xff2/Bullet.cpp
    src/game/xff2/Bullet.h
        src/easing/Back.cpp
        src/easing/Back.h
        src/easing/Back.cpp
        src/easing/Back.h
        src/easing/Bounce.cpp
        src/easing/Bounce.h
        src/easing/Circ.cpp
        src/easing/Circ.h
        src/easing/Cubic.cpp
        src/easing/Cubic.h
        src/easing/Elastic.cpp
        src/easing/Elastic.h
        src/easing/Expo.cpp
        src/easing/Expo.h
        src/easing/Linear.cpp
        src/easing/Linear.h
        src/easing/Quad.cpp
        src/easing/Quad.h
        src/easing/Quart.cpp
        src/easing/Quart.h
        src/easing/Quint.cpp
        src/easing/Quint.h
        src/easing/Sine.cpp
        src/easing/Sine.h src/game/xff2/Background.cpp src/game/xff2/Background.h)

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