//
// Created by kotborealis on 11.11.2016.
//

#pragma once

#include "Entity.h"
#include "BulletHell.h"

namespace PovisEngine{

class Enemy:public Entity{
public:
    Enemy();
    virtual ~Enemy();

    void draw(RenderInfo* renderInfo) const override;
    void update(StateInfo* stateInfo) override;

    bool isBoss() const;

    Interpolator<glm::vec2>* moveInterp;

protected:
    float hit_points_max;
    float hit_points;

    bool m_isBoss = false;

    BulletHell bulletHell;
};

}
