//
// Created by kotborealis on 10.08.2016.
//

#include <SDL_image.h>
#include <GL/glew.h>
#include <Logger.h>
#include "WindowManager.h"

namespace PovisEngine{


WindowManager::WindowManager(std::string& title, unsigned int height, unsigned int width):width(width), height(height),
                                                                                          title(title){
    if(init_sdl() != 0)
        Logger::error("Failed to init SDL: "<<SDL_GetError());

    if(init_sdl_img() != 0)
        Logger::error("Failed to init SDL_image: "<<SDL_GetError());

    GLenum glewError = init_gl();
    if(glewError != GLEW_OK)
        Logger::error("Failed to init GL: "<<glewGetErrorString(glewError));
}

WindowManager::~WindowManager(){
    SDL_DestroyWindow(sdl_window);
    IMG_Quit();
    SDL_Quit();
}

GLenum WindowManager::init_sdl(){
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
        return 1;

    sdl_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    if(sdl_window==nullptr)
        return 1;

    return 0;
}

GLenum WindowManager::init_sdl_img(){
    return (IMG_Init(IMG_INIT_PNG)&IMG_INIT_PNG) ? 0 : 1;
}

GLenum WindowManager::init_gl(){
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    gl_context = SDL_GL_CreateContext(sdl_window);

    glewExperimental = GL_TRUE;
    GLenum glewError = glewInit();

    SDL_GL_SetSwapInterval(1);

    return glewError;
}

unsigned int WindowManager::getWidth() const{
    return width;
}

unsigned int WindowManager::getHeight() const{
    return height;
}

void WindowManager::swap() const{
    SDL_GL_SwapWindow(sdl_window);
}

}