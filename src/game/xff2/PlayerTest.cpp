//
// Created by kotborealis on 18.09.2016.
//

#include <render/ResourceManager.h>
#include "PlayerTest.h"

namespace PovisEngine{

PlayerTest::PlayerTest(){
    sprite = ResourceSprite->create(ResourceTexture->load("assets/xff2/textures/bullet1.png"),
                                    {{
                                             {1 / 16.f, 1.f / 16.f},
                                             {1.f / 16.f * 2, 1.f / 16.f},
                                             {1.f / 16.f * 2, 0},
                                             {1 / 16.f, 0}}},
                                    {0, 1 / 16.f}, 16, 10);
}

PlayerTest::~PlayerTest(){

}

}