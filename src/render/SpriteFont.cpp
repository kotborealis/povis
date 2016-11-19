//
// Created by kotborealis on 19.11.16.
//

#include "SpriteFont.h"

namespace PovisEngine {


SpriteFont::SpriteFont(const Texture::Ptr &m_texture, unsigned int sprite_w, unsigned int sprite_h) :m_texture(
        m_texture), sprite_w(sprite_w), sprite_h(sprite_h){
    for(int i = 0; i < sprite_w; i++){
        for(int j = 0; j < sprite_h; j++){
            int _ = i * sprite_h + j;
            Glyph* g = new Glyph();
            g->sprite = new Sprite(m_texture, sprite_w, sprite_h, _, 0, 0);
            glyph_map[_] = g;
        }
    }
}

SpriteFont::~SpriteFont() {

}

// 0 - ABCDEFGHIJKLMNOPQRSTUVWXYZ
// 26 - abcdefghijklmnopqrstuvwxyz
// 52 - 0123456789
// 53 - .
// 54 - ,
// 55 - !
// 56 - ?
// 57 - '
// 58 - @
// 59 - #
// 60 - $
// 61 - %
// 62 - &
// 63 - ()
// 65 - /
// 66 - -
// 67 - +
// 68 - =
// 69 - …
unsigned int SpriteFont::charToGlyphID(char c){
    if(c >= 'A' && c <= 'Z'){
        return (unsigned int)(c - 'A');
    }
    if(c >= 'a' && c <= 'z'){
        return (unsigned int)(c - 'a' + 26);
    }
    if(c >= '0' && c <= '9'){
        return (unsigned int)(c - '0' + 52);
    }

    switch(c){
        case '.':
            return 63 - 1;
        case ',':
            return 64 - 1;
        case '!':
            return 65 - 1;
        case '?':
            return 66 - 1;
        case '\'':
            return 67 - 1;
        case '@':
            return 68 - 1;
        case '#':
            return 69 - 1;
        case '$':
            return 70 - 1;
        case '%':
            return 71 - 1;
        case '(':
            return 73 - 1;
        case ')':
            return 74 - 1;
        case '/':
            return 75 - 1;
        case '-':
            return 76 - 1;
        case '+':
            return 77 - 1;
        case '=':
            return 78 - 1;
        case ' ':
            return 80 - 1;
        default:
            return 65;
    }
}

SpriteFont::String* SpriteFont::string(std::string str, float size){
    SpriteFont::String* s = new SpriteFont::String();
    s->glyph_map = &glyph_map;
    s->size = size;
    for(auto&& i : str){
        GlyphInstance _;
        _.glyph_id = charToGlyphID(i);
        if(i == '\n'){
            _.special = LINE_BREAK;
        }
        s->glyphs.push_back(_);
    }
    return s;
}

void SpriteFont::String::draw(RenderInfo* renderInfo){
    glm::vec2 pos = renderInfo->position;
    int x_offset = 0;
    int y_offset = 0;
    for(auto&& glyph : glyphs){
        if(glyph.special == LINE_BREAK){
            y_offset--;
            x_offset = 0;
        }else{
            x_offset++;
            renderInfo->position = pos + glm::vec2(size * x_offset, (size + size / 2) * y_offset);
            auto _ = this->glyph_map->at(glyph.glyph_id);
            _->sprite->scale(size);
            _->sprite->draw(renderInfo);
        }
    }
}
}