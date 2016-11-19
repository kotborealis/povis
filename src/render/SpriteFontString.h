//
// Created by kotborealis on 19.11.16.
//

#include <string>
#include "Sprite.h"
#include "SpriteFont.h"

#pragma once

namespace PovisEngine{

class SpriteFontString{
public:
    SpriteFontString(SpriteFont *spriteFont, std::string _string, float font_size);
    virtual ~SpriteFontString();

    void draw(RenderInfo* renderInfo);

private:
    struct Glyph{
        Glyph(const Sprite &sprite, const glm::vec2 &relative_pos);

        glm::vec2 relative_pos;
        Sprite sprite;
    };
    SpriteFont* spriteFont;
    std::string m_string;
    float font_size;
    std::list<Glyph> glyphs;
};

}