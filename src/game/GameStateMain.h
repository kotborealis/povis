#pragma once

#include <list>
#include <vector>

#include "GameState.h"
#include "Logger.h"
#include "Game.h"
#include "render/ResourceManager.h"

namespace PovisEngine{

class GameStateMain:public GameState{
public:
    GameStateMain();
    ~GameStateMain();

    void handleEvent(SDL_Event* event);
    void update(float delta);
    void draw();

private:
    Camera* camera = new Camera(glm::vec3(0, 0, 10), 45);

    Sprite::Ptr sprite_bullet;
    Sprite::Ptr sprite_hitbox;

    Shader::Ptr sprite_shader;


};

}