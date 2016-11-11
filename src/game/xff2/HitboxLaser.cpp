//
// Created by kotborealis on 11.11.2016.
//

#include "HitboxLaser.h"

namespace PovisEngine{


HitboxLaser::HitboxLaser(){

}

HitboxLaser::~HitboxLaser(){

}

const float& HitboxLaser::width() const{
    return m_width;
}

void HitboxLaser::width(float& _width){
    m_width = _width;
}

const glm::vec2& HitboxLaser::posA() const{
    return m_pos_a;
}

void HitboxLaser::posA(glm::vec2& _pos_a){
    m_pos_a = _pos_a;
}

const glm::vec2& HitboxLaser::posB() const{
    return m_pos_b;
}

void HitboxLaser::posB(glm::vec2& _pos_b){
    m_pos_b = _pos_b;
}

bool HitboxLaser::collision(HitboxLaser& laser){
    return false;
}

bool HitboxLaser::collision(HitboxCircle& circle){
    return false;
}
}