#include <render/Sprite.h>
#include "WindowManager.h"
#include "render/Font.h"

namespace pse{


WindowManager::WindowManager(std::string& title, unsigned int width, unsigned int height):m_width(width),
                                                                                          m_height(height),
                                                                                          title(title){
    init_sdl();
    init_sdl_img();
    init_gl();
    Sprite::__init();
    Font::__init();
}

WindowManager::~WindowManager(){
    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(sdl_window);
    IMG_Quit();
    SDL_Quit();
}

void WindowManager::init_sdl(){
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
        throw new Init_SDL_Exception();

    sdl_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_width, m_height,
                                  SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
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

    const GLubyte* vendor = glGetString(GL_VENDOR);
    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* version = glGetString(GL_VERSION);
    Logger::info("OpenGL " << vendor << " " << renderer << " " << version);
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

void WindowManager::handleEvent(SDL_Event* event){
    if(event->type == SDL_WINDOWEVENT && event->window.event == SDL_WINDOWEVENT_RESIZED){
        windowResizeHandler({0, 0, event->window.data1, event->window.data2});
    }else if(event->type == SDL_KEYDOWN){
        if(event->key.keysym.sym == SDLK_f){
            toggleFullscreen();
        }
    }
}

void WindowManager::toggleFullscreen(){
    if(!fullscreen){
        SDL_GetWindowSize(sdl_window, &windowBounds.w, &windowBounds.h);
        SDL_GetWindowPosition(sdl_window, &windowBounds.x, &windowBounds.y);

        int idx = SDL_GetWindowDisplayIndex(sdl_window);
        SDL_Rect bounds;
        SDL_GetDisplayBounds(idx, &bounds);
        SDL_SetWindowBordered(sdl_window, SDL_FALSE);
        SDL_SetWindowPosition(sdl_window, bounds.x, bounds.y);
        SDL_SetWindowSize(sdl_window, bounds.w, bounds.h);

        windowResizeHandler(bounds);
        SDL_RaiseWindow(sdl_window);
        fullscreen = true;
    }else{
        SDL_SetWindowSize(sdl_window, windowBounds.w, windowBounds.h);
        SDL_SetWindowPosition(sdl_window, windowBounds.x, windowBounds.y);
        SDL_SetWindowBordered(sdl_window, SDL_TRUE);

        windowResizeHandler(windowBounds);
        SDL_RaiseWindow(sdl_window);
        fullscreen = false;
    }
}

void WindowManager::windowResizeHandler(SDL_Rect bounds){
    m_width = (unsigned int)bounds.w;
    m_height = (unsigned int)bounds.h;

    for(auto it = Framebuffer::list.begin(); it != Framebuffer::list.end(); it++){
        if((*it)->wh_auto){
            (*it)->reallocate(m_width, m_height);
        }
    }
}

}