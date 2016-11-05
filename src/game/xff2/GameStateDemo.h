#pragma once

#include <list>
#include <vector>
#include <render/Framebuffer.h>

#include "GameState.h"
#include "Logger.h"
#include "Game.h"
#include "render/ResourceManager.h"
#include "BulletHell.h"
#include "Player.h"
#include "Enemy.h"
#include "Background.h"

namespace PovisEngine{

class GameStateDemo:public GameState{
public:
    GameStateDemo();
    ~GameStateDemo();

    void handleEvent(SDL_Event* event);
    void update(float delta);
    void draw();

private:
    Camera* camera = new Camera(glm::vec3(0, 0, 1000), 45);
    glm::mat4 view = camera->getView();
    glm::mat4 projection = camera->getProjection(4.f / 3.f);

    Framebuffer* diffuseFramebuffer = new Framebuffer();
    Framebuffer* shadingFramebuffer = new Framebuffer(256, 256);

    Shader::Ptr shader_sprite;
    Shader::Ptr shader_shading;
    Shader::Ptr shader_hitpoints;

    Background* background;

    Player* player;
    std::vector<Enemy*> enemies;

    StateInfo stateInfo;
    Sprite* sprite_player_lives;
    Shader::Ptr shader_lighting;
};

}