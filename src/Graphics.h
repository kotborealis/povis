/*
 * Graphics.h
 *
 *  Created on: 24 èþë. 2016 ã.
 *      Author: kotborealis
 */

#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include <string>
#include <map>

#include <SDL2/SDL.h>
#include <gl/glew.h>
#include <SDL2/SDL_opengl.h>
#include <gl/glu.h>
#include <SDL2/SDL_image.h>

#include "Logger.h"

namespace PovisEngine {

struct Texture {
	std::string filename;
	GLuint tId;
};

class Graphics {
public:
	Graphics(std::string title, unsigned int width, unsigned int height);
	virtual ~Graphics();

	GLuint loadTexture(std::string filename);
	GLuint reserveTexture();

	void removeTexture(GLuint tId);

	void clear();
	void render();

	unsigned int width(){
		return m_width;
	}
	unsigned int height(){
		return m_height;
	}

private:
	unsigned int m_width, m_height;
	SDL_Window* window;
	SDL_GLContext gl;

	GLuint tIdCounter = 1;
	std::map<GLuint,Texture*> tMap;
	std::map<std::string,GLuint> fMap;

	GLuint lookUpTextureByFilename(std::string filename);
};

} /* namespace PovisEngine */

#endif /* GRAPHICS_H_ */
