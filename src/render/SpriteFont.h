//
// Created by kotborealis on 19.11.16.
//

#pragma once

#include <render/resources/Texture.h>

namespace PovisEngine {

class SpriteFont {
    friend class SpriteFontString;
public:
    SpriteFont(const Texture::Ptr &m_texture, unsigned int sprite_w, unsigned int sprite_h);
    virtual ~SpriteFont();

private:
    Texture::Ptr m_texture;
    unsigned sprite_w;
    unsigned sprite_h;
};

}

