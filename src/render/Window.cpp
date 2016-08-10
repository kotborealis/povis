//
// Created by kotborealis on 10.08.2016.
//

#include <SDL_image.h>
#include <GL/glew.h>
#include <Logger.h>
#include "Window.h"

namespace PovisEngine{


Window::Window(std::string title, unsigned int height, unsigned int width):width(width), height(height), title(title){
    if(init_sdl() != 0)
        Logger::error("Failed to init SDL: "<<SDL_GetError());

    if(init_sdl_img() != 0)
        Logger::error("Failed to init SDL_image: "<<SDL_GetError());

    GLenum glewError = init_gl();
    if(glewError != GLEW_OK)
        Logger::error("Failed to init GL: "<<glewGetErrorString(glewError));
}

Window::~Window(){

}

GLenum Window::init_sdl(){
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
        return 1;

    sdl_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    if(sdl_window==nullptr)
        return 1;

    return 0;
}

GLenum Window::init_sdl_img(){
    return (IMG_Init(IMG_INIT_PNG)&IMG_INIT_PNG) ? 0 : 1;
}

GLenum Window::init_gl(){
    gl_context = SDL_GL_CreateContext(sdl_window);

    glewExperimental = GL_TRUE;
    GLenum glewError = glewInit();

    SDL_GL_SetSwapInterval(1);

    return glewError;
}

unsigned int Window::getWidth() const{
    return width;
}

unsigned int Window::getHeight() const{
    return height;
}

}