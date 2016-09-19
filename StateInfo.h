//
// Created by kotborealis on 19.09.16.
//

#pragma once

namespace PovisEngine {

class Player;

struct StateInfo {
    long long unsigned int frameCounter = 0;
    Player *player = nullptr;
};

}