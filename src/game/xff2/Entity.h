#pragma once

#include <cstdint>
#include <glm/vec2.hpp>
#include <render/resources/Shader.h>
#include <render/Sprite.h>
#include <queue>
#include <easing/Back.h>
#include <easing/Expo.h>
#include "Hitbox.h"
#include "Interpolator.h"

namespace PovisEngine{

struct RenderInfo;
struct StateInfo;

class Entity{
public:
	Entity();
	virtual ~Entity();

	virtual void draw(RenderInfo* renderInfo) const;
	virtual void update(StateInfo* stateInfo);

	const glm::vec2& pos() const;
    void pos(glm::vec2 _pos);

    const Hitbox* hitbox() const;

	Interpolator* moveInterp;

protected:
	uint64_t tick = 0;

	glm::vec2 m_pos;
    Hitbox* m_hitbox;

	std::shared_ptr<Sprite> m_sprite;
	Shader::Ptr m_shader;
};

}