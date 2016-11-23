//
// Created by kotborealis on 22.11.2016.
//

#pragma once

#include <game/xff2/BulletPattern.h>
#include <Interpolation/Sine.h>

namespace pse{

class Timer;

class BulletPatternInvaderBoss02:public BulletPattern{
public:
    BulletPatternInvaderBoss02(BulletHell* bulletHell, Enemy* source);
    virtual ~BulletPatternInvaderBoss02();

    void update(StateInfo* stateInfo) override;

private:
    BulletType* m_bullet01;

    glm::vec2 latest_player_pos;
    float angle_to_player;
    Interpolator<float>* angle_to_player_interp = new Interpolator<float>(&angle_to_player, &interp::Sine::easeInOut);

    Timer::Ptr shoot0_t;

    Timer::Ptr shoot1_t;
    int cascade_c = 1;

    Timer::Ptr shoot2_t;
    int offset2 = 0;
    BulletType* m_bullet02;
};

}
