#pragma once

#include <cstdint>
#include <glm/vec2.hpp>
#include <render/resources/Shader.h>
#include <render/Sprite.h>
#include <queue>
#include <Interpolation/Back.h>
#include <Interpolation/Expo.h>
#include "Hitbox.h"
#include "Interpolation/Interpolator.h"

namespace pse{

struct RenderInfo;
struct StateInfo;

class Entity{
public:
	Entity();
	virtual ~Entity();

	virtual void draw(RenderInfo* renderInfo) const;
	virtual void update(StateInfo* stateInfo);

    const glm::vec2& getPosition() const;
    void setPosition(glm::vec2 _pos);

    const float& getRotation() const;
    void setRotation(float _rotation);

    Hitbox* getHitbox() const;

protected:
	uint64_t tick = 0;

    glm::vec2 position;
    float rotation = 0;
    Hitbox* hitbox;

    std::shared_ptr<Sprite> sprite;
    Shader::Ptr shader;
};

}