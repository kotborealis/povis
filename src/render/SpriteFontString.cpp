//
// Created by kotborealis on 19.11.16.
//

#include "SpriteFontString.h"

namespace PovisEngine{


SpriteFontString::SpriteFontString(SpriteFont *spriteFont, std::string _string, float font_size)
        : m_string(_string), spriteFont(spriteFont), font_size(font_size) {
    int i = 0;
    for (auto it = m_string.begin(); it != m_string.end(); ++it) {
        SpriteFontString::Glyph g(Sprite(spriteFont->m_texture, spriteFont->sprite_w, spriteFont->sprite_h, 0, 0,
                                         font_size), {(i++) * font_size, 0});
        glyphs.push_back(g);
    }
}

SpriteFontString::~SpriteFontString() {

}

void SpriteFontString::draw(RenderInfo *renderInfo) {
    glm::vec2 pos = renderInfo->position;
    for (auto &&glyph : glyphs) {
        renderInfo->position = pos + glyph.relative_pos;
        glyph.sprite.draw(renderInfo);
    }
}

SpriteFontString::Glyph::Glyph(const Sprite &sprite, const glm::vec2 &relative_pos) : relative_pos(relative_pos),
                                                                                      sprite(sprite) {}
}