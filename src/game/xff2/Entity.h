#pragma once

#include <cstdint>
#include <glm/vec2.hpp>
#include <render/resources/Shader.h>
#include <render/Sprite.h>
#include <queue>
#include <easing/Back.h>
#include <easing/Expo.h>
#include "Hitbox.h"

namespace PovisEngine{

struct RenderInfo;
struct StateInfo;

struct MoveEntity{
	unsigned interp_cur_ticks = 0;
	unsigned interp_dur_ticks = 0;
	glm::vec2 offset = glm::vec2();
	glm::vec2 interp_start_pos = glm::vec2();
	glm::vec2 interp_target_pos = glm::vec2();
};

struct MoveQueue{
	std::queue<MoveEntity> queue;
	MoveEntity current_move_entity;
	float (* interpolation)(float, float, float, float) = &Easing::Expo::easeInOut;
};

class Entity{
public:
	Entity();
	virtual ~Entity();

	virtual void draw(RenderInfo* renderInfo) const;
	virtual void update(StateInfo* stateInfo);

	const glm::vec2& pos() const;
    void pos(glm::vec2 _pos);

	void pushMoveOffset(glm::vec2 offset, unsigned ticks);

    const Hitbox* hitbox() const;

protected:
	uint64_t tick = 0;

	glm::vec2 m_pos;
    Hitbox* m_hitbox;

	std::shared_ptr<Sprite> m_sprite;
	Shader::Ptr m_shader;

	MoveQueue moveQueue;
};

}