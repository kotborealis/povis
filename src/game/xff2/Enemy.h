//
// Created by kotborealis on 11.11.2016.
//

#pragma once

#include "Entity.h"

namespace PovisEngine{

class Enemy:public Entity{
public:
    Enemy();
    virtual ~Enemy();

    void draw(RenderInfo* renderInfo) const;
    void update(StateInfo* stateInfo);

    bool isBoss() const;

protected:
    float hit_points_max;
    float hit_points;

    bool m_isBoss = false;
};

}
