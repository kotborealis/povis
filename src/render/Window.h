//
// Created by kotborealis on 10.08.2016.
//

#pragma once

#include <SDL.h>
#include <string>

namespace PovisEngine{

class Window{
public:
    Window(std::string title, unsigned int height, unsigned int width);
    ~Window();

    unsigned int getWidth() const;
    unsigned int getHeight() const;

private:
    GLenum init_sdl();
    GLenum init_sdl_img();
    GLenum init_gl();

    unsigned int width, height;
    std::string title;

    SDL_Window* sdl_window;
    SDL_GLContext gl_context;
};

}


