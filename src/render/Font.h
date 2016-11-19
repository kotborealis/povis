//
// Created by kotborealis on 19.11.16.
//

#pragma once

#include <render/resources/Texture.h>
#include <vector>
#include "Sprite.h"

namespace pse{

enum GlyphInstanceSpecial{NONE, LINE_BREAK};

class Font{
public:
    struct Glyph{
        Sprite* sprite;
    };

    struct GlyphInstance{
        unsigned glyph_id;
        GlyphInstanceSpecial special = NONE;
    };

    class String{
        friend class Font;
    public:
        void draw(RenderInfo* renderInfo);
        float size;
    private:
        std::vector<GlyphInstance> glyphs;
        std::map<unsigned, Glyph*>* glyph_map;
    };

    virtual Font::String* string(std::string, float size = 50);

    static void __init();
    static Font* Default;

private:
    Font(const Texture::Ptr& m_texture, unsigned int sprite_w, unsigned int sprite_h);
    virtual ~Font();

    virtual unsigned int charToGlyphID(char c);

    Texture::Ptr m_texture;
    unsigned sprite_w;
    unsigned sprite_h;

    std::map<unsigned, Glyph*> glyph_map;
};

}

