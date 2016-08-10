//
// Created by kotborealis on 10.08.2016.
//

#include "TextureManager.h"

namespace PovisEngine{

TextureManager::TextureManager(){}

TextureManager::~TextureManager(){
    //Delete all possible textures
    for(GLuint i = 0; i < textureIdCounter; i++)
        glDeleteTextures(1, &i);
}

Texture TextureManager::load(std::string filename){
    Logger::info("Loading texture: "<<filename);

    //Search for loaded texture
    Texture cached_texture = searchTexture(filename);
    if(cached_texture)
        return cached_texture;

    //Load image to sdl surface
    auto surface = IMG_Load(filename.c_str());

    if(!surface){
        Logger::warn(IMG_GetError());
        return nullptr;
    }

    GLuint textureId = textureIdCounter++;
    GLenum mode = surface->format->BytesPerPixel==4 ? GL_RGBA : GL_RGB;

    //Generate OpenGL texture from surface pixel data
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, mode, surface->w, surface->h, 0, mode, GL_UNSIGNED_BYTE, surface->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    SDL_FreeSurface(surface);

    Texture texture(new TextureObject(textureId));

    //Save texture to texture list
    textures.insert(std::make_pair(texture, filename));

    return texture;
}

Texture TextureManager::searchTexture(std::string filename){
    for(auto it = textures.begin(); it != textures.end(); it++)
        if(it->second == filename)
            return it->first;
    return nullptr;
}

Texture TextureManager::reserve(){
    return PovisEngine::Texture(new TextureObject(textureIdCounter++));
}

}
