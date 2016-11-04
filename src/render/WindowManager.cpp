#include "WindowManager.h"

namespace PovisEngine{


WindowManager::WindowManager(std::string& title, unsigned int width, unsigned int height):m_width(width),
                                                                                          m_height(height),
                                                                                          title(title){
    init_sdl();
    init_sdl_img();
    init_gl();
}

WindowManager::~WindowManager(){
    SDL_DestroyWindow(sdl_window);
    IMG_Quit();
    SDL_Quit();
}

void WindowManager::init_sdl(){
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
        throw new Init_SDL_Exception();

    sdl_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_width, m_height,
                                  SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    if(sdl_window == nullptr)
        throw new Init_SDL_Exception();
}

void WindowManager::init_sdl_img(){
    if(!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
        throw new Init_SDL_Image_Exception();
}

void WindowManager::init_gl(){
    if(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3) != 0){
        Logger::error("Error setting GL_CONTEXT_MINOR_VERSION");
        throw new Init_GL_Exception();
    }
    if(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1) != 0){
        Logger::error("Error setting GL_CONTEXT_MINOR_VERSION");
        throw new Init_GL_Exception();
    }
    if(SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE) != 0){
        Logger::error("Error setting GL_CONTEXT_PROFILE_MASK");
        throw new Init_GL_Exception();
    }

    gl_context = SDL_GL_CreateContext(sdl_window);

    glewExperimental = GL_TRUE;
    GLenum glewError = glewInit();

    if(glewError)
        throw new Init_GL_Exception();

    SDL_GL_SetSwapInterval(1);
}

unsigned int WindowManager::width() const{
    return m_width;
}

unsigned int WindowManager::height() const{
    return m_height;
}

void WindowManager::swap() const{
    SDL_GL_SwapWindow(sdl_window);
}

}