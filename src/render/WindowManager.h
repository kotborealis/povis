//
// Created by kotborealis on 10.08.2016.
//

#pragma once

#include <string>
#include <exception>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/glew.h>
#include <GL/gl.h>

#include <Logger.h>
#include <Timer.h>

namespace pse{

class WindowManager{
public:
    WindowManager(std::string& title, unsigned int height, unsigned int width);
    ~WindowManager();

    void swap() const;

    unsigned int width() const;
    unsigned int height() const;

    void handleEvent(SDL_Event* pEvent);

    class Init_SDL_Exception:public std::exception{
        virtual const char* what() const throw(){
            return "init_sdl_init Exception";
        }
    };

    class Init_SDL_Image_Exception:public std::exception{
        virtual const char* what() const throw(){
            return "init_sdl_img Exception";
        }
    };

    class Init_GL_Exception:public std::exception{
        virtual const char* what() const throw(){
            return "init_gl Exception";
        }
    };
private:
    void init_sdl();
    void init_sdl_img();
    void init_gl();

    unsigned int m_width, m_height;
    std::string title;

    SDL_Window* sdl_window;
    SDL_GLContext gl_context;

    bool fullscreen = false;
    SDL_Rect windowBounds;

    void windowResizeHandler(SDL_Rect bounds);
    void toggleFullscreen();

    pse::Timer::Ptr fullscreen_toggle_timer;
};

}


