#pragma once

#include <vector>
#include <string>

#include "SDL2/SDL.h"

#include "GameState.h"
#include "Logger.h"
#include "render/managers/RenderManager.h"

namespace PovisEngine{

class GameState;

class Game{
public:
    static Game& i(){
        return instance();
    }

    static Game& instance(){
        static Game m_instance;
        return m_instance;
    }

    void run();
    void setState(GameState *newState);
    void pushState(GameState *newState);
    void popState();

    RenderManager* render() const;
    ShaderManager* shader() const;
    TextureManager* texture() const;
    ModelManager* model() const;

    void stop(){
        running=false;
    }

private:
    //Singletone
    Game();
    ~Game();
    Game(Game const &)=delete;
    Game &operator=(Game const &)=delete;

    //Game State
    inline void CState(){cState=states.back();}
    std::vector<GameState *> states;
    GameState *cState;

    //Managers
    const RenderManager* m_renderManager=new RenderManager(std::string("Awooo"), (unsigned int)1024, (unsigned int)768);
    const ShaderManager* m_shaderManager=new ShaderManager();
    const TextureManager* m_textureManager=new TextureManager();
    const ModelManager* m_modelManager=new ModelManager();

    bool running;
};

}