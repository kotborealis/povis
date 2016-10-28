//
// Created by kotborealis on 19.09.16.
//

#pragma once

#include <game/xff2/Player.h>

namespace PovisEngine{

struct StateInfo{
    long long unsigned int tick = 0;
    Player* player = nullptr;
};

}