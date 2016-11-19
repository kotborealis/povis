//
// Created by kotborealis on 19.11.16.
//

#include "SpriteFont.h"

namespace PovisEngine {


SpriteFont::SpriteFont(const Texture::Ptr &m_texture, unsigned int sprite_w, unsigned int sprite_h) : m_texture(
        m_texture), sprite_w(sprite_w), sprite_h(sprite_h) {}

SpriteFont::~SpriteFont() {

}
}