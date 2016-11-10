#pragma once

#include <cstdint>
#include <glm/vec2.hpp>
#include <render/resources/Shader.h>
#include <render/resources/Sprite.h>

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
	void pos(glm::vec2&);

	const glm::vec2& hitbox() const;
	void hitbox(glm::vec2&);

protected:
	uint64_t tick = 0;

	glm::vec2 m_pos;
	glm::vec2 m_hitbox;

	Sprite* m_sprite;
	Shader::Ptr m_shader;
}

}