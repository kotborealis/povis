#pragma once

namespace PovisEngine{

class Entity{
public:
    Entity(){};

    virtual ~Entity(){};

    virtual void draw()=0;

    virtual void update()=0;
};

}