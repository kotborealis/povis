//
// Created by kotborealis on 10.08.2016.
//

#include "TextureManager.h"

namespace PovisEngine{

TextureManager::TextureManager(){}

TextureManager::~TextureManager(){}

Texture::Ptr TextureManager::load(std::string filename){
    Logger::info("Loading texture: " << filename);

    //Search for loaded texture
    Texture::WeakPtr cached_texture = search(filename);
    if(!cached_texture.expired()){
        Logger::info("Already loaded");
        return cached_texture.lock();
    }

    //Load image to sdl surface
    auto surface = IMG_Load(filename.c_str());

    if(!surface){
        Logger::warn(IMG_GetError());
        return nullptr;
    }

    GLuint textureId;
    GLenum mode = surface->format->BytesPerPixel == 4 ? GL_RGBA : GL_RGB;

    //Generate OpenGL texture from surface pixel data
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, mode, surface->w, surface->h, 0, mode, GL_UNSIGNED_BYTE, surface->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    SDL_FreeSurface(surface);

    Texture::Ptr texture(new Texture(textureId));
    Texture::WeakPtr textureWeakPtr(texture);

    //Save texture to texture list
    list.insert(std::make_pair(filename, textureWeakPtr));

    return texture;
}

Texture::WeakPtr TextureManager::search(std::string filename){
    auto it = list.find(filename);
    if(it != list.end())
        return it->second;
    return Texture::WeakPtr();
}

Texture::Ptr TextureManager::create(unsigned int width, unsigned int height){
    GLuint textureId;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 width, height,
                 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    Texture::Ptr texture(new Texture(textureId));
    Texture::WeakPtr textureWeakPtr(texture);

    //Save texture to texture list
    list.insert(std::make_pair(TO_STRING("created_texture_" << textureId), textureWeakPtr));

    return texture;
}

}
