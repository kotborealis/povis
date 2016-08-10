//
// Created by kotborealis on 10.08.2016.
//

#pragma once

#include <SDL2/SDL.h>
#include <string>

namespace PovisEngine{

class WindowManager{
public:
    WindowManager(std::string& title, unsigned int height, unsigned int width);
    ~WindowManager();

    void swap() const;

    unsigned int width() const;
    unsigned int height() const;

private:
    GLenum init_sdl();
    GLenum init_sdl_img();
    GLenum init_gl();

    unsigned int m_width, m_height;
    std::string title;

    SDL_Window* sdl_window;
    SDL_GLContext gl_context;
};

}


