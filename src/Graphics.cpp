/*
 * Graphics.cpp
 *
 *  Created on: 24 èþë. 2016 ã.
 *      Author: kotborealis
 */

#include "Graphics.h"

namespace PovisEngine {

Graphics::Graphics(std::string title, unsigned int width, unsigned int height)
	:m_width(width)
	,m_height(height){

	Logger::info("Initializing graphics");

	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );

	if(SDL_Init(SDL_INIT_VIDEO)<0)
		Logger::error(SDL_GetError());

	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

	if(window == nullptr)
		Logger::error(SDL_GetError());

	if(!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
		Logger::error(SDL_GetError());

	gl = SDL_GL_CreateContext(window);

	glewExperimental = GL_TRUE;
	GLenum glewError = glewInit();
	if(glewError != GLEW_OK)
		Logger::error(glewGetErrorString(glewError));

	if(SDL_GL_SetSwapInterval(1)<0)
		Logger::warn("No v-sync for you fag "<<SDL_GetError());

	glEnable(GL_TEXTURE_2D);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

Graphics::~Graphics() {
	Logger::info("Destroying graphics");
	for(auto it = tMap.begin(); it!=tMap.end(); it++){
		glDeleteTextures(1,&(it->second->tId));
	}
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
}

GLuint Graphics::loadTexture(std::string filename){
	Logger::info("Loading texture "<<filename);

	GLuint _id = lookUpTextureByFilename(filename);
	if(_id != 0){
		Logger::info("Already loaded");
		return _id;
	}

	Texture* t = new Texture();
	auto surface = IMG_Load(filename.c_str());

	if(surface==nullptr){
		Logger::warn(IMG_GetError());
		return 0;
	}

	GLuint tId = tIdCounter++;

	t->filename = filename;
	t->tId = tId;

	int mode = GL_RGB;
	if(surface->format->BytesPerPixel == 4) mode = GL_RGBA;

	glGenTextures(1,&tId);
	glBindTexture(GL_TEXTURE_2D,tId);
	glTexImage2D(GL_TEXTURE_2D, 0, mode, surface->w, surface->h, 0, mode, GL_UNSIGNED_BYTE, surface->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	SDL_FreeSurface(surface);

	tMap.insert(std::pair<GLuint,Texture*>(tId,t));
	fMap.insert(std::pair<std::string,GLuint>(filename,tId));

	return tId;
}

GLuint Graphics::lookUpTextureByFilename(std::string filename){
	for(auto it = tMap.begin(); it!=tMap.end(); it++)
			if(it->second->filename == filename)
				return it->second->tId;
	return 0;
}

GLuint Graphics::reserveTexture(){
	return tIdCounter++;
}

void Graphics::removeTexture(GLuint tId){
	auto t = tMap.find(tId);
	if(t!=tMap.end()){
		Logger::info("Destroying texture "<<t->second->filename);
		tMap.erase(tId);
	}

	glDeleteTextures(1,&tId);
}

void Graphics::clear() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Graphics::render() {
    glFlush();
	SDL_GL_SwapWindow(window);
}

} /* namespace PovisEngine */
