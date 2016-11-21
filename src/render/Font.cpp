//
// Created by kotborealis on 19.11.16.
//

#include "Font.h"

namespace pse{


Font::Font(const Texture::Ptr& m_texture, unsigned int sprite_w, unsigned int sprite_h):m_texture(
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

Font::~Font(){

}


unsigned int Font::charToGlyphID(char c){
    if(c >= ' ' && c <= 'z'){
        return (unsigned int)(c - 32);
    }else{
        return ('?' - 32);
    }
}

Font::String* Font::string(std::string str, float size){
    Font::String* s = new Font::String();
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

Font* Font::Default;

void Font::__init(){
    Default = new Font(ResourceTexture->load("assets/common/textures/font_default.png"), 16, 8);
}

void Font::String::draw(RenderInfo* renderInfo){
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