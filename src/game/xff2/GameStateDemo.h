#pragma once

#include <list>
#include <vector>

#include "GameState.h"
#include "Logger.h"
#include "Game.h"
#include "render/ResourceManager.h"
#include "BulletHell.h"
#include "Player.h"
#include "Enemy.h"

namespace PovisEngine{

class GameStateDemo:public GameState{
public:
    GameStateDemo();
    ~GameStateDemo();

    void handleEvent(SDL_Event* event);
    void update(float delta);
    void draw();

private:
    Camera* camera = new Camera(glm::vec3(0, 0, 1), 45);

    Shader::Ptr shader_sprite;

    Texture::Ptr texture_bullets;

    Sprite::Ptr sprite_bg;
    Sprite::Ptr bulletRed01;
    Sprite::Ptr sprite_player;

    BulletHell* bullets;
    Player* player;
    Enemy* enemyTest;
};

}