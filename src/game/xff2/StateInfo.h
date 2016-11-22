//
// Created by kotborealis on 09.11.16.
//

#pragma once

#include <cstdint>

namespace pse{

struct StateInfo{
    uint64_t tick = 0;
    glm::vec2 player_pos;
    bool player_alive;

    class Player* player;
};

}
