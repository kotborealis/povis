//
// Created by kotborealis on 19.11.16.
//

#pragma once

#include <render/resources/Texture.h>
#include <vector>
#include "Sprite.h"

namespace PovisEngine {

enum GlyphInstanceSpecial{NONE, LINE_BREAK};

class SpriteFont {
public:
    struct Glyph{
        Sprite* sprite;
    };

    struct GlyphInstance{
        unsigned glyph_id;
        GlyphInstanceSpecial special = NONE;
    };

    class String{
        friend class SpriteFont;

    public:
        void draw(RenderInfo* renderInfo);
        float size;
    private:
        std::vector<GlyphInstance> glyphs;
        std::map<unsigned, Glyph*>* glyph_map;
    };

    SpriteFont(const Texture::Ptr &m_texture, unsigned int sprite_w, unsigned int sprite_h);
    virtual ~SpriteFont();

    virtual SpriteFont::String* string(std::string, float size = 50);
    virtual unsigned int charToGlyphID(char c);

private:
    Texture::Ptr m_texture;
    unsigned sprite_w;
    unsigned sprite_h;

    std::map<unsigned, Glyph*> glyph_map;
};

}

